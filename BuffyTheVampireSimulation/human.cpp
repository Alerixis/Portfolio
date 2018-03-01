#include <iostream>
#include <sstream>
using namespace std;

#include "human.h"

Human::Human() 
  : m_infected(false),  m_morph(NULL), m_turnsInfected(0)
{/*Empty Constructor Body*/}

void Human::biteMe(Character *ptr)
{
  //Human is bitten and begins to turn into something
  m_infected = true;
  m_morph = ptr;  
}

void Human::hitMe()
{
  //Does nothing
}

void Human::cureMe()
{

  if (m_infected)
    {
      cout << identify() << " was cured!\n";
      m_infected = false;
      //Reset humans turn timer to 0 and delete the object that bit them
      m_turnsInfected = 0;
      delete m_morph;
    }
}

Character *Human::morph() 
{
  if ((m_morph != NULL) && (m_turnsInfected == 3))
    {
      return m_morph;
      cout << identify() << " changing into " << m_morph->identify() << endl;
    }
  return NULL;
}

string Human::identify()
{
  ostringstream oss;
  oss << "Human #" << getId();
  return oss.str();
}

void Human::encounter(Character *ptr)
{

  //Increase the turn timer if they are infected.
  if (m_infected)
    {
      m_turnsInfected = m_turnsInfected + 1;
      cout << identify() << " is " << m_turnsInfected << " steps to turning.\n";
    }
}
