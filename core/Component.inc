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
     * Abstract class to implement a (Controller) Component.
     * 
     * @author  coderkun <olli@coderkun.de>
     */
    abstract class Component
    {




        /**
         * Load the class of a Component.
         * 
         * @throws  \nre\exceptions\ComponentNotFoundException
         * @throws  \nre\exceptions\ComponentNotValidException
         * @param   string  $componentName  Name of the Component to load
         */
        public static function load($componentName)
        {
            // Determine full classname
            $className = self::getClassName($componentName);

            try {
                // Load class
                ClassLoader::load($className);

                // Validate class
                ClassLoader::check($className, get_class());
            }
            catch(\nre\exceptions\ClassNotValidException $e) {
                throw new \nre\exceptions\ComponentNotValidException($e->getClassName());
            }
            catch(\nre\exceptions\ClassNotFoundException $e) {
                throw new \nre\exceptions\ComponentNotFoundException($e->getClassName());
            }
        }


        /**
         * Instantiate a Component (Factory Pattern).
         * 
         * @param   string  $componentName  Name of the Component to instantiate
         */
        public static function factory($componentName)
        {
            // Determine full classname
            $className = self::getClassName($componentName);

            // Construct and return Controller
            return new $className();
        }


        /**
         * Determine the classname for the given Component name.
         * 
         * @param   string  $componentName  Component name to get classname of
         * @return  string                  Classname for the Component name
         */
        private static function getClassName($componentName)
        {
            $className = \nre\core\ClassLoader::concatClassNames($componentName, \nre\core\ClassLoader::stripNamespace(get_class()));


            return \nre\configs\AppConfig::$app['namespace']."controllers\\components\\$className";
        }

    }

?>