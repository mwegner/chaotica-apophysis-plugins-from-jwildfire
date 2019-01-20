<?php

/* build our JW variations from scratch */
$pathBuildProject = realpath("../ApoPluginCompile");

`RD /S /Q output`;
mkdir("output");

`RD /S /Q stubs`;
mkdir("stubs");

`php convert.php`;

`php overrides.php`;

// do actual compile, first pass
`del ..\\ApoPluginCompile\\plugin_source\\*.cpp`;
`copy output\\*.* ..\\ApoPluginCompile\\plugin_source\\`;
chdir("../ApoPluginCompile");
`psexec build.cmd`;

// scrub build directory
chdir(__DIR__);
`RD /S /Q build`;
mkdir("build");

// move first past files to here
chdir(__DIR__);
chdir("build");
mkdir("x64_first");
mkdir("x86_first");
$files = glob("{$pathBuildProject}/x64/*.dll");
foreach($files as $file)
{
	$name = basename($file);
	copy($file, "x64_first/{$name}");
}
$files = glob("{$pathBuildProject}/x86/*.dll");
foreach($files as $file)
{
	$name = basename($file);
	copy($file, "x86_first/{$name}");
}

chdir(__DIR__);

// do second compile, stubs
`del ..\\ApoPluginCompile\\plugin_source\\*.cpp`;
`copy stubs\\*.* ..\\ApoPluginCompile\\plugin_source\\`;
chdir("../ApoPluginCompile");
`psexec build.cmd`;

// move first past files to here
chdir(__DIR__);
chdir("build");
mkdir("x64_stubs");
mkdir("x86_stubs");
$files = glob("{$pathBuildProject}/x64/*.dll");
foreach($files as $file)
{
	$name = basename($file);
	copy($file, "x64_stubs/{$name}");
}
$files = glob("{$pathBuildProject}/x86/*.dll");
foreach($files as $file)
{
	$name = basename($file);
	copy($file, "x86_stubs/{$name}");
}

// verbatim files
chdir(__DIR__);
chdir("build");
mkdir("x64_verbatim");
mkdir("x86_verbatim");
$files = glob(__DIR__ . "/wf_dlls/x64/*.dll");
foreach($files as $file)
{
	$name = basename($file);
	copy($file, "x64_verbatim/{$name}");
}

chdir(__DIR__);
chdir("build");

$plugins = CollectPlugins("x64");
CollectPlugins("x86");

chdir(__DIR__);
chdir("build");

ksort($plugins);

// make release notes
$release = file_get_contents(__DIR__ . "/templates/release.md");
$list = "";
$totals = array();
foreach($plugins as $plugin => $origin)
{
	@$totals[$origin]++;

	if($origin == "empty_stub")
		$plugin = "~~{$plugin}~~";

	if($origin == "original")
		$plugin = "**{$plugin}**";

	if($origin == "missing")
		$plugin = "*~~{$plugin}~~*";
	
	$origin = "*{$origin}*";

	$list .= "| {$plugin} | {$origin} |\n";
}

$working = $totals['auto_convert'] + $totals['manual_convert'] + $totals['original'] + $totals['verbatim'];

arsort($totals);
$counts = "";

foreach($totals as $origin => $total)
{
	if($origin == "empty_stub")
		$origin = "~~{$origin}~~";

	if($origin == "original")
		$origin = "**{$origin}**";

	if($origin == "missing")
		$origin = "*~~{$origin}~~*";

	$counts .= "| {$total} | {$origin} |\n";
}

$release = str_replace("%WORKING%", $working, $release);
$release = str_replace("%COUNTS%", $counts, $release);
$release = str_replace("%PLUGINS%", $list, $release);

file_put_contents("release.md", $release);

function CollectPlugins($platform)
{
	// create final directory
	chdir(__DIR__);
	chdir("build");
	mkdir($platform);

	// build up an index of final plugin sources for better docs
	$plugins = array();

	// start with java files
	$files = glob('C:\Users\Matthew\Downloads\JWildfire-master/src/org/jwildfire/create/tina/variation/*.java', GLOB_BRACE);
	foreach($files as $file)
	{
		$java = file_get_contents($file);

		// use name of variation
	    if(preg_match('/public\sString\sgetName\(\)\s{[\s\n\t\r]+return\s"(\w+)"/m', $java, $matches))
	    {
	    	$name = $matches[1];

	    	if(in_array($name, ["glsl_", "_slice_indicator_wf"]))
	    	{
	    		continue;
	    	}

	        $plugins[$name] = "missing";
	    }
	}

	$files = glob("{$platform}_stubs/*.dll");
	foreach($files as $file)
	{
		$name = basename($file);
		copy($file, "{$platform}/{$name}");

		$parts = explode(".", $name);
		$plugin = $parts[0];

		$plugins[$plugin] = "empty_stub";
	}

	$files = glob("{$platform}_first/*.dll");
	foreach($files as $file)
	{
		$name = basename($file);
		copy($file, "{$platform}/{$name}");

		$parts = explode(".", $name);
		$plugin = $parts[0];

		$type = "auto_convert";

		// was this an override?
		$override = __DIR__ . "/override/{$plugin}.cpp";
		if(file_exists($override))
		{
			$code = file_get_contents($override);
			if(preg_match("/APO_VARIABLE_PREFIX/", $code))
			{
				$type = "manual_convert";
			}
			else
			{
				$type = "original";
			}
		}

		$plugins[$plugin] = $type;
	}

	$files = glob("{$platform}_verbatim/*.dll");
	foreach($files as $file)
	{
		$name = basename($file);
		copy($file, "{$platform}/{$name}");

		$parts = explode(".", $name);
		$plugin = $parts[0];

		$plugins[$plugin] = "verbatim";
	}

	$list = "";
	foreach($plugins as $plugin => $type)
	{
		$list .= "$type\t$plugin\r\n";
	}
	
	file_put_contents("{$platform}/_list.txt", $list);

	`RD /S /Q {$platform}_first`;
	`RD /S /Q {$platform}_stubs`;
	`RD /S /Q {$platform}_verbatim`;

	// final rename with JW prefix
	$files = glob("{$platform}/*.dll");
	foreach($files as $file)
	{
		$rename = str_replace(".dll", ".jwmod.dll", $file);
		rename($file, $rename);
	}

	chdir($platform);
	`"c:\\Program Files\\7-Zip\\7z.exe" a ..\\chaotica-jwildfire-plugins-{$platform}.zip *`;

	return $plugins;
}

