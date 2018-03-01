#include <iostream>
#include <sstream>
using namespace std;

#include "zombie.h"
#include "human.h"

Zombie::Zombie()
  : HP(3), m_cured(false)
{/*Empty constructor body*/}

void Zombie::biteMe(Character *ptr)
{
  delete ptr;
}

void Zombie::hitMe()
{
  cout << "Zombie drops one HP from being hit.\n";
  HP--;
  if (HP == 0)
    {
      cout << identify() << " has died!!!" << endl; 
      m_isDead = true;
    }
}

void Zombie::cureMe()
{
  //Zombie should be marked to morph back into a human at end of turn
  m_cured = true;
}

Character *Zombie::morph() 
{
  if (m_cured)
    {
      Character *morph = new Human;
      return morph;
    }
  return NULL;
}

string Zombie:: identify()
{
  ostringstream oss;
  oss << "Zombie #" << getId() << " HP: " << HP;
  return oss.str();
}

void Zombie::encounter(Character *ptr)
{
  //Zombie bites a random character
  cout << "I'm " << identify() << ", ";
  cout << "and I'll bite " << ptr->identify() << endl;
  Character *Zptr = new Zombie; 
  ptr->biteMe(Zptr);
}

