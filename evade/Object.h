#ifndef OBJECT_H
#define OBJECT_H

#include "Types.h"

class ObjectManager;

class Object {
  friend ObjectManager;

protected:
  Object *next;

public:
  COORD x, y, z;    // coordinates
  COORD vx, vy, vz; // velocity in x,y,z
  BYTE step;        // step of explosion animation, -1 = not exploding
  WORD theta;       // rotation around Z (in degrees, 0-60)
  const BYTE *lines;

public:
  void move();
  void draw();
  void erase();
};

#endif
