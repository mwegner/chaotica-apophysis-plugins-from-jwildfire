
DOWNLOAD:
----------

Here for the plugins?  [Check the releases page](https://github.com/mwegner/chaotica-apophysis-plugins-from-jwildfire/releases).  I'd recommend using the full set together--it's easy to rename your `plugins` folder to something else to swap in and out.

JWILDFIRE:
----------

I've been using JW more and more for structure work, with Chaotica as my final render step.

If you completely normalize the variable names, you can paste directly into Chaotica, to avoid having to use the old JW 2.50 Chaotica Bridge integration.  The problem is, lots of plugins aren't named well for this.  JW saves out `plugin_variable`, and
Chaotica wants this to match *exactly*.  Lots of plugins don't prefix.

So one night, I started work on a quick-and-dirty PHP script to automatically convert the Java files into the C/C++ template.  I got to a few hundred variations compiling in a few hours over night, so poked it a few times over the next few days.

Currently, 500 of the possibly-compatible 549 variations are compiling.  The ones that aren't either have some complicated classes doing things, or are maybe using JW-specific features like layers.

I have no idea how many are failing to render correctly (or even crashing).  I'll try to automate testing them soon.

If this fits your workflow, and you hit some problems, feel free to raise an issue here!

The conversion script is included here, if you want to shake your head at a total ball of tangled regular expression yarn.

I don't think it'll be hard to go from Chaotica _back_ to JWildfire intact, which will be my next tool.  I regularly decide things could use major structural changes after coloring/tweaking, but that's hard with the UI in Chao, unfortunately.

The conversion process has an "overrides" folder.  It copies those contents into the output after conversion.  Some of these are the original Apophysis plugin C source, when a variation came from there, and some are just hand-tweaked files that hit a corner case on my parsing.  It's very sloppy parsing.

NOTES:
------

* The basic plugin is now in a [separate repository](https://github.com/mwegner/apophysis-chaotica-plugin-build)!

* I've now tagged all of these plugins with a dummy variable ,warning it's a JW modification.  Hopefully this will prevent these DLLs from intermingling over time, in case they have subtle changes.

* If a plugin fails to compile, I bring in a stub plugin.  This plugin does nothing, but keeps all variable names.  This prevents Chaotica from sometimes-crashing, but also keeps the variation in the save file going forward.

* Sorry for the mess.  C/C++ is absolutely NOT my thing.  I think this is the most C code I've ever written in my whole life, and I've been a full-time programming in some sense for awhile now.

* I marked this as LGPL, which matches JWildfire's licensing.  Some of the included original Apophysis source files are GPL.


ME:
---

-Matthew (@mwegner on gmail/twitter/etc)
