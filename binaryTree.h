
#ifndef BINARYTREE_H
#define BINARYTREE_H

// definitions
typedef struct nodetag node;


// function definitions
void inorder(node *root);
node *insertNode(node *root, char name[], int line);
void destroyTree(node **root);


#endif

