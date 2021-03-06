<?php

    /**
     * NRE
     *
     * @author      coderkun <olli@coderkun.de>
     * @copyright   2013 coderkun (http://www.coderkun.de)
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        http://www.coderkun.de/projects/nre
     */

    namespace nre\exceptions;


    /**
     * Exception: Driver not valid.
     * 
     * @author  coderkun <olli@coderkun.de>
     */
    class DriverNotValidException extends \nre\exceptions\ClassNotValidException
    {
        /**
         * Error code
         * 
         * @var int
         */
        const CODE = 81;
        /**
         * Error message
         * 
         * @var string
         */
        const MESSAGE = 'driver not valid';




        /**
         * Konstruktor.
         * 
         * @param   string  $driverName Name of the invalid driver
         */
        function __construct($driverName)
        {
            // Elternkonstruktor aufrufen
            parent::__construct(
                $driverName,
                self::MESSAGE,
                self::CODE
            );
        }




        /**
         * Get the name of the invalid driver.
         * 
         * @return  string  Name of the invalid driver
         */
        public function getDriverName()
        {
            return $this->getClassName();
        }

    }

?>
