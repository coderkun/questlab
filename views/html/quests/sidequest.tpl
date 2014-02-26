<h1><?=_('Seminaries')?></h1>
<h2><?=$seminary['title']?></h2>

<?=$questgroupshierarchypath?>
<?=$questgroupspicture?>

<h3><a href="<?=$linker->link(array('quest',$seminary['url'],$questgroup['url'],$quest['url'],$questtext['type_url'],$questtext['pos']),1)?>"><?=$quest['title']?></a></h3>
<h4><?=$sidequest['title']?></h4>
<p><?=_('This Quest is optional')?>.</p>
<?php if(!is_null($media)) : ?>
<img src="<?=$linker->link(array('media','index',$seminary['url'],$media['url']))?>" />
<?php endif ?>
<section>
	<?php if($sidequesttext['type'] == 'solved') : ?>
	<h1><?=_('solved')?></h1>
	<?php elseif($sidequesttext['type'] == 'unsolved') : ?>
	<h1><?=_('unsolved')?></h1>
	<?php else : ?>
	<h1><?=$sidequesttext['type']?></h1>
	<?php endif ?>
	<p><?=\hhu\z\Utils::t($sidequesttext['text'])?></p>
	
	<?php if(array_key_exists('out_text', $sidequesttext) && !empty($sidequesttext['out_text'])) : ?>
	<?php if(array_key_exists('abort_text', $sidequesttext) && !empty($sidequesttext['abort_text'])) : ?>
	<ul>
		<li><a href="<?=$linker->link(array('quest',$seminary['url'],$questgroup['url'],$quest['url'],$questtext['type_url'],$questtext['pos']),1)?>"><?=$sidequesttext['abort_text']?></a></li>
		<li><a href="<?=$linker->link(array($sidequesttext['type_url'],$sidequesttext['pos']+1),6)?>"><?=$sidequesttext['out_text']?></a></li>
	</ul>
	<?php else : ?>
	<a href="<?=$linker->link($sidequesttext['pos']+1, 7)?>"><?=$sidequesttext['out_text']?></a><br />
	<?php endif ?>
	<?php endif ?>
	
	<?php if(array_key_exists('pos', $sidequesttext)) : ?>
	<?php if($sidequesttext['pos'] > 1) : ?><a href="<?=$linker->link(array($sidequesttext['type_url'],$sidequesttext['pos']-1),6)?>">&lt;</a><?php endif ?>
	<?=$sidequesttext['pos']?>/<?=$sidequesttext['count']?>
	<?php if($sidequesttext['pos'] < $sidequesttext['count'] && empty($sidequesttext['out_text'])) : ?><a href="<?=$linker->link(array($sidequesttext['type_url'],$sidequesttext['pos']+1),6)?>">&gt;</a><?php endif ?>
	<?php endif ?>
</section>

<?php if(!is_null($task)) : ?>
<section>
	<h1><?=_('Task')?></h1>
	<p><?=\hhu\z\Utils::t($sidequest['task'])?></p>
	<p><?=$task?></p>
</section>
<?php endif ?>
