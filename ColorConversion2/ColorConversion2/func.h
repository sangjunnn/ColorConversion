//DSPE_2011706153_¿ÃªÛ¡ÿ_12

#ifndef Color_conversion
#define Color_conversion

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable:4996)

#define WIDTH (352)
#define HEIGHT (288)

#define Clip(x) (x < 0 ? 0 : (x > 255 ? 255 : x))

typedef unsigned char uchar;

uchar** MemAlloc_2D(int width, int height);
void MemFree_2D(uchar** pic, int height);

int Read_Frame(FILE* fp_in, uchar** img_in, int width, int height);
void Write_Frame(FILE* fp_out, uchar** img_in, int width, int height);

void RGB_to_YUV(uchar** img_in, uchar** img_out, int width, int height);
void YUV_to_RGB(uchar** img_in, uchar** img_out, int width, int height);

void YUV444_to_420(uchar** img_in, uchar** img_Y, uchar** img_U420, uchar** img_V420, int width, int height);
void YUV420_to_444(uchar** img_Y, uchar** img_U420, uchar** img_V420, uchar** img_out, int width, int height);

void YUV444_to_422(uchar** img_in, uchar** img_Y, uchar** img_U422, uchar** img_V422, int width, int height);
void YUV422_to_444(uchar** img_Y, uchar** img_U422, uchar** img_V422, uchar** img_out, int width, int height);


#endif // !Color_conversion


