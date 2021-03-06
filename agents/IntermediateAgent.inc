<?php

    /**
     * NRE
     *
     * @author      coderkun <olli@coderkun.de>
     * @copyright   2013 coderkun (http://www.coderkun.de)
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        http://www.coderkun.de/projects/nre
     */

    namespace nre\agents;


    /**
     * The IntermediateAgent assumes the task of a module. There is only one
     * IntermediateAgent per request.
     * 
     * @author  coderkun <olli@coderkun.de>
     */
    abstract class IntermediateAgent extends \nre\core\Agent
    {




        /**
         * Get the layout if it was explicitly defined.
         * 
         * @param   string  $agentName  Agent name
         * @return  string              Layout of the IntermediateAgent
         */
        public static function getLayout($agentName)
        {
            // Determine classname
            $className = Autoloader::concatClassNames($agentName, 'Agent');
            
            // Check property
            if(isset($className::$layout)) {
                return $className::$layout;
            }


            return null;
        }

    }

?>
