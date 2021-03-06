<?php

    /**
     * NRE
     *
     * @author      coderkun <olli@coderkun.de>
     * @copyright   2013 coderkun (http://www.coderkun.de)
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        http://www.coderkun.de/projects/nre
     */

    /**
     * Define constants
     */
    // Directory separator
    if(!defined('DS')) {
        /**
         * @internal
         */
        define('DS', DIRECTORY_SEPARATOR);
    }
    // Root directory
    if(!defined('ROOT')) {
        /**
         * @internal
         */
        define('ROOT', dirname(dirname(__FILE__)));
    }


    /**
     * De-/Activate error messages
     */
    if($_SERVER['SERVER_ADDR'] == '127.0.0.1' || $_SERVER['SERVER_ADDR'] == '::1') {
        error_reporting(E_ALL);
        ini_set('display_errors', 1);
        ini_set('log_errors', 0);
    }
    else {
        error_reporting(E_ALL);
        ini_set('display_errors', 0);
        ini_set('log_errors', 1);
    }


    /**
     * Run application
     */
    require ROOT.DS.'bootstrap.inc';

?>
