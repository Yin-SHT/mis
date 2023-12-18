#include "sobel.h"
#include <stdlib.h>

void Gradient_X(PIXEL *src, PIXEL *gx, int h, int w) {
  int kernel[9] = {
    -1, 0, 1,
    -2, 0, 2,
    -1, 0, 1
  };

  int idx = 0;
  for (int i = 0; i < h - 2; i ++) {
    for (int j = 0; j < w - 2; j ++) {
      gx[idx] = 0;
      for (int m = 0; m < 3; m ++) {
        for (int n = 0; n < 3; n ++) {
          gx[idx] += kernel[m * 3 + n] * src[(i + m) * w + j + n];
        }
      }
      if (gx[idx] < 0) gx[idx] = 0;
      if (gx[idx] > 255) gx[idx] = 255;
      idx ++;
    }
  }
}

void Gradient_Y(PIXEL *src, PIXEL *gy, int h, int w) {
  int kernel[9] = {
    -1, -2, -1,
    0, 0, 0, 
    1, 2, 1
  };

  int idx = 0;
  for (int i = 0; i < h - 2; i ++) {
    for (int j = 0; j < w - 2; j ++) {
      gy[idx] = 0;
      for (int m = 0; m < 3; m ++) {
        for (int n = 0; n < 3; n ++) {
          gy[idx] += kernel[m * 3 + n] * src[(i + m) * w + j + n];
        }
      }
      if (gy[idx] < 0) gy[idx] = 0;
      if (gy[idx] > 255) gy[idx] = 255;
      idx ++;
    }
  }
}

void sobel(PIXEL src[HEIGHT*WIDTH], PIXEL dst[(HEIGHT-2)*(WIDTH-2)], int rows, int cols)
{
	int h = rows;
	int w = cols;

  PIXEL *gx = (PIXEL *)calloc((h - 2) * (w - 2), sizeof (PIXEL));
  PIXEL *gy = (PIXEL *)calloc((h - 2) * (w - 2), sizeof (PIXEL));

  Gradient_X(src, gx, h, w);
	Gradient_Y(src, gy, h, w);

  for (int i = 0; i < (h - 2) * (w - 2); i ++) {
    dst[i] = gx[i] + gy[i];
    if (dst[i] < 0) dst[i] = 0;
    if (dst[i] > 255) dst[i] = 255;
  }

  free(gx);
  free(gy);
}
