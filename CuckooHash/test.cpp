#include "Pinball.h"
#include <iostream>

int main()
{
  Pinball table(1019);

  table.insert("aardvark");
  table.insert("aardwolf");
  table.insert("aaron");
  table.insert("aback");
  table.insert("abacus");
  table.insert("aabaft");
  table.insert("abalone");
  table.insert("abandoned");
  table.insert("abandonment");
  table.insert("abandons");
  table.insert("zoomed");
  table.insert("zooming");
  table.insert("zooms");
  table.insert("zooplankton");
  table.insert("zoos");
  table.insert("zulu");
  table.insert("zulus");
  table.insert("zulu");
  cout << "\n\n\n" << endl;

  if ( table.find("abandons") != -1)
    {
      cout << "found" << endl;
    }
  if(table.find("dog") == -1)
    {
      cout << "not found" << endl;
    }
  if ( table.find("aab") != -1)
    {
      cout << "found" << endl;
    }

  table.remove("abandons");

  if(table.find("abandons") == -1)
    {
      cout << "GONE" << endl;
    }
  else
    {
      cout << "Abandons is still there." << endl;
    }
  cout << table.at(610) << endl;
  if(table.at(2) == NULL)
    {
      cout << "YES" << endl;
    }
  table.printStats();
}

