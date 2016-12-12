//DSPE_2011706153_�̻���_13

#include "func.h"

int GetMax(int a, int b) {
	if (a<b) {
		return b;
	}
	else {
		return a;
	}
}

int GetMin(int a, int b) {
	if (a<b) {
		return a;
	}
	else {
		return b;
	}
}

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
}// unsigned char�� ���� �Ҵ�

void MemFree_2D(uchar** pic, int height) {
	for (int i = 0; i < height; i++) {
		free(pic[i]);
	}
	free(pic);
}//2���� ���� �޸� ����

float GetPSNR(uchar** img_ori, uchar** img_dist, int width, int height) {
	float mse = 0;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			mse += ((img_ori[i][j] - img_dist[i][j])*(img_ori[i][j] - img_dist[i][j])) / (float)(width*height);
		}
	}
	return 10 * (float)log10((255 * 255) / mse);
}

int Read_Frame(FILE* fp_in, uchar** img_in, int width, int height) {
	int size = 0;

	for (int i = 0; i < height; i++) {
		size += fread(img_in[i], sizeof(uchar), width, fp_in);
	}//�������� �ϳ� ������ ���� size�� Ŀ���� �� 
	return size;
}//size�� ��ȯ

void Write_Frame(FILE* fp_out, uchar** img_in, int width, int height) {
	for (int i = 0; i < height; i++) {
		fwrite(img_in[i], sizeof(uchar), width, fp_out);
	}
}//������ ����

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
}//RGB�������� YUV�� ����� ���� ���Ŀ� �����ؼ� ����� ���

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
}//YUV�������� RGB�� ����� ���� ���Ŀ� �����ؼ� ����� ���

void YUV444_to_420(uchar** img_in, uchar** img_Y, uchar** img_U420, uchar** img_V420, int width, int height) {
	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			img_Y[h][w] = img_in[h][w];
		}
	}

	for (int h = 0; h < height / 2; h++) {
		for (int w = 0; w < width / 2; w++) {
			img_U420[h][w] =
				(img_in[HEIGHT + 2 * h][2 * w] +
					img_in[HEIGHT + 2 * h][2 * w + 1] +
					img_in[HEIGHT + 2 * h + 1][2 * w] +
					img_in[HEIGHT + 2 * h + 1][2 * w + 1]) / 4;
			//U420�� ���ϱ� ���� 2x2���� ����� ����
			img_V420[h][w] =
				(img_in[HEIGHT * 2 + 2 * h][2 * w] +
					img_in[HEIGHT * 2 + 2 * h][2 * w + 1] +
					img_in[HEIGHT * 2 + 2 * h + 1][2 * w] +
					img_in[HEIGHT * 2 + 2 * h + 1][2 * w + 1]) / 4;
			//V420�� ���ϱ� ���� 2x2���� ����� ����
		}
	}

}

void YUV420_to_444(uchar** img_Y, uchar** img_U420, uchar** img_V420, uchar** img_out, int width, int height) {
	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			img_out[h][w] = img_Y[h][w];
		}
	}

	for (int h = 0; h < height / 2; h++) {
		for (int w = 0; w < width / 2; w++) {
			img_out[HEIGHT + 2 * h][2 * w] = img_U420[h][w];
			img_out[HEIGHT + 2 * h + 1][2 * w] = img_U420[h][w];
			img_out[HEIGHT + 2 * h][2 * w + 1] = img_U420[h][w];
			img_out[HEIGHT + 2 * h + 1][2 * w + 1] = img_U420[h][w];
			//U420�� 2x2������ ����

			img_out[2 * HEIGHT + 2 * h][2 * w] = img_V420[h][w];
			img_out[2 * HEIGHT + 2 * h + 1][2 * w] = img_V420[h][w];
			img_out[2 * HEIGHT + 2 * h][2 * w + 1] = img_V420[h][w];
			img_out[2 * HEIGHT + 2 * h + 1][2 * w + 1] = img_V420[h][w];
			//V420�� 2x2������ ����
		}
	}
}

