#include <stdio.h>
#include <stdlib.h>

typedef struct NODE{
    int level;
    int space;
    int value;
    double potenV;
    struct NODE *lChild;
    struct NODE *rChild;
} node;

typedef struct LEAFNODES{
    node*  leafNode;
    struct LEAFNODES *nextLeaf;
} lnode;


typedef struct ITEM{
    int W;
    int V;
    struct ITEM* nextItem;
} item;

int insertLeafNode(lnode* leafNodes, node* insNode);
double calcNodePotenial(node* curNode, item* items, int itemSize);

int main(void){
    int i;
    int N, K, tmpW, tmpV;
    double tmpVpW, curVpW, nextVpW;
    int itemIdx, curSpace, curValue, curW, curV;
    int maxValue;
    node *rootNode;
    node *curNode;
    node *childNode;
    node *insertNode;
    lnode *leafNodes;
    item *items, *tmpItem, *curItem, *nextItem;
    int *arrW, *arrV;

    scanf("%d %d", &N, &K);
    items = (item*)malloc(sizeof(item));  
    items->W = 1;  
    items->V = 1001;  
    items->nextItem = NULL;  
    for(i = 0; i < N; i++) {
        tmpItem = (item*)malloc(sizeof(item));
        scanf("%d %d", &(tmpItem->W), &(tmpItem->V));    
        if(!items->nextItem) {
            items->nextItem = tmpItem;
            continue;
        }
        curItem = items;
        nextItem = items->nextItem;
        printf("%f\n", tmpVpW);
        while(nextItem){
            curVpW = curItem->V / (double)curItem->W;
            nextVpW = nextItem->V / (double)nextItem->W;
            if(curVpW >= tmpVpW && tmpVpW >= nextVpW) break;
            curItem = nextItem;
            nextItem = nextItem->nextItem;
        }
        curItem->nextItem = tmpItem;
        tmpItem->nextItem = nextItem;
    }
    
    for(curItem = items->nextItem; curItem; curItem = curItem->nextItem) printf("(%d, %d)\n", curItem->W, curItem->V);
    

    rootNode = (node*)malloc(sizeof(node));
    curNode = rootNode;
    curNode->level = 0;
    curNode->space = K;
    curNode->value = 0;
    curNode->potenV = calcNodePotenial(curNode, items, N);
    curNode->lChild = NULL;
    curNode->rChild = NULL;

    leafNodes = (lnode*)malloc(sizeof(lnode));
    leafNodes->leafNode = NULL;
    leafNodes->nextLeaf = (lnode*)malloc(sizeof(lnode));
    leafNodes->nextLeaf->leafNode = rootNode;
    leafNodes->nextLeaf->nextLeaf = NULL;
    
    maxValue = 0;
    while(curNode){
        leafNodes->nextLeaf = leafNodes->nextLeaf->nextLeaf;
        if((float)maxValue > curNode->potenV){
            curNode = leafNodes->nextLeaf->leafNode;
            continue;
        }

        printf("curNode\n"); //****
        itemIdx = curNode->level;
        curSpace = curNode->space;
        curValue = curNode->value;
        curW = items[itemIdx].W;
        curV = items[itemIdx].V;

        if(!(curNode->lChild) && curSpace > curW){    // make lChild (yes Item)
            printf("lChild\n"); //****
            childNode = (node*)malloc(sizeof(node));
            childNode->level = itemIdx + 1;
            childNode->space = curSpace - curW;
            childNode->value = curValue + curV;
            childNode->potenV = calcNodePotenial(childNode, items, N);
            printf("poten : %f\n", childNode->potenV);
            insertLeafNode(leafNodes, childNode);
            curNode->lChild = childNode;
            if(maxValue < childNode->value) maxValue = childNode->value;
        }
        if(!(curNode->rChild)){                        // make rChild (no Item)
            printf("RChild\n"); //****
            childNode = (node*)malloc(sizeof(node));
            childNode->level = itemIdx + 1;
            childNode->space = curSpace;
            childNode->value = curValue;
            childNode->potenV = calcNodePotenial(childNode, items, N);
            printf("poten : %f\n", childNode->potenV);
            insertLeafNode(leafNodes, childNode);
            curNode->rChild = childNode;
        }
        
        if(leafNodes->nextLeaf) curNode = leafNodes->nextLeaf->leafNode;
        else curNode = NULL;
        
    }

    printf("%d\n", maxValue);


    return 0;
}

int insertLeafNode(lnode* leafNodes, node* insNode){
    lnode *curLeaf, *nextLeaf, *tmpLeaf;

    curLeaf = leafNodes;
    nextLeaf = leafNodes->nextLeaf;
    while(nextLeaf){
        if(curLeaf->leafNode && curLeaf->leafNode->value > insNode->value && insNode->value >nextLeaf->leafNode->value) break;
        curLeaf = nextLeaf;
        nextLeaf = curLeaf->nextLeaf;
    }
    tmpLeaf = (lnode*)malloc(sizeof(lnode));
    tmpLeaf->leafNode = insNode;
    tmpLeaf->nextLeaf = nextLeaf;
    curLeaf->nextLeaf = tmpLeaf;

    return 0;
}

double calcNodePotenial(node* curNode, item* items, int itemSize){
    int i;
    int VpW, tmpW, tmpV; // Value per Weight, Wieght
    int level;
    int curSpace;
    double poten;
        
    level = curNode->level;
    curSpace = curNode->space;

    poten = 0;
    for(i = level; i < itemSize; i++){
        tmpW = items[i].W;
        tmpV = items[i].V;
        printf("\tpoten(%f)\ttmpW(%d)\ttmpV(%d)\n", poten, tmpW, tmpV);
        if(curSpace > tmpW){
            curSpace -= tmpW;
            poten += tmpV;
        }
        else if (0 < curSpace && curSpace < tmpW){
            curSpace = 0;
            poten += tmpV * (curSpace / (float)tmpW);
        }
        if(curSpace == 0) break;        
    }

    return poten;
}