#ifndef BST_H
#define BST_H

#define SIZE (1<<6)

// Node for the link list
	typedef struct Node_ Node;
	struct Node_ {
		int roll;
        char name[SIZE];
		Node* left;
		Node* right;
	};

	// Link list structure
	typedef struct BSTree_ {
		Node* root;
	}BSTree;

	// TODO: Write functions to add/remove an element from the binary tree. 
	// TODO: Write a function to search if an element belongs to the BST
	// TODO: Write a function to print out the whole BST
	Node* search( Node* node, int roll );
	Node* new_node( int roll, char* name );
	
	void print_bst( Node* root );
	
	Node* insert( Node* root, int roll, char* name);

#endif // BST_H
