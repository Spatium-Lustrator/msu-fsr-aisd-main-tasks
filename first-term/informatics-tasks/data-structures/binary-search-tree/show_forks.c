#include <stdio.h>
#include <stdlib.h>

struct bst_node {
    int value;
    struct bst_node *left;
    struct bst_node *right;
};

struct bst_node* create_node(int value) {
    struct bst_node* new_node = malloc(sizeof(struct bst_node));
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

struct bst_node* find_min_node(struct bst_node *node) {

    if (node == NULL) {
        return NULL;
    } else if(node->left != NULL) {
        find_min_node(node->left);
    }

    return node;


}

struct bst_node* insert_node(struct bst_node *node, int value) {
    if (node == NULL) {
        return create_node(value);
    } else if (value < node->value) {
        node->left = insert_node(node->left, value);
    } else if (value > node->value) {
        node->right = insert_node(node->right, value);
    }

    return node;
}

struct bst_node* delete_node(struct bst_node *node, int value) {

    if (node == NULL) {
        return NULL;
    }

    if (value > node->value) {
        node->right = delete_node(node->right, value);
    } else if (value < node->value) {
        node->left = delete_node(node->left, value);
    } else {
        if (node->left == NULL && node->right == NULL) {
            free(node);
            return NULL;
        } else if (node->left == NULL || node->right == NULL) {
            struct bst_node *temp;
            if (node->left == NULL) {
                temp = node->right;
            } else {
                temp = node->left;
            }

            free(node);
            return temp;
        } else {
            struct bst_node *temp = find_min_node(node->right);
            node->value = temp->value;
            node->right = delete_node(node->right, temp->value); 
        }
    }

    return node;

}

struct bst_node* search_node(struct bst_node *node, int value) {
    if (node == NULL || node->value == value) {
        return node;
    } else if (value > node->value) {
        return search_node(node->right, value);
    } else {
        return search_node(node->left, value);
    }
}

void clear(struct bst_node *node) {
    if (node != NULL) {
        clear(node->left);
        clear(node->right);
        free(node);
    }
}

void in_order_traversal(struct bst_node *node) {
    if (node != NULL) {
        in_order_traversal(node->left);
        if (node->left != NULL && node->right != NULL) {
            printf("%d ", node->value);
        }
        in_order_traversal(node->right);
    }
}

int main(void) {

    struct bst_node *root = NULL;
    int value=1;

    scanf("%d", &value);
    root = insert_node(root, value);

    scanf("%d", &value);
    while (value) {
        insert_node(root, value);
        scanf("%d", &value);
    }


    in_order_traversal(root);

    clear(root);

    return 0;
}