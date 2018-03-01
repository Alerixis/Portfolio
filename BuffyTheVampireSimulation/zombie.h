#ifndef _ZOMBIE_H_
#define _ZOMBIE_H_

#include "character.h"

class Zombie : public Character 
{

 public:
  
  Zombie();
  void encounter(Character *ptr);
  void biteMe(Character *ptr);
  void hitMe();
  void cureMe();
  Character *morph();
  string identify();

 private:
  int HP;
  bool m_cured;
};

#endif
 
