#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_MAX 1001
#define ALPHABET 26

// alphabet to index
#define atoi(x) ((x) - 'a')

void solve(){
    int i, j;
    int iN;
    int count, idx, check;
    char **encStrList, decStr[STR_MAX], query[STR_MAX];
    int  decPattern[STR_MAX];
    char patDict[ALPHABET];
    char *tmpDict;
    char *encDict;
    char decDict[ALPHABET];
    char *swap;
    int  strSize;
    int match;

    tmpDict = (char*)malloc(sizeof(char)*ALPHABET);
    encDict = (char*)malloc(sizeof(char)*ALPHABET);
    for(i = 0; i < ALPHABET; i++) {
        patDict[i] = 0;
        encDict[i] = 0;
    }

    // Input
    scanf("%d", &iN);
    encStrList = (char**)malloc(sizeof(char*)*iN);
    for(i = 0; i < iN; i++){
        encStrList[i] = (char*)malloc(sizeof(char)*STR_MAX);
        scanf("%s", encStrList[i]);
    }
    scanf("%s", decStr);
    scanf("%s", query);
    strSize = strlen(decStr);

    // Analyze decStr Pattern
    count = 1;
    for(i = 0; i < strSize; i++){
        if(patDict[atoi(decStr[i])] == 0) patDict[atoi(decStr[i])] = count++;
        decPattern[i] = patDict[atoi(decStr[i])];
    }

    // Analyze encStrList Pattern 
    // If pattern matches, update decDict
    match = 0;
    for(i = 0; i < iN; i++){
        if(strlen(encStrList[i]) != strSize) continue;
        count = 1;
        for(j = 0; j < ALPHABET; j++) {
            patDict[j] = 0;
            tmpDict[j] = 0;
        }
        for(j = 0; j < strSize; j++){
            if(patDict[atoi(encStrList[i][j])] == 0) patDict[atoi(encStrList[i][j])] = count++;
            if(decPattern[j] != patDict[atoi(encStrList[i][j])]) break;
            if(encDict[atoi(decStr[j])] == 0) tmpDict[atoi(decStr[j])] = encStrList[i][j];
            else if(encDict[atoi(decStr[j])] != encStrList[i][j]) tmpDict[atoi(decStr[j])] = -1;
            else tmpDict[atoi(decStr[j])] = encDict[atoi(decStr[j])];
        }
        if(j < strSize) continue;
        match = 1;
        swap = encDict;
        encDict = tmpDict;
        tmpDict = swap;
    }

    if(match == 0) {
        printf("IMPOSSIBLE\n");
        goto solve_finale;
    }

    for(i = 0; i < ALPHABET; i++) decDict[i] = '?';
    for(i = 0; i < ALPHABET; i++) {
        if(encDict[i] <= 0) continue;        
        decDict[atoi(encDict[i])] = 'a' + i;
    }
    // case : if 25 alphabet is known
    count = 0;
    for(i = 0; i < ALPHABET; i++){
        if(decDict[i] == '?') count++;
    }

    check = 0;
    if(count == 1){
        for(i = 0; i < ALPHABET; i++){
            if(decDict[i] == '?') idx = i;
            else check |= (1 << atoi(decDict[i]));
        }
        check = (1 << ALPHABET) - check - 1;
        for(i = 0; (check >> i) > 1 ; i++);
        decDict[idx] = 'a' + i;
    }

    // decrypt query
    for(i = 0; i < strlen(query); i++){
        printf("%c", decDict[atoi(query[i])]);
    }
    printf("\n");

solve_finale:
    for(i = 0; i < iN; i++) free(encStrList[i]);
    free(encStrList);
    free(encDict);
    free(tmpDict);

    return;
}

int main(void){
    int iT;
    scanf("%d", &iT);
    while(iT--) solve();

    return 0;
}