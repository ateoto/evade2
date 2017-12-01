#include "Game.h"

// Splash process uses an Object that isn't displayed!
// The object structure provides some variable space we
// can use, saving precious global variable space.
void Splash::start_game(Process *me) {
  ProcessManager::birth(Player::player_process, PTYPE_SYSTEM);
  ProcessManager::birth(Fighter1::fighter1_process);
  ProcessManager::birth(Fighter1::fighter1_process);
  
  //  ProcessManager::birth(Fighter1::fighter1_process);
  me->suicide();
}

/**
 * Display "Get Ready" for o->state frames
 */
void Splash::get_ready(Process *me) {
  Font::printf(35, 35, "GET READY!");
  Object *o = me->o;
  BYTE timer = o->state;

  if (timer <= 1) {
#ifdef ENABLE_LED_LOGIC
    arduboy.setRGBled(0, 0, 0);
#endif
    //    TX_LED_OFF();
    //    RX_LED_OFF();
    //    L_LED_OFF();
    Splash::start_game(me);
    return;
  }
#ifdef ENABLE_LED_LOGIC
  else if (timer < 15) {
    arduboy.setRGBled(0x3f, 0, 0);
    //    TX_LED_OFF();
    //    RX_LED_OFF();
    //    L_LED_ON();
  }
  else if (timer < 30) {
    arduboy.setRGBled(0, 0x3f, 0);
    //    TX_LED_ON();
    //    RX_LED_OFF();
    //    L_LED_OFF();
  }
  else {
    arduboy.setRGBled(0, 0, 0x3f);
    //    TX_LED_OFF();
    //    RX_LED_ON();
    //    L_LED_OFF();
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

  Font::scale = 2;
  Font::printf(15, 25, "EVADE 2");
  Font::scale = 1;
  if (Controls::debounced(BUTTON_A)) {
    o->state = 45; // how long to show "Get Ready"
    me->sleep(1, Splash::get_ready);
    return;
  }
  else if (o->state & (1 << 4)) {
    Font::printf(40, 45, "Press A");
    Font::printf(35, 60, "to start");
  }
  o->state++;
  o->theta++;
#ifdef ENABLE_LED_LOGIC
  BYTE theta = o->theta & 0x3f;
  arduboy.setRGBled(theta, theta, theta);
#endif
  me->sleep(1);
}

void Splash::splash_process(Process *me) {
  register Object *o = ObjectManager::alloc();
  me->o = o;
  o->lines = NULL;
  o->state = 0;
  o->theta = 0;

  Player::life = Player::power = -1;
  Camera::vz = CAMERA_VZ;
  Sound::play_score(INTRO_SONG);
  me->sleep(1, Splash::wait);
}
