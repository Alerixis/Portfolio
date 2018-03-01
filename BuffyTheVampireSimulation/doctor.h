#ifndef _DOCTOR_H_
#define _DOCTOR_H_

#include "character.h"

class Doctor : public Character 
{

 public:
  
  Doctor();
  void encounter(Character *ptr);
  void biteMe(Character *ptr);
  void hitMe();
  void cureMe();
  Character *morph();
  string identify() ;

 private:
  bool m_infected;
  bool m_cured;
  Character *m_morph;
  int m_turnsInfected;
};

#endif
