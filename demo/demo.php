<?php

error_reporting(E_ALL & E_STRICT);

echo "We can run at most " . getThreadsMaxCount() . " threads<br/>" . PHP_EOL;

$asd = rand(1, 10);

runThreads(3, function() use ($asd) {
    echo $asd . 'gigel <br/>';
}, $asd);

runThreads(5, function() use ($asd){
    $result = $asd;
    echo 'ion #' . $result . "<br/>";
});

