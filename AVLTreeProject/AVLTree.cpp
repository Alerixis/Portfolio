/* File: AVLTree.cpp
   Proj: CMSC 341 Proj 3
   Author: James Morton
   Date: 10/20/16
   Section: 1
   Email: jmorton1@umbc.edu
   
   This is the implementation of the AVL Tree objects. This will 
   hold all the appropriate nodes in each AVL Tree.
*/
#ifndef _AVLTREE_CPP_
#define _AVLTREE_CPP_

#include <iostream>
#include <string>
#include <cstdio>
#include <queue>

#include "AVLTree.h"
#include "AVLTreeNode.h"

//Default Constructor
template<class T1, class T2>
AVLTree<T1, T2>::AVLTree(int ID, int print, int data, int key)
{
  m_TreeID = ID;
  root = NULL;

  //Set print enum
  if(print == 0)
    {
      printType = AVLTreeBase::IN;
    }
  else if(print == 1)
    {
      printType = AVLTreeBase::PRE;
    }
  else if(print == 2)
    {
      printType = AVLTreeBase::POST;
    }
  else if(print == 3)
    {
      printType = AVLTreeBase::LEVEL;
    }
  else
    {
      std::cout << "INVALID PRINT TYPE" << std::endl;
    }
  
  //set data enum
  if(data == 0)
    {
      dataType = AVLTreeBase::CHARACTER;
    }
  else if(data == 1)
    {
      dataType = AVLTreeBase::STRING;
    }
  else
    {
      std::cout << "INVALID DATA TYPE" << std::endl;
    }

  //set number enum
  if(key == 0)
    {
      numberType = AVLTreeBase::INTEGER;
    }
  else if (key == 1)
    {
      numberType = AVLTreeBase::FLOAT;
    }
  else
    {
      std::cout << "INVALID NUMBER TYPE" << std::endl;
    }
}
//Destructor
template<class T1, class T2>
AVLTree<T1,T2>::~AVLTree()
{
  delete root;
}

//balance()
//Pre: An unbalanced AVL Tree section
//Post: A balanced AVL Tree section
template<class  T1, class T2>
void AVLTree<T1,T2>::checkBalance(AVLTreeNode<T1,T2>* node)
{
  //Set the balance. Should be 1, -1 , or 0
  node->balance = getHeight(node->right) - getHeight(node->left);

  //if not then choose the correct rotation for each node
  //Right heavy?
  if(node->balance == 2)
    {
      //If the tree section is right heavy rotate left
      if(getHeight(node->right->right) >= getHeight(node->right->left))
	{
	  node = leftRotate(node);
	}
      //Double rotate if necessary
      else
	{
	  node = rightLeftRotate(node);
	}
    }
  //If the tree section is left heavy
  else if(node->balance == -2)
    {
      //Rotate right
      if(getHeight(node->left->left) >= getHeight(node->left->right))
	{
	  node = rightRotate(node);
	}
      //Double Rotate if necessary
      else
	{
	  node = leftRightRotate(node);
	}
    }

  //If the parent isnt empty check balance on the parent
  // of this node
  if(node->parent != NULL)
    {
      checkBalance(node->parent);
    }
  //If the parent is empty then the root must be this node
  else if(node->parent == NULL)
    {
      root = node;     
    }
}

//insert()
//Pre:N/A
//Post: The node inserted at the correct point in the AVL Tree
template<class  T1, class T2>
void AVLTree<T1,T2>::insert(T1 data, T2 key)
{
  AVLTreeNode<T1,T2>* node = new AVLTreeNode<T1,T2>(data,key);
  AVLTreeNode<T1,T2>* parentTrack = root;

  //if the root is empty add the new node there
  if(root == NULL)
    {
      root = node;
    }
  else
    {
      bool inserting = true;
      while(inserting)
	{
	  //Insert to the left if there is no node present
	  if((parentTrack->key > node->key) && (parentTrack->left == NULL))
	    {
	      parentTrack->left = node;
	      node->parent = parentTrack;
	      inserting = false;
	    }

	  //Insert to the right if there is no node present
	  else if ((parentTrack->key < node->key) &&
		   (parentTrack->right == NULL))
	    {
	      parentTrack->right = node;
	      node->parent = parentTrack;
	      inserting = false;
	    }

	  //If there is a node on the left move to that node
	  else if ((parentTrack->key > node->key) && 
		   (parentTrack->left != NULL))
	    {
	      parentTrack = parentTrack->left;
	    }

	  //If there is a node on the right move to that node
	  else if ((parentTrack->key < node->key) &&
                   (parentTrack->right != NULL))
            {
              parentTrack = parentTrack->right;
            }
	}

      //check the balancing throughout the tree
      checkBalance(parentTrack);
    }
}

//getHeight()
//Pre: n/a
//Post: Returns the height of the node requested
template<class  T1, class T2>
int AVLTree<T1,T2>::getHeight(AVLTreeNode<T1,T2>* node)
{
  //If the node is the root or an empty child
  if(node == NULL)
    {
      return -1;
    }
  //Recursively get the height for each node in the tree
  return std::max(getHeight(node->right), getHeight(node->left)) + 1;
}

