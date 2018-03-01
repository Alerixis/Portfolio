#include <vector>
#include <string>
#include <iostream>

#include "AVLTree.h"
#include "AVLTreeNode.h"

int main()
{
  AVLTree<char, int>* tree = new AVLTree<char, int>(1);

  AVLTreeNode<char, int>* node = new AVLTreeNode<char, int>('1',10);
  tree->insert(node);
  std::cout << "Insert 10" << std::endl;

  AVLTreeNode<char, int>* node2 = new AVLTreeNode<char, int>('2',12);
  tree->insert(node2);
  std::cout << "Insert 12" << std::endl;

  AVLTreeNode<char, int>* node3 = new AVLTreeNode<char, int>('3',11);
  tree->insert(node3);
  std::cout << "Insert 11" << std::endl;

  AVLTreeNode<char, int>* node4 = new AVLTreeNode<char, int>('4',13);
  tree->insert(node4);
  std::cout << "Insert 13" << std::endl;

  AVLTreeNode<char, int>* node5 = new AVLTreeNode<char, int>('5',8);
  tree->insert(node5);
  std::cout << "Insert 8" << std::endl;

  AVLTreeNode<char, int>* node6 = new AVLTreeNode<char, int>('6',9);
  tree->insert(node6);
  std::cout << "Insert 9" << std::endl;

  tree->printTree();

  tree->~AVLTree();
}
