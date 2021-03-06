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
     * Exception: Component not found.
     * 
     * @author  coderkun <olli@coderkun.de>
     */
    class ComponentNotFoundException extends \nre\exceptions\ClassNotFoundException
    {
        /**
         * Error code
         * 
         * @var int
         */
        const CODE = 67;
        /**
         * Error message
         * 
         * @var string
         */
        const MESSAGE = 'component not found';




        /**
         * Construct a new exception.
         * 
         * @param   string  $componentName  Name of the Component that was not found
         */
        function __construct($componentName)
        {
            parent::__construct(
                $componentName,
                self::MESSAGE,
                self::CODE
            );
        }




        /**
         * Get the name of the Component that was not found.
         * 
         * @return  string  Name of the Component that was not found
         */
        public function getComponentName()
        {
            return $this->getClassName();
        }

    }

?>
