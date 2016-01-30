<div class="moodpic">
    <img src="<?=$linker->hardlink('/grafics/questlab.jpg')?>" />
</div>
<ul class="breadcrumbs">
    <li><a href="<?=$linker->link(null,3)?>"><?=$page['title']?></a></li>
</ul>

<h1><?=_('Edit page')?></h1>
<?php if($validation !== true && !empty($validation)) : ?>
<ul class="validation">
    <?php foreach($validation as $field => &$settings) : ?>
    <li>
        <ul>
            <?php foreach($settings as $setting => $value) : ?>
            <li>
                <?php switch($field) {
                    case 'title':
                        switch($setting) {
                            case 'minlength': printf(_('Title is too short (min. %d chars)'), $value);
                            break;
                            case 'maxlength': printf(_('Title is too long (max. %d chars)'), $value);
                            break;
                            case 'regex': echo _('Title contains illegal characters');
                            break;
                            case 'exist': echo _('Title already exists');
                            break;
                            default: echo _('Title invalid');
                        }
                    break;
                    default:
                        echo $exception->getMessage();
                    break;
                } ?>
            </li>
            <?php endforeach ?>
        </ul>
    </li>
    <?php endforeach ?>
</ul>
<?php endif ?>
<form method="post">
    <fieldset>
        <label for="title"><?=_('Title')?>:</label>
        <input id="title" name="title" type="text" placeholder="<?=_('Title')?>" title="<?=_('Title')?>" required="required" maxlength="<?=$validationSettings['title']['maxlength']?>" value="<?=$title?>" <?=(array_key_exists('title', $validation)) ? 'class="invalid"' : null?> /><br />
    </fieldset>
    <fieldset>
        <legend><?=_('Text')?></legend>
        <textarea id="text" name="text"><?=$text?></textarea>
    </fieldset>
    <input type="submit" name="save" value="<?=_('save')?>" />
</form>
<script>
    $(function() {
        $("#text").markItUp(mySettings);
    });
</script>
