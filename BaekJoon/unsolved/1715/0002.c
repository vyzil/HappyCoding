#include <stdio.h>
#include <stdlib.h>

typedef struct DECK{
    int num;
    struct DECK* next;
} deck;

int main(void){
    int i, tmp, sum;
    int N;
    deck *rootDeck, *curDeck, *newDeck, *firstDeck, *secondDeck;

    rootDeck = (deck*)malloc(sizeof(deck));
    rootDeck->next = NULL;
    scanf("%d", &N);
    for(i = 0; i < N; i++){
        scanf("%d", &tmp);
        newDeck = (deck*)malloc(sizeof(deck));
        newDeck->num = tmp;
        curDeck = rootDeck;
        while(curDeck->next){
            if(curDeck->next->num > newDeck->num) break;
            curDeck = curDeck->next;
        }
        newDeck->next = curDeck->next;
        curDeck->next = newDeck;
    }

    sum = (rootDeck->next->num) * (N-1);
    N--;    
    for(curDeck = rootDeck->next->next; curDeck; curDeck = curDeck->next){
        sum += (curDeck->num) * N;
        N--;
    }  

    printf("%d\n", sum);

    return 0;
}