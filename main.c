#include "fb.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

void fill_itr(fb_t* fb, char r, char g, char b){
    argb_t clr = {b, g, r, 0};

    argb_t* itr;
    for(itr = fb_begin(fb); itr != fb_end(fb); itr++){
        *itr = clr;
    }
}

void fill_loop(fb_t* fb, char r, char g, char b){
    int i, j;

    for(i = 0; i < fb->v_info->yres; i++){
        for(j = 0; j < fb->v_info->xres; j++){
            fb_set(fb, j, i, r, g, b);
        }
    }
}

void time_fill(fb_t* fb, char r, char g, char b, void(*fill)(fb_t*, char, char, char)){
    clock_t start = clock();

    fill(fb, r, g, b);

    clock_t end = clock();

    printf("Took %fs\n", (double)(end - start)/CLOCKS_PER_SEC);
}

int main(){
    fb_t* fb = malloc(sizeof(fb_t));
    fb_init(fb);
    fb_open(fb);
    fb_print_info(fb);

    printf("Loop ");
    time_fill(fb, 255, 100, 100, fill_loop);

    printf("Iter ");
    time_fill(fb, 255, 100, 100, fill_itr);

    fb_close(fb);
    free(fb);
}
