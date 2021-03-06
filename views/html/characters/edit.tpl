<?=$moodpic?>
<ul class="breadcrumbs">
    <li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
    <li>
        <i class="fa fa-chevron-right fa-fw"></i>
        <?php if(count(array_intersect(array('admin','moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) : ?>
        <a href="<?=$linker->link(array('index',$seminary['url']), 1)?>"><?=_('Characters')?></a>
        <?php else : ?>
        <?=_('Characters')?>
        <?php endif ?>
    </li>
</ul>

<h1><?=_('Edit Character')?></h1>
<form method="post" action="" class="logreg">
    <?php if($validation !== true && !empty($validation)) : ?>
    <ul class="validation">
        <?php foreach($validation as $field => &$settings) : ?>
        <li>
            <ul>
                <?php foreach($settings as $setting => $value) : ?>
                <li>
                    <?php switch($field) {
                        case 'charactername':
                            switch($setting) {
                                case 'minlength': printf(_('Character name is too short (min. %d chars)'), $value);
                                break;
                                case 'maxlength': printf(_('Character name is too long (max. %d chars)'), $value);
                                break;
                                case 'regex': echo _('Character name contains illegal characters');
                                break;
                                case 'exist': echo _('Character name already exists');
                                break;
                                default: echo _('Character name invalid');
                            }
                        break;
                        case 'gender':
                            switch($setting) {
                                case 'correct': echo _('Please select a gender');
                                break;
                            }
                        break;
                    } ?>
                </li>
                <?php endforeach ?>
            </ul>
        </li>
        <?php endforeach ?>
    </ul>
    <?php endif ?>
    <fieldset>
        <legend class="fwb"><?=_('Character properties')?></legend>
        <label for="charactername"><?=_('Character name')?>:</label>
        <?php if(count(array_intersect(array('admin','moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) : ?>
        <input type="text" name="charactername" placeholder="<?=_('Character name')?>" required="required" value="<?=$charactername?>" maxlength="<?=$validationSettings['charactername']['maxlength']?>" <?=(array_key_exists('charactername', $validation)) ? 'class="invalid"' : null ?>/>
        <?php else : ?>
        <input type="text" name="charactername" placeholder="<?=_('Character name')?>" disabled="disabled" value="<?=$charactername?>" />
        <input type="hidden" name="charactername" value="<?=$charactername?>" />
        <?php endif ?><br />
        <ul class="avatar">
            <?php foreach($types as &$type) : ?>
            <li>
                <label for="type-<?=$type['id']?>">
                    <p><?=$type['name']?></p>
                    <img id="avatar" src="<?=$linker->link(array('media','avatar',$seminary['url'],$type['url'],$xplevels[0]['level'],'portrait'))?>" />
                </label>
                <?php if(count(array_intersect(array('admin','moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) : ?>
                <input id="type-<?=$type['id']?>" name="type" type="radio" value="<?=$type['url']?>" <?php if(array_key_exists('selected', $type) && $type['selected']) : ?>checked="checked"<?php endif ?> />
                <?php else : ?>
                <input id="type-<?=$type['id']?>" name="type" type="radio" disabled="disabled" value="<?=$type['url']?>" <?php if(array_key_exists('selected', $type) && $type['selected']) : ?>checked="checked"<?php endif ?> />
                <?php if(array_key_exists('selected', $type) && $type['selected']) : ?>
                <input name="type" type="hidden" value="<?=$type['url']?>" />
                <?php endif ?>
                <?php endif ?>
            </li>
            <?php endforeach ?>
        </ul>
        <label for="gender"><?=_('Gender')?>:</label>
        <select id="gender" name="gender">
            <option value=""><?=_('Select gender')?></option>
            <option value="0" <?php if($gender === 0) : ?>selected="selected"<?php endif ?>><?=_('Female')?></option>
            <option value="1" <?php if($gender === 1) : ?>selected="selected"<?php endif ?>><?=_('Male')?></option>
        </select>
    </fieldset>

<?php if(count($titles) > 0) : ?>
    <fieldset>
        <legend><?=_('Display settings')?></legend>
<?php if(count($titles) > 0) : ?>
        <label><?=_('Charactertitle')?></label>
        <select id="title" name="title">
            <option value="" <?php if(is_null($charactertitle)) : ?>selected="selected"<?php endif ?>><?=_('no title')?></option>
<?php foreach($titles as &$title) : ?>
            <option value="<?=$title['id']?>" <?php if(!is_null($charactertitle) && $title['id'] == $charactertitle['id']) : ?>selected="selected"<?php endif ?>><?=($gender) ? $title['title_male'] : $title['title_female']?></option>
<?php endforeach ?>
        </select>
<?php endif ?>
    </fieldset>
<?php endif ?>
    
    <?php if($fieldsValidation !== true) : ?>
    <ul>
        <?php foreach($fieldsValidation as $field => &$settings) : ?>
        <li><?=sprintf(_('The Seminary field “%s” is invalid'), $field)?></li>
        <?php endforeach ?>
    </ul>
    <?php endif ?>
    <fieldset>
        <legend class="fwb"><?=_('Seminary fields')?></legend>
        <?php foreach($fields as &$field) : ?>
        <label for="fields[<?=$field['url']?>]"><?=$field['title']?>:</label>
        <?php switch($field['type_title']) {
            case 'Number':
            case 'Varchar': ?>
                <input type="text" name="fields[<?=$field['url']?>]" pattern="<?=(!empty($field['regex'])) ? substr($field['regex'],1,strrpos($field['regex'],$field['regex'][0])-1) : ''?>" <?php if(array_key_exists('uservalue', $field)) : ?>value="<?=$field['uservalue']?>"<?php endif ?> <?php if($field['required']) : ?>required="required"<?php endif ?>/>
            <?php break;
            case 'Text': ?>
                <textarea name="fields[<?=$field['url']?>]"><?=(array_key_exists('uservalue', $field) ? $field['uservalue'] : null)?></textarea>
            <?php break;
            case 'List': ?>
                <select name="fields[<?=$field['url']?>]">
                    <?php foreach(explode('|', substr($field['regex'],1,strrpos($field['regex'],$field['regex'][0])-1)) as $option) : ?>
                    <option value="<?=mb_eregi_replace('\\\\','',$option)?>" <?php if(array_key_exists('uservalue', $field) && $field['uservalue'] == mb_eregi_replace('\\\\','',$option)) : ?>selected="selected"<?php endif ?>><?=mb_eregi_replace('\\\\','',$option)?></option>
                    <?php endforeach?>
                </select>
            <?php break;
        } ?>
        <br />
        <?php endforeach ?>
    </fieldset>
    <input type="submit" name="edit" value="<?=_('edit')?>" />
</form>
