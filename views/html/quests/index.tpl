<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminarymoodpic',$seminary['url']))?>">
</div>
<?php endif ?>
<ul class="breadcrumbs">
	<li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
</ul>
<h1><?=_('Quests')?></h1>

<form method="post" class="logreg admnqf">
	<fieldset>
		<legend>Filter</legend>
		<label for="filters[questgroup]"><?=_('Questgroup')?>:</label>
		<select name="filters[questgroup]">
			<option value="0">alle</option>
			<?php foreach($filters['questgroups'] as &$filter) : ?>
			<option value="<?=$filter['id']?>" <?php if($filter['id'] == $selectedFilters['questgroup']) : ?>selected="selected"<?php endif ?>><?=$filter['title']?></option>
			<?php endforeach ?>
		</select><br />
		<label for="filters[questtype]"><?=_('Questtype')?>:</label>
		<select name="filters[questtype]">
			<option value="">alle</option>
			<?php foreach($filters['questtypes'] as &$filter) : ?>
			<option value="<?=$filter['classname']?>" <?php if($filter['classname'] == $selectedFilters['questtype']) : ?>selected="selected"<?php endif ?>><?=$filter['title']?></option>
			<?php endforeach ?>
		</select>
	</fieldset>
	<input type="submit" name="filter" value="<?=_('Apply filters')?>" />
	<input type="submit" name="reset" value="<?=_('Reset filters')?>" />
</form>

<ul class="admnql">
	<?php foreach($quests as &$quest) : ?>
	<li>
		<p class="fwb"><a href="<?=$linker->link(array('quest',$seminary['url'],$quest['questgroup']['url'],$quest['url']),1)?>"><?=$quest['title']?></a><span><a href="<?=$linker->link(array('submissions',$seminary['url'],$quest['questgroup']['url'],$quest['url']),1)?>"><?=$quest['opensubmissionscount']?> open submissions</a></span></p>
		<p><small><?=$quest['questtype']['title']?>, <?=sprintf(_('%d XPs'), $quest['xps'])?></small></p>
		<p><small><a href="<?=$linker->link(array('questgroups','questgroup',$seminary['url'],$quest['questgroup']['url']))?>"><?=$quest['questgroup']['title']?></a></small></p>
	</li>
	<?php endforeach ?>
</ul>
