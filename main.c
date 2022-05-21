#include "main.h"

void process_args(int argc, char** argv) {
    // Skipping program name
    argv++;
    argc--;
    exit_if_null(*argv, "No argument provided");
    input_file = *argv;
    log_msg("File to read.");
    log_msg(input_file);
}

Gif* load_grayscale_gif() {
    Gif *gif = gif_load(input_file);
    exit_if_null(gif, "Gif load failed.");
    log_msg("Loaded gif.");
    Gif *grayscale_gif = malloc(sizeof(Gif));
    grayscale_gif->len = gif->len;
    grayscale_gif->delays = malloc(grayscale_gif->len * sizeof(int));
    grayscale_gif->frames = malloc(grayscale_gif->len * sizeof(Image));
    Image *gray_buff, *buff;
    for (int i = 0; i < grayscale_gif->len; ++i) {
        gray_buff = grayscale_image(&gif->frames[i]);
        buff = resize_image(gray_buff, screen.width, screen.height);
        free_image(gray_buff);
//        max_contrast_grayscale_image(buff);
        grayscale_gif->frames[i] = *buff;
        grayscale_gif->delays[i] = gif->delays[i];
        free(buff);
    }
    max_contrast_grayscale_gif(grayscale_gif);
    free_gif(gif);
    log_msg("Gif was converted to grayscale.");
    return grayscale_gif;
}

int main(int argc, char** argv) {
    log_file = fopen("log.txt", "w");
    log_msg("Started program.");
    initialization(&screen);
    log_msg("Finished screen initialization.");
    process_args(argc, argv);
    Gif* grayscale_gif = load_grayscale_gif();
    fclose(log_file);
    prepare_screen();
    run_gif(grayscale_gif);
    free_gif(grayscale_gif);
    release(&screen);
    return 0;
}

void run_gif(Gif* gif) {
    int i = 0;
    while (!0)
    {
        display_gimage(&screen, &gif->frames[i]);
        refresh_screen(&screen);
        msleep(gif->delays[i++]);
        if (i >= gif->len)
            i = 0;
        if (getch() != ERR)
            break;
    }
}
