#include <stdio.h>

#define NUM_MAX 100000

int main(void){
    int i, j, k;
    int map[3][3];
    int sum, line, tmp;

    k = 1;
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++) {
            scanf("%d", &map[i][j]);
            if(map[i][j] == 0) map[i][j] =  NUM_MAX;
        }
    }

    sum = NUM_MAX;
    for(i = 0; i < 3; i++) {
        line = 0;
        for(j = 0; j < 3; j++) line += map[i][j];
        if(line < NUM_MAX) sum = line;
        
        line = 0;
        for(j = 0; j < 3; j++) line += map[j][i];
        if(line < NUM_MAX) sum = line;

        line = map[0][0] + map[1][1] + map[2][2];
        if(line < NUM_MAX) sum = line;
        
        line = map[2][0] + map[1][1] + map[0][2];
        if(line < NUM_MAX) sum = line;
    }

    if(sum < NUM_MAX){ // Can calculate one line
        for(i = 0; i < 3; i++) {
            line = 0;
            for(j = 0; j < 3; j++) line += map[i][j];
            if(NUM_MAX <= line && line < NUM_MAX*2){
                line -= NUM_MAX;
                line = sum - line;
                for(j = 0; j < 3 ; j++){
                    if(map[i][j] == NUM_MAX) map[i][j] = line;
                }
            }

            line = 0;
            for(j = 0; j < 3; j++) line += map[j][i];
            if(NUM_MAX <= line && line < NUM_MAX*2){
                line -= NUM_MAX;
                line = sum - line;
                for(j = 0; j < 3 ; j++){
                    if(map[j][i] == NUM_MAX) map[j][i] = line;
                }
            }            
        }

        for(i = 0; i < 3; i++) {
            line = 0;
            for(j = 0; j < 3; j++) line += map[i][j];
            if(NUM_MAX <= line && line < NUM_MAX*2){
                line -= NUM_MAX;
                line = sum - line;
                for(j = 0; j < 3 ; j++){
                    if(map[i][j] == NUM_MAX) map[i][j] = line;
                }
            }
        }
    }
    else { // Can not calculate one line
        sum = 0;
        for(i = 0; i < 3; i++) {
            line = 0;
            for(j = 0; j < 3; j++) line += map[i][j];
            if(sum < line) sum = line;
        }
        
        for(i = 0; i < 3; i++) {
            line = 0;
            for(j = 0; j < 3; j++) line += map[i][j];
            for(j = 0; j < 3; j++){
                if(map[i][j] == NUM_MAX) map[i][j] = NUM_MAX + sum - line;
            }
        }

        line = map[0][0] + map[0][1] + map[0][2];
        tmp = map[0][0] + map[1][1] + map[2][2];
        if(tmp < 3* NUM_MAX) tmp = map[2][0] + map[1][1] + map[0][2];
        tmp = (line - tmp + 2* NUM_MAX) / 2;
        for(i = 0; i < 3; i++){
            for(j = 0; j < 3; j++) {
                if(map[i][j] >= NUM_MAX) map[i][j] = map[i][j] - NUM_MAX + tmp;
            }
        }
    }

    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++) printf("%d ", map[i][j]);
        printf("\n");
    }

    return 0;
}