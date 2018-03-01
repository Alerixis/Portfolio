#include <iostream>
#include <sstream>
using namespace std;

#include "vampire.h"

Vampire::Vampire()
  : HP(3)
{/*Empty constructor body*/}

void Vampire::biteMe(Character *ptr)
{
  delete ptr;
}

void Vampire::hitMe()
{
  cout << "Vampire drops one HP from being hit.\n";
  HP--;
  if (HP == 0)
    {
      cout << identify() << " has died!!!" << endl;
      m_isDead = true;
    }
}

void Vampire::cureMe()
{
  //Does nothing.
}

Character *Vampire::morph()
{
  return NULL;
}

string Vampire::identify()
{
  ostringstream oss;
  oss << "Vampire #" << getId() << " HP: " << HP;
  return oss.str();
}

void Vampire::encounter(Character *ptr)
{
  //Vampire attempts to bite a random character
  cout << "Im " << identify() << ", ";
  cout << "and I'll bite " << ptr->identify() << endl;
  Character *Vptr = new Vampire;
  ptr->biteMe(Vptr);
}

