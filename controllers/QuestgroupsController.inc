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
     * Controller of the QuestgroupsAgent to display Questgroups.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class QuestgroupsController extends \hhu\z\controllers\SeminaryController
    {
        /**
         * Required models
         *
         * @var array
         */
        public $models = array('seminaries', 'questgroupshierarchy', 'questgroups', 'questgrouptexts', 'quests', 'questtexts', 'media');
        /**
         * Required components
         *
         * @var array
         */
        public $components = array('validation');
        /**
         * User permissions
         *
         * @var array
         */
        public $permissions = array(
            'questgroup'    => array('admin', 'moderator', 'user'),
            'create'    => array('admin', 'moderator', 'user'),
            'edit'      => array('admin', 'moderator', 'user'),
            'edittexts' => array('admin', 'moderator', 'user'),
            'moveup'    => array('admin', 'moderator', 'user'),
            'movedown'  => array('admin', 'moderator', 'user'),
            'delete'    => array('admin', 'moderator', 'user')
        );
        /**
         * User seminary permissions
         *
         * @var array
         */
        public $seminaryPermissions = array(
            'questgroup'    => array('admin', 'moderator', 'user'),
            'create'    => array('admin'),
            'edit'      => array('admin', 'moderator'),
            'edittexts' => array('admin', 'moderator'),
            'moveup'    => array('admin'),
            'movedown'  => array('admin'),
            'delete'    => array('admin')
        );




        /**
         * Action: questgroup.
         *
         * Display a Questgroup and its data.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-Title of a Seminary
         * @param   string  $questgroupUrl  URL-Title of a Questgroup
         */
        public function questgroup($seminaryUrl, $questgroupUrl)
        {
            // Get Seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Questgroup
            $questgroup = $this->Questgroups->getQuestgroupByUrl($seminary['id'], $questgroupUrl);

            // Get Questgrouphierarchy
            $questgroup['hierarchy'] = $this->Questgroupshierarchy->getHierarchyForQuestgroup($questgroup['id']);

            // Get Character
            $character = $this->Characters->getCharacterForUserAndSeminary($this->Auth->getUserId(), $seminary['id']);

            // Check permission
            if(count(array_intersect(array('admin','moderator'), SeminaryController::$character['characterroles'])) == 0)
            {
                // Check permission of previous parent Questgroups
                $parentQuestgroup = $questgroup;
                while(!is_null($parentQuestgroup['hierarchy']['parent_questgroup_id']))
                {
                    $parentQuestgroup = $this->Questgroups->getQuestgroupById($parentQuestgroup['hierarchy']['parent_questgroup_id']);
                    $parentQuestgroup['hierarchy'] = $this->Questgroupshierarchy->getHierarchyForQuestgroup($parentQuestgroup['id']);
                    try {
                        $previousQuestgroup = $this->Questgroups->getPreviousQuestgroup($seminary['id'], $parentQuestgroup['id']);
                        if(!$this->Questgroups->hasCharacterSolvedQuestgroup($previousQuestgroup['id'], $character['id'])) {
                            throw new \nre\exceptions\AccessDeniedException();
                        }
                    }
                    catch(\nre\exceptions\IdNotFoundException $e) {
                    }
                }

                // Check permission of previous Questgroup
                if($this->Questgroups->hasCharacterEnteredQuestgroup($questgroup['id'], $character['id']))
                {
                    $previousQuestgroup = $this->Questgroups->getPreviousQuestgroup($seminary['id'], $questgroup['id']);
                    if(!is_null($previousQuestgroup)) {
                        if(!$this->Questgroups->hasCharacterSolvedQuestgroup($previousQuestgroup['id'], $character['id'])) {
                            throw new \nre\exceptions\AccessDeniedException();
                        }
                    }
                }
            }

            // Set status “entered”
            $this->Questgroups->setQuestgroupEntered($questgroup['id'], $character['id']);

            // Get child Questgroupshierarchy
            $childQuestgroupshierarchy = null;
            if(!empty($questgroup['hierarchy']))
            {
                $childQuestgroupshierarchy = $this->Questgroupshierarchy->getChildQuestgroupshierarchy($questgroup['hierarchy']['id']);
                foreach($childQuestgroupshierarchy as &$hierarchy)
                {
                    // Get Questgroups
                    $hierarchy['questgroups'] = $this->Questgroups->getQuestgroupsForHierarchy($hierarchy['id'], $questgroup['id']);

                    // Get additional data
                    foreach($hierarchy['questgroups'] as $i => &$group)
                    {
                        $group['solved'] = $this->Questgroups->hasCharacterSolvedQuestgroup($group['id'], $character['id']);

                        // Check permission of Questgroups
                        if($i >= 1 && count(array_intersect(array('admin','moderator'), SeminaryController::$character['characterroles'])) == 0)
                        {
                            if(!$hierarchy['questgroups'][$i-1]['solved'])
                            {
                                $hierarchy['questgroups'] = array_slice($hierarchy['questgroups'], 0, $i);
                                break;
                            }
                        }

                        // Get Character XPs
                        $group['character_xps'] = $this->Questgroups->getAchievedXPsForQuestgroup($group['id'], $character['id']);

                        // Attach related Questgroups
                        $group['relatedQuestgroups'] = array();
                        $relatedQuestgroups = $this->Questgroups->getRelatedQuestsgroupsOfQuestgroup($group['id']);
                        foreach($relatedQuestgroups as &$relatedQuestgroup) {
                            if($this->Questgroups->hasCharacterEnteredQuestgroup($relatedQuestgroup['id'], $character['id'])) {
                                $group['relatedQuestgroups'][] = $this->Questgroups->getQuestgroupById($relatedQuestgroup['id']);
                            }

                        }
                    }
                }
            }

            // Get texts
            $questgroupTexts = $this->Questgrouptexts->getQuestgroupTexts($questgroup['id']);

            // Get Quests
            $quests = array();
            if(count($childQuestgroupshierarchy) == 0)
            {
                $currentQuest = null;
                do {
                    // Get next Quest
                    if(is_null($currentQuest)) {
                        $currentQuest = $this->Quests->getFirstQuestOfQuestgroup($questgroup['id']);
                    }
                    else {
                        $nextQuests = $this->Quests->getNextQuests($currentQuest['id']);
                        $currentQuest = null;
                        foreach($nextQuests as &$nextQuest) {
                            if($this->Quests->hasCharacterEnteredQuest($nextQuest['id'], $character['id'])) {
                                $currentQuest = $nextQuest;
                                break;
                            }
                        }
                    }

                    // Add additional data
                    if(!is_null($currentQuest))
                    {
                        // Set status
                        $currentQuest['solved'] = $this->Quests->hasCharacterSolvedQuest($currentQuest['id'], $character['id']);

                        // Attach related Questgroups
                        $currentQuest['relatedQuestgroups'] = array();
                        $relatedQuestgroups = $this->Questgroups->getRelatedQuestsgroupsOfQuest($currentQuest['id']);
                        foreach($relatedQuestgroups as &$relatedQuestgroup)
                        {
                            if($this->Questgroups->hasCharacterEnteredQuestgroup($relatedQuestgroup['id'], $character['id'])) {
                                $currentQuest['relatedQuestgroups'][] = $this->Questgroups->getQuestgroupById($relatedQuestgroup['id']);
                            }
                        }

                        // Add Quest to Quests
                        $quests[] = $currentQuest;
                    }
                }
                while(!is_null($currentQuest) && ($currentQuest['solved'] || count(array_intersect(array('admin','moderator'), SeminaryController::$character['characterroles'])) > 0));
            }


            // Set titile
            if(!is_null($questgroup['hierarchy'])) {
                $this->addTitle(sprintf('%s %d: %s', $questgroup['hierarchy']['title_singular'], $questgroup['hierarchy']['questgroup_pos'], $questgroup['title']));
            }
            else {
                $this->addTitle($questgroup['title']);
            }
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('questgroup', $questgroup);
            $this->set('childquestgroupshierarchy', $childQuestgroupshierarchy);
            $this->set('texts', $questgroupTexts);
            $this->set('quests', $quests);
        }


        /**
         * Action: create.
         *
         * Create a new Questgroup.
         *
         * @param   string  $seminaryUrl    URL-Title of a Seminary
         */
        public function create($seminaryUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get allowed mimetypes
            $mimetypes = \nre\configs\AppConfig::$mimetypes['moodpics'];

            // Values
            $selectedQuestgroupshierarchy = null;
            $selectedQuestgroup = null;
            $title = '';
            $fields = array('title');
            $validation = array();

            // Check request method
            if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('create')))
            {
                // Get params and validate them
                $validation = $this->Validation->validateParams($this->request->getPostParams(), $fields);
                $title = $this->request->getPostParam('title');
                if($this->Questgroups->questgroupTitleExists($seminary['id'], $title)) {
                    $validation = $this->Validation->addValidationResult($validation, 'title', 'exist', true);
                }

                // Validate Questgroupshierarchy
                try {
                    $selectedQuestgroupshierarchy = $this->Questgroupshierarchy->getHierarchyByUrl($seminary['id'], $this->request->getPostParam('questgroupshierarchy'));
                }
                catch(\nre\exceptions\IdNotFoundException $e) {
                    throw new \nre\exceptions\ParamsNotValidException($this->request->getPostParam('questgroupshierarchy'));
                }

                // Validate Questgroup
                if(!is_null($selectedQuestgroupshierarchy['parent_questgroupshierarchy_id'])) {
                    try {
                        $selectedQuestgroup = $this->Questgroups->getQuestgroupByUrl($seminary['id'], $this->request->getPostParam('questgroup'));
                    }
                    catch(\nre\exceptions\IdNotFoundException $e) {
                        throw new \nre\exceptions\ParamsNotValidException($this->request->getPostParam('questgroups'));
                    }
                }

                // Validate moodpic
                $moodpic = null;
                if(!empty($_FILES) && array_key_exists('moodpic', $_FILES) && $_FILES['moodpic']['error'] != UPLOAD_ERR_NO_FILE)
                {
                    $moodpic = $_FILES['moodpic'];

                    // Check error
                    if($moodpic['error'] !== UPLOAD_ERR_OK) {
                        $validation = $this->Validation->addValidationResult($validation, 'moodpic', 'error', $moodpic['error']);
                    }

                    // Check mimetype
                    $mediaMimetype = null;
                    $moodpic['mimetype'] = \hhu\z\Utils::getMimetype($moodpic['tmp_name'], $moodpic['type']);
                    foreach($mimetypes as &$mimetype) {
                        if($mimetype['mimetype'] == $moodpic['mimetype']) {
                            $mediaMimetype = $mimetype;
                            break;
                        }
                    }
                    if(is_null($mediaMimetype)) {
                        $validation = $this->Validation->addValidationResult($validation, 'moodpic', 'mimetype', $moodpic['mimetype']);
                    }
                    elseif($moodpic['size'] > $mediaMimetype['size']) {
                        $validation = $this->Validation->addValidationResult($validation, 'moodpic', 'size', $mediaMimetype['size']);
                    }
                }

                // Create new Questgroup
                if($validation === true)
                {
                    $questgroupId = $this->Questgroups->createQuestgroup(
                        $this->Auth->getUserId(),
                        $seminary['id'],
                        $title
                    );
                    $questgroup = $this->Questgroups->getQuestgroupById($questgroupId);

                    // Add to Hierarchy
                    $this->Questgroups->addQuestgroupToHierarchy(
                        $questgroupId,
                        $selectedQuestgroupshierarchy['id'],
                        (!is_null($selectedQuestgroup)) ? $selectedQuestgroup['id'] : null
                    );

                    // Upload moodpic
                    if(!is_null($moodpic))
                    {
                        $mediaId = $this->Media->createQuestgrouppicture(
                            $this->Auth->getUserId(),
                            $seminary['id'],
                            $questgroup['id'],
                            sprintf('questgroupmoodpic-%s', $questgroup['url']),
                            '',
                            $moodpic['mimetype'],
                            $moodpic['tmp_name']
                        );
                        if($mediaId !== false) {
                            $this->Questgroups->setMoodpicForQuestgroup($questgroup['id'], $mediaId);
                        }
                    }


                    // Redirect to new Questgroup
                    $this->redirect($this->linker->link(array('questgroup', $seminary['url'], $questgroup['url']), 1));
                }
            }

            // Get validation settings
            $validationSettings = array();
            foreach($fields as &$field) {
                $validationSettings[$field] = \nre\configs\AppConfig::$validation[$field];
            }


            // Set titile
            $this->addTitleLocalized('Create Questgroup');
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('mimetypes', $mimetypes);
            $this->set('questgroupshierarchy', $selectedQuestgroupshierarchy);
            $this->set('questgroup', $selectedQuestgroup);
            $this->set('title', $title);
            $this->set('validation', $validation);
            $this->set('validationSettings', $validationSettings);
        }


        /**
         * Action: edit.
         *
         * Edit a Questgroup.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-title of a Seminary
         * @param   string  $questgroupUrl  URL-title of Questgroup to edit
         */
        public function edit($seminaryUrl, $questgroupUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Questgroup
            $questgroup = $this->Questgroups->getQuestgroupByUrl($seminary['id'], $questgroupUrl);

            // Get allowed mimetypes
            $mimetypes = \nre\configs\AppConfig::$mimetypes['moodpics'];

            // Values
            $title = $questgroup['title'];
            $fields = array('title');
            $validation = array();

            // Check request method
            if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('edit')))
            {
                // Get params and validate them
                $validation = $this->Validation->validateParams($this->request->getPostParams(), $fields);
                $title = $this->request->getPostParam('title');
                if($this->Questgroups->questgroupTitleExists($seminary['id'], $title, $questgroup['id'])) {
                    $validation = $this->Validation->addValidationResult($validation, 'title', 'exist', true);
                }

                // Validate moodpic
                $moodpic = null;
                if(!empty($_FILES) && array_key_exists('moodpic', $_FILES) && $_FILES['moodpic']['error'] != UPLOAD_ERR_NO_FILE)
                {
                    $moodpic = $_FILES['moodpic'];

                    // Check error
                    if($moodpic['error'] !== UPLOAD_ERR_OK) {
                        $validation = $this->Validation->addValidationResult($validation, 'moodpic', 'error', $moodpic['error']);
                    }

                    // Check mimetype
                    $mediaMimetype = null;
                    $moodpic['mimetype'] = \hhu\z\Utils::getMimetype($moodpic['tmp_name'], $moodpic['type']);
                    foreach($mimetypes as &$mimetype) {
                        if($mimetype['mimetype'] == $moodpic['mimetype']) {
                            $mediaMimetype = $mimetype;
                            break;
                        }
                    }
                    if(is_null($mediaMimetype)) {
                        $validation = $this->Validation->addValidationResult($validation, 'moodpic', 'mimetype', $moodpic['mimetype']);
                    }
                    elseif($moodpic['size'] > $mediaMimetype['size']) {
                        $validation = $this->Validation->addValidationResult($validation, 'moodpic', 'size', $mediaMimetype['size']);
                    }
                }

                // Edit Questgroup
                if($validation === true)
                {
                    $this->Questgroups->editQuestgroup(
                        $questgroup['id'],
                        $title
                    );
                    $questgroup = $this->Questgroups->getQuestgroupById($questgroup['id']);

                    // Upload moodpic
                    if(!is_null($moodpic))
                    {
                        $mediaId = $this->Media->createQuestgrouppicture(
                            $this->Auth->getUserId(),
                            $seminary['id'],
                            $questgroup['id'],
                            sprintf('questgroupmoodpic-%s', $questgroup['url']),
                            '',
                            $moodpic['mimetype'],
                            $moodpic['tmp_name']
                        );
                        if($mediaId !== false) {
                            $this->Questgroups->setMoodpicForQuestgroup($questgroup['id'], $mediaId);
                        }
                    }


                    // Redirect to new Questgroup
                    $this->redirect($this->linker->link(array('questgroup', $seminary['url'], $questgroup['url']), 1));
                }
            }

            // Get validation settings
            $validationSettings = array();
            foreach($fields as &$field) {
                $validationSettings[$field] = \nre\configs\AppConfig::$validation[$field];
            }


            // Set titile
            $this->addTitleLocalized('Edit Questgroup');
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('questgroup', $questgroup);
            $this->set('title', $title);
            $this->set('mimetypes', $mimetypes);
            $this->set('validation', $validation);
            $this->set('validationSettings', $validationSettings);
        }


        /**
         * Action: edittexts.
         *
         * Edit the texts of a Questgroup.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-title of a Seminary
         * @param   string  $questgroupUrl  URL-title of Questgroup to edit
         */
        public function edittexts($seminaryUrl, $questgroupUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Questgroup
            $questgroup = $this->Questgroups->getQuestgroupByUrl($seminary['id'], $questgroupUrl);

            // Get Questgroup texts
            $questgroupTexts = $this->Questgrouptexts->getQuestgroupTexts($questgroup['id']);

            // Get allowed mimetypes
            $mimetypes = \nre\configs\AppConfig::$mimetypes['moodpics'];

            // Check request method
            if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('edit')))
            {
                $texts = $this->request->getPostParam('questgrouptexts');
                $deleteTexts = $this->request->getPostParam('deletes');
                if(!is_array($deleteTexts)) {
                    $deleteTexts = array();
                }

                // Edit or delete texts
                foreach($questgroupTexts as $text)
                {
                    if(array_key_exists($text['id'], $deleteTexts))
                    {
                        $this->Questgrouptexts->deleteQuestgrouptext($text);
                        unset($texts[$text['id']]);
                    }
                    elseif(array_key_exists($text['id'], $texts))
                    {
                        $this->Questgrouptexts->editQuestgrouptext($text['id'], $texts[$text['id']]);
                        unset($texts[$text['id']]);
                    }
                }

                // Add new texts
                foreach($texts as $text) {
                    if(!empty($text)) {
                        $this->Questgrouptexts->addQuestgrouptextToQuestgroup($this->Auth->getUserId(), $questgroup['id'], $text);
                    }
                }

                // Redirect to Questgroup
                $this->redirect($this->linker->link(array('questgroup', $seminary['url'], $questgroup['url']), 1));
            }


            // Set titile
            $this->addTitleLocalized('Edit Questgroup texts');
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('questgroup', $questgroup);
            $this->set('questgrouptexts', $questgroupTexts);
            $this->set('mimetypes', $mimetypes);
        }


        /**
         * Action: moveup.
         *
         * Move a Questgroup up (decrement position).
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-title of Seminary
         * @param   string  $questgroupUrl  URL-title of Questgroup
         */
        public function moveup($seminaryUrl, $questgroupUrl)
        {
            // Get Seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Questgroup
            $questgroup = $this->Questgroups->getQuestgroupByUrl($seminary['id'], $questgroupUrl);
            $questgroup['hierarchy'] = $this->Questgroupshierarchy->getHierarchyForQuestgroup($questgroup['id']);

            // Check request method
            if($this->request->getRequestMethod() == 'POST')
            {
                // Check confirmation
                if(!is_null($this->request->getPostParam('move')))
                {
                    // Set position
                    $this->Questgroups->moveQuestgroup($questgroup, true);
                }

                // Redirect
                $referer = $this->request->getGetParam('referer');
                if(!is_null($referer))
                {
                    try {
                        $questgroup = $this->Questgroups->getQuestgroupById($referer);
                        $this->redirect($this->linker->link(array('questgroups', 'questgroup', $seminary['url'], $questgroup['url'])));
                    }
                    catch(IdNotFoundException $e) {
                    }
                }
                $this->redirect($this->linker->link(array('seminaries', 'seminary', $seminary['url'])));
            }


            // Set titile
            $this->addTitleLocalized('Move Questgroup');

            // Show confirmation
            $this->set('seminary', $seminary);
            $this->set('questgroup', $questgroup);
        }


        /**
         * Action: movedown
         *
         * Move a Questgroup down (increment position).
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-title of Seminary
         * @param   string  $questgroupUrl  URL-title of Questgroup
         */
        public function movedown($seminaryUrl, $questgroupUrl)
        {
            // Get Seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Questgroup
            $questgroup = $this->Questgroups->getQuestgroupByUrl($seminary['id'], $questgroupUrl);
            $questgroup['hierarchy'] = $this->Questgroupshierarchy->getHierarchyForQuestgroup($questgroup['id']);

            // Check request method
            if($this->request->getRequestMethod() == 'POST')
            {
                // Check confirmation
                if(!is_null($this->request->getPostParam('move')))
                {
                    // Set position
                    $this->Questgroups->moveQuestgroup($questgroup, false);
                }

                // Redirect
                $referer = $this->request->getGetParam('referer');
                if(!is_null($referer))
                {
                    try {
                        $questgroup = $this->Questgroups->getQuestgroupById($referer);
                        $this->redirect($this->linker->link(array('questgroups', 'questgroup', $seminary['url'], $questgroup['url'])));
                    }
                    catch(IdNotFoundException $e) {
                    }
                }
                $this->redirect($this->linker->link(array('seminaries', 'seminary', $seminary['url'])));
            }


            // Set titile
            $this->addTitleLocalized('Move Questgroup');

            // Show confirmation
            $this->set('seminary', $seminary);
            $this->set('questgroup', $questgroup);
        }


        /**
         * Action: delete.
         *
         * Delete a Questgroup.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-Title of a Seminary
         * @param   string  $questgroupUrl  URL-Title of a Questgroup
         */
        public function delete($seminaryUrl, $questgroupUrl)
        {
            // Get Seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Questgroup
            $questgroup = $this->Questgroups->getQuestgroupByUrl($seminary['id'], $questgroupUrl);

            // Get Questgrouphierarchy
            $questgroup['hierarchy'] = $this->Questgroupshierarchy->getHierarchyForQuestgroup($questgroup['id']);

            // Check request method
            if($this->request->getRequestMethod() == 'POST')
            {
                // Check confirmation
                if(!is_null($this->request->getPostParam('delete')))
                {
                    // Delete Questgroup
                    $this->Questgroups->deleteQuestgroup($questgroup['id']);

                    // Redirect
                    if(!is_null($questgroup['hierarchy']))
                    {
                        // Parent Questgroup
                        if(is_null($questgroup['hierarchy']['parent_questgroup_id'])) {
                            $this->redirect($this->linker->link(array('seminaries', 'seminary', $seminary['url'])));
                        }
                        else
                        {
                            $parentQuestgroup = $this->Questgroups->getQuestgroupById($questgroup['hierarchy']['parent_questgroup_id']);
                            $this->redirect($this->linker->link(array('questgroup', $seminary['url'], $parentQuestgroup['url']), 1));
                        }
                    }
                    else
                    {
                        // Related Questgroup
                        $questtexts = $this->Questtexts->getRelatedQuesttextsForQuestgroup($questgroup['id']);
                        $questtext = $this->Questtexts->pickQuesttextLastEnteredByCharacter(\hhu\z\controllers\SeminaryController::$character['id'], $questtexts);
                        $quest = $this->Quests->getQuestById($questtext['quest_id']);
                        $relatedQuestgroup = $this->Questgroups->getQuestgroupById($quest['questgroup_id']);
                        $this->redirect($this->linker->link(array('questgroup', $seminary['url'], $relatedQuestgroup['url']), 1));
                    }
                }

                // Redirect to entry
                $this->redirect($this->linker->link(array('questgroup', $seminary['url'], $questgroup['url']), 1));
            }


            // Set titile
            $this->addTitleLocalized('Delete Questgroup');

            // Show confirmation
            $this->set('seminary', $seminary);
            $this->set('questgroup', $questgroup);
        }

    }

?>
