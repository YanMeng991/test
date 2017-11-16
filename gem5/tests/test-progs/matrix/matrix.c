#include <stdio.h>
#include "m5_approx_args.h"

//#define LEN 40

int main()
{
    int matrix[LEN][LEN];
    printf("%p\n", matrix);
    
    m5_DECLARE_APPROXIMATE_wrap((uint64_t)matrix, LEN, LEN, 3, sizeof(int));
    for(int i = 0; i < LEN; i++){
        for(int j = 0; j < LEN; j++){
            matrix[i][j] = i;
        }
    }
    
    //printf("%p\n", matrix);

    for(int i = 0; i < LEN; i++){
        for(int j = 0; j < LEN; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    m5_UNDECLARE_APPROXIMATE_wrap((uint64_t)matrix);
    return 0;
}
