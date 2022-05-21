//
// Created by Electro98 on 06.02.2022.
//

#include "images.h"

Image *load_image(const char *filename) {
    Image *img = malloc(sizeof(Image));
    img->data = stbi_load(filename, &img->width, &img->height, &img->channels, 0);
    if (img->data == NULL) {
        free(img);
        return NULL;
    }
    return img;
}

Image *resize_image(Image *old_img, int width, int height) {
    if (old_img == NULL)
        return NULL;
    Image *new_img = malloc(sizeof(Image));
    new_img->width = width;
    new_img->height = height;
    new_img->channels = old_img->channels;
    new_img->data = malloc(width * height * new_img->channels);
    stbir_filter filter = (old_img->width >= new_img->width)? STBIR_FILTER_MITCHELL: STBIR_FILTER_CATMULLROM;
    if (!stbir_resize_uint8_generic(
            old_img->data, old_img->width, old_img->height, 0,
            new_img->data, new_img->width, new_img->height, 0,
            old_img->channels, -1, 0,
            STBIR_EDGE_CLAMP, filter, STBIR_COLORSPACE_LINEAR, NULL)) {
        free_image(new_img);
        return NULL;
    }
    return new_img;
}

Image *grayscale_image(Image *img) {
    if (img == NULL || img->channels < 3)
        return NULL;
    Image *new_img = malloc(sizeof(Image));
    new_img->width = img->width;
    new_img->height = img->height;
    new_img->channels = 1;
    new_img->data = malloc(img->width * img->height);
    uint8_t *img_end = img->data + img->width * img->height * img->channels;
    for (uint8_t *p = img->data, *pg = new_img->data; p != img_end; p += img->channels, ++pg) {
        *pg = (uint8_t)((*p + *(p + 1) + *(p + 2)) / 3.0);
        // if (img->channels == 4);
        // TODO: Do something with alpha channel
    }
    return new_img;
}

void max_contrast_grayscale_gif(Gif* grayscale_gif) {
    uint8_t min = 255, max = 0;
    for (int i = 0; i < grayscale_gif->len; ++i)
    {
        Image img = grayscale_gif->frames[i];
        uint8_t *img_end = img.data + img.width * img.height;
        for (uint8_t* src = img.data; src != img_end; ++src)
        {
            if (*src > max)
                max = *src;
            if (*src < min)
                min = *src;
        }
    }
    for (int i = 0; i < grayscale_gif->len; ++i)
        max_contrast_grayscale_image_min_max(&grayscale_gif->frames[i], min, max);
}

void max_contrast_grayscale_image(Image *img) {
    uint8_t *img_end = img->data + img->width * img->height;
    uint8_t min = 255, max = 0;
    for (uint8_t* src = img->data; src != img_end; ++src)
    {
        if (*src > max)
            max = *src;
        if (*src < min)
            min = *src;
    }
    max_contrast_grayscale_image_min_max(img, min, max);
}

void max_contrast_grayscale_image_min_max(Image *img, uint8_t min, uint8_t max) {
    if (img == NULL || img->channels != 1)
        return;
    size_t img_size = img->width * img->height;
    uint8_t *img_end = img->data + img_size;
    double shift_const = 255. / (max - min);
    for (uint8_t* src = img->data; src != img_end; ++src)
        *src = (uint8_t) shift_const * (*src - min);
}

void free_image(Image *img) {
    if (img == NULL)
        return;
    if (img->data != NULL)
        stbi_image_free(img->data);
    img->data = NULL;
    img->width = 0;
    img->height = 0;
    img->channels = 0;
    free(img);
}

int save_image(const char *filename, Image *img, img_save_format format) {
    switch (format) {
        case IMG_SAVE_PNG:
            return stbi_write_png(filename, img->width, img->height, img->channels, img->data, 0);
        case IMG_SAVE_BMP:
            return stbi_write_bmp(filename, img->width, img->height, img->channels, img->data);
        case IMG_SAVE_JPG:
            return stbi_write_jpg(filename, img->width, img->height, img->channels, img->data, 100);
        default:
            assert(0);
            return 0;
    }
}

Gif *gif_load(char const *filename)
{
    FILE *f;
    stbi__context s;

    if (!(f = stbi__fopen(filename, "rb")))
        return NULL;

    stbi__start_file(&s, f);

    Gif *gif_result = malloc(sizeof(Gif));
    gif_result->frames = malloc(sizeof(Image));

    gif_result->len = 0;
    uint8_t *gif_data = stbi__load_gif_main(&s, &gif_result->delays,
                                            &gif_result->frames->width, &gif_result->frames->height,
                                            &gif_result->len, &gif_result->frames->channels, 4);
    // Close file after reading
    fclose(f);
    if (stbi__vertically_flip_on_load) {
        stbi__vertical_flip_slices(gif_data, gif_result->frames->width, gif_result->frames->height,
                                   gif_result->len, gif_result->frames->channels);
    }
    if (gif_data == NULL) {
        free(gif_result->frames);
        free(gif_result);
        gif_result = 0;
        return NULL;
    }
    gif_result->frames = realloc((void*)gif_result->frames, gif_result->len * sizeof(Image));
    Image ref = *gif_result->frames;
    Image *fp = gif_result->frames;
    for (int i = 0; i < gif_result->len; ++i, ++fp) {
        *fp = ref;
        fp->data = gif_data + ref.width * ref.height * ref.channels * i;
    }
    return gif_result;
}

void free_gif(Gif *gif) {
    if (gif == NULL)
        return;
    free(gif->delays);
    gif->delays = 0;
    free(gif->frames->data);
    free(gif->frames);
    gif->frames = 0;
    gif->len = 0;
    free(gif);
}
