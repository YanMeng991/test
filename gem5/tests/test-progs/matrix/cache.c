#include <stdio.h>

char buf[1024];
int img[200][200];

int main(void){
    FILE *fp = fopen("/home/dongx/gem5/tests/test-progs/matrix/fishing_boat.txt", "r");
    if(fp == NULL){
        printf("Cannot open file.\n");
        return 0;
    }
    int row = 0, col = 0, pixel;
    while(fgets(buf, 1024, fp) != NULL){
        int tCol = 0;
        while(sscanf(buf + tCol * 4, "%d", &pixel) == 1){
            img[row][tCol] = pixel;
            tCol++;
        }
        col = tCol;
        row++;
    }
    printf("Row: %d\n", row);
    printf("Col: %d\n", col);

    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            printf("%03d ", img[i][j]);
        }
        printf("\n");
    }

    return 0;
}
