<?php

    /**
     * NRE
     *
     * @author      coderkun <olli@coderkun.de>
     * @copyright   2013 coderkun (http://www.coderkun.de)
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        http://www.coderkun.de/projects/nre
     */

    // Include required classes
    require_once(ROOT.DS.'configs'.DS.'CoreConfig.inc');
    require_once(ROOT.DS.\nre\configs\CoreConfig::getClassDir('core').DS.'Autoloader.inc');


    // Set PHP-logging
    ini_set('error_log', ROOT.DS.\nre\configs\CoreConfig::getClassDir('logs').DS.'php'.\nre\configs\CoreConfig::getFileExt('logs'));

    // Register autoloader
    \nre\core\Autoloader::register();


    // Initialize WebApi
    $webApi = new \nre\apis\WebApi();

    // Run WebApi
    $webApi->run();

    // Render output
    $webApi->render();

?>
