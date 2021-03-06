<?php

    /**
     * Questlab
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 – 2016 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://github.com/coderkun/questlab
     */

    namespace hhu\z\questtypes;


    /**
     * Controller of the SubmitQuesttypeAgent for a submit task.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class SubmitQuesttypeController extends \hhu\z\controllers\QuesttypeController
    {
        /**
         * Required models
         *
         * @var array
         */
        public $models = array('quests', 'uploads', 'users', 'characters', 'questgroups');




        /**
         * Save the answers of a Character for a Quest.
         *
         * @throws  \hhu\z\exceptions\SubmissionNotValidException
         * @param   array   $seminary   Current Seminary data
         * @param   array   $questgroup Current Questgroup data
         * @param   array   $quest      Current Quest data
         * @param   array   $character  Current Character data
         * @param   array   $answers    Character answers for the Quest
         */
        public function saveAnswersOfCharacter($seminary, $questgroup, $quest, $character, $answers)
        {
            // Save answer
            if(array_key_exists('answers', $_FILES))
            {
                $answer = $_FILES['answers'];

                // Check error
                if($answer['error'] !== 0) {
                    throw new \hhu\z\exceptions\SubmissionNotValidException(
                        new \hhu\z\exceptions\FileUploadException($answer['error'])
                    );
                }

                // Check mimetype
                $mimetypes = $this->Submit->getAllowedMimetypes($seminary['id']);
                $answerMimetype = null;
                $answer['mimetype'] = \hhu\z\Utils::getMimetype($answer['tmp_name'], $answer['type']);
                foreach($mimetypes as &$mimetype) {
                    if($mimetype['mimetype'] == $answer['mimetype']) {
                        $answerMimetype = $mimetype;
                        break;
                    }
                }
                if(is_null($answerMimetype)) {
                    throw new \hhu\z\exceptions\SubmissionNotValidException(
                        new \hhu\z\exceptions\WrongFiletypeException($answer['mimetype'])
                    );
                }

                // Check file size
                if($answer['size'] > $answerMimetype['size']) {
                    throw new \hhu\z\exceptions\SubmissionNotValidException(
                        new \hhu\z\exceptions\MaxFilesizeException()
                    );
                }

                // Create filename
                $filename = sprintf(
                    '%s,%s,%s.%s',
                    $character['url'],
                    mb_substr($quest['url'], 0, 32),
                    date('Ymd-His'),
                    mb_substr(mb_substr($answer['name'], strrpos($answer['name'], '.')+1), 0, 4)
                );

                // Save file
                if(!$this->Submit->setCharacterSubmission($seminary['id'], $quest['id'], $this->Auth->getUserId(), $character['id'], $answer, $filename)) {
                    throw new \hhu\z\exceptions\SubmissionNotValidException(
                        new \hhu\z\exceptions\FileUploadException(error_get_last()['message'])
                    );
                }
            }
        }


        /**
         * Save additional data for the answers of a Character for a Quest.
         *
         * @param   array   $seminary   Current Seminary data
         * @param   array   $questgroup Current Questgroup data
         * @param   array   $quest      Current Quest data
         * @param   array   $character  Current Character data
         * @param   array   $data       Additional (POST-) data
         */
        public function saveDataForCharacterAnswers($seminary, $questgroup, $quest, $character, $data)
        {
            $this->Submit->addCommentForCharacterAnswer($this->Auth->getUserId(), $data['submission_id'], $data['comment']);
        }


        /**
         * Check if answers of a Character for a Quest match the correct ones.
         *
         * @param   array   $seminary   Current Seminary data
         * @param   array   $questgroup Current Questgroup data
         * @param   array   $quest      Current Quest data
         * @param   array   $character  Current Character data
         * @param   array   $answers    Character answers for the Quest
         * @return  boolean         True/false for a right/wrong answer or null for moderator evaluation
         */
        public function matchAnswersOfCharacter($seminary, $questgroup, $quest, $character, $answers)
        {
            // A moderator has to evaluate the answer
            return null;
        }


        /**
         * Action: quest.
         *
         * Display a big textbox to let the user enter a text that has
         * to be evaluated by a moderator.
         *
         * @param   array       $seminary   Current Seminary data
         * @param   array       $questgroup Current Questgroup data
         * @param   array       $quest      Current Quest data
         * @param   array       $character  Current Character data
         * @param   \Exception  $exception  Character submission exception
         */
        public function quest($seminary, $questgroup, $quest, $character, $exception)
        {
            // Answers (Submissions)
            $characterSubmissions = $this->Submit->getCharacterSubmissions($quest['id'], $character['id']);
            foreach($characterSubmissions as &$submission)
            {
                $submission['upload'] = $this->Uploads->getSeminaryuploadById($submission['upload_id']);
                $submission['comments'] = $this->Submit->getCharacterSubmissionComments($submission['id']);
                foreach($submission['comments'] as &$comment)
                {
                    try {
                        $comment['user'] = $this->Users->getUserById($comment['created_user_id']);
                        $comment['user']['character'] = $this->Characters->getCharacterForUserAndSeminary($comment['user']['id'], $seminary['id']);
                    }
                    catch(\nre\exceptions\IdNotFoundException $e) {
                    }
                }
            }

            // Show answer of Character
            if($this->request->getGetParam('show-answer') == 'true') {
                $this->redirect($this->linker->link(array('uploads','seminary',$seminary['url'], $characterSubmissions[count($characterSubmissions)-1]['upload']['url'])));
            }

            // Has Character already solved Quest?
            $solved = $this->Quests->hasCharacterSolvedQuest($quest['id'], $character['id']);

            // Last Quest status for Character
            $lastStatus = $this->Quests->getLastQuestStatus($quest['id'], $character['id']);

            // Get allowed mimetypes
            $mimetypes = $this->Submit->getAllowedMimetypes($seminary['id']);


            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('submissions', $characterSubmissions);
            $this->set('solved', $solved);
            $this->set('lastStatus', $lastStatus);
            $this->set('mimetypes', $mimetypes);
            $this->set('exception', $exception);
        }


        /**
         * Action: submission.
         *
         * Show the submission of a Character for a Quest.
         *
         * @param   array   $seminary   Current Seminary data
         * @param   array   $questgroup Current Questgroup data
         * @param   array   $quest      Current Quest data
         * @param   array   $character  Current Character data
         */
        public function submission($seminary, $questgroup, $quest, $character)
        {
            // Get Character submissions
            $submissions = $this->Submit->getCharacterSubmissions($quest['id'], $character['id']);
            foreach($submissions as &$submission)
            {
                $submission['upload'] = $this->Uploads->getSeminaryuploadById($submission['upload_id']);
                $submission['comments'] = $this->Submit->getCharacterSubmissionComments($submission['id']);
                foreach($submission['comments'] as &$comment)
                {
                    try {
                        $comment['user'] = $this->Users->getUserById($comment['created_user_id']);
                        $comment['user']['character'] = $this->Characters->getCharacterForUserAndSeminary($comment['user']['id'], $seminary['id']);
                    }
                    catch(\nre\exceptions\IdNotFoundException $e) {
                    }
                }
                $submission['similar'] = $this->Submit->getSimilarSubmissions(
                    $seminary['id'],
                    $quest['id'],
                    $character['id'],
                    $submission['id']
                );
                foreach($submission['similar'] as &$similarSubmission)
                {
                    $similarSubmission['quest'] = $this->Quests->getQuestById(
                        $similarSubmission['quest_id']
                    );
                    $similarSubmission['questgroup'] = $this->Questgroups->getQuestgroupById(
                        $similarSubmission['quest']['questgroup_id']
                    );
                    $similarSubmission['character'] = $this->Characters->getCharacterById(
                        $similarSubmission['character_id']
                    );
                    $similarSubmission['upload'] = $this->Uploads->getSeminaryuploadById(
                        $similarSubmission['upload_id']
                    );
                }
            }

            // Status
            $solved = $this->Quests->hasCharacterSolvedQuest($quest['id'], $character['id']);


            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('submissions', $submissions);
            $this->set('solved', $solved);
        }


        /**
         * TODO Action: edittask.
         *
         * Edit the task of a Quest.
         *
         * @param   array       $seminary   Current Seminary data
         * @param   array       $questgroup Current Questgroup data
         * @param   array       $quest      Current Quest data
         */
        public function edittask($seminary, $questgroup, $quest)
        {
        }

    }

?>
