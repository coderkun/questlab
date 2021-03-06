<?php

    /**
     * Questlab
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 – 2016 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://github.com/coderkun/questlab
     */

    namespace hhu\z\controllers;


    /**
     * Controller of the MailAgent to generate a mail message.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class MailController extends \nre\core\Controller
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


            // Set linker
            $this->set('linker', ($request instanceof \hhu\z\requests\MailRequest && !is_null($request->getLinker())) ? $request->getLinker() : null);
        }


        /**
         * Action: userregistration.
         *
         * Generate a mail message to notify of a new user registration.
         *
         * @param   array   $receiver   User that the message will be send to
         * @param   array   $newUser    Newly registered user
         */
        public function userregistration($receiver, $newUser)
        {
            // Set subject
            $this->response->setSubject(_('New user registration'));


            // Pass data to view
            $this->set('user', $newUser);
        }


        /**
         * Action: characterregistration.
         *
         * Generate a mail message to notify of a new Character
         * registration.
         *
         * @param   array   $receiver   User that the message will be send to
         * @param   array   $seminary   Seminary which the Character was created for
         * @param   arary   $user       User of the newly registered Character
         * @param   array   $newCharacter   Newly registered Character
         */
        public function characterregistration($receiver, $seminary, $user, $newCharacter)
        {
            // Set subject
            $this->response->setSubject(_('New Character registration'));


            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('user', $user);
            $this->set('character', $newCharacter);
        }


        /**
         * Action: charactersubmission.
         *
         * Generate a mail message to notify of a new Character
         * submission for a Quest that needs to be valuated.
         *
         * @param   array   $receiver   User that the message will be send to
         * @param   array   $seminary   Seminary which the Quest belongs to
         * @param   array   $questgroup Questgroup of Quest
         * @param   array   $quest      Quest the answer has been submitted for
         * @param   array   $character  Character that send the submission
         */
        public function charactersubmission($receiver, $seminary, $questgroup, $quest, $character)
        {
            // Set subject
            $this->response->setSubject(_('New Character submission'));


            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('questgroup', $questgroup);
            $this->set('quest', $quest);
            $this->set('character', $character);
        }


        /**
         * Action: charactersubmissionapproved.
         *
         * Generate a mail message to notify a Character that its
         * submission has been approved.
         *
         * @param   array   $receiver   User that the message will be send to
         * @param   array   $seminary   Seminary which the Quest belongs to
         * @param   array   $questgroup Questgroup of Quest
         * @param   array   $quest      Quest the answer has been submitted for
         */
        public function charactersubmissionapproved($receiver, $seminary, $questgroup, $quest)
        {
            // Set subject
            $this->response->setSubject(_('Character submission approved'));


            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('questgroup', $questgroup);
            $this->set('quest', $quest);
        }

    }

?>
