#include <stdio.h>
#include <stdlib.h>

#define NO_BOMB '2'

/*
 * 
 * '.' : 0x2E 8b_0010_1110
 * 'X' : 0x58 8b_0101_1000
 * 'O' : 0x4F 8b_0100_1111
 * '2' : 0x32 8b_0010_0010
 * 
 */

int main(void){
    int i, j;
    int x, y;
    int N;
    char **map;

    scanf("%d", &N);
    map = (char**)malloc(sizeof(char*)*N);
    for(i = 0; i < N; i++) {
        map[i] = (char*)malloc(sizeof(char)*(N+1));
        scanf("%s", map[i]);
    }

    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            if(map[i][j] == 'O'){
                for(x = i-1, y = j; 0 <= x && ((map[x][y] & 0b11) == 0b10); map[x][y] = NO_BOMB, x--);
                for(x = i+1, y = j; x < N  && ((map[x][y] & 0b11) == 0b10); map[x][y] = NO_BOMB, x++);
                for(x = i, y = j-1; 0 <= y && ((map[x][y] & 0b11) == 0b10); map[x][y] = NO_BOMB, y--);
                for(x = i, y = j+1; y < N  && ((map[x][y] & 0b11) == 0b10); map[x][y] = NO_BOMB, y++);
            }
        }
    }

    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            if(map[i][j] == '.') map[i][j] = 'B';
            if(map[i][j] == NO_BOMB) map[i][j] = '.';
        }
    } 

    for(i = 0; i < N; i++) printf("%s\n", map[i]);
    
    
    for(i = 0; i < N; i++) free(map[i]);
    free(map);

    return 0;
}