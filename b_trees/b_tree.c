#include <stdio.h>
#include <stdlib.h>

/**
 * Fixed integer used to express the lower and upper bounds
 * on the number of keys that a node can contain.
 * We chose this value randomly,
 */
const int MINIMUM_DEGREE = 4;  //2 is the minimum possible


const int MIN_NUMBER_KEYS = MINIMUM_DEGREE - 1;
const int MAX_NUMBER_KEYS = (2 * MINIMUM_DEGREE) - 1;
const int MIN_NUMBER_NODES = MINIMUM_DEGREE;
const int MAX_NUMBER_NODES = 2 * MINIMUM_DEGREE;

/**
 * Struct to represent the b-tree node structure.
 *
 * int leaf - boolean to indicate whether the node is a leaf or not.
 * int numKeys - total number of keys currently in the node.
 * int keys[] - the array of keys stored in the node.
 * struct node children[] - the pointers to the children of the node. If leaf, this value is NULL.
 */
typedef struct node {
  int leaf;
  int numKeys;
  int keys[MAX_NUMBER_KEYS];
  struct node* children[MAX_NUMBER_NODES];
} bTreeNode;

/**
 * Function headers
 */
int isLeaf(bTreeNode* node);
bTreeNode* createEmptyTree(FILE* file);
bTreeNode* search(bTreeNode* node, int searchValue, int *returnIndex);
bTreeNode* split(bTreeNode* parent, int index);
void insertKey(bTreeNode* root, int key);
void deleteKey(bTreeNode* root, int key);
void writeToDisk(FILE* file, bTreeNode* node);
bTreeNode* readFromDisk(FILE* file, bTreeNode* node, int index);

int main() {

  FILE* file;
  bTreeNode* root;

  if( ((file = fopen("bTree.txt", "w+")) != NULL) ){
    puts("The file could not be opened!");
    return 9;
  }

  root = createEmptyTree(file);

  return 0;
}

/**
 * Function that checks if a node is a leaf
 * @param  node [the node to check]
 * @return      [1 if is leaf, 0 if it's not]
 */
int isLeaf(bTreeNode* node) {

  int isLeaf = 0;

  if (node->leaf == 1) {
    isLeaf = 1;
  }

  return isLeaf;
}

/**
 * Function that initiates a B-tree
 * @return root [a pointer to the new created tree]
 */
bTreeNode* createEmptyTree(FILE* file) {

  bTreeNode *root = (bTreeNode*) malloc(sizeof(bTreeNode));
  root->leaf = 1;
  root->numKeys = 0;
  // TODO: implement the function to write to disk
  writeToDisk(file, root);

  return root;
}

/**
 * Function that search for a given key in a B-Tree
 * @param node        [the node of the tree to search]
 * @param searchValue [the value given to search]
 * @param returnIndex [the index of the key, if found]
 * @return            [the node that contains the key, and the index of the found key, or NULL]
 */
bTreeNode* search(bTreeNode* node, int searchValue, int *returnIndex) {

  int i = 1;

  if (isLeaf(node)) {
    return NULL;
  }

  while (i <= node->numKeys && searchValue > node->keys[i]) {
    i++;
  }

  if (i <= node->numKeys && node->keys[i] == searchValue) {
    *returnIndex = i;
    return node;
  } else {
    // TODO: implement readFromDisk to read the next node
  }
  return node;  //this path wasn't cover with a return
}

/**
* Function that write a bTreeNote to a file
* @return NUL if the operation was unsucessful
*/
void writeToDisk(FILE *file, bTreeNode* root) {

  return;
}
