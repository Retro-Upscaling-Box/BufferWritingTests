#ifndef __FB_H
#define __FB_H

#include <linux/fb.h>

typedef struct _fb
{
    // pointer to an open framebuffer and its size
    char* fb;
    long size;

    // framebuffer file descriptor
    int fbfd;

    // Info about screen and framebuffer
	struct fb_var_screeninfo v_info;
	struct fb_fix_screeninfo f_info;
} fb_t;

#endif
