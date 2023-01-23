#ifndef _TWODTREE_H_
#define _TWODTREE_H_

#include <utility>
#include "PNG.h"
#include "RGBAPixel.h"
#include "stats.h"

using namespace std;
using namespace util;

class twoDtree {
private:

   class Node {
   public:
      //Node constructor
      Node(pair<int,int> ul, pair<int,int> lr, RGBAPixel a);

      pair<int,int> upLeft; 
      pair<int,int> lowRight;
      RGBAPixel avg;

      Node * left;

      Node * right;
   };
  
public:

   ~twoDtree();


   twoDtree(const twoDtree & other);


   twoDtree & operator=(const twoDtree & rhs);

   twoDtree(PNG & imIn);

   PNG render();

   void prune(double pct, int tol);

private:

   Node* root;

   int height;

   int width;


   void clear();

   void copy(const twoDtree & other);

   Node * buildTree(stats & s,pair<int,int> ul, pair<int,int> lr);

   void deleteTree(Node* &rootD);

   Node * copyTree(Node* other);

   void changeLeafColour(Node* root, PNG &img);

   void toPrune(Node* &node, double pct, int tol);

   void calculateDistance(Node* &subRoot, Node* &child, double &withinTol, double &totalNodes, int tol);
};

#endif