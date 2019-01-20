<?php
/*

quick tag over overrides with plugin warning

*/

$files = glob('override/*', GLOB_BRACE);
foreach($files as $file)
{
    $code = file_get_contents($file);

    $code = "#define PLUGIN_WARNING \"NOTE_modded_for_jwildfire_workflow\"\n$code";

    $filename = basename($file);

    file_put_contents("output/{$filename}", $code);

    print "Overwrote: {$filename}\n";   
}