void YUV444_to_422(uchar** img_in, uchar** img_Y, uchar** img_U422, uchar** img_V422, int width, int height) {
	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			img_Y[h][w] = img_in[h][w];
		}
	}

	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width / 2; w++) {
			img_U422[h][w] =
				(img_in[HEIGHT + h][2 * w] +
					img_in[HEIGHT + h][2 * w + 1]) / 2;
			//U422�� ���ϱ� ���� ������ �ΰ� �ȼ��� ����� ����
			img_V422[h][w] =
				(img_in[HEIGHT * 2 + h][2 * w] +
					img_in[HEIGHT * 2 + h][2 * w + 1]) / 2;
			//V422�� ���ϱ� ���� ������ �ΰ� �ȼ��� ����� ����
		}
	}
}

void YUV422_to_444(uchar** img_Y, uchar** img_U422, uchar** img_V422, uchar** img_out, int width, int height) {
	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			img_out[h][w] = img_Y[h][w];
		}
	}

	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width / 2; w++) {
			img_out[HEIGHT + h][2 * w] = img_U422[h][w];
			img_out[HEIGHT + h][2 * w + 1] = img_U422[h][w];
			//U422�� �¿� �� �ʼ��� ����

			img_out[2 * HEIGHT + h][2 * w] = img_V422[h][w];
			img_out[2 * HEIGHT + h][2 * w + 1] = img_V422[h][w];
			//V422�� �¿� �� �ʼ��� ����
		}
	}
}

void InterPrediction(uchar** img_ori, uchar** img_ref, uchar** img_pred, uchar** img_resi, uchar** img_recon, int width, int height, int block_size, int search_range) {
	MV temp;


	MV mv[HEIGHT / BLOCK_SIZE][WIDTH / BLOCK_SIZE];

	for (int i = 0; i < height; i+= block_size) {
		for (int j = 0; j < width; j += block_size) {
			
			temp = GetMV(img_ori, img_ref, img_recon, i, j, width, height, block_size, search_range);
			//��� ���͸� �޾ƿ��� temp�� ���
			for (int w = 0; w < block_size; w++) {
				for (int h = 0; h < block_size; h++) {
					img_recon[(i + w)][j + h] = img_ref[(temp.y + w)][(temp.x + h)];
					//��� ���͸� �������� ����� ref�κ��� �����ؿ�
				}
			}

		}
	}
}

MV GetMV(uchar** current, uchar** reference, uchar** output, int cur_i, int cur_j,int width, int height, int block, int searchrange) {

	float min = 10000;
	float result;
	int cnt;
	MV temp;

	temp.x = 0;
	temp.y = 0;

	for (int y = GetMax(0, cur_i - searchrange); y < GetMin(height - block - 1, cur_i + searchrange - block - 1); y++) {
		for (int x = GetMax(0, cur_j - searchrange); x < GetMin(width - block - 1, cur_j + searchrange - block - 1); x++) {

			result = 0;
			cnt = 0;
			for (int k = 0; k < block; k++) {
				for (int l = 0; l < block; l++) {

					result += (current[(cur_i + k)][cur_j + l] - reference[(y + k)][(x + l)]);
					//MSE ���� ���ϱ� ���ؼ� ori�� ref�� ��� ������ ���� ���� ���� 
					cnt++;
					//����� ����� �������̱� ������ cnt��� ������ �̿��Ͽ� ����� ũ�⸦ �޾ƿ�
				}
			}

			result /= cnt;//���� ���࿡ �ʿ��� MSE�� ����

			if (result <= min) {

				min = result;
				temp.x = x;
				temp.y = y;
				//MSE�� �ּҰ��� ������ x,y�� ��ǥ�� ����
			}
		}
	}
	return temp;//struct���·� ��ȯ
}