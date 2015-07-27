<?php if(!is_null($picture)) : ?>
<div class="moodpic">
    <img src="<?=$linker->link(array('media','seminary',$seminary['url'],$picture['url']))?>" />
</div>
<?php else: ?>
<?=$moodpic?>
<?php endif ?>
<?=$questgroupshierarchypath?>

<?php if(!is_null($questgroup['hierarchy'])) : ?>
<h1><?=$questgroup['hierarchy']['title_singular']?> <?=$questgroup['hierarchy']['questgroup_pos']?>: <?=$questgroup['title']?></h1>
<?php else : ?>
<h1><?=$questgroup['title']?></h1>
<?php endif ?>

<h1><?=_('Move Questgroup')?></h1>
<?=sprintf(_('Should the Questgroup “%s” really be moved?'), $questgroup['title'])?>
<form method="post">
    <input type="submit" name="move" value="<?=_('move')?>" />
    <input type="submit" name="not-move" value="<?=_('cancel')?>" />
</form>
