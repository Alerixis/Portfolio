/* File: AVLTreeNode.h
   Proj: CMSC 341 Proj 3
   Author: James Morton
   Date: 10/20/16
   Section: 1
   Email: jmorton1@umbc.edu

   This is the header file for each AVL Tree Node. Implementation
   is in the .cpp file
*/
#ifndef _AVLTREENODE_H_
#define _AVLTREENODE_H_

template<class T1, class T2>
class AVLTreeNode
{
 public:
  AVLTreeNode(); //Constructor
  AVLTreeNode(T1 newData, T2 newKey);
  ~AVLTreeNode(); //Destructor

  T2 key;
  T1 data;
  int height;
  int balance;
  AVLTreeNode* left;
  AVLTreeNode* right;
  AVLTreeNode* parent;
  
};

#include "AVLTreeNode.cpp"

#endif
