#ifndef GAMEDEF_H
#define GAMEDEF_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

#define DIR "data"

typedef enum{gfalse, gtrue} gboolean;

#pragma warning(disable : 4244)
#pragma warning(disable : 4996)

#include "mathlib.h"
#include "common.h"
#include "cvar.h"
#include "cmd.h"
#include "entity.h"
#include "assert.h"
#include "spawns.h"
#include "game.h"

#endif /*GAMEDEF_H*/