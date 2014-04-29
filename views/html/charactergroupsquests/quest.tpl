<?php if(!is_null($seminary['charactergroups_seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminarymoodpic',$seminary['url'], 'charactergroups'))?>">
</div>
<?php endif ?>
<ul class="breadcrumbs">
	<li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
	<li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('charactergroups','index',$seminary['url']))?>"><?=_('Character Groups')?></a></li>
	<li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('charactergroups','groupsgroup',$seminary['url'],$groupsgroup['url']))?>"><?=$groupsgroup['name']?></a></li>
</ul>

<?php if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) : ?>
<nav class="admin">
	<li><a href="<?=$linker->link(array('edit',$seminary['url'],$groupsgroup['url'],$quest['url']),1)?>"><?=sprintf(_('Edit %s-Quest'), $groupsgroup['name'])?></a></li>
	<li><a href="<?=$linker->link(array('delete',$seminary['url'],$groupsgroup['url'],$quest['url']),1)?>"><?=sprintf(_('Delete %s-Quest'), $groupsgroup['name'])?></a></li>
</nav>
<?php endif ?>

<h1><?=$quest['title']?></h1>
<small><?=_('Maximum reward')?>: <span class="fwb"><?=$quest['xps']?> XP</span></small><br />
<small><?=_('Questgroup')?>: <?php if($questgroup['entered']) : ?><a href="<?=$linker->link(array('questgroups','questgroup',$seminary['url'],$questgroup['url']))?>"><?=$questgroup['title']?></a><?php else : ?><?=$questgroup['title']?><?php endif ?></small>

<section>
	<h1><i class="fa fa-envelope fa-fw"></i><?=_('Description')?></h1>
	<p>
	<?php if(!is_null($media)) : ?>
	<img src="<?=$linker->link(array('media','seminary',$seminary['url'],$media['url']))?>" class="grpqimg" />
	<?php endif ?>
	<?=\hhu\z\Utils::t($quest['description'])?>
	</p>
	<?php if(!empty($quest['rules'])) : ?>
	<h1><i class="fa fa-exclamation-triangle fa-fw"></i><?=_('Rules')?></h1>
	<p><?=\hhu\z\Utils::t($quest['rules'])?></p>
	<?php endif ?>
</section>

<?php if(!empty($quest['von_text'])) : ?>
<section>	
	<h1><i class="fa fa-thumbs-up fa-fw"></i><?=_('Won Quest')?></h1>
	<p><?=\hhu\z\Utils::t($quest['won_text'])?></p>
</section>
<?php endif ?>
<?php if(!empty($quest['lost_text'])) : ?>
<section>
	<h1><i class="fa fa-thumbs-down fa-fw"></i><?=_('Lost Quest')?></h1>
	<p><?=\hhu\z\Utils::t($quest['lost_text'])?></p>
</section>
<?php endif ?>

<section>
	<h1><i class="fa fa-users fa-fw"></i><?=$groupsgroup['name']?></h1>
	<ul class="grpqlist">
		<?php foreach($groups as &$group) : ?>
		<li>
			<span class="date"><?=$dateFormatter->format(new \DateTime($group['created']))?></span>
			<span class="group"><a href="<?=$linker->link(array('charactergroups','group',$seminary['url'],$groupsgroup['url'],$group['url']))?>"><?=$group['name']?></a></span>
			<span class="xp"><?=$group['xps']?> XP</span>
		</li>
		<?php endforeach ?>
	</ul>
</section>