//leftRotate()
//Pre: An unbalanced AVL Tree
//Post: A balanced portion of an AVL Tree from rotating left
template<class  T1, class T2>
AVLTreeNode<T1,T2>* AVLTree<T1,T2>::leftRotate(AVLTreeNode<T1,T2>* node)
{
  //Have a temporary node of right child to allow swapping
  AVLTreeNode<T1,T2>* temp = node->right;

  //Swap parent
  temp->parent = node->parent;
  
  //Give the node all of the children (if any) from the swap
  node->right = temp->left;

  //Swap each node over
  temp->left = node;
  node->parent = temp;

  //If the swapped node isnt the root
  if(temp->parent != NULL)
    {
      //Reconnect with the correct child of the parent
      if(temp->parent->right == node)
        {
          temp->parent->right = temp;
        }
      else
        {
          temp->parent->left = temp;
        }
    }
  return temp;
}

//rightRotate()
//Pre: An unbalanced AVL Tree
//Post: A balanced portion of an AVL Tree from rotating right
template<class  T1, class T2>
AVLTreeNode<T1,T2>* AVLTree<T1,T2>::rightRotate(AVLTreeNode<T1,T2>* node)
{
  //Have a temp node of the left child to allow swapping
  AVLTreeNode<T1,T2>* temp = node->left;

  //Swap the parent
  temp->parent = node->parent;
  
  //give the node all of the children (if any) from the swap
  node->left = temp->right;

  //Swpa each node over
  temp->right = node;
  node->parent = temp;

  //If the swapped node isnt the root
  if(temp->parent != NULL)
    {
      //Reconnect with the correct child of the parent
      if(temp->parent->right == node)
	{
	  temp->parent->right = temp;
	}
      else
	{
	  temp->parent->left = temp;
	}
    }
  return temp;
}

//leftRightRotate()
//Pre: An unbalanced AVL Tree
//Post: A balanced portion of an AVL Tree from rotating left then right
template<class  T1, class T2>
AVLTreeNode<T1,T2>* AVLTree<T1,T2>::leftRightRotate(AVLTreeNode<T1,T2>* node)
{
  node->left = leftRotate(node->left);
  return rightRotate(node);
}

//rightLeftRotate()
//Pre: An unbalanced AVL Tree
//Post: A balanced portion of an AVL Tree from rotating right then left
template<class  T1, class T2>
AVLTreeNode<T1,T2>* AVLTree<T1,T2>::rightLeftRotate(AVLTreeNode<T1,T2>* node)
{
  node->right = rightRotate(node->right);
  return leftRotate(node);
}

//printTree()
//Pre: N/A
//Post: Printed tree to user in pre order
template <class T1, class T2>
void AVLTree<T1,T2>::printTree()
{
  if (printType == IN)
    {
      inOrder(root);
    } 
  if(printType == PRE)
    {
      preOrder(root);
    }
  if(printType == POST)
    {
      postOrder(root);
    }
  if(printType == LEVEL)
    {
      levelOrder(root);
    }
  std::cout << std::endl;
}
//levelOrder
//Pre: N/A
//Post: Tree printed in level order using queues
template <class T1, class T2>
void AVLTree<T1,T2>::levelOrder(AVLTreeNode<T1,T2>* node)
{
  std::queue<AVLTreeNode<T1,T2>*> levelQueue;
  
  //put the root in first
  levelQueue.push(node);

  //While the queue isnt empty
  while(levelQueue.size() != 0)
    {
      //Go through from the root adding each child to the queue
      //and popping each parent as it prints
      AVLTreeNode<T1,T2>* printNode = levelQueue.front();
      std::cout << printNode->data << " ";

      //add each child of the node to the queue
      if(printNode->left != NULL)
	{
	  levelQueue.push(printNode->left);
	}
      if(printNode->right != NULL)
	{
	  levelQueue.push(printNode->right);
	}

      levelQueue.pop();
    }
}

//postOrder()
//Pre: N/A
//Post: Tree printed in postOrder
template <class T1, class T2>
void AVLTree<T1,T2>::postOrder(AVLTreeNode<T1,T2>* node)
{
  if(node != NULL)
    {
      postOrder(node->left);
      postOrder(node->right);
      std::cout << node->data << " ";
    }
}

//preOrder()
//Pre: N/A
//Post: Tree printed in preOrder
template <class T1, class T2>
void AVLTree<T1,T2>::preOrder(AVLTreeNode<T1,T2>* node)
{
  if(node != NULL)
    {
      std::cout << node->data << " ";
      preOrder(node->left);
      preOrder(node->right);
    }
}

//inOrder()
//Pre: N/A
//Post: The tree printed in order
template <class T1, class T2>
void AVLTree<T1,T2>::inOrder(AVLTreeNode<T1,T2>* node)
{
  if(node != NULL)
    {
      inOrder(node->left);
      std::cout << node->data << " ";
      inOrder(node->right);
    }
}

//printRange()
//Pre: N/A
//Post: A range of nodes printed out in order
template <class T1, class T2>
void AVLTree<T1,T2>::printRange(AVLTreeNode<T1,T2>* node, int start, int end)
{ 

  if(node == NULL)
    {
      return;
    }

  //If the current node is not in range by being less than. Check the left subtree
  if( node->key > start)
    {
      printRange(node->left, start, end);
    }
  //If the nodes are in range of the given values print the data
  if((node->key >= start) && (node->key <= end))
    {
      std::cout << node->data << " ";
    }
  if((node->key < end))
    {
      printRange(node->right, start, end);
    }
}
#endif

