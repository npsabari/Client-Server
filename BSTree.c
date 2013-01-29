/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : BSTree.c

* Purpose : Networks Assignment 

* Creation Date : 30-01-2013

* Last Modified : Wednesday 30 January 2013 03:00:13 AM IST

* Created By : npsabari

_._._._._._._._._._._._._._._._._._._._._.*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "BSTree.h"

Node* new_node(int roll, char* name){
    Node* node = (Node *)malloc(sizeof(Node));
    node->roll = roll;
    strcpy(node->name, name);
    node->left = node->right = NULL;
}

Node* search(Node* head, int roll){
    if(head == NULL || roll == head->roll)
        return head;
    return ( roll <= head->roll ? search(head->left, roll): search(head->right, roll) );
}

Node* insert(Node* root, int roll, char* name){
    if(root == NULL)
        return (root = new_node(roll, name));
    if(roll <= root->roll)
        root->left == NULL ? (root->left = new_node(roll, name)) : insert(root->left, roll, name);
    else
        root->right == NULL ? ( root->right = new_node(roll, name)) : insert(root->right, roll, name);
    return root;
}

void print_bst(Node* root){
    if(root == NULL)
        return;
    print_bst(root->left);
    printf("%d %s\n", root->roll, root->name);
    print_bst(root->right);
}

