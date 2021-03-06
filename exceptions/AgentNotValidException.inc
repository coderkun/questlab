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
     * Exception: Agent not valid.
     * 
     * @author  coderkun <olli@coderkun.de>
     */
    class AgentNotValidException extends \nre\exceptions\ClassNotValidException
    {
        /**
         * Error code
         * 
         * @var int
         */
        const CODE = 76;
        /**
         * Error message
         * 
         * @var string
         */
        const MESSAGE = 'agent not valid';




        /**
         * Construct a new exception.
         * 
         * @param   string  $agentName  Name of the invalid Agent
         */
        function __construct($agentName)
        {
            parent::__construct(
                $agentName,
                self::MESSAGE,
                self::CODE
            );
        }




        /**
         * Get the name of the invalid Agent.
         * 
         * @return  string  Name of the invalid Agent
         */
        public function getAgentName()
        {
            return $this->getClassName();
        }

    }

?>
