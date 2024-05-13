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
    int count;
    char **encStrList, decStr[STR_MAX], query[STR_MAX];
    int  decPattern[STR_MAX];
    char tmpDict[ALPHABET] = {0, };
    char decDict[ALPHABET] = {0, };
    char encDict[ALPHABET] = {0, };
    int match;

    scanf("%d", &iN);
    encStrList = (char**)malloc(sizeof(char*)*iN);
    for(i = 0; i < iN; i++){
        encStrList[i] = (char*)malloc(sizeof(char)*STR_MAX);
        scanf("%s", encStrList[i]);
    }

    scanf("%s", decStr);
    scanf("%s", query);

    // decStr Pattern
    count = 1;
    for(i = 0; decStr[i]; i++){
        if(tmpDict[atoi(decStr[i])] == 0) tmpDict[atoi(decStr[i])] = count++;
        decPattern[i] = tmpDict[atoi(decStr[i])];
    }

    // Analyze encStrList Pattern 
    // If pattern matches, update decDict
    match = 0;
    for(i = 0; i < iN; i++){
        count = 1;
        for(j = 0; j < ALPHABET; j++) tmpDict[j] = 0;
        for(j = 0; j < encStrList[i][j]; j++){
            if(tmpDict[atoi(encStrList[i][j])] == 0) tmpDict[atoi(encStrList[i][j])] = count++;
            if(decPattern[j] != tmpDict[atoi(encStrList[i][j])]) break;
        }
        if(encStrList[i][j] == '\0') {
            match = 1;
            for(j = 0; j < encStrList[i][j]; j++){
                if(encDict[atoi(decStr[j])] == 0) {
                    decDict[atoi(encStrList[i][j])] = decStr[j];
                    encDict[atoi(decStr[j])] = encStrList[i][j];
                }
                else if (encDict[atoi(decStr[j])] == '?'){
                    decDict[atoi(encStrList[i][j])] = '?';
                }
                else if ((encDict[atoi(decStr[j])] != encStrList[i][j])) {
                    decDict[atoi(encDict[atoi(decStr[j])])] = '?';
                    decDict[atoi(encStrList[i][j])] = '?';
                    encDict[atoi(decStr[j])] = '?';
                }
            }
        }
    }
    if(match == 0) {
        printf("IMPOSSIBLE\n");
        goto solve_finale;
    }

    count = 0;
    for(i = 0; i < ALPHABET; i++){
        if(decDict[i] == 0) decDict[i] = '?';
        if(decDict[i] == '?') count++;
    }
    // case : if 25 alphabet is known
    int idx, check = 0;
    if(count == 1){
        for(i = 0; i < ALPHABET; i++){
            if(decDict[i] == '?') idx = i;
            else check |= (1 << atoi(decDict[i]));
        }
        check = (1 << ALPHABET) - check;
        for(i = 0; (check >> i) > 1 ; i++);
        decDict[idx] = i + 'a';
    }

    // decrypt query
    for(i = 0; query[i]; i++){
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