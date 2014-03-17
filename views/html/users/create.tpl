<h1><?=_('Users')?></h1>
<h2><?=_('New user')?></h2>

<form method="post" action="<?=$linker->link('create', 1)?>">
	<fieldset>
		<label for="username"><?=_('Username')?>:</label>
		<input type="text" name="username" placeholder="<?=_('Username')?>" /><br />
		<label for="email"><?=_('E‑Mail-Address')?>:</label>
		<input type="email" name="email" placeholder="<?=_('E‑Mail-Address')?>" /><br />
		<label for="password"><?=_('Password')?>:</label>
		<input type="password" name="password" placeholder="<?=_('Password')?>" /><br />
	</fieldset>
	<input type="submit" name="create" value="<?=_('create')?>" />
</form>
