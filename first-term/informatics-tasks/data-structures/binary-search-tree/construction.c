#include <stdlib.h>
#include <stdio.h>

typedef struct bst_node {
    int value;
    int size_of_subtree;
    struct bst_node *left;
    struct bst_node *right;

} node;

node* create_node(int value) {
    struct bst_node *new_node = malloc(sizeof(struct bst_node));
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->size_of_subtree = 1;

    return new_node;

}

void update_size_of_subtree(node *root) {
    root->size_of_subtree = 1;
    if (root->left != NULL) root->size_of_subtree+=root->left->size_of_subtree;
    if (root->right != NULL) root->size_of_subtree+=root->right->size_of_subtree;
}

int insert_node(node **root, int value) {
    int position, size_of_left_subtree=0;
    if (*root == NULL) {
        *root = create_node(value);

        return 0;
    }

    if (value > (*root)->value) {
        position = insert_node(&((*root)->left), value);
    }

    if (value < (*root)->value) {
        if ((*root)->left != NULL) {
            size_of_left_subtree = (*root)->left->size_of_subtree;
        }

        position = size_of_left_subtree + insert_node(&((*root)->right), value) + 1;
    }

    update_size_of_subtree(*root);

    return position;
}

node* find_end_node(node* root) {
    node* current = root;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

void delete_node(node **root, int target_position) {
    int size_of_left_subtree = 0;

    if (*root == NULL) return;
    
    if ((*root)->left != NULL) {
        size_of_left_subtree = (*root)->left->size_of_subtree;
    }

    if (target_position < size_of_left_subtree) {
        delete_node(&(*root)->left, target_position);
        update_size_of_subtree(*root);
    }

    else if (target_position == size_of_left_subtree) {
        node *current = *root;

        if (current->left == NULL && current->right == NULL) {
            free(current);
            *root = NULL;

        } else if (current->left == NULL) {
            *root = current->right;
            free(current);

        } else if (current->right == NULL) {
            *root = current->left;
            free(current);

        } else {
            current->value = find_end_node(current->right)->value;
            delete_node(&current->right, 0);
            update_size_of_subtree(*root);

        }

    }
    else {
        delete_node(&(*root)->right, target_position - size_of_left_subtree - 1);
        update_size_of_subtree(*root);
    }
}

void clear(node *root) {
    if (root != NULL) {
        clear(root->left);
        clear(root->right);
        free(root);
    }
}

int main(void) {
    node *root = NULL;
    int n, command, value, i;


    scanf("%d", &n);

    for (i=0; i<n; i++) {
        scanf("%d %d", &command, &value);

        switch (command) {
        case 1:
            printf("%d\n", insert_node(&root, value));
            break;

        case 2:
            delete_node(&root, value);
            break;
        
        default:
            break;
        }
    }

    clear(root);
    return 0;
}