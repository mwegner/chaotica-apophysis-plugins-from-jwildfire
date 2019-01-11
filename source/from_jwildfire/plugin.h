// this is just here because I couldn't get CLion to see the include folder properly, sigh
#pragma once

#ifdef APO_NOVARIABLES
	#include "plugin_novar.h"
#else
	#include "../../include/plugin_var.h"
#endif
