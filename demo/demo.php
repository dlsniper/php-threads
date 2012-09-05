<?php

error_reporting(E_ALL & E_STRICT);

echo "We can run at most " . getThreadsMaxCount() . " threads" . PHP_EOL;

runThreads(3);

runThreads(5);

