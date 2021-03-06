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
     * Base class to represent a response.
     * 
     * @author  coderkun <olli@coderkun.de>
     */
    class Response
    {
        /**
         * Applied parameters
         * 
         * @var array
         */
        protected $params = array();
        /**
         * Generated output
         * 
         * @var string
         */
        private $output = '';
        /**
         * Abort futher execution
         * 
         * @var bool
         */
        private $exit = false;




        /**
         * Add a parameter.
         * 
         * @param   mixed   $value  Value of parameter
         */
        public function addParam($value)
        {
            $this->params[] = $value;
        }


        /**
         * Add multiple parameters.
         * 
         * @param   mixed   $value1 Value of first parameter
         * @param   mixed   …       Values of further parameters
         */
        public function addParams($value1)
        {
            $this->params = array_merge(
                $this->params,
                func_get_args()
            );
        }


        /**
         * Delete all stored parameters (from offset on).
         * 
         * @param   int $offset Offset-index
         */
        public function clearParams($offset=0)
        {
            $this->params = array_slice($this->params, 0, $offset);
        }


        /**
         * Get a parameter.
         * 
         * @param   int     $index          Index of parameter
         * @param   string  $defaultIndex   Index of default configuration value for this parameter
         * @return  string                  Value of parameter
         */
        public function getParam($index, $defaultIndex=null)
        {
            // Return parameter
            if(count($this->params) > $index) {
                return $this->params[$index];
            }


            // Return default value
            return \nre\core\Config::getDefault($defaultIndex);
        }


        /**
         * Get all parameters from index on.
         * 
         * @param   int     $offset Offset-index
         * @return  array           Parameter values
         */
        public function getParams($offset=0)
        {
            return array_slice($this->params, $offset);
        }


        /**
         * Set output.
         * 
         * @param   string  $output Generated output
         */
        public function setOutput($output)
        {
            $this->output = $output;
        }


        /**
         * Get generated output.
         * 
         * @return  string  Generated output
         */
        public function getOutput()
        {
            return $this->output;
        }


        /**
         * Set exit-state.
         * 
         * @param   bool    $exit   Abort further execution
         */
        public function setExit($exit=true)
        {
            $this->exit = $exit;
        }


        /**
         * Get exit-state.
         * 
         * @return    bool    Abort further execution
         */
        public function getExit()
        {
            return $this->exit;
        }

    }

?>
