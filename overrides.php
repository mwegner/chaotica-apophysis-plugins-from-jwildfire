<?php
/*

quick tag over overrides with plugin warning

*/

$files = glob('override/*', GLOB_BRACE);
foreach($files as $file)
{
    $code = file_get_contents($file);

    $code = preg_replace('/^}\sVariables;/m', "\tint ___warning;\n} Variables;", $code);
    $code = preg_replace('/^\);/m', "\t{ \"WARNING_modified_for_JW_workflow\", INTEGER, OFFSET(___warning), 0, 1, 0 },\n);", $code);


    $filename = basename($file);

    file_put_contents("output/{$filename}", $code);

    print "Overwrote: {$filename}\n";   
}