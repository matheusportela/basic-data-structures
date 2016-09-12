#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* right;
    struct node* left;
    struct node* parent;
};

struct tree {
    struct node* root;
};

struct tree* create_tree();
void delete_tree(struct tree* tree);
struct node* search_tree(struct tree* tree, int data);
void print_tree(struct tree* tree);
struct node* create_node(int data);
void transplant_node(struct tree* tree, struct node* old, struct node* new);
struct node* minimum_node(struct node* node);
void delete_node(struct tree* tree, struct node* node);
void insert_node(struct tree* tree, struct node* node);
void inorder_walk(struct node* node);
struct node* search_node(struct node* node, int data);
void print_node(struct node* node);

int main() {
    printf("Creating tree\n");
    struct tree* tree = create_tree();

    printf("\nInserting 6 nodes to the tree\n");
    insert_node(tree, create_node(6));
    insert_node(tree, create_node(5));
    insert_node(tree, create_node(7));
    insert_node(tree, create_node(5));
    insert_node(tree, create_node(2));
    insert_node(tree, create_node(8));
    print_tree(tree);

    printf("\nSearching for tree \"7\"\n");
    print_node(search_tree(tree, 7));

    printf("\nSearching for tree \"9\", which is not in the tree\n");
    print_node(search_tree(tree, 9));

    printf("\nDeleting \"5\"\n");
    delete_node(tree, search_tree(tree, 5));
    print_tree(tree);

    printf("\nDeleting tree\n");
    delete_tree(tree);

    return 0;
}

struct tree* create_tree() {
    struct tree* tree = malloc(sizeof(struct tree));
    tree->root = NULL;
    return tree;
}

void delete_tree(struct tree* tree) {
    while (tree->root)
        delete_node(tree, tree->root);
    free(tree);
}

struct node* search_tree(struct tree* tree, int data) {
    return search_node(tree->root, data);
}

void print_tree(struct tree* tree) {
    printf("Tree:\n");
    inorder_walk(tree->root);
}

struct node* create_node(int data) {
    struct node* node = malloc(sizeof(struct node));
    node->data = data;
    node->right = NULL;
    node->left = NULL;
    node->parent = NULL;
    return node;
}

void transplant_node(struct tree* tree, struct node* old, struct node* new) {
    if (old->parent == NULL)
        tree->root = new;
    else if (old == old->parent->left)
        old->parent->left = new;
    else
        old->parent->right = new;

    if (new != NULL)
        new->parent = old->parent;
}

struct node* minimum_node(struct node* node) {
    if (node == NULL || node->left == NULL)
        return node;
    else
        minimum_node(node->left);
}

void delete_node(struct tree* tree, struct node* node) {
    struct node* minimum;

    if (node->left == NULL) {
        transplant_node(tree, node, node->right);
    } else if (node->right == NULL) {
        transplant_node(tree, node, node->left);
    } else {
        minimum = minimum_node(node->right);

        if (minimum->parent != node) {
            transplant_node(tree, minimum, minimum->right);
            minimum->right = node->right;
            minimum->right->parent = minimum;
        }

        transplant_node(tree, node, minimum);
        minimum->left = node->left;
        minimum->left->parent = minimum;
    }

    free(node);
}

void insert_node(struct tree* tree, struct node* node) {
    struct node* root = tree->root;
    struct node* parent = NULL;

    while (root != NULL) {
        parent = root;

        if (node->data < root->data)
            root = root->left;
        else
            root = root->right;
    }

    node->parent = parent;

    if (parent == NULL)
        tree->root = node;
    else if (node->data < parent->data)
        parent->left = node;
    else
        parent->right = node;
}

void inorder_walk(struct node* node) {
    if (node != NULL) {
        inorder_walk(node->left);
        print_node(node);
        inorder_walk(node->right);
    }
}

struct node* search_node(struct node* node, int data) {
    if (node == NULL || node->data == data)
        return node;

    if (data < node->data)
        return search_node(node->left, data);
    else
        return search_node(node->right, data);
}

void print_node(struct node* node) {
    printf("Node: ");

    if (node) {
        printf("%d (parent: ", node->data);

        if (node->parent)
            printf("%d", node->parent->data);
        else
            printf("nil");

        printf(",\tleft: ");

        if (node->left)
            printf("%d", node->left->data);
        else
            printf("nil");

        printf(",\tright: ");

        if (node->right)
            printf("%d", node->right->data);
        else
            printf("nil");

        printf(")\n");
    } else {
        printf("nil\n");
    }
}
