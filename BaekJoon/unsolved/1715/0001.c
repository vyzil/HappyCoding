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

    sum = 0;
    firstDeck = rootDeck->next;
    secondDeck = firstDeck->next;
    while(secondDeck){
        rootDeck->next = secondDeck->next;   
        firstDeck->num += secondDeck->num;
        sum += firstDeck->num;
        free(secondDeck);
        
        curDeck = rootDeck;
        while(curDeck->next){
            if(curDeck->next->num > firstDeck->num) break;
            curDeck = curDeck->next;
        }
        firstDeck->next = curDeck->next;
        curDeck->next = firstDeck;
        
        // Epilogue
        firstDeck = rootDeck->next;
        secondDeck = firstDeck->next;
    }

    printf("%d\n", sum);

    return 0;
}