<div class="moodpic">
	<img src="http://s1.directupload.net/images/140323/tpzvoy5c.png">
</div>

<?=$questgroupspicture?>
<h2><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></h2>

<?=$questgroupshierarchypath?>

<?php if(!is_null($questgroup['hierarchy'])) : ?>
<h3><?=$questgroup['hierarchy']['title_singular']?> <?=$questgroup['hierarchy']['questgroup_pos']?>: <?=$questgroup['title']?></h3>
<?php else : ?>
<h3><?=$questgroup['title']?></h3>
<?php endif ?>
<?php foreach($texts as &$text) : ?>
<p><?=\hhu\z\Utils::t($text['text'])?></p>
<?php endforeach ?>

<?php if(!is_null($childquestgroupshierarchy)) : ?>
<?php foreach($childquestgroupshierarchy as &$hierarchy) : ?>
<?php if(count($hierarchy['questgroups']) > 0) : ?>
<h3><?=$hierarchy['title_plural']?></h3>
<ul class="qg">
	<?php foreach($hierarchy['questgroups'] as &$group) : ?>
	<li class="cf">
		<?php if(!array_key_exists('access', $group) || $group['access']) : ?>
		<span class="qgicon"><i class="fa fa-check-square-o"></i></span>
		<div class="qgtitle"><a href="<?=$linker->link(array('questgroups','questgroup',$seminary['url'],$group['url']))?>"><?=$group['title']?></a></div>
		<div class="qgprogress cf">
			<p class="xpinfo">Fortschritt:</p>
			<div class="xpbar">
				<span style="width:<?=round($group['character_xps']/$group['xps']*100)?>%"></span>
			</div>
			<p class="xpnumeric"><?=$group['character_xps']?> / <?=$group['xps']?> XP</p>
		</div>
		<?php else : ?>
		<span class="qgicon locked"><i class="fa fa-square-o"></i></span>
		<div class="qgtitle"><?=$hierarchy['title_singular']?> <?=_('locked')?></div>
		<?php endif ?>
	</li>
	<?php endforeach?>
</ul>
<?php endif ?>
<?php endforeach ?>
<?php endif ?>

<?php if(isset($quests) && !is_null($quests)) : ?>
<h3><?=_('Quests')?></h3>
<ul class="qglist">
	<?php foreach($quests as &$quest) : ?>
	<li class="qgtitle">
		<?php if(!array_key_exists('access', $quest) || $quest['access']) : ?>
		<a href="<?=$linker->link(array('quests','quest',$seminary['url'],$questgroup['url'],$quest['url']))?>" <?php if($quest['solved']) : ?>class="solved"<?php endif ?>><i class="fa <?=($quest['solved']) ? 'fa-check-square-o' : 'fa-share-square-o'?> fa-fw"></i><?=$quest['title']?></a>
		<?php if(count($quest['relatedQuestgroups']) > 0) : ?>
		<ul class="gplist">
			<?php foreach($quest['relatedQuestgroups'] as &$relatedQuestgroup) : ?>
			<li class="qgtitle">
				<a href="<?=$linker->link(array('questgroups','questgroup',$seminary['url'],$relatedQuestgroup['url']))?>" class="bonus"><i class="fa fa-share-square-o fa-fw"><?=$relatedQuestgroup['title']?></i></a>
			</li>
			<?php endforeach ?>
		</ul>
		<?php endif ?>
		<?php else : ?>
		<i class="fa fa-share-square-o fa-fw"><?=_('locked')?></i>
		<?php endif ?>
	</li>
	<?php endforeach ?>
</ul>
<?php endif ?>
