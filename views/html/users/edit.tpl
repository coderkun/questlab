<h2><?=_('Users')?></h2>
<h3><?=_('Edit user')?></h3>

<form method="post">
	<fieldset>
		<label for="username"><?=_('Username')?>:</label>
		<input type="text" name="username" placeholder="<?=_('Username')?>" value="<?=$user['username']?>" /><br />
		<label for="email"><?=_('E‑Mail-Address')?>:</label>
		<input type="email" name="email" placeholder="<?=_('E‑Mail-Address')?>" value="<?=$user['email']?>" /><br />
		<label for="password"><?=_('Password')?>:</label>
		<input type="password" name="password" placeholder="<?=_('Password')?>" /><br />
	</fieldset>
	<input type="submit" name="save" value="<?=_('save')?>" />
</form>
