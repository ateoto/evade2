#ifndef GAME_H
#define GAME_H

#define DEV
//#undef DEV

#include "Types.h"

#define SCREEN_WIDTH WIDTH   // Screen width in pixels.
#define SCREEN_HEIGHT HEIGHT // Screen height in pixels.

// define this to enable LED logic
// note: this seems to take 12 bytes of RAM!
#define ENABLE_LED
//#undef ENABLE_LED

// define this to enable audio
#define ENABLE_AUDIO
//#undef ENABLE_AUDIO

// if SMART_ERASE is defined, the engine will try to erase
// all the lines and points drawn previous frame instead
// of clearing the whole screen to black each frame.
#define SMART_ERASE
#undef SMART_ERASE

// if SCORE_ENABLE is defined, the score will be displayed on
// screen during game play.
#define SCORE_ENABLE
//#undef SCORE_ENABLE

// const variables take NO RAM, they are like #define, but with type info for the
// compiler to use when checking validity of code.

const int FRAMERATE = 30;

const int NUM_OBJECTS = 12;
const int NUM_PROCESSES = 4;

// we should probably key on FRAMERATE and adjust things accordingly
const int NUM_STARS = 5;

// joystick up/down/left/right changes camera by DELTACONTROL
const float DELTACONTROL = 11;
// speed of camera flying through stars
const float CAMERA_VZ = 6;
// speed of player bullets
const float BULLET_VZ = 21;

const BYTE MAX_BULLETS = 6;

const BYTE PTYPE_USER = 0;
const BYTE PTYPE_SYSTEM = 1;

class Sound;
class Controls;
class Object;
class ObjectManager;
class Process;
class ProcessManager;
class Starfield;

extern Arduboy2Core arduboy;

#define MODE_SPLASH 1
#define MODE_HIGHSCORES 2
#define MODE_ATTRACT 3
#define MODE_GAME 4
#define MODE_GAMEOVER 5
#define MODE_ENTER_INITIALS 6

extern BYTE game_mode;

#include "Controls.h"
#include "Font.h"
#include "Graphics.h"
#ifdef ENABLE_LED
#include "LED.h"
#endif
#include "Object.h"
#include "ObjectManager.h"
#include "Process.h"
#include "ProcessManager.h"
#include "Sound.h"
#include "debug.h"

#include "GameOver.h"
#include "HighScore.h"
#include "Splash.h"

#include "Bullet.h"
#include "Camera.h"
#include "EBullet.h"
#include "EnemyBase.h"
#include "Enemy_Heavy_Bomber.h"
#include "Enemy_Scout.h"
#include "Player.h"
#include "Starfield.h"

#endif
