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
     * Controller of the CharactergroupsquestsAgent to display Character
     * groups Quests.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class CharactergroupsquestsController extends \hhu\z\controllers\SeminaryController
    {
        /**
         * Required models
         *
         * @var array
         */
        public $models = array('seminaries', 'charactergroups', 'charactergroupsquests', 'media', 'questgroups', 'uploads');
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
            'quest' => array('admin', 'moderator', 'user')
        );
        /**
         * User seminary permissions
         *
         * @var array
         */
        public $seminaryPermissions = array(
            'quest' => array('admin', 'moderator', 'user')
        );




        /**
         * Action: quest.
         *
         * Show a Character groups Quest for a Character groups-group
         * of a Seminary.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl        URL-Title of a Seminary
         * @param   string  $groupsgroupUrl     URL-Title of a Character groups-group
         * @param   string  $questUrl       URL-Title of a Character groups Quest
         */
        public function quest($seminaryUrl, $groupsgroupUrl, $questUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Character groups-group
            $groupsgroup = $this->Charactergroups->getGroupsgroupByUrl($seminary['id'], $groupsgroupUrl);

            // Get Character groups-group Quests
            $quest = $this->Charactergroupsquests->getQuestByUrl($groupsgroup['id'], $questUrl);

            // Get Questgroup
            $questgroup = $this->Questgroups->getQuestgroupById($quest['questgroups_id']);
            $questgroup['entered'] = $this->Questgroups->hasCharacterEnteredQuestgroup($questgroup['id'], self::$character['id']);

            // Get Character groups-groups
            $groups = $this->Charactergroups->getGroupsForQuest($quest['id']);

            // Get uploads
            $uploads = $this->Charactergroupsquests->getMediaForQuest($quest['id']);
            foreach($uploads as &$upload) {
                $upload['upload'] = $this->Uploads->getSeminaryuploadById($upload['seminaryupload_id']);
            }


            // Set title
            $this->addTitle($quest['title']);
            $this->addTitle($groupsgroup['name']);
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('groupsgroup', $groupsgroup);
            $this->set('quest', $quest);
            $this->set('questgroup', $questgroup);
            $this->set('groups', $groups);
            $this->set('uploads', $uploads);
        }


        /**
         * Action: manage.
         *
         * Manage a Character groups Quest for a Character groups-group
         * of a Seminary.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl        URL-Title of a Seminary
         * @param   string  $groupsgroupUrl     URL-Title of a Character groups-group
         * @param   string  $questUrl       URL-Title of a Character groups Quest
         */
        public function manage($seminaryUrl, $groupsgroupUrl, $questUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Character groups-group
            $groupsgroup = $this->Charactergroups->getGroupsgroupByUrl($seminary['id'], $groupsgroupUrl);

            // Get Character groups-group Quests
            $quest = $this->Charactergroupsquests->getQuestByUrl($groupsgroup['id'], $questUrl);

            // Get Questgroup
            $questgroup = $this->Questgroups->getQuestgroupById($quest['questgroups_id']);
            $questgroup['entered'] = $this->Questgroups->hasCharacterEnteredQuestgroup($questgroup['id'], self::$character['id']);

            // Get Character groups
            $groups = $this->Charactergroups->getGroupsForGroupsgroup($groupsgroup['id']);

            // Get allowed mimetypes
            $mimetypes = \nre\configs\AppConfig::$mimetypes['charactergroupsquests'];

            // Manage
            $validation = array();
            if($this->request->getRequestMethod() == 'POST')
            {
                // Upload media
                if(!is_null($this->request->getPostParam('setmedia')))
                {
                    $file = $_FILES['media'];

                    // Check error
                    if($file['error'] !== 0 || empty($file['tmp_name'])) {
                        $validation = $this->Validation->addValidationResult($validation, 'media', 'error', $file['error']);
                    }

                    // Check mimetype
                    $mediaMimetype = null;
                    $file['mimetype'] = \hhu\z\Utils::getMimetype($file['tmp_name'], $file['type']);
                    foreach($mimetypes as &$mimetype) {
                        if($mimetype['mimetype'] == $file['mimetype']) {
                            $mediaMimetype = $mimetype;
                            break;
                        }
                    }
                    if(is_null($mediaMimetype)) {
                        $validation = $this->Validation->addValidationResult($validation, 'media', 'mimetype', $file['mimetype']);
                    }
                    elseif($file['size'] > $mediaMimetype['size']) {
                        $validation = $this->Validation->addValidationResult($validation, 'media', 'size', $mediaMimetype['size']);
                    }

                    // Upload media
                    if($validation === true || empty($valiadion))
                    {
                        // Create filename
                        $filename = sprintf(
                            '%s-%d-%s.%s',
                            'charactergroupsquest',
                            $quest['id'],
                            date('Ymd-His'),
                            mb_substr($file['name'], strrpos($file['name'], '.')+1)
                        );

                        // Upload file
                        $this->Charactergroupsquests->uploadMediaForQuest($this->Auth->getUserId(), $seminary['id'], $quest['id'], $file, $filename);
                    }
                }

                // Delete media
                if(!is_null($this->request->getPostParam('deletemedia')))
                {
                    $uploadIds = $this->request->getPostParam('uploads');
                    var_dump($uploadIds);
                    foreach($uploadIds as $uploadId) {
                        $this->Uploads->deleteSeminaryupload($uploadId);
                    }
                }

                // Set XPs of Character groups for this Character groups Quest
                if(!is_null($this->request->getPostParam('setxps')))
                {
                    $xps = $this->request->getPostParam('xps');
                    foreach($groups as &$group)
                    {
                        if(array_key_exists($group['url'], $xps) && $xps[$group['url']] != 'null')
                        {
                            $xpsFactor = intval($xps[$group['url']]) / $quest['xps'];
                            $this->Charactergroupsquests->setXPsOfGroupForQuest($quest['id'], $group['id'], $xpsFactor);
                        }
                        else {
                            $this->Charactergroupsquests->deleteGroupForQuest($quest['id'], $group['id']);
                        }
                    }
                }

                // Redirect to Quest page
                if($validation === true || empty($validation)) {
                    $this->redirect($this->linker->link(array('quest', $seminary['url'], $groupsgroup['url'], $quest['url']), 1));
                }
            }

            // Get icon
            $questmedia = null;
            if(!is_null($quest['questsmedia_id'])) {
                $questmedia = $this->Media->getSeminaryMediaById($quest['questsmedia_id']);
            }

            // Get uploads
            $uploads = $this->Charactergroupsquests->getMediaForQuest($quest['id']);
            foreach($uploads as &$upload) {
                $upload['upload'] = $this->Uploads->getSeminaryuploadById($upload['seminaryupload_id']);
            }


            // Set XPs for Groups
            foreach($groups as &$group) {
                $group['quest_group'] = $this->Charactergroupsquests->getXPsOfGroupForQuest($quest['id'], $group['id']);
            }


            // Set title
            $this->addTitle($quest['title']);
            $this->addTitle($groupsgroup['name']);
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('groupsgroup', $groupsgroup);
            $this->set('quest', $quest);
            $this->set('uploads', $uploads);
            $this->set('mimetypes', $mimetypes);
            $this->set('questgroup', $questgroup);
            $this->set('groups', $groups);
            $this->set('media', $questmedia);
            $this->set('validation', $validation);
        }


        /**
         * Action: create.
         *
         * Create a new Character groups Quest for a Character
         * groups-group of a Seminary.
         *
         * @param   string  $seminaryUrl        URL-Title of a Seminary
         * @param   string  $groupsgroupUrl     URL-Title of a Character groups-group
         */
        public function create($seminaryUrl, $groupsgroupUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Character groups-group
            $groupsgroup = $this->Charactergroups->getGroupsgroupByUrl($seminary['id'], $groupsgroupUrl);

            // Get Questgroups
            $questgroups = $this->Questgroups->getQuestgroupsForSeminary($seminary['id']);

            // Get allowed mimetypes
            $mimetypes = \nre\configs\AppConfig::$mimetypes['icons'];

            // Values
            $title = '';
            $xps = 0;
            $description = '';
            $rules = '';
            $wonText = '';
            $lostText = '';
            $fields = array('title', 'xps');
            $validation = array();

            // Create a new Character groups Quest
            if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('create')))
            {
                // Get params and validate them
                $validation = $this->Validation->validateParams($this->request->getPostParams(), $fields);
                $title = $this->request->getPostParam('title');
                if($this->Charactergroupsquests->characterGroupsQuestTitleExists($groupsgroup['id'], $title)) {
                    $validation = $this->Validation->addValidationResult($validation, 'title', 'exist', true);
                }
                $xps = $this->request->getPostParam('xps');
                $description = $this->request->getPostParam('description');
                $rules = $this->request->getPostParam('rules');
                $wonText = $this->request->getPostParam('wonText');
                $lostText = $this->request->getPostParam('lostText');

                // Validate icon
                $icon = null;
                if(!empty($_FILES) && array_key_exists('icon', $_FILES) && $_FILES['icon']['error'] != UPLOAD_ERR_NO_FILE)
                {
                    $icon = $_FILES['icon'];

                    // Check error
                    if($icon['error'] !== UPLOAD_ERR_OK) {
                        $validation = $this->Validation->addValidationResult($validation, 'icon', 'error', $icon['error']);
                    }

                    // Check mimetype
                    $mediaMimetype = null;
                    $icon['mimetype'] = \hhu\z\Utils::getMimetype($icon['tmp_name'], $icon['type']);
                    foreach($mimetypes as &$mimetype) {
                        if($mimetype['mimetype'] == $icon['mimetype']) {
                            $mediaMimetype = $mimetype;
                            break;
                        }
                    }
                    if(is_null($mediaMimetype)) {
                        $validation = $this->Validation->addValidationResult($validation, 'icon', 'mimetype', $icon['mimetype']);
                    }
                    elseif($icon['size'] > $mediaMimetype['size']) {
                        $validation = $this->Validation->addValidationResult($validation, 'icon', 'size', $mediaMimetype['size']);
                    }
                }

                // Validate Questgroup
                $questgroupIndex = null;
                foreach($questgroups as $index => &$questgroup)
                {
                    $questgroup['selected'] = ($questgroup['url'] == $this->request->getPostParam('questgroup'));
                    if($questgroup['selected']) {
                        $questgroupIndex = $index;
                    }
                }
                if(is_null($questgroupIndex)) {
                    throw new \nre\exceptions\ParamsNotValidException($questgroup);
                }

                // Create groups Quest
                if($validation === true)
                {
                    $questId = $this->Charactergroupsquests->createQuest(
                        $this->Auth->getUserId(),
                        $groupsgroup['id'],
                        $questgroups[$questgroupIndex]['id'],
                        $title,
                        $description,
                        $xps,
                        $rules,
                        $wonText,
                        $lostText
                    );
                    $quest = $this->Charactergroupsquests->getQuestById($questId);

                    // Upload icon
                    if(!is_null($icon))
                    {
                        $mediaId = $this->Media->createQuestMedia(
                            $this->Auth->getUserId(),
                            $seminary['id'],
                            sprintf('charactergroupsquest-%s', $quest['url']),
                            '',
                            $icon['mimetype'],
                            $icon['tmp_name']
                        );
                        if($mediaId !== false) {
                            $this->Charactergroupsquests->setMediaForQuest($quest['id'], $mediaId);
                        }
                    }

                    // Redirect to Quest page
                    $this->redirect($this->linker->link(array('quest', $seminary['url'], $groupsgroup['url'], $quest['url']), 1));
                }
            }

            // Get validation settings
            $validationSettings = array();
            foreach($fields as &$field) {
                $validationSettings[$field] = \nre\configs\AppConfig::$validation[$field];
            }


            // Set title
            $this->addTitleLocalized('New %s-Quest', $groupsgroup['name']);
            $this->addTitle($groupsgroup['name']);
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('groupsgroup', $groupsgroup);
            $this->set('questgroups', $questgroups);
            $this->set('title', $title);
            $this->set('xps', $xps);
            $this->set('description', $description);
            $this->set('rules', $rules);
            $this->set('wonText', $wonText);
            $this->set('lostText', $lostText);
            $this->set('mimetypes', $mimetypes);
            $this->set('validation', $validation);
            $this->set('validationSettings', $validationSettings);
        }


        /**
         * Action: edit.
         *
         * Edit a Character groups Quest of a Character groups-group
         * of a Seminary.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl        URL-Title of a Seminary
         * @param   string  $groupsgroupUrl     URL-Title of a Character groups-group
         * @param   string  $questUrl       URL-Title of a Character groups Quest
         */
        public function edit($seminaryUrl, $groupsgroupUrl, $questUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Character groups-group
            $groupsgroup = $this->Charactergroups->getGroupsgroupByUrl($seminary['id'], $groupsgroupUrl);

            // Get Character groups-group Quests
            $quest = $this->Charactergroupsquests->getQuestByUrl($groupsgroup['id'], $questUrl);

            // Get Questgroups
            $questgroups = $this->Questgroups->getQuestgroupsForSeminary($seminary['id']);
            foreach($questgroups as $index => &$questgroup) {
                $questgroup['selected'] = ($questgroup['id'] == $quest['questgroups_id']);
            }

            // Get allowed mimetypes
            $mimetypes = \nre\configs\AppConfig::$mimetypes['icons'];

            // Values
            $title = $quest['title'];
            $xps = $quest['xps'];
            $description = $quest['description'];
            $rules = $quest['rules'];
            $wonText = $quest['won_text'];
            $lostText = $quest['lost_text'];
            $fields = array('title', 'xps');
            $validation = array();

            // Edit Character group
            if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('edit')))
            {
                // Get params and validate them
                $validation = $this->Validation->validateParams($this->request->getPostParams(), $fields);
                $title = $this->request->getPostParam('title');
                if($this->Charactergroupsquests->characterGroupsQuestTitleExists($groupsgroup['id'], $title, $quest['id'])) {
                    $validation = $this->Validation->addValidationResult($validation, 'title', 'exist', true);
                }
                $xps = $this->request->getPostParam('xps');
                $description = $this->request->getPostParam('description');
                $rules = $this->request->getPostParam('rules');
                $wonText = $this->request->getPostParam('wonText');
                $lostText = $this->request->getPostParam('lostText');

                // Validate icon
                $icon = null;
                if(!empty($_FILES) && array_key_exists('icon', $_FILES) && $_FILES['icon']['error'] != UPLOAD_ERR_NO_FILE)
                {
                    $icon = $_FILES['icon'];

                    // Check error
                    if($icon['error'] !== UPLOAD_ERR_OK) {
                        $validation = $this->Validation->addValidationResult($validation, 'icon', 'error', $icon['error']);
                    }

                    // Check mimetype
                    $mediaMimetype = null;
                    $icon['mimetype'] = \hhu\z\Utils::getMimetype($icon['tmp_name'], $icon['type']);
                    foreach($mimetypes as &$mimetype) {
                        if($mimetype['mimetype'] == $icon['mimetype']) {
                            $mediaMimetype = $mimetype;
                            break;
                        }
                    }
                    if(is_null($mediaMimetype)) {
                        $validation = $this->Validation->addValidationResult($validation, 'icon', 'mimetype', $icon['mimetype']);
                    }
                    elseif($icon['size'] > $mediaMimetype['size']) {
                        $validation = $this->Validation->addValidationResult($validation, 'icon', 'size', $mediaMimetype['size']);
                    }
                }

                // Validate Questgroup
                $questgroupIndex = null;
                foreach($questgroups as $index => &$questgroup)
                {
                    $questgroup['selected'] = ($questgroup['url'] == $this->request->getPostParam('questgroup'));
                    if($questgroup['selected']) {
                        $questgroupIndex = $index;
                    }
                }
                if(is_null($questgroupIndex)) {
                    throw new \nre\exceptions\ParamsNotValidException($questgroup);
                }

                // Edit groups Quest
                if($validation === true)
                {
                    $this->Charactergroupsquests->editQuest(
                        $quest['id'],
                        $groupsgroup['id'],
                        $questgroups[$questgroupIndex]['id'],
                        $title,
                        $description,
                        $xps,
                        $rules,
                        $wonText,
                        $lostText
                    );
                    $quest = $this->Charactergroupsquests->getQuestById($quest['id']);

                    // Upload icon
                    if(!is_null($icon))
                    {
                        $mediaId = $this->Media->createQuestMedia(
                            $this->Auth->getUserId(),
                            $seminary['id'],
                            sprintf('charactergroupsquest-%s', $quest['url']),
                            '',
                            $icon['mimetype'],
                            $icon['tmp_name']
                        );
                        if($mediaId !== false) {
                            $this->Charactergroupsquests->setMediaForQuest($quest['id'], $mediaId);
                        }
                    }

                    // Redirect to Quest page
                    $this->redirect($this->linker->link(array('quest', $seminary['url'], $groupsgroup['url'], $quest['url']), 1));
                }
            }

            // Get validation settings
            $validationSettings = array();
            foreach($fields as &$field) {
                $validationSettings[$field] = \nre\configs\AppConfig::$validation[$field];
            }


            // Set title
            $this->addTitleLocalized('Edit %s-Quest', $groupsgroup['name']);
            $this->addTitle($groupsgroup['name']);
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('groupsgroup', $groupsgroup);
            $this->set('quest', $quest);
            $this->set('questgroups', $questgroups);
            $this->set('title', $title);
            $this->set('xps', $xps);
            $this->set('description', $description);
            $this->set('rules', $rules);
            $this->set('wonText', $wonText);
            $this->set('lostText', $lostText);
            $this->set('mimetypes', $mimetypes);
            $this->set('validation', $validation);
            $this->set('validationSettings', $validationSettings);
        }


        /**
         * Action: delete.
         *
         * Delete a Character groups Quest of a Character groups-group
         * of a Seminary.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl        URL-Title of a Seminary
         * @param   string  $groupsgroupUrl     URL-Title of a Character groups-group
         * @param   string  $questUrl       URL-Title of a Character groups Quest
         */
        public function delete($seminaryUrl, $groupsgroupUrl, $questUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Character groups-group
            $groupsgroup = $this->Charactergroups->getGroupsgroupByUrl($seminary['id'], $groupsgroupUrl);

            // Get Character groups-group Quests
            $quest = $this->Charactergroupsquests->getQuestByUrl($groupsgroup['id'], $questUrl);

            // Check request method
            if($this->request->getRequestMethod() == 'POST')
            {
                // Check confirmation
                if(!is_null($this->request->getPostParam('delete')))
                {
                    // Delete seminary
                    $this->Charactergroupsquests->deleteQuest($quest['id']);

                    // Redirect to overview
                    $this->redirect($this->linker->link(array('charactergroups', 'groupsgroup', $seminary['url'], $groupsgroup['url'])));
                }

                // Redirect to entry
                $this->redirect($this->linker->link(array('quest', $seminary['url'], $groupsgroup['url'], $quest['url']), 1));
            }


            // Set title
            $this->addTitleLocalized('Delete %s-Quest', $groupsgroup['name']);
            $this->addTitle($groupsgroup['name']);
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('groupsgroup', $groupsgroup);
            $this->set('quest', $quest);
        }

    }

?>