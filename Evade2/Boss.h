#ifndef BOSS_H
#define BOSS_H

#include "Evade2.h"

class Boss {
public:
  static BYTE hit_points;
  static void entry(Process *me, Object *o);
  static void explode(Process *me, Object *o);
private:
  static void enter(Process *me, Object *o);
  static void action(Process *me, Object *o);
};

#endif
