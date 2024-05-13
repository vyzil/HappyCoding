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
    char checkStr[STR_MAX];
    char tmpDict[ALPHABET];
    char decDict[ALPHABET];
    int  strSize;
    int match;

    for(i = 0; i < STR_MAX; i++) checkStr[i] = 0;
    for(i = 0; i < ALPHABET; i++) tmpDict[i] = 0;

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
        if(tmpDict[atoi(decStr[i])] == 0) tmpDict[atoi(decStr[i])] = count++;
        decPattern[i] = tmpDict[atoi(decStr[i])];
    }

    // Analyze encStrList Pattern 
    // If pattern matches, update decDict
    match = 0;
    for(i = 0; i < iN; i++){
        if(strlen(encStrList[i]) != strSize) continue;
        count = 1;
        for(j = 0; j < ALPHABET; j++) tmpDict[j] = 0;
        for(j = 0; j < strSize; j++){
            if(tmpDict[atoi(encStrList[i][j])] == 0) tmpDict[atoi(encStrList[i][j])] = count++;
            if(decPattern[j] != tmpDict[atoi(encStrList[i][j])]) break;
        }
        if(j < strSize) continue;
        match = 1;
        for(j = 0; j < strSize; j++){
            if(checkStr[j] == 0) checkStr[j] = encStrList[i][j];
            else if(checkStr[j] != encStrList[i][j]) checkStr[j] = -1;
        }
    }

    if(match == 0) {
        printf("IMPOSSIBLE\n");
        goto solve_finale;
    }

    for(i = 0; i < ALPHABET; i++) decDict[i] = '?';
    for(i = 0; i < strSize; i++) {
        if(checkStr[i] <= 0) continue;
        else decDict[atoi(checkStr[i])] = decStr[i];
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

    return;
}

int main(void){
    int iT;
    scanf("%d", &iT);
    while(iT--) solve();

    return 0;
}