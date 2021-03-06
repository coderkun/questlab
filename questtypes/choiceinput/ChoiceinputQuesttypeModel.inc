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
     * Model of the ChoiceinputQuesttypeAgent for choosing between
     * predefined input values.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class ChoiceinputQuesttypeModel extends \hhu\z\models\QuesttypeModel
    {




        /**
         * Copy a Quest
         *
         * @param   int $userId             ID of creating user
         * @param   int $sourceQuestId      ID of Quest to copy from
         * @param   int $targetQuestId      ID of Quest to copy to
         * @param   int $seminaryMediaIds   Mapping of SeminaryMedia-IDs from source Seminary to targetSeminary
         */
        public function copyQuest($userId, $sourceQuestId, $targetQuestId, $seminaryMediaIds)
        {
            // Copy choiceinput
            $this->db->query(
                'INSERT INTO questtypes_choiceinput '.
                '(quest_id, created_user_id, text) '.
                'SELECT ?, ?, text '.
                'FROM questtypes_choiceinput '.
                'WHERE quest_id = ?',
                'iii',
                $targetQuestId, $userId,
                $sourceQuestId
            );

            // Copy lists
            $lists = $this->getChoiceinputLists($sourceQuestId);
            foreach($lists as &$list)
            {
                // Copy list
                $this->db->query(
                    'INSERT INTO questtypes_choiceinput_lists '.
                    '(questtypes_choiceinput_quest_id, number) '.
                    'SELECT ?, number '.
                    'FROM questtypes_choiceinput_lists '.
                    'WHERE id = ?',
                    'ii',
                    $targetQuestId,
                    $list['id']
                );
                $targetListId = $this->db->getInsertId();

                // Copy choices
                $choiceIds = array();
                $choices = $this->getChoiceinputChoices($list['id']);
                foreach($choices as $choice)
                {
                    $this->db->query(
                        'INSERT INTO questtypes_choiceinput_choices '.
                        '(questtypes_choiceinput_list_id, pos, text) '.
                        'SELECT ?, pos, text '.
                        'FROM questtypes_choiceinput_choices '.
                        'WHERE id = ?',
                        'ii',
                        $targetListId,
                        $choice['id']
                    );
                    $choiceIds[$choice['id']] = $this->db->getInsertId();
                }

                // Set correct choice
                if(!is_null($list['questtypes_choiceinput_choice_id']))
                {
                    $this->db->query(
                        'UPDATE questtypes_choiceinput_lists '.
                        'SET questtypes_choiceinput_choice_id = ? '.
                        'WHERE id = ?',
                        'ii',
                        $choiceIds[$list['questtypes_choiceinput_choice_id']],
                        $targetListId
                    );
                }
            }
        }


        /**
         * Delete a Quest.
         * 
         * @param   int $questId    ID of Quest to delete
         */
        public function deleteQuest($questId)
        {
            $this->db->query('DELETE FROM questtypes_choiceinput WHERE quest_id = ?', 'i', $questId);
        }


        /**
         * Get choiceinput-text for a Quest.
         *
         * @param   int     $questId    ID of Quest
         * @return  array               Choiceinput-text
         */
        public function getChoiceinputQuest($questId)
        {
            $data = $this->db->query(
                'SELECT text '.
                'FROM questtypes_choiceinput '.
                'WHERE quest_id = ?',
                'i',
                $questId
            );
            if(!empty($data)) {
                return $data[0];
            }


            return null;
        }


        /**
         * Get all lists of input values for a choiceinput-text.
         *
         * @param   int     $questId    ID of Quest
         * @return  array               List
         */
        public function getChoiceinputLists($questId)
        {
            return $this->db->query(
                'SELECT id, number, questtypes_choiceinput_choice_id '.
                'FROM questtypes_choiceinput_lists '.
                'WHERE questtypes_choiceinput_quest_id = ? '.
                'ORDER BY number ASC',
                'i',
                $questId
            );
        }


        /**
         * Get the list of values for a choiceinput-list.
         *
         * @param   int     $listId ID of list
         * @return  array           Input values
         */
        public function getChoiceinputChoices($listId)
        {
            return $this->db->query(
                'SELECT id, pos, text '.
                'FROM questtypes_choiceinput_choices '.
                'WHERE questtypes_choiceinput_list_id = ? '.
                'ORDER BY pos ASC',
                'i',
                $listId
            );
        }


        /**
         * Save Character’s submitted answer for one choiceinput-list.
         *
         * @param   int     $listId         ID of list
         * @param   int     $characterId    ID of Character
         * @param   string  $answer         Submitted answer for this list
         */
        public function setCharacterSubmission($listId, $characterId, $answer)
        {
            if(is_null($answer))
            {
                $this->db->query(
                    'INSERT INTO questtypes_choiceinput_lists_characters '.
                    '(questtypes_choiceinput_list_id, character_id, questtypes_choiceinput_choice_id) '.
                    'VALUES '.
                    '(?, ?, NULL) '.
                    'ON DUPLICATE KEY UPDATE '.
                    'questtypes_choiceinput_choice_id = NULL',
                    'ii',
                    $listId, $characterId
                );
            }
            else
            {
                $this->db->query(
                    'INSERT INTO questtypes_choiceinput_lists_characters '.
                    '(questtypes_choiceinput_list_id, character_id, questtypes_choiceinput_choice_id) '.
                    'VALUES '.
                    '(?, ?, ?) '.
                    'ON DUPLICATE KEY UPDATE '.
                    'questtypes_choiceinput_choice_id = ?',
                    'iiii',
                    $listId, $characterId, $answer, $answer
                );
            }
        }


        /**
         * Get answer of one choiceinput-list submitted by Character.
         *
         * @param   int     $listId         ID of list
         * @param   int     $characterId    ID of Character
         * @return  int                     Submitted answer for this list or null
         */
        public function getCharacterSubmission($listId, $characterId)
        {
            $data = $this->db->query(
                'SELECT questtypes_choiceinput_choice_id '.
                'FROM questtypes_choiceinput_lists_characters '.
                'WHERE questtypes_choiceinput_list_id = ? AND character_id = ? ',
                'ii',
                $listId, $characterId
            );
            if(!empty($data)) {
                return $data[0]['questtypes_choiceinput_choice_id'];
            }


            return null;
        }


        /**
         * Set the text for a Quest and correct choice input lists count.
         *
         * @param   int     $userId     ID of user setting text
         * @param   int     $questId    ID of Quest to set text for
         * @param   string  $text       Text for Quest
         */
        public function setTextForQuest($userId, $questId, $text)
        {
            $this->db->setAutocommit(false);
            try {
                // Set text
                $this->db->query(
                    'INSERT INTO questtypes_choiceinput '.
                    '(quest_id, created_user_id, text) '.
                    'VALUES '.
                    '(?, ?, ?) '.
                    'ON DUPLICATE KEY UPDATE '.
                    'text = ?',
                    'iiss',
                    $questId,
                    $userId,
                    $text,
                    $text
                );

                // Count fields
                $listCount = substr_count($text, '[choiceinput]');

                // Remove fields
                $this->db->query(
                    'DELETE FROM questtypes_choiceinput_lists '.
                    'WHERE questtypes_choiceinput_quest_id = ? AND number > ?',
                    'ii',
                    $questId,
                    $listCount
                );

                // Add fields
                for($i=1; $i<=$listCount; $i++)
                {
                    $this->db->query(
                        'INSERT IGNORE INTO questtypes_choiceinput_lists '.
                        '(questtypes_choiceinput_quest_id, number, questtypes_choiceinput_choice_id) '.
                        'VALUES '.
                        '(?, ?, NULL) ',
                        'ii',
                        $questId,
                        $i
                    );
                }

                $this->db->commit();
            }
            catch(\Exception $e) {
                $this->db->rollback();
                $this->db->setAutocommit(true);
                throw $e;
            }

            $this->db->setAutocommit(true);
        }


        /**
         * Set list of choices for a text.
         *
         * @param   int     $questId    ID of Quest to set choices for
         * @param   int     $number     List number
         * @param   array   $choices    List of choices
         * @param   int     $correctPos Position of correct answer
         */
        public function setListForText($questId, $number, $choices, $correctPos)
        {
            // Get ID of list
            $listId = $this->db->query(
                'SELECT id '.
                'FROM questtypes_choiceinput_lists '.
                'WHERE questtypes_choiceinput_quest_id = ? AND number = ?',
                'ii',
                $questId,
                $number
            );
            $listId = $listId[0]['id'];

            // Manage choices
            $this->db->setAutocommit(false);
            try {
                // Remove choices
                $this->db->query(
                    'DELETE FROM questtypes_choiceinput_choices '.
                    'WHERE questtypes_choiceinput_list_id = ? AND pos > ?',
                    'ii',
                    $listId,
                    count($choices)
                );

                // Add choices
                foreach($choices as $index => &$choice)
                {
                    $this->db->query(
                        'INSERT INTO questtypes_choiceinput_choices '.
                        '(questtypes_choiceinput_list_id, pos, text) '.
                        'VALUES '.
                        '(?, ?, ?) '.
                        'ON DUPLICATE KEY UPDATE '.
                        'text = ?',
                        'iiss',
                        $listId,
                        $index + 1,
                        $choice,
                        $choice
                    );
                }

                // Set correct choice for list
                $this->db->query(
                    'UPDATE questtypes_choiceinput_lists '.
                    'SET questtypes_choiceinput_choice_id = ('.
                        'SELECT id '.
                        'FROM questtypes_choiceinput_choices '.
                        'WHERE questtypes_choiceinput_list_id = ? AND pos = ?'.
                    ') '.
                    'WHERE id = ?',
                    'iii',
                    $listId,
                    $correctPos,
                    $listId
                );

                $this->db->commit();
            }
            catch(\Exception $e) {
                $this->db->rollback();
                $this->db->setAutocommit(true);
                throw $e;
            }

            $this->db->setAutocommit(true);
        }

    }

?>
