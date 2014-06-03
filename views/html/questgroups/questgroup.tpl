<?php if(!is_null($picture)) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminary',$seminary['url'],$picture['url']))?>" />
</div>
<?php endif ?>
<?=$questgroupshierarchypath?>

<?php if(!is_null($questgroup['hierarchy'])) : ?>
<h1><?=$questgroup['hierarchy']['title_singular']?> <?=$questgroup['hierarchy']['questgroup_pos']?>: <?=$questgroup['title']?></h1>
<?php else : ?>
<h1><?=$questgroup['title']?></h1>
<?php endif ?>
<?php if(count($texts) > 0): ?>
<div class="qtextbox">
<?php foreach($texts as &$text) : ?>
<p class="qtext"><?=\hhu\z\Utils::t($text['text'])?></p>
<?php endforeach ?>
</div>
<?php endif ?>

<?php if(!is_null($childquestgroupshierarchy)) : ?>
<?php foreach($childquestgroupshierarchy as $hierarchyIndex => &$hierarchy) : ?>
<?php if(count($hierarchy['questgroups']) > 0 || count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) : ?>
<h3><?=$hierarchy['title_plural']?></h3>
<?php if(in_array('admin', \hhu\z\controllers\SeminaryController::$character['characterroles'])) : ?>
<nav class="admin">
	<li><a href="<?=$linker->link(array('questgroupshierarchy','edit',$seminary['url'],$hierarchy['url']))?>"><?=_('Edit Questgroupshierarchy')?></a></li>
	<li><a href="<?=$linker->link(array('questgroupshierarchy','delete',$seminary['url'],$hierarchy['url']))?>"><?=_('Delete Questgroupshierarchy')?></a></li>
	<?php if($hierarchyIndex > 0) : ?><li><a href="<?=$linker->link(array('questgroupshierarchy','moveup',$seminary['url'],$hierarchy['url']),0,true,array('referer'=>$questgroup['id']))?>">↑</a></li><?php endif ?>
	<?php if($hierarchyIndex < count($childquestgroupshierarchy)-1) : ?><li><a href="<?=$linker->link(array('questgroupshierarchy','movedown',$seminary['url'],$hierarchy['url']),0,true,array('referer'=>$questgroup['id']))?>">↓</a></li><?php endif ?>
</nav>
<?php endif ?>
<ul class="qg">
	<?php foreach($hierarchy['questgroups'] as &$group) : ?>
	<li class="cf">
		<span class="qgicon">
		<?php if($group['solved']) : ?>
		<i class="fa fa-check-square-o"></i>
		<?php else : ?>
		<i class="fa fa-square-o"></i>
		<?php endif ?>
		</span>
		<div class="qgtitle"><a href="<?=$linker->link(array('questgroups','questgroup',$seminary['url'],$group['url']))?>"><?=$group['title']?></a></div>
		<div class="qgprogress cf">
			<p class="xpinfo">Fortschritt:</p>
			<div class="xpbar">
				<span style="width:<?=round($group['character_xps']/$group['achievable_xps']*100)?>%"></span>
			</div>
			<p class="xpnumeric"><?=$group['character_xps']?> / <?=$group['achievable_xps']?> XP</p>
		</div>
		<?php foreach($group['relatedQuestgroups'] as &$relatedGroup) : ?>
		<div class="qghidden">
			<p><?=_('Found optional Questline')?>:</p>
			<p><a href="<?=$linker->link(array($seminary['url'],$relatedGroup['url']),2)?>"><i class="fa fa-star-o fa-fw"></i><?=$relatedGroup['title']?></a></p>
		</div>
		<?php endforeach ?>
	</li>
	<?php endforeach?>
</ul>
<?php endif ?>
<?php endforeach ?>
<?php if(in_array('admin', \hhu\z\controllers\SeminaryController::$character['characterroles'])) : ?>
<form method="post" action="<?=$linker->link(array('questgroupshierarchy','create',$seminary['url']))?>">
	<h2><?=_('New Questgroupshierarchy')?></h2>
	<?=_('Title (singular)')?>: <input type="text" name="title_singular" placeholder="<?=_('Title (singular)')?>" />
	<?=_('Title (plural)')?>: <input type="text" name="title_plural" placeholder="<?=_('Title (plural)')?>" />
	<input type="hidden" name="parent" value="<?=$questgroup['hierarchy']['url']?>" />
	<input type="submit" name="create" value="<?=_('Add new Questgroupshierarchy')?>" />
</form>
<?php endif ?>
<?php endif ?>

<?php if(isset($quests) && !is_null($quests) && count($quests) > 0) : ?>
<h3><?=_('Quests')?></h3>
<ul class="qglist">
	<?php foreach($quests as &$quest) : ?>
	<li class="qgtitle">
		<a href="<?=$linker->link(array('quests','quest',$seminary['url'],$questgroup['url'],$quest['url']))?>" <?php if($quest['solved']) : ?>class="solved"<?php endif ?>><i class="fa <?=($quest['solved']) ? 'fa-check-square-o' : 'fa-square-o'?> fa-fw"></i><?=$quest['title']?></a>
	</li>
	<?php if(count($quest['relatedQuestgroups']) > 0) : ?>
		<?php foreach($quest['relatedQuestgroups'] as &$relatedQuestgroup) : ?>
		<li class="qgtitle">
			<a href="<?=$linker->link(array('questgroups','questgroup',$seminary['url'],$relatedQuestgroup['url']))?>" class="bonus"><i class="fa fa-share-square-o fa-fw"></i><?=$relatedQuestgroup['title']?></a>
		</li>
		<?php endforeach ?>
	<?php endif ?>
	<?php endforeach ?>
</ul>
<?php endif ?>
