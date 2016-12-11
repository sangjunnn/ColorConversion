//DSPE_2011706153_¿ÃªÛ¡ÿ_13

#ifndef Inter_Prediction
#define Inter_Prediction

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable:4996)

#define WIDTH (352)
#define HEIGHT (288)

#define BLOCK_SIZE (4)
#define SR (16)

#define cWIDTH (WIDTH>>1)
#define cHEIGHT (HEIGHT>>1)

#define cBLOCK_SIZE (BLOCK_SIZE>>1)
#define cSR (SR>>1)

#define Clip(x) (x < 0 ? 0 : (x > 255 ? 255 : x))

typedef unsigned char uchar;

typedef struct MV {
	int x;
	int y;
}MV;

int GetMin(int a, int b);
int GetMax(int a, int b);

uchar** MemAlloc_2D(int width, int height);
void MemFree_2D(uchar** pic, int height);

float GetPSNR(uchar** img_ori, uchar** img_dist, int width, int height);

int Read_Frame(FILE* fp_in, uchar** img_in, int width, int height);
void Write_Frame(FILE* fp_out, uchar** img_in, int width, int height);

void RGB_to_YUV(uchar** img_in, uchar** img_out, int width, int height);
void YUV_to_RGB(uchar** img_in, uchar** img_out, int width, int height);

void YUV444_to_420(uchar** img_in, uchar** img_Y, uchar** img_U420, uchar** img_V420, int width, int height);
void YUV420_to_444(uchar** img_Y, uchar** img_U420, uchar** img_V420, uchar** img_out, int width, int height);

void InterPrediction(uchar** img_ori, uchar** img_ref, uchar** img_pred, uchar** img_resi, uchar** img_recon, int width, int height, int block_size, int search_range);

MV GetMV(uchar** current, uchar** reference, uchar** output, int cur_i, int cur_j, int width, int height, int block, int searchrange);

#endif // !Inter_Prediction

