<?php

    /**
     * Questlab
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 – 2016 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://github.com/coderkun/questlab
     */

    namespace hhu\z\exceptions;


    /**
     * Exception: QuesttypeController not valid.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class QuesttypeControllerNotValidException extends \nre\core\Exception
    {
        /**
         * Error code
         *
         * @var int
         */
        const CODE = 104;
        /**
         * Error message
         *
         * @var string
         */
        const MESSAGE = 'QuesttypeController not valid';

        /**
         * Name of the invalid class
         *
         * @var string
         */
        private $questtypeName;




        /**
         * Construct a new exception.
         *
         * @param   string  $questtypeName  Name of the invalid QuesttypeController
         * @param   string  $message    Error message
         * @param   int $code       Error code
         */
        function __construct($questtypeName, $message=self::MESSAGE, $code=self::CODE)
        {
            parent::__construct(
                $message,
                $code,
                $questtypeName
            );

            // Store value
            $this->questtypeName = $questtypeName;
        }




        /**
         * Get the name of the invalid QuesttypeController.
         *
         * @return  string  Name of the invalid QuesttypeController
         */
        public function getClassName()
        {
            return $this->questtypeName;
        }

    }

?>
