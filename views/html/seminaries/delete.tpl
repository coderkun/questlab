<h1><?=_('Seminaries')?></h1>
<h2><?=_('Delete seminary')?></h2>

<?=sprintf(_('Should the seminary “%s” really be deleted?'), $seminary['title'])?>
<form method="post">
	<input type="submit" name="delete" value="<?=_('delete')?>" />
	<input type="submit" name="not-delete" value="<?=_('cancel')?>" />
</form>
