#ifndef _AVLFOREST_H_
#define _AVLFOREST_H_

/* include your tree implementation  */
#include <vector>
#include <string>
#include <iostream>

#include "AVLTree.h"
#include "AVLTreeBase.h"
#include "AVLTreeNode.h"

class AVLForest
{
  // vector of trees
  // we use a non-templated base class so we can hold all template instantiations
  std::vector<AVLTreeBase*> forest;

  // other data memebers
  
 public:
  AVLForest();
  ~AVLForest();

  void insert(std::string);
  void print_range(std::ostream&, std::string);
  friend std::ostream& operator << (std::ostream&, AVLForest&);

};

#endif /* _AVLFOREST_H_ */
