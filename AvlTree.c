#include <stdio.h>
#include <stdlib.h>

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define ull unsigned long long

typedef struct avlNode {
    ull data;
    int height;
    struct avlNode *left, *right;
} *AvlTree;

AvlTree new_node(ull x) {
    AvlTree ret = malloc(sizeof(struct avlNode));
    ret->data = x;
    ret->height = 0;
    ret->left = NULL;
    ret->right = NULL;
    return ret;
}

int get_height(AvlTree t) {
    if (t == NULL) {
        return -1;
    }
    return t->height;
}

AvlTree ll(AvlTree t) {
    AvlTree ret;
    ret = t->left;
    t->left = ret->right;
    ret->right = t;
    t->height = MAX(get_height(t->left), get_height(t->right)) + 1;
    ret->height = MAX(get_height(ret->left), t->height) + 1;
    return ret;
}

AvlTree rr(AvlTree t) {
    AvlTree ret;
    ret = t->right;
    t->right = ret->left;
    ret->left = t;
    t->height = MAX(get_height(t->left), get_height(t->right)) + 1;
    ret->height = MAX(get_height(ret->right), t->height) + 1;
    return ret;
}

AvlTree lr(AvlTree t) {
    t->left = rr(t->left);
    return ll(t);
}

AvlTree rl(AvlTree t) {
    t->right = ll(t->right);
    return rr(t);
}

AvlTree insert(AvlTree t, ull x) {
    if (t == NULL) {
        t = new_node(x);
    } else if (x < t->data) {
        t->left = insert(t->left, x);
        if (get_height(t->left) - get_height(t->right) == 2) {
            if (x < t->left->data) {
                t = ll(t);
            } else {
                t = lr(t);
            }
        }
    } else if (x > t->data) {
        t->right = insert(t->right, x);
        if (get_height(t->right) - get_height(t->left) == 2) {
            if (x > t->right->data) {
                t = rr(t);
            } else {
                t = rl(t);
            }
        }
    }
    t->height = MAX(get_height(t->left), get_height(t->right)) + 1;
    return t;
}

int find(AvlTree t, ull x) {
    if (t == NULL) {
        return 0;
    }
    if (t->data < x) {
        if (t->right == NULL) {
            return 0;
        }
        return find(t->right, x);
    }
    if (t->data > x) {
        if (t->left == NULL) {
            return 0;
        }
        return find(t->left, x);
    }
    return 1;
}

int main() {
    AvlTree myTree = NULL;
    for (int i = 0; i < 5; i++) {
        myTree = insert(myTree, i + 1);
    }
    printf("%d", find(myTree, 6));

    return 0;
}