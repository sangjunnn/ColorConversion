//DSPE_2011706153_ÀÌ»óÁØ_12

#include "func.h"

void main() {
	FILE* fp_in = fopen("Suzie_CIF_150_30.rgb", "rb");
	FILE* fp_out0 = fopen("[YUV444]Suzie_CIF_150_30.yuv", "wb");
	FILE* fp_out1 = fopen("[YUV420]Suzie_CIF_150_30.yuv", "wb");
	FILE* fp_out2 = fopen("[YUV422]Suzie_CIF_150_30.yuv", "wb");
	FILE* fp_out3 = fopen("[Recon_420]Suzie_CIF_150_30.rgb", "wb");
	FILE* fp_out4 = fopen("[Recon_422]Suzie_CIF_150_30.rgb", "wb");

	uchar** img_RGB, ** img_YUV444;
	uchar** img_Y, ** img_U420, **img_V420;
	uchar** img_U422, **img_V422;

	int size = 1;

	img_YUV444 = MemAlloc_2D(WIDTH, HEIGHT * 3);
	img_RGB = MemAlloc_2D(WIDTH, HEIGHT * 3);

	img_Y = MemAlloc_2D(WIDTH, HEIGHT);

	img_U420 = MemAlloc_2D(WIDTH >> 1, HEIGHT >> 1);
	img_V420 = MemAlloc_2D(WIDTH >> 1, HEIGHT >> 1);

	img_U422 = MemAlloc_2D(WIDTH >> 1, HEIGHT);
	img_V422 = MemAlloc_2D(WIDTH >> 1, HEIGHT);

	while (size = Read_Frame(fp_in, img_RGB, WIDTH, HEIGHT * 3)) {
		RGB_to_YUV(img_RGB, img_YUV444, WIDTH, HEIGHT);
		Write_Frame(fp_out0, img_YUV444, WIDTH, HEIGHT * 3);

		YUV444_to_420(img_YUV444, img_Y, img_U420, img_V420, WIDTH, HEIGHT);
		YUV444_to_422(img_YUV444, img_Y, img_U422, img_V422, WIDTH, HEIGHT);

		Write_Frame(fp_out1, img_Y, WIDTH, HEIGHT);
		Write_Frame(fp_out1, img_U420, WIDTH >> 1, HEIGHT >> 1);
		Write_Frame(fp_out1, img_V420, WIDTH >> 1, HEIGHT >> 1);

		Write_Frame(fp_out2, img_Y, WIDTH, HEIGHT);
		Write_Frame(fp_out2, img_U422, WIDTH >> 1, HEIGHT);
		Write_Frame(fp_out2, img_V422, WIDTH >> 1, HEIGHT);

		YUV420_to_444(img_Y, img_U420, img_V420, img_YUV444, WIDTH, HEIGHT);
		YUV_to_RGB(img_YUV444, img_RGB, WIDTH, HEIGHT);
		Write_Frame(fp_out3, img_RGB, WIDTH, HEIGHT * 3);

		YUV422_to_444(img_Y, img_U422, img_V422, img_YUV444, WIDTH, HEIGHT);
		YUV_to_RGB(img_YUV444, img_RGB, WIDTH, HEIGHT);
		Write_Frame(fp_out4, img_RGB, WIDTH, HEIGHT * 3);
	}

	MemFree_2D(img_RGB, HEIGHT * 3);
	MemFree_2D(img_YUV444, HEIGHT * 3);

	MemFree_2D(img_Y, HEIGHT);

	MemFree_2D(img_U420, HEIGHT >> 1);
	MemFree_2D(img_V420, HEIGHT >> 1);

	MemFree_2D(img_U422, HEIGHT>> 2);
	MemFree_2D(img_V422, HEIGHT>> 2);

	fclose(fp_in);
	fclose(fp_out0);
	fclose(fp_out1);
	fclose(fp_out2);
	fclose(fp_out3);
	fclose(fp_out4);
}