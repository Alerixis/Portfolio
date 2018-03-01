#ifndef _HUMAN_H_
#define _HUMAN_H_

#include "character.h"

class Human : public Character 
{
  
 public:

  Human();  //Default constructor for Humans
  void encounter(Character *ptr);
  void biteMe(Character *ptr);
  void hitMe();
  void cureMe();
  Character *morph();
  string identify();

 private:
  bool m_infected;
  Character *m_morph;
  int m_turnsInfected;
};

#endif
