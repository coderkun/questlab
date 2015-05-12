<?php

    /**
     * The Legend of Z
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://bitbucket.org/coderkun/the-legend-of-z
     */

    namespace hhu\z\controllers;


    /**
     * Controller of the Agent to display a menu with Seminary related
     * links.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class SeminarymenuController extends \hhu\z\Controller
    {




        /**
         * Prefilter.
         *
         * @param   \nre\core\Request   $request    Current request
         * @param   \nre\core\Response  $response   Current response
         */
        public function preFilter(\nre\core\Request $request, \nre\core\Response $response)
        {
            parent::preFilter($request, $response);

            // Set userdata
            $this->set('loggedUser', \hhu\z\controllers\IntermediateController::$user);
            $this->set('loggedSeminary', \hhu\z\controllers\SeminaryController::$seminary);
            $this->set('loggedCharacter', \hhu\z\controllers\SeminaryController::$character);
        }


        /**
         * Action: index.
         */
        public function index()
        {
        }

    }

?>