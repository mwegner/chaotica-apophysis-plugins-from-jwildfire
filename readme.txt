   //   ) )  // | |     //    ) ) 
   //___/ /  //__| |    //    / /  
  / ___ (   / ___  |   //    / /   
 //   | |  //    | |  //    / /    
//    | | //     | | //____/ /     
                                                                
                                                                
    //    / / //   / /  // | |     //    ) ) //   / /  //   ) ) 
   //___ / / //____    //__| |    //    / / //____    //___/ /  
  / ___   / / ____    / ___  |   //    / / / ____    / ___ (    
 //    / / //        //    | |  //    / / //        //   | |    
//    / / //____/ / //     | | //____/ / //____/ / //    | |    


INTRO:
------

There are a few different templates for Apophysis plugin compilation out there, but I hadn't seen one that automates
compilation.

This takes the plugin development template by DarkBeam and bezo97, found here:https://bezo97.tk/plugins/development

And automates compilation with a batch file.  It expects to find Visual Studio 2017 Build Tools, which are free to
download: https://visualstudio.microsoft.com/thank-you-downloading-visual-studio/?sku=BuildTools&rel=15

On the build tools install, I just used default C/C++ selection, and it worked out. You should be able to update the
batch file to use other VS environments.


BUILD AUTOMATION:
-----------------

Run build.cmd with no arguments to compile all variations in the "sources" folder.  It drops 64-bit/32-bit versions into
x64/x86 folders.  Logs with warnings/errors go into x64/x86.

You can also invoke build.cmd with the name of a variation, without extension, like:  "build.cmd twoface"


JWILDFIRE:
----------

Initially, I built this automation to make it easier to hand-port some of the JWildfire variations that I favor. I've been
using JW more and more for structure work, with Chaotica as my final render step.

If you completely normalize the variable names, you can paste directly into Chaotica, to avoid having to use the old JW 2.50
Chaotica Bridge integration.  The problem is, lots of plugins aren't named well for this.  JW saves out "plugin_variable", and
Chaotica wants this to match *exactly*.  Lots of plugins don't prefix.

So one night, I started work on a quick-and-dirty PHP script to automatically convert the Java files into the C/C++ template.
I go to a few hundred variations compiling in a few hours over night, so poked it a few times over the next few days.

Currently, 500 of the possible 549 variations are compiling.  The ones that aren't either have some complicated classes doing things,
or are maybe using JW-specific features like layers.

I have no idea how many are failing to render correctly (or even crashing).  I'll try to automate testing them soon.

If this fits your workflow, and you hit some problems, feel free to raise an issue here!

The conversion script is included here, if you want to shake your head at a total ball of tangled regular expression yarn.

I don't think it'll be hard to go from Chaotica _back_ to JWildfire intact, which will be my next tool.  I regularly decide things
could use major structural changes after coloring/tweaking, but that's hard with the UI in Chao, unfortunately.

The conversion process has an "overrides" folder.  It copies those contents into the output after conversion.  Some of these are
the original Apophysis plugin C source, when a variation came from there, and some are just hand-tweaked files that hit a corner
case on my parsing.  It's very sloppy parsing.

NOTES:
------

If you want the basic plugin template, check the first revision here.  I modified things pretty heavily during the JW port project.

Specifically, there are some extra helpers for bringing in an instance of a better random number generator.  Currently it's a library
doing SIMD-accelerate Mersenne Twister, but I'm not sure offhand is there's a better option.

Some of the 32-bit DLLs aren't compiling, I think from the complex number library I brought in to help some things.  I don't think
anyone really uses 32-bit anything anymore, though?

Sorry for the mess.  C/C++ is absolutely NOT my thing.  I think this is the most C code I've ever written in my whole life, and I've
been a full-time programming in some sense for awhile now.


ME:
---

-Matthew (@mwegner on gmail/twitter/etc)
