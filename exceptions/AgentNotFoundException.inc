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
     * Exception: Agent not found.
     * 
     * @author  coderkun <olli@coderkun.de>
     */
    class AgentNotFoundException extends \nre\exceptions\ClassNotFoundException
    {
        /**
         * Error code
         * 
         * @var int
         */
        const CODE = 66;
        /**
         * Error message
         * 
         * @var string
         */
        const MESSAGE = 'agent not found';




        /**
         * Construct a new exception.
         * 
         * @param   string  $agentName  Name of the Agent that was not found
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
         * Get the name of the Agent that was not found.
         * 
         * @return  string  Name of the Agent that was not found
         */
        public function getAgentName()
        {
            return $this->getClassName();
        }

    }

?>
