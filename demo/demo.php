<?php

error_reporting(E_ALL & E_STRICT);

echo "We can run at most " . getThreadsMaxCount() . " threads<br/>" . PHP_EOL;

runThreads(3, function(){
    echo 'gigel';
});

runThreads(5, function(){
    $result = rand(1, 1000);
    echo 'ion #' . $result . "<br/>";
});

