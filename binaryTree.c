/**
 * File used to build the binary tree
 */


#include "queue.h"
#include "binaryTree.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// definitions
#define MAX 30 // assuming no identifier is longer than 16 characters

void insertHelper(node *root, node *target); //not "public"; aka not in header
void inorderHelper(node *root);
void destroyTreeHelper(node *root);
int isLeaf(node *root);


// node in the binary tree
struct nodetag {
    char identifier[MAX];
    node *leftChild;
    node *rightChild;
   
    //queue
    qNode *queue;
    qNode *rear;
};

/* Insert into the binary tree
 * - The node structure will be created dynamically
 * - Uses a helper function to insert when and indentical
 *   indentifier is found within the tree
 */
node *insertNode(node *root, char name[], int line){
    //make this the root node
    if(!root){
        root = malloc(sizeof(node));
        if(!root) printf("Error allocating memory"), exit(100);

        // initialize the node
        strcpy(root->identifier, name);
        root->queue = NULL, root->rear = NULL;
        root->leftChild = NULL, root->rightChild = NULL;
        enqueue(&root->queue, &root->rear, line);
        return root;
    }
    
    if(strcmp(name, root->identifier) < 0 ){
        // continue left
        root->leftChild = insertNode(root->leftChild, name, line);
    }
    else if(strcmp(name, root->identifier) > 0){
        // continue right
        root->rightChild = insertNode(root->rightChild, name, line);
    }
    // identifier already exists in the tree
    else
        enqueue(&root->queue, &root->rear, line);

    return root; 
}


/* inorder traversal of the list */
void inorder(node *root){
    if(!root){
        printf("Tree is empty!\n");
        return;
    }
    // recursive helper
    inorderHelper(root);
}

/* Recursive helper for the inorder traversal */
void inorderHelper(node *root){
    if(!root) return;
    
    inorderHelper(root->leftChild);
    
    //print the root and the queue
    printf("%-*s", MAX, root->identifier);
    //print queue. 'MAX' specifies formatting for spacing
    printQueue(root->queue, MAX);
    printf("\n");
    
    
    inorderHelper(root->rightChild);
}

/* Simple check for leaf nodes */
int isLeaf(node *root){
    if(!root->rightChild && !root->leftChild)
        return 1;
    return 0;
}

/* Removes the tree from memory */
void destroyTree(node **root){
    if(!*root) {
        printf("There is no tree to destroy.\n");
        return;
    }
    
    // recrusive helper
    destroyTreeHelper(*root);
    *root = NULL; // update root pointer
}

/* Recursive helper for deleting the tree */
void destroyTreeHelper(node *root){
    if(!root) return;

    if(root->leftChild && isLeaf(root->leftChild)){
        // free queue
        destroyQueue(root->leftChild->queue);
        printf("Deleted Node: %s\n", root->leftChild->identifier);
        //free node
        free(root->leftChild); 
    } else destroyTreeHelper(root->leftChild);

    if(root->rightChild && isLeaf(root->rightChild)){
        // free queue
        destroyQueue(root->rightChild->queue);
        printf("Deleted Node: %s\n", root->rightChild->identifier);
        // free node
        free(root->rightChild);
    } else destroyTreeHelper(root->rightChild);

    // free queue
    destroyQueue(root->queue);
    printf("Deleted Node: %s\n", root->identifier);
    // free queue
    free(root);
}





