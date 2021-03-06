<?php

    /**
     * Questlab
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 – 2016 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://github.com/coderkun/questlab
     */

    namespace hhu\z;


    /**
     * Abstract class for implementing an application Controller.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    abstract class Controller extends \nre\core\Controller
    {
        /**
         * Required components
         *
         * @var array
         */
        public $components = array('auth');

        /**
         * Logger instance
         *
         * @var \nre\core\Logger
         */
        protected $log = null;
        /**
         * Linker instance
         *
         * @var \nre\core\Linker
         */
        protected $linker = null;




        /**
         * Construct a new application Controller.
         *
         * @throws  \nre\exceptions\DriverNotFoundException
         * @throws  \nre\exceptions\DriverNotValidException
         * @throws  \nre\exceptions\ModelNotValidException
         * @throws  \nre\exceptions\ModelNotFoundException
         * @throws  \nre\exceptions\ViewNotFoundException
         * @param   string      $layoutName Name of the current Layout
         * @param   string      $action     Current Action
         * @param   \nre\core\Agent $agent      Corresponding Agent
         */
        public function __construct($layoutName, $action, $agent)
        {
            parent::__construct($layoutName, $action, $agent);

            // Create logger
            $this->log = new \nre\core\Logger();
        }



        /**
         * Prefilter that is executed before running the Controller.
         *
         * @param   \nre\core\Request   $request    Current request
         * @param   \nre\core\Response  $response   Current response
         */
        public function preFilter(\nre\core\Request $request, \nre\core\Response $response)
        {
            parent::preFilter($request, $response);

            // Create linker
            $this->linker = new \nre\core\Linker($request);
            $this->set('linker', $this->linker);

            // Create text formatter
            $this->set('t', new \hhu\z\TextFormatter($this->linker));

            // Create date and time and number formatter
            $this->set('dateFormatter', new \IntlDateFormatter(
                //\nre\core\Config::getDefault('locale'),
                \Locale::getDefault(),
                \IntlDateFormatter::MEDIUM,
                \IntlDateFormatter::NONE,
                NULL
            ));
            $this->set('timeFormatter', new \IntlDateFormatter(
                //\nre\core\Config::getDefault('locale'),
                \Locale::getDefault(),
                \IntlDateFormatter::NONE,
                \IntlDateFormatter::SHORT,
                NULL
            ));
            $this->set('numberFormatter', new \NumberFormatter(
                //\nre\core\Config::getDefault('locale'),
                \Locale::getDefault(),
                \NumberFormatter::DEFAULT_STYLE
            ));
        }


        /**
         * Postfilter that is executed after running the Controller.
         *
         * @param   \nre\core\Request   $request    Current request
         * @param   \nre\core\Response  $response   Current response
         */
        public function postFilter(\nre\core\Request $request, \nre\core\Response $response)
        {
            parent::postFilter($request, $response);
        }




        /**
         * Log an error.
         *
         * @param   string  $message    Error message to log
         * @param   int $logMode    Log mode (optional)
         */
        protected function log($message, $logMode=\nre\core\Logger::LOGMODE_AUTO)
        {
            $this->log->log($message, $logMode);
        }

    }

?>
