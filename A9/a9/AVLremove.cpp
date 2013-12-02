// =============================================================================
// AVLTree.cpp
// ~~~~~~~~~~~
// ANNA ROZANSKY
// implement the remove function of the AVL tree
// =============================================================================

#include <iostream>
#include <vector>
#include <sstream>
#include <stdexcept>
using namespace std; // BAD PRACTICE

const string usage_msg = "AVL Tree Driver. Version 0.2\n"
                         "Author: Anna Rozansky\n"                       
                         "Report bugs to annaroza@buffalo.edu";

/**
 * -----------------------------------------------------------------------------
 * Assignment 9: 
 * - implement this function
 * - to remove a node that has one child: splice it out
 * - if it has two children, put its predecessor in its place then splice
 *   the predecessor. This is not the same strategy as in the lecture slides
 *   which uses the successor. The reason is that you can run the applet
 *   at http://webdiis.unizar.es/asignaturas/EDA/AVLTree/avltree.html
 *   to verify whether your implementation is correct, and that applet uses
 *   the predecessor strategy.
 * - adjust the balance fields correctly, fix balances and rotate
 *   up to the root
 * - all the rotate functions have already been implemented
 * - I STRONGLY suggest that you read and understand the insert function that I
 *   implemented in the file AVLTree.cpp
 * - you can add (private) methods to AVLTree class in AVLTree.h to help out
 * - so the two files your can modify are AVLremove.cpp and AVLTree.h
 *
 * RETURN: 
 * - true if a key was removed
 * - false if the key does not exist
 * -----------------------------------------------------------------------------
 */

template <typename Key>
bool AVLTree<Key>::remove(Key key) {
	//case1 - node to remove has no children
	//			- delete the node
	//			- set parent's pointer to null
	//case2 - node to remove has 1 child
	//		D
	//		 \
	//		  H
	//		 /
	//		F
	//	       / \
	//	      E   G
	//			- make D point to F as its right child
	//			- set F's parent to D
	//case3 - node to remove has 2 children
	//			- put predecessor in its place
	//			- splice the predecessor
	AVLNode* node;
	AVLNode* predecessor;
	AVLNode* child;
	bool found = false;	
	node = search(root_, key);
	if(node == NULL){
		return false;
	}
	else{
		predecessor = node->parent;
		//case 1
		if(node->right == NULL && node->left == NULL){
			if(node == predecessor->left){
				predecessor->left = NULL;	
			}
			if(node == predecessor->right){
				predecessor->right = NULL;
			}
			delete(node);
		}
		//case 2 
		if(node->left == NULL){	//keep node's non-null child, if any
			child = node->right;
		}
		else{
			child = node->left;
		}					//could still be null but that's ok
		if(predecessor == NULL){		//then node is the root
			root_ = NULL;
		}
		else{
			if(predecessor->left == node){
				predecessor->left = child;
			}
			else{
				predecessor->right = child;
			}
		}
		//case 3
		if(node->left != NULL && node->right != NULL){
			child->right = node->right;
		}
		return true;
	}
	return false;
}
