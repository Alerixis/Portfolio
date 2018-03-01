#ifndef _VAMPIRE_H_
#define _VAMPIRE_H_

#include "character.h"

class Vampire : public Character 
{

 public:
  
  Vampire();
  void encounter(Character *ptr);
  void biteMe(Character *ptr);
  void hitMe();
  void cureMe();
  Character *morph();
  string identify();

 private:
  
  int HP;
  
};

#endif
