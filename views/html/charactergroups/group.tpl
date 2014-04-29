<?php if(!is_null($seminary['charactergroups_seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminarymoodpic',$seminary['url'], 'charactergroups'))?>">
</div>
<?php endif ?>
<ul class="breadcrumbs">
	<li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
	<li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('index',$seminary['url']),1)?>"><?=_('Character Groups')?></a></li>
	<li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('groupsgroup',$seminary['url'],$groupsgroup['url']),1)?>"><?=$groupsgroup['name']?></a></li>
</ul>

<?php if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) : ?>
<nav class="admin">
	<li><a href="<?=$linker->link(array('editgroup',$seminary['url'],$groupsgroup['url'],$group['url']),1)?>"><?=_('Edit Character group')?></a></li>
	<li><a href="<?=$linker->link(array('deletegroup',$seminary['url'],$groupsgroup['url'],$group['url']),1)?>"><?=_('Delete Character group')?></a></li>
	<li><a href="<?=$linker->link(array('managegroup',$seminary['url'],$groupsgroup['url'],$group['url']),1)?>"><?=_('Manage Character group')?></a></li>
</nav>
<?php endif ?>

<div class="gbanner cf">
	<?php if(!is_null($group['seminaryupload_id'])) : ?>
	<img src="<?=$linker->link(array('uploads','charactergroup',$seminary['url'],$groupsgroup['url'],$group['url']))?>" class="gbanner">
	<?php else : ?>
	<img src="<?=$linker->link(array('grafics','charactergroup.jpg'))?>" class="gbanner">
	<?php endif ?>
	<h1><?=$group['name']?></h1>
	<p>"<?=$group['motto']?>"</p>
</div>
<ul class="gdata cf">
	<li><?=$group['rank']?>. <?=_('Rank')?></li>
	<li><?=$group['xps']?> XP</li>
	<li><?=count($group['characters'])?> <?=(count($group['characters']) == 0 || count($group['characters']) > 1) ? _('Members') : _('Member')?></li>
</ul>

<section>
	<h1><i class="fa fa-users fa-fw"></i><?=_('Characters')?></h1>
	<ul class="gchars cf">
		<?php foreach($group['characters'] as &$character) : ?>
		<li>
			<?php if(array_key_exists('small_avatar', $character)) : ?>
			<p><img src="<?=$linker->link(array('media','seminary',$seminary['url'],$character['small_avatar']['url']))?>"></p>
			<?php endif ?>
			<p><a href="<?=$linker->link(array('characters','character',$seminary['url'],$character['url']))?>"><?=$character['name']?></a></p>
			<p><small><?=$character['xps']?> XP</small></p>
		</li>
		<?php endforeach ?>
	</ul>
</section>

<section>
	<h1><i class="fa fa-pencil-square-o fa-fw"></i><?=sprintf(_('%s-Quests'),$groupsgroup['name'])?></h1>
	<ul class="gquests">
		<?php foreach($quests as &$quest) : ?>
		<li class="cf">
			<p>
				<span class="date"><?=$dateFormatter->format(new \DateTime($quest['created']))?></span>
				<a href="<?=$linker->link(array('charactergroupsquests','quest',$seminary['url'],$groupsgroup['url'],$quest['url']))?>" class="fwb"><?=$quest['title']?></a>
				<span class="xp"><?=$quest['group_xps']?> / <?=$quest['xps']?> XP</span>
			</p>
		</li>
		<?php endforeach ?>
	</ul>
</section>
