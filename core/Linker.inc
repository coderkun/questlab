<?php

    /**
     * NRE
     *
     * @author      coderkun <olli@coderkun.de>
     * @copyright   2013 coderkun (http://www.coderkun.de)
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        http://www.coderkun.de/projects/nre
     */

    namespace nre\core;


    /**
     * Class to create web links based on the current request.
     * 
     * @author  coderkun <olli@coderkun.de>
     */
    class Linker
    {
        /**
         * Current request
         * 
         * @var Request
         */
        private $request;




        /**
         * Construct a new linker.
         * 
         * @param   Request $request    Current request
         */
        function __construct(\nre\requests\WebRequest $request)
        {
            $this->request = $request;
        }




        /**
         * Mask parameters to be used in an URL.
         * 
         * @param   string  $param1 First parameter
         * @return  string          Masked parameters as string
         */
        public static function createLinkParam($param1)
        {
            return implode(
                \nre\configs\CoreConfig::$classes['linker']['url']['delimiter'],
                call_user_func_array(
                    '\nre\core\Linker::createLinkParams',
                    func_get_args()
                )
            );
        }


        /**
         * Mask parameters to be used in an URL.
         * 
         * @param   string  $param1 First parameter
         * @return  string          Masked parameters as array
         */
        public static function createLinkParams($param1)
        {
            // Parameters
            $linkParams = array();
            $params = func_get_args();

            foreach($params as $param)
            {
                // Delete critical signs
                $specials = array('/', '?', '&', '#');
                foreach($specials as &$special) {
                    $param = str_replace($special, '', $param);
                }

                // Process parameter
                $param = str_replace(
                    ' ',
                    \nre\configs\CoreConfig::$classes['linker']['url']['delimiter'],
                    substr(
                        $param,
                        0,
                        \nre\configs\CoreConfig::$classes['linker']['url']['length']
                    )
                );

                // Encode parameter
                $linkParams[] = $param;
            }


            // Return link parameters
            return $linkParams;
        }




        /**
         * Create a web link.
         * 
         * @param   array   $params             Parameters to use
         * @param   int     $offset             Ignore first parameters
         * @param   bool    $exclusiveParams    Use only the given parameters
         * @param   array   $getParams          GET-parameter to use
         * @param   bool    $exclusiveGetParams Use only the given GET-parameters
         * @param   string  $anchor             Target anchor
         * @param   bool    $absolute           Include hostname etc. for an absolute URL
         * @return  string                      Created link
         */
        public function link($params=null, $offset=0, $exclusiveParams=true, $getParams=null, $exclusiveGetParams=true, $anchor=null, $absolute=false)
        {
            // Make current request to response
            $response = new \nre\responses\WebResponse();


            // Check parameters
            if(is_null($params)) {
                $params = array();
            }
            elseif(!is_array($params)) {
                $params = array($params);
            }

            // Set parameters from request
            $reqParams = array_slice($this->request->getParams(), 1, $offset);
            if(count($reqParams) < $offset && $offset > 0) {
                $reqParams[] = $this->request->getParam(1, 'intermediate');
            }
            if(count($reqParams) < $offset && $offset > 1) {
                $reqParams[] = $this->request->getParam(2, 'action');
            }
            $params = array_merge($reqParams, $params);

            // Use Layout
            $layout = \nre\configs\AppConfig::$defaults['toplevel'];
            if(!empty($getParams) && array_key_exists('layout', $getParams)) {
                $layout = $getParams['layout'];
            }
            array_unshift($params, $layout);

            // Use parameters from request only
            if(!$exclusiveParams)
            {
                $params = array_merge(
                    $params,
                    array_slice(
                        $this->request->getParams(),
                        count($params)
                    )
                );
            }

            // Encode parameters
            $params = array_map('rawurlencode', $params);

            // Set parameters
            call_user_func_array(
                array(
                    $response,
                    'addParams'
                ),
                $params
            );


            // Check GET-parameters
            if(is_null($getParams)) {
                $getParams = array();
            }
            elseif(!is_array($params)) {
                $params = array($params);
            }
            if(!$exclusiveGetParams)
            {
                $getParams = array_merge(
                    $this->request->getGetParams(),
                    $getParams
                );
            }

            // Set GET-parameters
            $response->addGetParams($getParams);


            // Create and return link
            return self::createLink($this->request, $response, $anchor, $absolute);
        }


        /**
         * Create a link from an URL.
         * 
         * @param   string  $url        URL to create link from
         * @param   bool    $absolute   Create absolute URL
         * @return  string              Created link
         */
        public function hardlink($url, $absolute=false)
        {
            return $this->createUrl($url, $this->request, $absolute);
        }




        /**
         * Create a link.
         * 
         * @param   Request     $request    Current request
         * @param   Response    $response   Current response
         * @param   string      $anchor     Anchor on target
         * @param   bool        $absolute   Create absolute link
         * @return  string                  Created link
         */
        private static function createLink(Request $request, Response $response, $anchor=null, $absolute=false)
        {
            // Check response
            if(is_null($response)) {
                return null;
            }


            // Get parameters
            $params = $response->getParams(1);

            // Check Action
            if(count($params) == 2 && $params[1] ==  \nre\configs\CoreConfig::$defaults['action']) {
                array_pop($params);
            }

            // Set parameters
            $link = implode('/', $params);

            // Apply reverse-routes
            $link = $request->applyReverseRoutes($link);


            // Get GET-parameters
            $getParams = $response->getGetParams();

            // Layout überprüfen
            if(array_key_exists('layout', $getParams) && $getParams['layout'] == \nre\configs\AppConfig::$defaults['toplevel']) {
                unset($getParams['layout']);
            }

            // Set GET-parameters
            if(array_key_exists('url', $getParams)) {
                unset($getParams['url']);
            }
            if(count($getParams) > 0) {
                $link .= '?'.http_build_query($getParams);
            }

            // Add anchor
            if(!is_null($anchor)) {
                $link .= "#$anchor";
            }


            // Create URL
            $url = self::createUrl($link, $request, $absolute);


            return $url;
        }


        /**
         * Adapt a link to the environment.
         * 
         * @param   string  $url        URL
         * @param   Request $request    Current request
         * @param   bool    $absolute   Create absolute URL
         * @return  string              Adapted URL
         */
        private static function createUrl($url, Request $request, $absolute=false)
        {
            // Variables
            $server = $_SERVER['SERVER_NAME'];
            $uri = $_SERVER['REQUEST_URI'];
            $prefix = '';


            // Determine prefix
            $ppos = array(strlen($uri));
            if(($p = strpos($uri, '/'.$request->getParam(1, 'intermediate'))) !== false) {
                $ppos[] = $p;
            }
            $prefix = substr($uri, 0, min($ppos));

            // Create absolute URL
            if($absolute) {
                $prefix = "http://$server/".trim($prefix, '/');
            }

            // Put URL together
            $url = rtrim($prefix, '/').'/'.ltrim($url, '/');


            // Return URL
            return $url;
        }

    }

?>
