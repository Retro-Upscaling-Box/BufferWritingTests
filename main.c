#include "fb.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>



int main(){
    fb_t* fb = malloc(sizeof(fb_t));
    fb_init(fb);
    fb_open(fb);
    fb_print_info(fb);

    clock_t start, end, total;

    start = clock();

    while(1){
        double clk = (double)(clock()  % CLOCKS_PER_SEC) * 2 / CLOCKS_PER_SEC;

        if(clk >= 1){
            clk = (1 - (clk - 1));
        }

        int i, j;
        for(i = 0; i < 1200; i++){
            for(j = 0; j < 1920; j++){
                fb_set(fb, j, i, clk * 255, 0, (1 - clk) * 255);
            }
        }
    }

    end = clock();
    total = end - start;

    printf("Took %fs\n", (double)total/CLOCKS_PER_SEC);

    fb_close(fb);
    free(fb);
}
