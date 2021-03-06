<?=$moodpic?>
<ul class="breadcrumbs">
    <li><a href="<?=$linker->link('index',1)?>"><?=_('Seminaries')?></a></li>
</ul>

<h1><?=_('Edit seminary')?></h1>
<?php if($validation !== true && !empty($validation)) : ?>
<ul class="validation">
    <?php foreach($validation as $field => &$settings) : ?>
    <li>
        <ul>
            <?php foreach($settings as $setting => $value) : ?>
            <li>
                <?php switch($field) {
                    case 'moodpic':
                        switch($setting) {
                            case 'error': printf(_('Error during moodpic upload: %s'), $value);
                            break;
                            case 'mimetype': printf(_('Moodpic has wrong type “%s”'), $value);
                            break;
                            case 'size': echo _('Moodpic exceeds size maximum');
                            break;
                            default: echo _('Moodpic invalid');
                        }
                    break;
                    case 'title':
                        switch($setting) {
                            case 'minlength': printf(_('Title is too short (min. %d chars)'), $value);
                            break;
                            case 'maxlength': printf(_('Title is too long (max. %d chars)'), $value);
                            break;
                            case 'regex': echo _('Title contains illegal characters');
                            break;
                            case 'exist': echo _('Title already exists');
                            break;
                            default: echo _('Title invalid');
                        }
                    break;
                    case 'course':
                        switch($setting) {
                            case 'maxlength': printf(_('Course is too long (max. %d chars)'), $value);
                            break;
                            default: echo _('Course invalid');
                        }
                    break;
                } ?>
            </li>
            <?php endforeach ?>
        </ul>
    </li>
    <?php endforeach ?>
</ul>
<?php endif ?>
<form method="post" class="logreg" enctype="multipart/form-data">
    <fieldset>
        <legend><?=_('Moodpic')?></legend>
        <input type="file" name="moodpic" accept="<?=implode(',', array_map(function($m) { return $m['mimetype']; }, $mimetypes))?>" />
        <p><?=_('Allowed file types')?>:</p>
        <ul>
            <?php foreach($mimetypes as &$mimetype) : ?>
            <li><?=sprintf(_('%s-files'), strtoupper(explode('/',$mimetype['mimetype'])[1]))?> <?php if($mimetype['size'] > 0) : ?>(<?=_('max.')?> <?=round($mimetype['size']/(1024*1024),2)?> MiB)<?php endif ?></li>
            <?php endforeach ?>
        </ul>
    </fieldset>
    <fieldset>
        <label for="title"><?=_('Title')?>:</label>
        <input type="text" name="title" placeholder="<?=_('Title')?>" required="required" maxlength="<?=$validationSettings['title']['maxlength']?>" value="<?=$title?>" <?=(array_key_exists('title', $validation)) ? 'class="invalid"' : null?> /><br />
        <label for="course"><?=_('Course')?>:</label>
        <input type="text" name="course" placeholder="<?=_('Course')?>" maxlength="<?=$validationSettings['course']['maxlength']?>" value="<?=$course?>" <?=(array_key_exists('course', $validation)) ? 'class="invalid"' : null?> /><br />
        <label for="description"><?=_('Description')?>:<br />
        <textarea name="description" placeholder="<?=_('Description')?>"><?=$description?></textarea><br />
    </fieldset>
    <fieldset>
        <legend><?=_('Location')?></legend>
        <div id="map" class="map"></div>
        <input id="longitude" name="longitude" type="hidden" value="<?=$longitude?>" />
        <input id="latitude" name="latitude" type="hidden" value="<?=$latitude?>" />
    </fieldset>
    <input type="submit" name="edit" value="<?=_('edit')?>" />
</form>
<script>
    var drawSource = new ol.source.Vector({
        wrapX: false
    });
    var drawLayer = new ol.layer.Vector({
        source: drawSource,
        style: new ol.style.Style({
            text: new ol.style.Text({
                text: '\uf276',
                font: 'normal 28px FontAwesome',
                textBaseline: 'Bottom',
                fill: new ol.style.Fill({
                    color: '#0F373C'
                })
            })
        })
    });
    var map = new ol.Map({
        layers: [
            new ol.layer.Tile({
                source: new ol.source.OSM()
            }),
            drawLayer
        ],
        controls: ol.control.defaults(),
        target: 'map',
        view: new ol.View({
<?php if(!is_null($latitude) && !is_null($longitude)) : ?>
            center: ol.proj.transform([<?=$longitude?>, <?=$latitude?>], 'EPSG:4326', 'EPSG:3857'),
            zoom: 17,
<?php else : ?>
            center: [0, 0],
            zoom: 0,
<?php endif ?>
            maxZoom: 19
        })
    });
    var draw = new ol.interaction.Draw({
        source: drawSource,
        type: 'Point',
        maxPoints: 1,
    });
    map.addInteraction(draw);

    // Add existing point
    var longitude = $('#longitude').val();
    var latitude = $('#latitude').val();
    if(longitude && latitude) {
        drawSource.addFeature(
            new ol.Feature({
                geometry: new ol.geom.Point(
                    ol.proj.transform([parseFloat(longitude), parseFloat(latitude)], 'EPSG:4326', 'EPSG:3857')
                )
            })
        );
    }

    // Wire events
    drawSource.on('addfeature', function(event) {
        var coordinates = event.feature.getGeometry().getCoordinates();
        coordinates = ol.proj.transform(coordinates, 'EPSG:3857', 'EPSG:4326');
        $('#longitude').val(coordinates[0]);
        $('#latitude').val(coordinates[1]);
    });
    draw.on('drawstart', function() {
        drawSource.clear();
    });
</script>
