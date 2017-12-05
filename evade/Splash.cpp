#include "Game.h"

// Splash process uses an Object that isn't displayed!
// The object structure provides some variable space we
// can use, saving precious global variable space.
void Splash::start_game(Process *me) {
  Sound::stfu();
  Sound::play_score(STAGE_1_SONG);
  game_mode = MODE_GAME;
  Player::init();
  ProcessManager::birth(Enemy_Scout::enemy_scout_process);
  ProcessManager::birth(Enemy_Heavy_Bomber::enemy_heavy_bomber_process);
  me->suicide();
}

/**
 * Display "Get Ready" for o->state frames
 */
void Splash::get_ready(Process *me) {
  Font::printf(30, 35, "GET READY!");
  Object *o = me->o;
  BYTE timer = o->state;

  if (timer <= 1) {
#ifdef ENABLE_LED
    LED::rgb(0, 0, 0);
#endif
    Splash::start_game(me);
    return;
  }
#ifdef ENABLE_LED
  else if (timer < 15) {
    LED::rgb(0x3f, 0, 0);
  }
  else if (timer < 30) {
    LED::rgb(0, 0x3f, 0);
  }
  else {
    LED::rgb(0, 0, 0x3f);
  }
#endif
  o->state--;
  me->sleep(1);
}

/**
 * Wait for the human to press the A button
 */
void Splash::wait(Process *me) {
  register Object *o = me->o;

  if (game_mode == MODE_SPLASH) {
    Font::scale = 2;
    Font::printf(15, 25, "EVADE 2");
    Font::scale = 1;
    if (o->state & (1 << 4)) {
      Font::printf(40, 45, "Press A");
      Font::printf(35, 60, "to start");
#ifdef ENABLE_LED
      LED::rgb(0, 0xff, 0);
#endif
    }
#ifdef ENABLE_LED
    else {
      LED::rgb(0, 0, 0);
    }
#endif
  }
  else {
    LED::rgb(0, 0, 0);
    HighScore::renderHighScores();
  }
  if (Controls::debounced(BUTTON_A)) {
    o->state = 45; // how long to show "Get Ready"
    me->sleep(1, Splash::get_ready);
    return;
  }
  o->state++;
  o->theta++;
  if (o->theta > 150) {
    o->theta = 0;
    if (game_mode == MODE_SPLASH) {
      game_mode = MODE_HIGHSCORES;
    }
    else {
      game_mode = MODE_SPLASH;
    }
  }
  me->sleep(1);
}

void Splash::splash_process(Process *me) {
  register Object *o = ObjectManager::alloc();
  me->o = o;
  o->lines = NULL;
  o->theta = 0;

  Player::life = Player::power = -1;
  Camera::vz = CAMERA_VZ;
  Sound::play_score(INTRO_SONG);
  me->sleep(1, Splash::wait);
}
