//DSPE_2011706153_이상준_12

#include "func.h"

uchar** MemAlloc_2D(int width, int height) {
	uchar** pic;

	pic = (uchar**)malloc(sizeof(uchar*)*height);
	for (int i = 0; i < height; i++) {
		pic[i] = (uchar*)malloc(sizeof(uchar)*width);
	}

	if (pic == NULL) {
		printf("wrong allocation");
		return 0;
	}
	return pic;
}// unsigned char형 동적 할당

void MemFree_2D(uchar** pic, int height) {
	for (int i = 0; i < height; i++) {
		free(pic[i]);
	}
	free(pic);
}//2차원 동적 메모리 해제

int Read_Frame(FILE* fp_in, uchar** img_in, int width, int height) {
	int size = 0;

	for (int i = 0; i < height; i++) {
		size += fread(img_in[i], sizeof(uchar), width, fp_in);
	}//프레임을 하나 읽을때 마다 size가 커지게 됨 
	return size;
}//size값 반환

void Write_Frame(FILE* fp_out, uchar** img_in, int width, int height) {
	for (int i = 0; i < height; i++) {
		fwrite(img_in[i], sizeof(uchar), width, fp_out);
	}
}//프레임 쓰기

void RGB_to_YUV(uchar** img_in, uchar** img_out, int width, int height) {
	int tempY = 0;
	int tempU = 0;
	int tempV = 0;

	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			tempY = img_in[h][w] * 66 + img_in[HEIGHT + h][w] * 129 + img_in[2 * HEIGHT + h][w] * 25 + 128;
			tempU = img_in[h][w] * (-38) - img_in[HEIGHT + h][w] * 74 + img_in[2 * HEIGHT + h][w] * 112 + 128;
			tempV = img_in[h][w] * 112 - img_in[HEIGHT + h][w] * 94 - img_in[2 * HEIGHT + h][w] * 18 + 128;

			tempY = tempY >> 8;
			tempU = tempU >> 8;
			tempV = tempV >> 8;

			tempY += 16;
			tempU += 128;
			tempV += 128;

			img_out[h][w] = tempY;
			img_out[HEIGHT + h][w] = tempU;
			img_out[2 * HEIGHT + h][w] = tempV;
		}
	}
}//RGB성분으로 YUV를 만들기 위한 수식에 대입해서 결과물 출력

void YUV_to_RGB(uchar** img_in, uchar** img_out, int width, int height) {
	int C, D, E;
	int tempR, tempG, tempB;

	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			C = img_in[h][w] - 16;
			D = img_in[h + HEIGHT][w] - 128;
			E = img_in[h + 2 * HEIGHT][w] - 128;

			tempR = 298 * C + 409 * E + 128;
			tempG = 298 * C - 100 * D - 208 * E + 128;
			tempB = 289 * C + 516 * D + 128;

			tempR = tempR >> 8;
			tempG = tempG >> 8;
			tempB = tempB >> 8;

			img_out[h][w] = Clip(tempR);
			img_out[h + HEIGHT][w] = Clip(tempG);
			img_out[h + 2 * HEIGHT][w] = Clip(tempB);
		}
	}
}//YUV성분으로 RGB를 만들기 위한 수식에 대입해서 결과물 출력

void YUV444_to_420(uchar** img_in, uchar** img_Y, uchar** img_U420, uchar** img_V420, int width, int height) {
	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			img_Y[h][w] = img_in[h][w];
		}
	}

	for (int h = 0; h < height/2; h++) {
		for (int w = 0; w < width/2; w++) {
			img_U420[h][w] = (img_in[HEIGHT + 2*h][2*w] + img_in[HEIGHT + 2*h][2*w + 1] + img_in[HEIGHT + 2*h + 1][2*w] + img_in[HEIGHT + 2*h + 1][2*w + 1]) / 4;
			img_V420[h][w] = (img_in[HEIGHT*2 + 2*h][2*w] + img_in[HEIGHT * 2+2*h][2*w + 1] + img_in[HEIGHT * 2+2*h + 1][2*w] + img_in[HEIGHT * 2+2*h + 1][2*w + 1]) / 4;
		}
	}

}

void YUV420_to_444(uchar** img_Y, uchar** img_U420, uchar** img_V420, uchar** img_out, int width, int height) {
	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			img_out[h][w] = img_Y[h][w];
		}
	}

	for (int h = 0; h < height/2; h++) {
		for (int w = 0; w < width/2; w++) {
			img_out[HEIGHT + 2*h][2 * w] = img_U420[h][w];
			img_out[HEIGHT + 2*h + 1][2 * w] = img_U420[h][w];
			img_out[HEIGHT + 2 * h][2 * w + 1] = img_U420[h][w];
			img_out[HEIGHT + 2 * h + 1][2 * w + 1] = img_U420[h][w];

			img_out[2*HEIGHT + 2 * h][2 * w] = img_V420[h][w];
			img_out[2*HEIGHT + 2 * h + 1][2 * w] = img_V420[h][w];
			img_out[2*HEIGHT + 2 * h][2 * w + 1] = img_V420[h][w];
			img_out[2*HEIGHT + 2 * h + 1][2 * w + 1] = img_V420[h][w];
		}
	}
}

void YUV444_to_422(uchar** img_in, uchar** img_Y, uchar** img_U422, uchar** img_V422, int width, int height) {
	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			img_Y[h][w] = img_in[h][w];
		}
	}

	for (int h = 0; h < height; h ++) {
		for (int w = 0; w < width/2; w ++) {
			img_U422[h][w] = (img_in[HEIGHT+h][2*w] + img_in[HEIGHT + h][2*w + 1]) / 2;
			img_V422[h][w] = (img_in[HEIGHT*2 + h][2*w] + img_in[HEIGHT * 2 + h][2*w + 1]) / 2;
		}
	}
}

void YUV422_to_444(uchar** img_Y, uchar** img_U422, uchar** img_V422, uchar** img_out, int width, int height) {
	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			img_out[h][w] = img_Y[h][w];
		}
	}

	for (int h = 0; h < height; h ++) {
		for (int w = 0; w < width/2; w ++) {
			img_out[HEIGHT + h][2*w] = img_U422[h][w];
			img_out[HEIGHT + h][2*w + 1] = img_U422[h][w];

			img_out[2 * HEIGHT + h][2*w] = img_V422[h][w];
			img_out[2 * HEIGHT + h][2*w + 1] = img_V422[h][w];
		}
	}
}