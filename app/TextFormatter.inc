<?php

    /**
     * Questlab
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 – 2016 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://github.com/coderkun/questlab
     */

    namespace hhu\z;


    /**
     * Class to format text with different syntax tags.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class TextFormatter
    {
        /**
         * Linker to create links.
         *
         * @var \nre\core\Linker
         */
        private $linker;
        /**
         * Media-Model to retrieve media data
         *
         * @static
         * @var \nre\core\Model
         */
        private static $Media = null;




        /**
         * Create a new text formatter.
         *
         * @param   \nre\core\Linker $linker    Linker to create links with
         */
        public function __construct(\nre\core\Linker $linker)
        {
            $this->linker = $linker;
        }




        /**
         * Format a string.
         *
         * @param   string  $string String to format
         * @return  string          Formatted string
         */
        public function t($string)
        {
            // Use Textile
            \hhu\z\lib\Textile::load();
            $textileParser = new \Netcarver\Textile\Parser('html5');
            $string = $textileParser->textileThis($string);

            // Add link targets
            $string = $this->tLinks($string);

            // Handle Seminarymedia
            $string = $this->tSeminarymedia($string);


            // Return processed string
            return $string;
        }




        /**
         * Load the Media-Model if it is not loaded
         *
         * @return  boolean Whether the Media-Model has been loaded or not
         */
        private function loadMediaModel()
        {
            // Do not load Model if it has already been loaded
            if(!is_null(self::$Media)) {
                return true;
            }

            try {
                // Load class
                Model::load('media');

                // Construct Model
                self::$Media = Model::factory('media');
            }
            catch(\Exception $e) {
            }


            // Return whether Media-Model has been loaded or not
            return !is_null(self::$Media);
        }


        /**
         * Add “target” attribute to anchors (links).
         * 
         * @param   string  $string String to format
         * @return  string          Formatted string
         */
        private function tLinks($string)
        {
            if(!class_exists('\DOMDocument')) {
                return $string;
            }
            try {
                $dom = new \DOMDocument('1.0');
                $dom->loadHTML('<!DOCTYPE html><html><head><meta charset="utf-8" /></head><body>'.$string.'</body></html>');
                foreach($dom->getElementsByTagName('a') as $link) {
                    $link->setAttribute('target', '_blank');
                }
                $body = $dom->getElementsByTagName('body')->item(0);
                $string = $dom->saveHTML($body);

                return trim(substr($string, 6, strlen($string) - 13));
            }
            catch(\Exception $e) {
                return $string;
            }
        }


        /**
         * Handle including Seminarymedia.
         * 
         * @param   string  $string String to format
         * @return  string          Formatted string
         */
        private function tSeminarymedia($string)
        {
            $seminarymedia = array();
            preg_match_all('/\[seminarymedia:(\d+)\]/iu', $string, $matches); //, PREG_SET_ORDER | PREG_OFFSET_CAPTURE);
            $seminarymediaIds = array_unique($matches[1]);
            foreach($seminarymediaIds as &$seminarymediaId)
            {
                $replacement = null;
                if(!is_null(\hhu\z\controllers\SeminaryController::$seminary) && $this->loadMediaModel())
                {
                    try {
                        $medium = self::$Media->getSeminaryMediaById($seminarymediaId);
                        $replacement = sprintf(
                            '<img src="%s" alt="%s" />',
                            $this->linker->link(array('media','seminary', \hhu\z\controllers\SeminaryController::$seminary['url'],$medium['url'])),
                            $medium['description']
                        );
                    }
                    catch(\nre\exceptions\IdNotFoundException $e) {
                    }
                }

                $seminarymedia[$seminarymediaId] = $replacement;
            }
            foreach($seminarymedia as $seminarymediaId => $replacement) {
                $string = str_replace("[seminarymedia:$seminarymediaId]", $replacement, $string);
            }


            // Return new string
            return $string;
        }


    }

?>
