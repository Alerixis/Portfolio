#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>

#include "AVLForest.h"
#include "AVLTree.h"

AVLForest::AVLForest()
{
}


AVLForest::~AVLForest()
{
}

void AVLForest::insert(std::string line)
{  
  //First parse the data into string vectors ignoring commas
  std::stringstream sStream(line);
  std::vector<std::string> parsedLine;

  while(sStream.good())
    {
      std::string subString;
      getline(sStream, subString, ',');
      parsedLine.push_back(subString);
    }
  // create a new tree and add it to the vector if it isn't already there
  if(parsedLine.size() == 4)
    {

      //Convert each string enumuerator to integers for tree creation
      std::vector<int> treeData;
      for(int i = 0; i < parsedLine.size(); i++)
	{
	  int idEnum;
	  std::stringstream sStream2(parsedLine[i]);
	  sStream2 >> idEnum;
	  treeData.push_back(idEnum);
	}

      //Check if the tree is already in the forest
      bool treeExists = false;
      if((treeExists == false) || (forest.empty()))
	{
	  //Declare a char int tree and add to vector
	  if(treeData[2] == 0 && treeData[3] == 0)
	    {
	      AVLTreeBase* newTree = new AVLTree<char,int>(treeData[0],treeData[1],treeData[2],treeData[3]);
	      AVLTree<char,int>* derivedTree = static_cast<AVLTree<char,int>*>(newTree);
	      forest.push_back(derivedTree);
	    }
	  //Declare a char float tree and add to vector
	  else if(treeData[2] == 0 && treeData[3] == 1)
	    {
	      AVLTreeBase* newTree = new AVLTree<char,float>(treeData[0],treeData[1],treeData[2],treeData[3]);
              AVLTree<char,float>* derivedTree = static_cast<AVLTree<char,float>*>(newTree);
	      forest.push_back(derivedTree);
	    }
	  //Declare a string int tree and add to vector
	  else if(treeData[2] == 1 && treeData[3] == 0)
	    {
	      AVLTreeBase* newTree = new AVLTree<std::string,int>(treeData[0],treeData[1],treeData[2],treeData[3]);
              AVLTree<std::string,int>* derivedTree = static_cast<AVLTree<std::string,int>*>(newTree);
              forest.push_back(derivedTree);
	    }
	  //Declare a string float tree and add to vector
	  else if(treeData[2] == 1 && treeData[3] == 1)
	    {
	      AVLTreeBase* newTree = new AVLTree<std::string,int>(treeData[0],treeData[1],treeData[2],treeData[3]);
              AVLTree<std::string,float>* derivedTree = static_cast<AVLTree<std::string,float>*>(newTree);
	      forest.push_back(derivedTree);
	    }
	  else
	    {
	      std::cout << "\nINVALID LINE: " << line << std::endl;
	    }
	}
    }
  else if(parsedLine.size() == 3)
    {
      //Grab the integer ID of the tree and find the correct tree to insert
      std::stringstream sStreamID(parsedLine[0]);
      std::stringstream sStreamData(parsedLine[1]);
      std::stringstream sStreamKey(parsedLine[2]);

      int ID;
      int keyInt;
      float keyFloat;
      char charData;
      char spaceCheck;
      std::string stringData;

      sStreamID >> ID;
   
      // find if the tree is in the vector
      for(int i = 0; i < forest.size(); i++)
	{
	  AVLTree<char,int>* checkTree = static_cast<AVLTree<char,int>*>(forest[i]);
          if(checkTree->m_TreeID == ID)
	    {
	      
	      // with the tree found
	      // insert data, number pair
	      if((checkTree->dataType == 0) && (checkTree->numberType == 0))
		{
		  AVLTree<char,int>* insertTree = static_cast<AVLTree<char,int>*>(forest[i]);
		  sStreamKey >> keyInt;
		  sStreamData >> charData;
		  insertTree->insert(charData, keyInt);
		}
	      else if((checkTree->dataType == 0) && (checkTree->numberType == 1))
		{
		  AVLTree<char,float>* insertTree = static_cast<AVLTree<char,float>*>(forest[i]);
		  sStreamKey >> keyFloat;
                  sStreamData >> charData;
                  insertTree->insert(charData, keyFloat); 
		}
	      else if((checkTree->dataType == 1) && (checkTree->numberType == 0) )
		{
		  AVLTree<std::string,int>* insertTree = static_cast<AVLTree<std::string,int>*>(forest[i]);
		  sStreamKey >> keyInt;
                  sStreamData >> stringData;
                  insertTree->insert(stringData, keyInt);
		}
	      else if((checkTree->dataType == 1) && (checkTree->numberType == 1))
		{
		  AVLTree<std::string,float>* insertTree = static_cast<AVLTree<std::string,float>*>(forest[i]);
		  sStreamKey >> keyFloat;
                  sStreamData >> stringData;
                  insertTree->insert(stringData, keyFloat);
		}
	      else
		{
		  std::cout << "NOT A VALID TREE" << std::endl;
		}
	    }
	}
    }
}

