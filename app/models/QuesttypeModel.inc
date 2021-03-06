<?php

    /**
     * Questlab
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 – 2016 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://github.com/coderkun/questlab
     */

    namespace hhu\z\models;


    /**
     * Abstract class for implementing a QuesttypeModel.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    abstract class QuesttypeModel extends \hhu\z\Model
    {




        /**
         * Copy a Quest.
         *
         * @param   int $userId             ID of creating user
         * @param   int $sourceQuestId      ID of Quest to copy from
         * @param   int $targetQuestId      ID of Quest to copy to
         * @param   int $seminaryMediaIds   Mapping of SeminaryMedia-IDs from source Seminary to targetSeminary
         */
        public abstract function copyQuest($userId, $sourceQuestId, $targetQuestId, $seminaryMediaIds);


        /**
         * Delete a Quest.
         * 
         * @param   int $questId    ID of Quest to delete
         */
        public abstract function deleteQuest($questId);


        /**
         * Load a Model.
         *
         * @static
         * @throws  \hhu\z\exceptions\QuesttypeModelNotFoundException
         * @throws  \hhu\z\exceptions\QuesttypeModelNotValidException
         * @param   string  $modelName      Name of the QuesttypeModel to load
         */
        public static function load($modelName)
        {
            // Determine full classname
            $className = self::getClassName($modelName);

            try {
                // Load class
                static::loadClass($modelName, $className);

                // Validate class
                static::checkClass($className, get_class());
            }
            catch(\nre\exceptions\ClassNotValidException $e) {
                throw new \hhu\z\exceptions\QuesttypeModelNotValidException($e->getClassName());
            }
            catch(\nre\exceptions\ClassNotFoundException $e) {
                throw new \hhu\z\exceptions\QuesttypeModelNotFoundException($e->getClassName());
            }
        }


        /**
         * Instantiate a QuesttypeModel (Factory Pattern).
         *
         * @static
         * @param   string  $questtypeName  Name of the QuesttypeModel to instantiate
         */
        public static function factory($questtypeName)
        {
            // Determine full classname
            $className = self::getClassName($questtypeName);

            // Construct and return Model
            return new $className();
        }


        /**
         * Determine the Model-classname for the given Questtype-name.
         *
         * @static
         * @param   string  $questtypeName  Questtype-name to get Model-classname of
         * @return  string          Classname for the Questtype-name
         */
        private static function getClassName($questtypeName)
        {
            $className = \nre\core\ClassLoader::concatClassNames($questtypeName, \nre\core\ClassLoader::stripClassType(\nre\core\ClassLoader::stripNamespace(get_class())), 'model');


            return \nre\configs\AppConfig::$app['namespace']."questtypes\\$className";
        }


        /**
         * Load the class of a QuesttypeModel.
         *
         * @static
         * @throws  \nre\exceptions\ClassNotFoundException
         * @param   string  $questtypeName  Name of the QuesttypeModel to load
         * @param   string  $fullClassName  Name of the class to load
         */
        private static function loadClass($questtypeName, $fullClassName)
        {
            // Determine folder to look in
            $className = explode('\\', $fullClassName);
            $className = array_pop($className);

            // Determine filename
            $fileName = ROOT.DS.\nre\configs\AppConfig::$dirs['questtypes'].DS.strtolower($questtypeName).DS.$className.\nre\configs\CoreConfig::getFileExt('includes');

            // Check file
            if(!file_exists($fileName))
            {
                throw new \nre\exceptions\ClassNotFoundException(
                    $fullClassName
                );
            }

            // Include file
            include_once($fileName);
        }


        /**
         * Check inheritance of the QuesttypeModel-class.
         *
         * @static
         * @throws  \nre\exceptions\ClassNotValidException
         * @param   string  $className      Name of the class to check
         * @param   string  $parentClassName    Name of the parent class
         */
        public static function checkClass($className, $parentClassName)
        {
            // Check if class is subclass of parent class
            if(!is_subclass_of($className, $parentClassName)) {
                throw new \nre\exceptions\ClassNotValidException(
                    $className
                );
            }
        }




        /**
         * Construct a new QuesttypeModel.
         *
         * @throws  \nre\exceptions\DatamodelException
         * @throws  \nre\exceptions\DriverNotFoundException
         * @throws  \nre\exceptions\DriverNotValidException
         * @throws  \hhu\z\exceptions\QuesttypeModelNotValidException
         * @throws  \hhu\z\exceptions\QuesttypeModelNotFoundException
         */
        public function __construct()
        {
            parent::__construct();
        }

    }

?>
