/* MAXまでの素数をすべて出力する。*/

#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX 1000000000

int main(){
    unsigned long max = (MAX >> 1);
    int i,j,s=sqrt(max),n=max,m;
    char *prime = (char *)malloc(max >> 3);

    for(i=1; i ^ s; i++) {
        if(! (prime[ i >> 3 ] & (1 << (i & 0x7))) ) {

            #pragma omp parallel for
            for(j = i + (i << 1) + 1; j < max; j += (i << 1) + 1) {
                if(!(prime[ j >> 0x3 ] & (0x1 << (j & 0x7))) ) {
                    prime[ j >> 3 ] |= (1 << (j & 0x7));
                }
            }
        }
    }

    #pragma omp parallel for
    for(i=1; i < max; i++) {
        if((prime[ i >> 3 ] & (1 << (i & 0x7)))) {
            --n;
        }
    }

    printf("%d\n", n);
    free(prime);
    return 0;
}
