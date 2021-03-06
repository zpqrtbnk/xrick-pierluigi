/*
 * xrick/system/main_sdl.c
 *
 * Copyright (C) 1998-2002 BigOrno (bigorno@bigorno.net).
 * Copyright (C) 2008-2014 Pierluigi Vicinanza.
 * All rights reserved.
 *
 * The use and distribution terms for this software are contained in the file
 * named README, which can be found in the root of this distribution. By
 * using this software in any fashion, you are agreeing to be bound by the
 * terms of this license.
 *
 * You must not remove this notice, or any other, from this software.
 */

#include "xrick/system/system.h"
#include "xrick/game.h"

#include <SDL.h>

/*
 * main
 */
int
main(int argc, char *argv[])
{
    bool success = sys_init(argc, argv);
	if (success)
    {
        game_run();
    }
	sys_shutdown();
    return (success? 0 : 1);
}

/* eof */
