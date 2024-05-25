#include <stdio.h>
#include <stdlib.h>

typedef struct _NODE {
    int x;  // Key
    int h;  // Value
} NODE;

typedef struct AVLNode {
    NODE data;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
} AVLNode;

int height(AVLNode* node) {
    return node ? node->height : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

AVLNode* search(AVLNode* root, int key) {
    if (root == NULL || root->data.x == key)
        return root;

    if (root->data.x < key)
        return search(root->right, key);

    return search(root->left, key);
}

AVLNode* createNode(NODE data) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(AVLNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

AVLNode* insert(AVLNode* node, NODE data) {
    if (node == NULL)
        return createNode(data);

    if (data.x < node->data.x)
        node->left = insert(node->left, data);
    else if (data.x > node->data.x)
        node->right = insert(node->right, data);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && data.x < node->left->data.x)
        return rightRotate(node);

    if (balance < -1 && data.x > node->right->data.x)
        return leftRotate(node);

    if (balance > 1 && data.x > node->left->data.x) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && data.x < node->right->data.x) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Update function to change the value of `h` for a given key `x`
AVLNode* update(AVLNode* root, int x, int new_h) {
    if (root == NULL)
        return NULL;

    if (x < root->data.x)
        root->left = update(root->left, x, new_h);
    else if (x > root->data.x)
        root->right = update(root->right, x, new_h);
    else
        root->data.h = new_h;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

int exists(AVLNode* root, int x) {
    return search(root, x) != NULL;
}

void inorder(AVLNode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("Key: %d, Value: %d\n", root->data.x, root->data.h);
        inorder(root->right);
    }
}

int main() {
    int Q;
    int q, i;
    int max, tmp;
    AVLNode* root = NULL;

    scanf("%d", &Q);
    while(Q--){
        scanf("%d %d", &q, &i);
        if(q == 1){
            max = 0;
            if (exists(root, i)) {
                tmp = search(root, i)->data.h;
                if(tmp > max) max = tmp;
            }

            if (exists(root, i+1)) {
                tmp = search(root, i+1)->data.h;
                if(tmp > max) max = tmp;
            }

            if (exists(root, i+2)) {
                tmp = search(root, i+2)->data.h;
                if(tmp > max) max = tmp;
            }

            if (exists(root, i+3)) {
                tmp = search(root, i+3)->data.h;
                if(tmp > max) max = tmp;
            }

            max++;

            root = insert(root, (NODE){i, max});
            root = update(root, i, max);
            root = insert(root, (NODE){i+1, max});
            root = update(root, i+1, max);
            root = insert(root, (NODE){i+2, max});
            root = update(root, i+2, max);
            root = insert(root, (NODE){i+3, max});
            root = update(root, i+3, max);

        } else if (q == 2) {
            max = 0;
            if(exists(root, i)) max = search(root, i)->data.h;
            max += 4;
            root = insert(root, (NODE){i, max});
            root = update(root, i, max);

        } else {  // q == 3
            if(exists(root, i)) {
                printf("%d\n", search(root, i)->data.h);
            } else {
                printf("0\n");  // Key doesn't exist
            }
        }
    }

    return 0;
}
