#pragma once

#include "../matrix/matrix.h"
#include "raylib.h"

typedef struct {
	matrix* img_data;
	int label;
} Img;

Img** csv_to_imgs(char* file_string, int number_of_imgs);
void img_print(Img* img);
void img_free(Img *img);
void imgs_free(Img **imgs, int n);
matrix *GetImage(Texture2D texture , Rectangle rec);
