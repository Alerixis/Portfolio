#ifndef _NODE_H_
#define _NODE_H_

#include "character.h"
class Character ;

class Node {

 public:

  Node() ;
  ~Node() ;
  Character *m_cptr ; 
  Node *m_next;
};

#endif
