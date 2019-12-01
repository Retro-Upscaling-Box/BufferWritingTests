#include "fb.h"

#include <stdio.h>
#include <stdlib.h>

#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

// Resets the vars in a framebuffer
void fb_init(fb_t* fb){
    fb->fb = NULL;
    fb->size = 0;
    fb->fbfd = -1;

    fb->v_info = NULL;
    fb->f_info = NULL;
}

// Opens the framebuffer in the given struct
void fb_open(fb_t* fb){
    // Open the file descriptor with read/write access
    fb->fbfd = open("/dev/fb0", O_RDWR);

    if(fb->fbfd == -1){
        printf("Something went wrong opening the framebuffer file descriptor\n");
        return;
    }

    // Fetch screen info
    fb->v_info = malloc(sizeof(struct fb_var_screeninfo));
    fb->f_info = malloc(sizeof(struct fb_fix_screeninfo));
    int v_status = ioctl(fb->fbfd, FBIOGET_VSCREENINFO, fb->v_info);
    int f_status = ioctl(fb->fbfd, FBIOGET_FSCREENINFO, fb->f_info);

    if(v_status == -1){
        printf("Something went wrong retreiving variable info from the framebuffer\n");
        return;
    }
    if(f_status == -1){
        printf("Something went wrong retreiving fixed info from the framebuffer\n");
        return;
    }

    // store the size of the framebuffer
    fb->size = fb->f_info->smem_len;

    // map the framebuffer
    fb->fb = mmap(
        NULL,
        fb->f_info->smem_len,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        fb->fbfd, 0);

    if((int)fb->fb == -1){
        printf("Something went wrong when mapping the framebuffer memory\n");
        return;
    }
}