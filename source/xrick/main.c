/*
 * xrick/src/xrick.c
 *
 * Copyright (C) 1998-2002 BigOrno (bigorno@bigorno.net). All rights reserved.
 *
 * The use and distribution terms for this software are contained in the file
 * named README, which can be found in the root of this distribution. By
 * using this software in any fashion, you are agreeing to be bound by the
 * terms of this license.
 *
 * You must not remove this notice, or any other, from this software.
 */

#include "system/system.h"
#include "game.h"

#include <SDL.h>

/*
 * main
 */
int
main(int argc, char *argv[])
{
	sys_init(argc, argv);
	if (sysarg_args_data)
    {
		data_setRootPath(sysarg_args_data);
    }
    else
    {
        data_setRootPath(data_defaultPath);
    }
    game_run();
	data_closeRootPath();
	sys_shutdown();
	return 0;
}

/* eof */
