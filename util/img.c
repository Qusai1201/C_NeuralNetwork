#include "img.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHAR 10000

Img** csv_to_imgs(char* file_string, int number_of_imgs) {
	FILE *fp;
	Img** imgs = malloc(number_of_imgs * sizeof(Img*));
	char row[MAXCHAR];
	fp = fopen(file_string, "r");

	// Read the first line 
	fgets(row, MAXCHAR, fp);
	int i = 0;
	while (feof(fp) != 1 && i < number_of_imgs) {
		imgs[i] = malloc(sizeof(Img));

		int j = 0;
		fgets(row, MAXCHAR, fp);
		char* token = strtok(row, ",");
		imgs[i]->img_data = matrix_create(28, 28);
		while (token != NULL) {
			if (j == 0) {
				imgs[i]->label = atoi(token);
			} else {
				imgs[i]->img_data->entries[(j-1) / 28][(j-1) % 28] = atoi(token) / 256.0;
			}
			token = strtok(NULL, ",");
			j++;
		}
		i++;
	}
	fclose(fp);
	return imgs;
}

void img_print(Img* img) {
	matrix_print(img->img_data);
	printf("Img Label: %d\n", img->label);
}

void img_free(Img* img) {
	matrix_free(img->img_data);
	free(img);
	img = NULL;
}

void imgs_free(Img** imgs, int n) {
	for (int i = 0; i < n; i++) {
		img_free(imgs[i]);
	}
	free(imgs);
	imgs = NULL;
}
matrix *GetImage(Texture2D texture, Rectangle rec)
{
    matrix *img = matrix_create(28, 28);
    matrix_fill(img, 0);

    Image blackAndWhiteImage = LoadImageFromTexture(texture);

    ImageCrop(&blackAndWhiteImage, rec);
    ImageRotate(&blackAndWhiteImage, 180);
    ImageFlipHorizontal(&blackAndWhiteImage);
    ImageResize(&blackAndWhiteImage, 28, 28);

    Color pixel;
    for (int i = 0; i < 28 * 28; ++i)
    {
        pixel = ((Color *)blackAndWhiteImage.data)[i];
        unsigned char grayscaleValue = (pixel.r + pixel.g + pixel.b + pixel.a) / 4;
        int row = i / 28;
        int col = i % 28;

        if (pixel.a == 0)
        {
            img->entries[row][col] = 0;
            ((Color *)blackAndWhiteImage.data)[i] = (Color){0, 0, 0, 255};
        }
        else
        {
            if (pixel.r || pixel.g || pixel.b)
            {
                img->entries[row][col] = grayscaleValue;
                ((Color *)blackAndWhiteImage.data)[i] = (Color){grayscaleValue, grayscaleValue, grayscaleValue, 255};
            }
        }
    }
    UnloadImage(blackAndWhiteImage);
    return img;
}