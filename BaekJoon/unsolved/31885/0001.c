#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define int long long

typedef struct _ITEM {
    int a;
    int b;
} ITEM;

typedef struct AVLNode {
    ITEM data;
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

AVLNode* createNode(ITEM data) {
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

AVLNode* insert(AVLNode* node, ITEM data) {
    if (node == NULL)
        return createNode(data);

    if (data.a < node->data.a)
        node->left = insert(node->left, data);
    else if (data.a > node->data.a)
        node->right = insert(node->right, data);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && data.a < node->left->data.a)
        return rightRotate(node);

    if (balance < -1 && data.a > node->right->data.a)
        return leftRotate(node);

    if (balance > 1 && data.a > node->left->data.a) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && data.a < node->right->data.a) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

AVLNode* search(AVLNode* root, int key) {
    if (root == NULL || root->data.a == key)
        return root;

    if (root->data.a < key)
        return search(root->right, key);

    return search(root->left, key);
}

void inorder(AVLNode* root, AVLNode* root2, int dist) {
    if (root != NULL) {
        inorder(root->left, root2, dist);
        compare(root->data, root2, dist);
        inorder(root->right, root2, dist);
    }
}


int main(void){
    int i;
    int N, K;
    int startX, startY, endX, endY, res;
    ITEM *items, tmp;
    AVLNode *itemStart = NULL, *itemEnd = NULL;
    
    scanf("%d %d", &N, &K);
    items = (ITEM*)malloc(sizeof(ITEM)*N);
    for(i = 0; i < N; i++) scanf("%d %d", &items[i].a, &items[i].b);
    startX = 0, startY = 0;
    scanf("%d %d", &endX, &endY);

    for(i = 0; i < N; i++){
        itemStart = insert(itemStart, items[i]);
        tmp.a = endX - items[i].a;
        tmp.b = endY - items[i].b;
        itemEnd = insert(itemEnd, tmp);
    }

    res = 6;
    if(K >= 1){ // use 1

    }
    else if(K >= 2){ // use 2

    }
    else if(K >= 3){ // use 3

    }
    else if(K >= 4){ // use 4

    }
    else if(K >= 5){ // use 5
        
    }

    free(items);
    return 0;
}