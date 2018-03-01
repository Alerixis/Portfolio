#ifndef _REDSHIRT_H_
#define _REDSHIRT_H_

#include "character.h"

class RedShirt : public Character 
{

 public:
  
  RedShirt();
  void encounter(Character *ptr);
  void biteMe(Character *ptr);
  void hitMe();
  void cureMe();
  Character *morph();
  string identify();
  bool migrates();

};

#endif
