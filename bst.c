#include <assert.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include "error.h"
// each tree node contains an integer key and pointers to left and right children nodes
struct node {
    int key;
    struct node *left;
    struct node *right;
};

// tree's beginning is called the root
struct node *root = NULL;

// search for `value` starting with candidate
// return address of `element->left` or `element->right` whichever leads to searched node
struct node **tree_search(struct node **candidate, int value) {
    if (candidate == NULL || *candidate == NULL) {
        return candidate;
    }

    struct node *element = *candidate;
    if (value < element->key) {
        return tree_search(&element->left, value);
    }
    if (value > element->key) {
        return tree_search(&element->right, value);
    }
    return candidate;
}

// insert new node with `value`
struct node* tree_insert(int value) {
    struct node *element = (struct node*) malloc(sizeof(struct node));
    element->key = value;
    element->left = NULL;
    element->right = NULL;

    struct node **ppnode = tree_search(&root, value);
    *ppnode = element;
    return element;
}

// destroy tree (recursively free all allocated memory)
void tree_destroy(struct node *pnode) {
    if (pnode != NULL) {
        tree_destroy(pnode->left);
        tree_destroy(pnode->right);
        free(pnode);
        pnode = NULL;
    }
}

// global variables, required
FILE *fpout;
size_t visited;

// function called anytime a tree node is visited
// this implementation checks if node's value is equal to expected one
void tree_visit(struct node *pnode) {
    int key;
    if (fscanf(fpout, "%d", &key) != 1) {
        error(EXIT_FAILURE, 0, "Expected no more data, but got %d", pnode->key);
    }
    if (key != pnode->key) {
        error(EXIT_FAILURE, 0, "Expected node with key %d but got %d", key, pnode->key);
    }
    visited++;
}

void tree_preorder(struct node *pnode) {
   if (pnode==NULL)
    return;
   tree_visit(pnode);
    tree_preorder(pnode->left);
    tree_preorder(pnode->right);


}

void tree_inorder(struct node *pnode) {
    if(pnode==NULL)
        return;
        tree_inorder(pnode->left);
        tree_visit(pnode);
        tree_inorder(pnode->right);

}

void tree_postorder(struct node *pnode) {
   if(pnode==NULL)
    tree_postorder(pnode->left);
    tree_postorder(pnode->right);
    tree_visit(pnode);
   }

int main(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        // open file and insert every number in it onto a bst
        FILE *fp = fopen(argv[i], "r");
        int x, size = 0;
        while (fscanf(fp, "%d", &x) == 1) {
            tree_insert(x);
            size++;
        }
        fclose(fp);

        char filename[strlen(argv[i]) + 10];

        // run pre-order and check if ok
        printf("pre-order\n");
        strcpy(filename, argv[i]);
        strcat(filename, "-pre");
        fpout = fopen(filename, "r");
        visited = 0;
        tree_preorder(root);
        fclose(fpout);

        if (visited != size) {
            error(EXIT_FAILURE, 0, "Pre-order visited %d nodes out of %d available", visited, size);
        }

        // run in-order and check if ok
        printf("in-order\n");
        strcpy(filename, argv[i]);
        strcat(filename, "-in");
        fpout = fopen(filename, "r");
        visited = 0;
        tree_inorder(root);
        fclose(fpout);

        if (visited != size) {
            error(EXIT_FAILURE, 0, "In-order visited %d nodes out of %d available", visited, size);
        }

        // run post-order and check if ok
        printf("post-order\n");
        strcpy(filename, argv[i]);
        strcat(filename, "-post");
        fpout = fopen(filename, "r");
        visited = 0;
        tree_postorder(root);
        fclose(fpout);

        if (visited != size) {
            error(EXIT_FAILURE, 0, "Post-order visited %d nodes out of %d available", visited, size);
        }

        tree_destroy(root);
        root = NULL;
    }
    return 0;
}
