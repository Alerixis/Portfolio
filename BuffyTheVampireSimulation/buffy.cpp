#include <iostream>
#include <sstream>
using namespace std;

#include "buffy.h"

Buffy::Buffy()
{/*Empty constructor body*/}

void Buffy::biteMe(Character *ptr)
{
  //Does nothing.
  delete ptr;
}

void Buffy::hitMe()
{
  //does nothing
}

void Buffy::cureMe()
{
  //does nothing
}

Character *Buffy::morph()
{
  //nothing can become buffy
  return NULL;
}

string Buffy::identify()
{
  ostringstream oss;
  oss << "Buffy #" << getId();
  return oss.str();
}

void Buffy::encounter(Character *ptr)
{
  //Buffy hits something in the room
  cout << "Im " << identify() << ", ";
  cout << "and I'm gonna hit " << ptr->identify() << endl;
  ptr->hitMe();
}
