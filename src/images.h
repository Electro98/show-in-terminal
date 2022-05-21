//
// Created by Electro98 on 06.02.2022.
//

#ifndef SHOWINTERMINAL_IMAGES_H
#define SHOWINTERMINAL_IMAGES_H

#include <stdint.h>

#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"
#define STB_IMAGE_RESIZE_STATIC
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "../stb/stb_image_resize.h"
#define STB_IMAGE_WRITE_STATIC
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../stb/stb_image_write.h"

typedef struct {
    uint8_t *data;
    int width;
    int height;
    int channels;
} Image;

Image *load_image(const char *filename);
Image *resize_image(Image *old_img, int width, int height);
Image *grayscale_image(Image *img);
void free_image(Image *img);

typedef enum {
    IMG_SAVE_JPG,
    IMG_SAVE_PNG,
    IMG_SAVE_BMP,
} img_save_format;

int save_image(const char *filename, Image *img, img_save_format format);

typedef struct {
    Image *frames;
    int *delays;
    int len;
} Gif;

Gif *gif_load(char const *filename);
void free_gif(Gif *gif);

void max_contrast_grayscale_gif(Gif* grayscale_gif);
void max_contrast_grayscale_image(Image *img);
void max_contrast_grayscale_image_min_max(Image *img, uint8_t min, uint8_t max);

#endif //SHOWINTERMINAL_IMAGES_H
