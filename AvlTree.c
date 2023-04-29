#include <stdio.h>
#include <stdlib.h>

#define MAX(x, y) x > y ? x : y
#define ull unsigned long long

typedef struct avlnode {
    ull data;
    int height;
    struct avlnode *left, *right;
} *avltree;

int geth(avltree t) {
    if (t == NULL) {
        return -1;
    }
    return t->height;
}

avltree ll(avltree t) {
    avltree ret;
    ret = t->left;
    t->left = ret->right;
    ret->right = t;
    t->height = MAX(geth(t->left), geth(t->right)) + 1;
    ret->height = MAX(geth(ret->left), t->height) + 1;
    return ret;
}

avltree rr(avltree t) {
    avltree ret;
    ret = t->right;
    t->right = ret->left;
    ret->left = t;
    t->height = MAX(geth(t->left), geth(t->right)) + 1;
    ret->height = MAX(geth(ret->right), t->height) + 1;
    return ret;
}

avltree lr(avltree t) {
    t->left = rr(t->left);
    return ll(t);
}

avltree rl(avltree t) {
    t->right = ll(t->right);
    return rr(t);
}

avltree insert(avltree t, ull x) {
    if (t == NULL) {
        t = malloc(sizeof(avltree));
        t->data = x;
        t->height = 0;
        t->left = NULL;
        t->right = NULL;
    } else if (x < t->data) {
        t->left = insert(t->left, x);
        if (geth(t->left) - geth(t->right) == 2) {
            if (x < t->left->data) {
                t = ll(t);
            } else {
                t = lr(t);
            }
        }
    } else if (x > t->data) {
        t->right = insert(t->right, x);
        if (geth(t->right) - geth(t->left) > 2) {
            if (x > t->right->data) {
                t = rr(t);
            } else {
                t = rl(t);
            }
        }
    }
    t->height = MAX(geth(t->left), geth(t->right)) + 1;
    return t;
}

int find(avltree t, ull x) {
    if (t == NULL) {
        return 0;
    }
    if (t->data < x) {
        if (t->right == NULL) {
            return 0;
        }
        return find(t->right, x);
    } else if (t->data > x) {
        if (t->left == NULL) {
            return 0;
        }
        return find(t->left, x);
    }
    return 1;
}

int main() {
    avltree mytree = NULL;
    mytree = insert(mytree, 1);
    mytree = insert(mytree, 2);
    mytree = insert(mytree, 3);
    mytree = insert(mytree, 4);
    printf("%d", find(mytree, 5));
    return 0;
}