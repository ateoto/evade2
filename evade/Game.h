#ifndef GAME_H
#define GAME_H

#define DEV
//#undef DEV

#include "Types.h"

#define SCREEN_WIDTH WIDTH   // Screen width in pixels.
#define SCREEN_HEIGHT HEIGHT // Screen height in pixels.

const int NUM_STARS = 100;
const int NUM_OBJECTS = 4;
const int NUM_PROCESSES = 4;

const BYTE PTYPE_USER = 0;
const BYTE PTYPE_SYSTEM = 1;

class Starfield;
class Object;
class ObjectManager;
class Process;
class ProcessManager;

#include "Camera.h"
#include "Object.h"
#include "ObjectManager.h"
#include "Process.h"
#include "ProcessManager.h"
#include "Starfield.h"
#include "debug.h"

extern Arduboy2 arduboy;
extern Starfield starfield;

#endif
