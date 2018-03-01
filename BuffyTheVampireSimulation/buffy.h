#ifndef _BUFFY_H_
#define _BUFFY_H_

#include "character.h"

class Buffy : public Character {

 public:
  
  Buffy();
  void encounter(Character *ptr);
  void biteMe(Character *ptr);
  void hitMe();
  void cureMe();
  Character *morph();
  string identify();

};

#endif
