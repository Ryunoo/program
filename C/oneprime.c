/*MAX番目の素数を出力*/
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX 1795

int main(){
    int max = MAX/2;
    int i=1,j,s=sqrt(max),m,n=9999999;
    char *prime = (char *)malloc(max >> 3);
    
    while(n) {
        m = (i << 1) + 1;

        if(!(prime[ i >> 3 ] & (1 << (i & 0x7)))) {

            if(i < s) {
                #pragma omp parallel for
                for(j = i+m; j < max; j += m){
                    if(!(prime[ j >> 0x3 ] & (0x1 << (j & 0x7))) ) {
                        prime[ j >> 3 ] |= (1 << (j & 0x7));
                    }
                }
            }
            --n;
        }
        ++i;
    }

    printf("%d\n", (i-1)*2+1);

    free(prime);
    return 0;
}

