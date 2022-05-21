//
// Created by Electro98 on 06.02.2022.
//

#ifndef SHOWINTERMINAL_CONSOLE_SCREEN_H
#define SHOWINTERMINAL_CONSOLE_SCREEN_H

#include <ncurses.h>
#include <unistd.h>

#include "images.h"

typedef struct {
    char *frame;
    int width;
    int height;
    int screen_size;
} Screen;

// Short one `@%#*+=-:. `
//#define PALETTE_SIZE 10
//static char PALETTE[] = " .:-=+*#%@";
// Long one ` .'`^",:;Il!i><~+_-?][}{1)(|\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$`
#define PALETTE_SIZE 70
static char PALETTE[] = " .'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";

void initialization(Screen *screen);
void prepare_screen();
void refresh_screen(Screen *screen);
char *get_buff_gimage(Screen *screen, Image *g_img);
int display_gimage(Screen *screen, Image *g_img);
void release(Screen *screen);

#endif //SHOWINTERMINAL_CONSOLE_SCREEN_H
