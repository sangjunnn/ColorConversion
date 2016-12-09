//DSPE_2011706153_¿ÃªÛ¡ÿ_13

#include "func.h"

void main() {
	FILE* fp_in0 = fopen("Suzie_CIF_1.rgb", "rb");
	FILE* fp_in1 = fopen("Suzie_CIF_13.rgb", "rb");

	FILE* fp_out0 = fopen("[Predc]Suzie_CIF_13.rgb", "wb");
	FILE* fp_out1 = fopen("[Resid]Suzie_CIF_13.rgb", "wb");
	FILE* fp_out2 = fopen("[Recon]Suzie_CIF_13.rgb", "wb");
	
	uchar** img_RGB, ** img_YUV444;
	uchar** img_ori_Y, ** img_ori_U, ** img_ori_V;
	uchar** img_ref_Y, ** img_ref_U, ** img_ref_V;

	uchar** img_recon_Y,** img_recon_U,** img_recon_V;
	uchar** img_pred_Y,** img_pred_U,** img_pred_V;
	uchar** img_resi_Y,** img_resi_U,** img_resi_V;

	int size = 1;

	img_YUV444 = MemAlloc_2D(WIDTH, HEIGHT * 3);
	img_RGB = MemAlloc_2D(WIDTH, HEIGHT * 3);

	img_pred_Y = MemAlloc_2D(WIDTH, HEIGHT);
	img_recon_Y = MemAlloc_2D(WIDTH, HEIGHT);
	img_resi_Y = MemAlloc_2D(WIDTH, HEIGHT);

	img_pred_U = MemAlloc_2D(WIDTH, HEIGHT);
	img_recon_U = MemAlloc_2D(WIDTH, HEIGHT);
	img_resi_U = MemAlloc_2D(WIDTH, HEIGHT);

	img_pred_V = MemAlloc_2D(WIDTH, HEIGHT);
	img_recon_V = MemAlloc_2D(WIDTH, HEIGHT);
	img_resi_V = MemAlloc_2D(WIDTH, HEIGHT);

	img_ref_Y = MemAlloc_2D(WIDTH, HEIGHT);
	img_ref_U = MemAlloc_2D(WIDTH, HEIGHT);
	img_ref_V = MemAlloc_2D(WIDTH, HEIGHT);

	img_ori_Y = MemAlloc_2D(WIDTH, HEIGHT);
	img_ori_U = MemAlloc_2D(WIDTH, HEIGHT);
	img_ori_V = MemAlloc_2D(WIDTH, HEIGHT);

	Read_Frame(fp_in0, img_RGB, WIDTH, HEIGHT * 3);
	RGB_to_YUV(img_RGB, img_YUV444, WIDTH, HEIGHT);
	YUV444_to_420(img_YUV444, img_ref_Y, img_ref_U, img_ref_V, WIDTH, HEIGHT);

	Read_Frame(fp_in1, img_RGB, WIDTH, HEIGHT * 3);
	RGB_to_YUV(img_RGB, img_YUV444, WIDTH, HEIGHT);
	YUV444_to_420(img_YUV444, img_ori_Y, img_ori_U, img_ori_V, WIDTH, HEIGHT);
	
	InterPrediction(img_ori_Y, img_ref_Y, img_pred_Y, img_resi_y, img_recon_Y, WIDTH,HEIGHT,)


	MemFree_2D(img_RGB, HEIGHT * 3);
	MemFree_2D(img_YUV444, HEIGHT * 3);

	MemFree_2D(img_pred_Y, HEIGHT);
	MemFree_2D(img_recon_Y, HEIGHT);
	MemFree_2D(img_resi_Y, HEIGHT);

	MemFree_2D(img_pred_U, HEIGHT);
	MemFree_2D(img_recon_U, HEIGHT);
	MemFree_2D(img_resi_U, HEIGHT);

	MemFree_2D(img_pred_V, HEIGHT);
	MemFree_2D(img_recon_V, HEIGHT);
	MemFree_2D(img_resi_V, HEIGHT);

	MemFree_2D(img_ref_Y, HEIGHT);
	MemFree_2D(img_ref_U, HEIGHT);
	MemFree_2D(img_ref_V, HEIGHT);

	MemFree_2D(img_ori_Y, HEIGHT);
	MemFree_2D(img_ori_U, HEIGHT);
	MemFree_2D(img_ori_V, HEIGHT);

	fclose(fp_in0);
	fclose(fp_in1);
	fclose(fp_out0);
	fclose(fp_out1);
	fclose(fp_out2);
}