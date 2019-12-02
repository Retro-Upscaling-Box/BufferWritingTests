#ifndef __FB_H
#define __FB_H

#include <linux/fb.h>

typedef struct _argb
{
    char b, g, r, a;
} argb_t;

typedef struct _fb
{
    // pointer to an open framebuffer and its size
    char* fb;
    long size;

    // framebuffer file descriptor
    int fbfd;

    // Info about screen and framebuffer
	struct fb_var_screeninfo* v_info;
	struct fb_fix_screeninfo* f_info;
} fb_t;

void fb_init(fb_t* fb);
void fb_open(fb_t* fb);

void fb_print_info(fb_t* fb);

argb_t* fb_begin(fb_t* fb);
argb_t* fb_end(fb_t* fb);

void fb_get(fb_t* fb, int x, int y, char* r, char* g, char* b);
void fb_set(fb_t* fb, int x, int y, char r, char g, char b);

void fb_close(fb_t* fb);

#endif
