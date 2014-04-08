<h1><?=_('Seminaries')?></h1>
<nav>
	<li><a href="<?=$linker->link('create', 1)?>"><?=_('Create new seminary')?></a></li>
</nav>
<ul>
	<?php foreach($seminaries as &$seminary) : ?>
	<li>
		<?php if(array_key_exists('media', $seminary)) : ?>
		<img src="<?=$linker->link(array('media','index',$seminary['media']['url']))?>" />
		<?php endif ?>
		<h2><a href="<?=$linker->link(array('seminary', $seminary['url']), 1)?>"><?=$seminary['title']?></a></h2>
		<details>
			<summary><?=sprintf(_('created by %s on %s'), $seminary['creator']['username'], $dateFormatter->format(new \DateTime($seminary['created'])))?></summary>
		</details>
	</li>
	<?php endforeach ?>
</ul>
