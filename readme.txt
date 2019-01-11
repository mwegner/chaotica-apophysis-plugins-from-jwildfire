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


USAGE:
------

Run build.cmd with no arguments to compile all variations in the "sources" folder.  It drops 64-bit/32-bit versions into
x64/x32 folders.

You can also invoke build.cmd with the name of a variation, without extension, like:  "build.cmd twoface"


NOTES:
------

C/C++ is absolutely not my thing, so feel free to suggest improvements or changes!

In particular, I'm not catching any errors/failures, because I wanted to keep things simple.  That sort of stuff would
be better suited to a "real" scripting language handling the build.  I guess PowerShell ships out with Windows 10 these
days, but I've never touched it.

Some modifications:

- Switched to <cmath> instead of <math.h> to fix some ambigious abs() calls (or can update to use fabs)

- Added missing VAR_REAL_NONZERO macro

- I did a gross thing in plugin_var.h to work around variadic macros with an empty APO_VARIABLES().  Comments in
- plugin_var.h


And things that seem to break, I think from Visual Studio compiler differences:

- Some plugins use a d literal suffix, which is uneeded (i.e. 0.9999999d)

- Inline functions inside of other functions won't compile.  Just move outside of a function definition block


ME:
---

-Matthew (@mwegner on gmail/twitter/etc)
