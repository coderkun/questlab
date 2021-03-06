<?php

    /**
     * Questlab
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 – 2016 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://github.com/coderkun/questlab
     */

    namespace hhu\z\controllers;


    /**
     * Controller of the UploadsAgent to process and show user uploads.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class UploadsController extends \hhu\z\controllers\SeminaryController
    {
        /**
         * Required models
         *
         * @var array
         */
        public $models = array('uploads', 'users', 'userroles', 'characterroles', 'seminaries', 'charactergroups');
        /**
         * User permissions
         *
         * @var array
         */
        public $permissions = array(
            'seminary'      => array('admin', 'moderator', 'user', 'guest'),
            'charactergroup'    => array('admin', 'moderator', 'user', 'guest')
        );
        /**
         * User seminary permissions
         *
         * @var array
         */
        public $seminaryPermissions = array(
            'seminary'      => array('admin', 'moderator', 'user', 'guest'),
            'charactergroup'    => array('admin', 'moderator', 'user')
        );




        /**
         * Prefilter.
         *
         * @param   \nre\core\Request   $request    Current request
         * @param   \nre\core\Response  $response   Current response
         */
        public function preFilter(\nre\core\Request $request, \nre\core\Response $response)
        {
            parent::preFilter($request, $response);

            // Set headers for caching control
            $response->addHeader("Pragma: public");
            $response->addHeader("Cache-control: public, max-age=".(60*60*24));
            $response->addHeader("Expires: ".gmdate('r', time()+(60*60*24)));
            $response->addHeader("Date: ".gmdate(\DateTime::RFC822));
        }


        /**
         * Action: seminary.
         *
         * Display a Seminary upload.
         *
         * @throws  \nre\exceptions\AccessDeniedException
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-title of Seminary
         * @param   string  $uploadUrl  URL-name of the upload
         * @param   string  $action     Current action (optional)
         */
        public function seminary($seminaryUrl, $uploadUrl, $action=null)
        {
            // Get Seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Upload
            $upload = $this->Uploads->getSeminaryuploadByUrl($seminary['id'], $uploadUrl);

            // Check permissions
            if(!$upload['public'])
            {
                $user = $this->Users->getUserById($this->Auth->getUserId());
                $user['roles'] = array_map(function($r) { return $r['name']; }, $this->Userroles->getUserrolesForUserById($user['id']));

                // System roles
                if(count(array_intersect(array('admin', 'moderator'), $user['roles'])) == 0)
                {
                    // Owner of file
                    if($upload['created_user_id'] != $user['id'])
                    {
                        // Seminary permissions
                        $characterRoles = array_map(function($r) { return $r['name']; }, $this->Characterroles->getCharacterrolesForCharacterById($character['id']));
                        if(count(array_intersect(array('admin', 'moderator'), $characterRoles)) == 0) {
                            throw new \nre\exceptions\AccessDeniedException();
                        }
                    }
                }
            }

            // Get file
            switch($action)
            {
                case null:
                    $file = $this->getUploadFile($upload);
                break;
                case 'thumbnail':
                    $file = $this->createThumbnail($upload);
                break;
                default:
                    throw new \nre\exceptions\ParamsNotValidException($action);
                break;
            }
            if(is_null($file)) {
                return;
            }


            // Pass data to view
            $this->set('upload', $upload);
            $this->set('file', $file);
        }


        /**
         * Action: charactergroup.
         *
         * Display the icon of a Character group.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl        URL-Title of a Seminary
         * @param   string  $groupsgroupUrl     URL-Title of a Character groups-group
         * @param   string  $groupUrl       URL-Title of a Character group
         */
        public function charactergroup($seminaryUrl, $groupsgroupUrl, $groupUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Character groups-group
            $groupsgroup = $this->Charactergroups->getGroupsgroupByUrl($seminary['id'], $groupsgroupUrl);

            // Get Character group
            $group = $this->Charactergroups->getGroupByUrl($groupsgroup['id'], $groupUrl);

            // Get Upload
            $upload = $this->Uploads->getSeminaryuploadById($group['seminaryupload_id']);

            // Get file
            $file = $this->getUploadFile($upload);
            if(is_null($file)) {
                return;
            }


            // Pass data to view
            $this->set('upload', $upload);
            $this->set('file', $file);
        }




        /**
         * Determine the file for an upload.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   array   $upload Upload to get file for
         * @return  object      File for the upload (or null if upload is cached)
         */
        private function getUploadFile($upload)
        {
            // Set content-type
            $this->response->addHeader("Content-type: ".$upload['mimetype']."");

            // Set filename
            $upload['filename'] = ROOT.DS.\nre\configs\AppConfig::$dirs['seminaryuploads'].DS.$upload['url'];
            if(!file_exists($upload['filename'])) {
                throw new \nre\exceptions\IdNotFoundException($uploadUrl);
            }

            // Cache
            if($this->setCacheHeaders($upload['filename'])) {
                return null;
            }


            return file_get_contents($upload['filename']);
        }


        /**
         * Create a thumbnail from an upload.
         *
         * @param   array   $upload Upload to create thumbnail for
         * @return  object      Thumbnail for the upload (or null if thumbnail is cached)
         */
        private function createThumbnail($upload)
        {
            // Set filename
            $upload['filename'] = ROOT.DS.\nre\configs\AppConfig::$dirs['seminaryuploads'].DS.$upload['url'];

            // Set content-type
            $this->response->addHeader("Content-type: image/jpeg");

            // Check file
            if(!file_exists($upload['filename'])) {
                throw new \nre\exceptions\IdNotFoundException($upload['url']);
            }

            // Cache
            if($this->setCacheHeaders($upload['filename'])) {
                return null;
            }

            // Set geometry
            $width = 100;
            $height = 100;

            switch($upload['mimetype'])
            {
                case 'image/jpeg':
                case 'image/png':
                    // Read image from cache
                    $tempFileName = ROOT.DS.\nre\configs\AppConfig::$dirs['temporary'].DS.$upload['url'].'-'.$width.'x'.$height;
                    if(file_exists($tempFileName))
                    {
                        // Check age of file
                        if(date('r', filemtime($tempFileName)+(60*60*24)) > date('r', time())) {
                            // Too old, delete
                            unlink($tempFileName);
                        }
                        else {
                            // Valid, read and return
                            return file_get_contents($tempFileName);
                        }
                    }

                    // ImageMagick
                    $im = new \Imagick($upload['filename']);

                    // Calculate new size
                    $geometry = $im->getImageGeometry();
                    if($geometry['width'] < $width) {
                        $width = $geometry['width'];
                    }
                    if($geometry['height'] < $height) {
                        $height = $geometry['width'];
                    }

                    // Process
                    $im->thumbnailImage($width, $height, true);
                    $im->contrastImage(1);
                    $im->setImageFormat('jpeg');

                    // Save temporary file
                    $im->writeImage($tempFileName);


                    // Return resized image
                    return $im;
                break;
                default:
                    throw new \nre\exceptions\ParamsNotValidException('thumbnail');
                break;
            }


            return $this->getUploadFile($upload);
        }


        /**
         * Determine file information and set the HTTP-header for
         * caching accordingly.
         *
         * @param   string  $fileName   Filename
         * @return  boolean         HTTP-status 304 was set (in cache)
         */
        private function setCacheHeaders($fileName)
        {
            // Determine last change of file
            $fileLastModified = gmdate('r', filemtime($fileName));

            // Generate E-Tag
            $fileEtag = hash('sha256', $fileLastModified.$fileName);


            // Set header
            $this->response->addHeader("Last-Modified: ".$fileLastModified);
            $this->response->addHeader("Etag: ".$fileEtag);
            // HTTP-status
            $headerModifiedSince = $this->request->getServerParam('HTTP_IF_MODIFIED_SINCE');
            $headerNoneMatch = $this->request->getServerParam('HTTP_IF_NONE_MATCH');
            if(
                !is_null($headerModifiedSince) && $fileLastModified < strtotime($headerModifiedSince) &&
                !is_null($headerNoneMatch) && $headerNoneMatch == $fileEtag
            ) {
                $this->response->setExit(true);
                $this->response->addHeader(\nre\core\WebUtils::getHttpHeader(304));

                return true;
            }


            return false;
        }

    }

?>
