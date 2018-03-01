#include <iostream>
#include <sstream>
using namespace std;

#include "doctor.h"

Doctor::Doctor()
  :m_infected(false), m_morph(NULL), m_turnsInfected(0)
{/*Empty constructor body*/}

void Doctor::biteMe(Character *ptr)
{
  //Doc is bitten and begins to turn.
  m_infected = true;
  m_morph = ptr;
}

void Doctor::hitMe()
{
  //Does nothing
}

void Doctor::cureMe()
{
  if (m_infected)
    {
      cout << identify() << " was cured! \n";
      
      //Doctor is cured and his turn timer resets and stops counting.
      m_infected = false;
      m_turnsInfected = 0;

      //Delete the pointer to the object that bit the doctor
      delete m_morph;
   }
}

Character *Doctor::morph()
{
  if ((m_morph != NULL) && (m_turnsInfected == 3))
    {
      cout << identify() << " changing into " << m_morph->identify() << endl;

      //Return new object passed to host from biteMe()
      return m_morph;
    }
  return NULL;
}

string Doctor::identify()
{
  ostringstream oss;
  oss << "Doctor #" << getId();
  return oss.str();
}

void Doctor::encounter(Character *ptr)
{
  //The doctor tries to cure something in the room.
  cout << "Im " << identify() << ", ";
  cout << " and I'll attempt to cure " << ptr->identify() << endl;
  ptr->cureMe();
  //Increase the turn timer if the doc has been bitten.
  if (m_infected)
    {
      m_turnsInfected = m_turnsInfected + 1;
      cout << identify() << " is " << m_turnsInfected << " step to turning.\n";
    }
}

