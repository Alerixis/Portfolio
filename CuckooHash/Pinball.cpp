/* File: Pinball.cpp
   Project: Proj 5 CMSC 341
   Author: James Morton
   Email: jmorton1@umbc.edu
   Section: 1
   Description: This is the implementation of my given
   Pinball Hash values.

   Degree: 7
   Ejection Limit: 20
   Randomness: Option 2: A little bit random
*/
#include <stdexcept>
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include "Pinball.h"

using namespace std;

Pinball::Pinball(int n)
{

  //Initialize proper values
  m_size = 0;
  m_capacity = n;
  m_degree = 7;
  m_ejectLimit = 20;  
  m_primSlots = 0;
  m_ejections = 0;
  m_maxSingleEjects = 0;
  m_singleRoundEjections = 0;
  
  //Initialized the array and each of its elements as a character
  H = new char*[m_capacity];
  m_primHitArray = new int[m_capacity];
  for(int i = 0; i < m_capacity; i++)
    {
       H[i] = new char;
       H[i] = NULL;
    }

  for(int i = 0; i < m_capacity; i++)
    {
      m_primHitArray[i] = 0;
    }
}

Pinball::~Pinball()
{
  //first deallocate each of the char pointers
  for(int i = 0; i < m_capacity; i++)
    {
      free(H[i]);
    }
  //then free the base structure
  delete H;
  delete m_primHitArray;
}

//Insert
//Pre: n/a
//Post: Moves through the hash table inserting into a new primary
// slot or accepting an auxiliary slot with or without bumping out a 
// random element if all slots are full
void Pinball::insert(const char *str)
{
  //First check for exceptions. Whether the table is full
  // or if the max limit of ejections has been hit.
  if(getSize() == getCapacity())
    {
      throw PinballHashFull("\n\nFull Table\n\n");
    }
  else if(m_singleRoundEjections == m_ejectLimit)
    {
      m_maxSingleEjects = m_singleRoundEjections;
      throw PinballHashFull("\n\nMax Ejects Hit\n\n");
    }

  //Now check to see if the string being inserted is already in the table
  // if so just note that its there and return. 
  if(find(str) != -1)
    {
      cout << str << " already in table." << endl;
      return;
    }

  //make a copy of the string to be able to make a moddable string object
  char* stringCopy = strdup(str);

  //Hash the new string copy to get the hash key for the array
  unsigned int index = hashCode(stringCopy) % getCapacity();
  m_primHitArray[index]++;
  
  //If that index of the array is empty. simply insert it there. This
  // is a new primary slow
  if (H[index] == NULL)
    {
      H[index] = stringCopy;
      increasePrimarySlots();
      increaseSize();
      return;
    }

  //Check auxillary slots for insert
  else
    {
      //Random seed integrated with Option 2. Using 
      // the primary index as the seed. We will save a random 
      // seed as mercifully given in the project description
      // just in case we need to eject an item
      int savedRandomSeed = rand();
      srand(index);
      
      //Call random up to the degree of the hash table
      // if needed to find an empty slot to insert the item
      int auxArray[m_degree - 1];
      for(int i = 0; i < m_degree; i++)
	{
	  int auxSlotIndex = rand() % getCapacity();
	  auxArray[i] = auxSlotIndex;
	  //cout << " at aux slot index: " << auxSlotIndex << endl; 
	  if(H[auxSlotIndex] == NULL)
	    {
	      H[auxSlotIndex] = stringCopy;
	      increaseSize();
	      return;
	    }
	}
      
      //If all aux slots are full. We need to eject a random item 
      // and enter this item there.But then must re-insert that item.
      srand(savedRandomSeed);
      int ejectIndex = rand() % (m_degree - 1);
      const char* ejectToInsert = H[auxArray[ejectIndex]];
      H[auxArray[ejectIndex]] = stringCopy;
      m_singleRoundEjections++;
      m_ejections++;
      insert(ejectToInsert);
    }

  //If this single round of ejections is greater than the 
  // current max. Then replace the value and update it.
  if(m_maxSingleEjects < m_singleRoundEjections)
    {
      m_maxSingleEjects = m_singleRoundEjections;
    }
  m_singleRoundEjections = 0;
}

int Pinball::find(const char *str)
{
  //Create a copy of the string being looked for
  char* stringCopy = strdup(str);

  //Hash that string to find its code
  unsigned int index = hashCode(stringCopy) % getCapacity();

  //Now check the primary slot and all auxiliary slots for the
  //correct item
  if(H[index] != NULL)
    {
      if(strcmp(H[index], stringCopy) == 0)
	{
	  int foundIndex = index;
	  return foundIndex;
	}
    }
  //Save a semi random seed to return to after checking the aux slots
  int savedRandomSeed = rand();
  srand(index); //create a random seed to get aux slots
  int auxArray[m_degree-1];
  for(int i = 0; i < m_degree; i++)
    {
      int auxSlotIndex = rand() % getCapacity();
      auxArray[i] = auxSlotIndex;
    
      if(H[auxSlotIndex] != NULL)
	{
	  if(strcmp(H[auxSlotIndex], stringCopy) == 0)
	    {
	      int foundIndex = auxSlotIndex;
	      return foundIndex;
	    }
	} 
    }
  srand(savedRandomSeed);
  return -1;
}

const char* Pinball::at(int index)
{
  if((index < 0) || (index >= m_capacity))
    {
      throw out_of_range("Int out of Range");
    } 

  const char* charAtIndex;
  charAtIndex = H[index];

  return charAtIndex;
   
}

char* Pinball::remove(const char *str)
{
  int index = find(str);
  cout << index << endl;
  if(index == -1)
    {
      return NULL;
    }
  else
    {
      char* removedValue = H[index];
      H[index] = NULL;
      free(H[index]);
      return removedValue;
    }
}

void Pinball::printStats()
{
  ofstream output;
  output.open("output.txt", ios::app);

  output << "\nHash Statistics Report: " << endl;
  output << "  Randomness level = a little bit random " << endl;
  output << "  Capacity = " << m_capacity << endl;
  output << "  Size = " << m_size << endl;
  output << "  Degree = " << m_degree << endl;
  output << "  Ejection Limit = " << m_ejectLimit << endl;
  output << "  Number of Primary Slots = " << m_primSlots << endl;
  m_avgPrimHits = float(m_size) / float(m_primSlots);
  output << " Average Primary Hits: " << m_avgPrimHits << endl;

  int maxPrimHit = findMaxHit();
  output << "  Maximum Hits to a Primary Slot = " << maxPrimHit << endl;
  output << "  Total Number of Ejections = " << m_ejections << endl;
  output << "  Maximum Number of Ejections in a single insertion = " << m_maxSingleEjects << endl;
  output << " \n\n\n";
  output.close();
}

int Pinball::getSize()
{
  return m_size;
}

int Pinball::getCapacity()
{
  return m_capacity;
}

char * Pinball::getItem(int i)
{
  return H[i];
} 

void Pinball::increaseSize()
{
  m_size++;
}

void Pinball::increasePrimarySlots()
{
  m_primSlots++;
}

int Pinball::findMaxHit()
{
  int max = 0;
  for(int i = 0; i < m_capacity; i++)
    {
      if(m_primHitArray[i] > max)
	{
	  max = m_primHitArray[i];
	}
    }
  return max;
}
