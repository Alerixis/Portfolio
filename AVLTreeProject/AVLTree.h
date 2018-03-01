/* File: AVLTree.h
   Proj: CMSC 341 Proj 3
   Author: James Morton
   Date: 10/20/16
   Section: 1
   email: jmorton1@umbc.edu
   
   This is the AVL Tree object header file. Implementation
   is in the .cpp file.
*/
#ifndef _AVLTREE_H_
#define _AVLTREE_H_

#include <vector>
#include <string>
#include <iostream>

#include "AVLTreeBase.h"
#include "AVLTreeNode.h"

template<class T1, class T2>
class AVLTree : public AVLTreeBase
{

 public: 

  //Constructor and Destructor
  AVLTree(int ID, int print, int data, int key);
  ~AVLTree();

  void checkBalance(AVLTreeNode<T1,T2>* node); //Rebalance the tree
  void insert(T1 data, T2 key); //Insert a new node into the tree
  int getHeight(AVLTreeNode<T1,T2>* node); //get the heigh of a node
  void printTree();
  void inOrder(AVLTreeNode<T1,T2>* node);
  void preOrder(AVLTreeNode<T1,T2>* node);
  void postOrder(AVLTreeNode<T1,T2>* node);
  void levelOrder(AVLTreeNode<T1,T2>* node);
  void printRange(AVLTreeNode<T1,T2>* node, int start, int end);

  //The various rotater functions
  AVLTreeNode<T1,T2>* leftRotate(AVLTreeNode<T1,T2>* node); 
  AVLTreeNode<T1,T2>* rightRotate(AVLTreeNode<T1,T2>* node);
  AVLTreeNode<T1,T2>* leftRightRotate(AVLTreeNode<T1,T2>* node);
  AVLTreeNode<T1,T2>* rightLeftRotate(AVLTreeNode<T1,T2>* node);

  int m_TreeID; //the trees unique ID
  AVLTreeNode<T1,T2>* root; //The top most node in the tree
  AVLTreeBase::PrintOrder printType;
  AVLTreeBase::DataType dataType;
  AVLTreeBase::NumberType numberType;

};

#include "AVLTree.cpp"

#endif
