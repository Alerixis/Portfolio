/* File: AVLTreeNode.cpp
   Proj: CMSC 341 PRoj 3
   Author: James Morton
   Date: 10/20/16
   Seciton: 1
   Email: jmorton1@umbc.edu

   This is the implementation file for the AVL Tree Nodes. These nodes
   contain the numeric key or the alphanumeric data set.
*/
#ifndef _AVLTREENODE_CPP_
#define _AVLTREENODE_CPP_

#include <cstdio>

#include "AVLTreeNode.h"

//Alternate Constructor
template<class T1, class T2>
AVLTreeNode<T1,T2>::AVLTreeNode(T1 newData, T2 newKey)
{
  data = newData;
  key = newKey;
  left = NULL;
  right = NULL;
  parent = NULL;
} 

//Destructor
template<class T1, class T2>
AVLTreeNode<T1,T2>::~AVLTreeNode()
{
  delete left;
  delete right;
}

#endif