void AVLForest::print_range(std::ostream& out, std::string line)
{

  //First parse the string into the three separate integers
  std::stringstream sStream(line);
  std::vector<int> parsedLine;
  while(sStream.good())
    {
      int integer;
      sStream >> integer;
      if(sStream.peek() == ',')
	{
	  sStream.ignore();
	}
      parsedLine.push_back(integer);
    }
  
  //now find the correct tree
  for(int i = 0; i < forest.size(); i++)
    {
      AVLTree<char,int>* checkTree = static_cast<AVLTree<char,int>*>(forest[i]);
      int start = parsedLine[1];
      int end = parsedLine[2];

      if(parsedLine[0] == checkTree->m_TreeID)
	{
	  if((checkTree->dataType == 0) && (checkTree->numberType == 0))
	    {
	      AVLTree<char,int>* printingTree = static_cast<AVLTree<char,int>*>(forest[i]);
	      printingTree->printRange(printingTree->root, start, end);
	    }

	  else if((checkTree->dataType == 0) && (checkTree->numberType == 1))
	    {
	      AVLTree<char,float>* printingTree = static_cast<AVLTree<char,float>*>(forest[i]);
	      printingTree->printRange(printingTree->root, start, end);
	    }

	  else if((checkTree->dataType == 1) && (checkTree->numberType == 0))
	    {
	      AVLTree<std::string,int>* printingTree = static_cast<AVLTree<std::string,int>*>(forest[i]);
	      printingTree->printRange(printingTree->root, start, end);
	    }

	  else if((checkTree->dataType == 1) && (checkTree->numberType == 1))
	    {
	      AVLTree<std::string,float>* printingTree = static_cast<AVLTree<std::string,float>*>(forest[i]);
	      printingTree->printRange(printingTree->root, start, end);
	    }

	  else
	    {
	      std::cout << "THIS IS NOT A VALID TREE TO PRINT" << std::endl;
	    }
	}
    }
  std::cout << std::endl;
}

std::ostream& operator << (std::ostream& out, AVLForest& avlForest)
{
  // print all trees
  for(int i = 0; i < (avlForest.forest.size()); i++)
    {
      //cast to a dummy object to check the enums for correct printing
      AVLTree<char,int>* checkTree = static_cast<AVLTree<char,int>*>(avlForest.forest[i]);

      //if char int print in that correct order
      if((checkTree->dataType == 0) && (checkTree->numberType == 0))
	{
	  AVLTree<char,int>* printingTree = static_cast<AVLTree<char,int>*>(avlForest.forest[i]);
	  printingTree->printTree();
	}
      //if char float print in that correct order
      else if((checkTree->dataType == 0) && (checkTree->numberType == 1))
	{
	  AVLTree<char,float>* printingTree = static_cast<AVLTree<char,float>*>(avlForest.forest[i]);
          printingTree->printTree();
	}
      //if string int print in that correct order
      else if((checkTree->dataType == 1) && (checkTree->numberType == 0))
	{
	  AVLTree<std::string,int>* printingTree = static_cast<AVLTree<std::string,int>*>(avlForest.forest[i]);
          printingTree->printTree();
	}
      //if string float print in the correct order
      else if((checkTree->dataType == 1) && (checkTree->numberType == 1))
	{
	  AVLTree<std::string,float>* printingTree = static_cast<AVLTree<std::string,float>*>(avlForest.forest[i]);
          printingTree->printTree(); 
	}
      //invalid case
      else
	{
	  std::cout << "THIS IS NOT A VALID TREE TO PRINT" << std::endl;
	}
    }
  return out;
}
