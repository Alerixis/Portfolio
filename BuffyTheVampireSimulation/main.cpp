#include <iostream>
#include <cstdlib>
using namespace std ;

#include "character.h"
#include "ghost.h"
#include "human.h"
#include "zombie.h"
#include "doctor.h"
#include "buffy.h"
#include "redshirt.h"
#include "vampire.h"

#include "game.h"

int main() {  

   bool map[] = { 
         // Room  0  1  2  3  4  5  6  7  8
                  0, 1, 0, 1, 0, 0, 0, 0, 0,   // Room 0
                  1, 0, 1, 0, 1, 0, 0, 0, 0,   // Room 1
                  0, 1, 0, 0, 0, 1, 0, 0, 0,   // Room 2
                  1, 0, 0, 0, 1, 0, 1, 0, 0,   // Room 3
                  0, 1, 0, 1, 0, 1, 0, 1, 0,   // Room 4
                  0, 0, 1, 0, 1, 0, 0, 0, 1,   // Room 5
                  0, 0, 0, 1, 0, 0, 0, 1, 0,   // Room 6
                  0, 0, 0, 0, 1, 0, 1, 0, 1,   // Room 7
                  0, 0, 0, 0, 0, 1, 0, 1, 0    // Room 8
                } ;

   /*

   Room connections in ASCII art:

                0 ---- 1 --- 2
                |      |     |
                3 ---- 4 --- 5
                |      |     |
                6 ---- 7 --- 8

   */




   Game G(9, map, rand()) ;

   G.addToRoom(rand() % 8,new Ghost()) ;

   G.addToRoom(rand() % 8,new Zombie()) ;
   G.addToRoom(rand() % 8,new Zombie()) ;
   G.addToRoom(rand() % 8,new Zombie()) ;
   G.addToRoom(rand() % 8,new Zombie()) ;

   G.addToRoom(rand() % 8,new Human()) ;
   G.addToRoom(rand() % 8,new Human()) ;
   G.addToRoom(rand() % 8,new Human()) ;
   G.addToRoom(rand() % 8,new Human()) ;


   G.addToRoom(rand() % 8,new Doctor()) ;
   G.addToRoom(rand() % 8,new Doctor()) ;
   G.addToRoom(rand() % 8,new Doctor()) ;
   G.addToRoom(rand() % 8,new Doctor()) ;

   G.addToRoom(rand() % 8,new Buffy()) ;
   G.addToRoom(rand() % 8,new Buffy()) ;

   G.addToRoom(rand() % 8,new Vampire()) ;
   G.addToRoom(rand() % 8,new Vampire()) ;
   G.addToRoom(rand() % 8,new Vampire()) ;
   G.addToRoom(rand() % 8,new Vampire()) ;

   G.addToRoom(rand() % 8, new RedShirt()) ;
   G.addToRoom(rand() % 8, new RedShirt()) ;
   G.addToRoom(rand() % 8, new RedShirt()) ;
   G.addToRoom(rand() % 8, new RedShirt()) ;
   G.addToRoom(rand() % 8, new RedShirt()) ;
   G.addToRoom(rand() % 8, new RedShirt()) ;

   G.display() ;

   for (int i=0 ; i < 30 ; i++) {

      cout << "***********************************\n" ;
      cout << "Begin Round #" << i << ":\n" ;
      cout << "***********************************\n" ;

      G.playOneTurn() ;

      cout << "----------------------------------\n" ;
      cout << "Characters in each room:\n" ;
      cout << "----------------------------------\n" ;
      G.display() ;
      cout << "----------------------------------\n" ;
   }

   cout << "Goodbye!\n" ;
   
   return 0;
}
