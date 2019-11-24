


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <linux/fb.h>


int main(int argc, char* argv[]){
	int fbfd = 0; 
	struct fb_var_screeninfo var_info;
	struct fb_fix_screeninfo f_info;
	long int screensize = 0;
	char *fbp = 0;
	char *our_fbp = 0;

	fbfd = open("/dev/fb0", O_RDWR);
	if(fbfd == -1){
		printf("Bananas\n");
		return(1);
	}


	if(ioctl(fbfd, FBIOGET_VSCREENINFO, &var_info)) {
		printf("!\n");
	}
	if(ioctl(fbfd, FBIOGET_FSCREENINFO, &f_info)) {
		printf("?\n");
	}

	printf("Display info %dx%d, %d bpp\n",
			var_info.xres, var_info.yres,
			var_info.bits_per_pixel);


	screensize = f_info.smem_len;

	our_fbp = (char*)malloc(sizeof(char)*screensize);

	int i = 0;
	for(i = 0; i < screensize; i++){
		if((i)%4 == 3){
			our_fbp[i] = 255;
			
		}
		else if((i)%4 == 1){
			our_fbp[i] =(char)(((double)i / (double)screensize) * 255);
		} 
		else if(i % 4 == 2){
			our_fbp[i] = (char)(((double)i / (double)screensize) * 255);
		}
		else {
			our_fbp[i] = 0;
		}
	}

	fbp = (char*)mmap(0,
			screensize,
			PROT_READ | PROT_WRITE,
			MAP_SHARED,
			fbfd, 0);

	if((int)fbp == -1) {
		printf("Bad mmap\n");
	}
	else{
		//memset(fbp, 0xff, screensize/2);
		//memset(fbp + screensize/2, 0x19, screensize/2);
		memcpy(fbp, our_fbp, screensize);
	}

	munmap(fbp, screensize);
	close(fbfd);

	return 0;
}
