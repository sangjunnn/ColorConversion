//DSPE_2011706153_¿ÃªÛ¡ÿ_11

#include "func.h"

void main() {
	FILE* fp_in = fopen("Suzie_CIF_150_30.rgb", "rb");
	FILE* fp_out1 = fopen("[YUV]Suzie_CIF_150_30.yuv", "wb");
	FILE* fp_out2 = fopen("[RGB]Suzie_CIF_150_30.rgb", "wb");

	uchar** img_in;
	uchar** img_out;

	int size = 1;

	img_in = MemAlloc_2D(WIDTH, HEIGHT * 3);
	img_out = MemAlloc_2D(WIDTH, HEIGHT * 3);

	while (size = Read_Frame(fp_in, img_in, WIDTH, HEIGHT * 3)) {
		RGB_to_YUV(img_in, img_out, WIDTH, HEIGHT);
		Write_Frame(fp_out1, img_out, WIDTH, HEIGHT * 3);

		YUV_to_RGB(img_out, img_in, WIDTH, HEIGHT);
		Write_Frame(fp_out2, img_in, WIDTH, HEIGHT * 3);
	}

	MemFree_2D(img_in, HEIGHT * 3);
	MemFree_2D(img_out, HEIGHT * 3);

	fclose(fp_in);
	fclose(fp_out1);
	fclose(fp_out2);
}