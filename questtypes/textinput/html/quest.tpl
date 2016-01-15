<form method="post" class="textinput">
    <?php $text = $t->t($task['text']); ?>
    <?php $posStart = 0; ?>
    <?php foreach($fields as &$field) : ?>
    <?php $posEnd = mb_strpos($text, '[textinput]', $posStart, 'UTF-8'); ?>
    <?=mb_substr($text, $posStart, $posEnd-$posStart, 'UTF-8')?>
    <input type="text" name="answers[]" value="<?=(array_key_exists('answer', $field)) ? $field['answer'] : ''?>" <?php if($field['size'] != 'default') : ?>class="<?=$field['size']?>"<?php endif ?> />
    <?php $posStart = $posEnd + mb_strlen('[textinput]', 'UTF-8'); ?>
    <?php endforeach ?>
    <?=mb_substr($text, $posStart, mb_strlen($text, 'UTF-8')-$posStart, 'UTF-8')?>

    <?php if(!is_null($nCorrectAnswers)) : ?>
    <p><?=sprintf(_('You filled %d of %d fields correctly'), $nCorrectAnswers, count($fields))?>.</p>
    <?php endif ?>
    <input type="submit" name="submit" value="<?=_('solve')?>" />
</form>
