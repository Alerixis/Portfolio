#include <iostream>
#include <sstream>
using namespace std;

#include "redshirt.h"

RedShirt::RedShirt()
{/*Empty constructor body*/}

void RedShirt::biteMe(Character *ptr)
{
  //If bitten they die.
  m_isDead = true;
  delete ptr;
}

void RedShirt::hitMe()
{
  //Does nothing
}

void RedShirt::cureMe()
{
  //Does Nothing
}

Character *RedShirt::morph()
{  
  //Does nothing
  return NULL;
}

string RedShirt::identify()
{
  ostringstream oss;
  oss << "RedShirt #" << getId();
  return oss.str();
}

void RedShirt::encounter(Character *ptr)
{
  //RedShirt hits a random character
  cout << "I'm " << identify() << ", ";
  cout << "and I'm gonna hit " << ptr->identify() << endl;
  ptr->hitMe();
}

bool RedShirt::migrates()
{
  //RedShirts dont move
  return false;
}
