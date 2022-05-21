//
// Created by Electro98 on 06.02.2022.
//

#include "console_screen.h"


void initialization(Screen *screen) {
    initscr();
    nodelay(stdscr, true);
    getmaxyx(stdscr, screen->height, screen->width);
    screen->screen_size = screen->width * screen->height;
    screen->frame = malloc(screen->screen_size);
    // Hiding cursor
    curses_trace(TRACE_DISABLE);
}

void prepare_screen() {
    move(0, 0);
}

void refresh_screen(Screen *screen) {
    addnstr(screen->frame, screen->screen_size);
    move(0, 0);
}

char *get_buff_gimage(Screen *screen, Image *g_img)
{
    if (screen->width == g_img->width && screen->height == g_img->width && g_img->channels == 1)
        return NULL;
    uint8_t *frame = malloc(screen->screen_size);
    uint8_t *frame_end = (uint8_t*)frame + screen->width * screen->height;
    for (uint8_t *sp = (uint8_t*)frame, *ip = g_img->data; sp != frame_end; ++sp, ++ip)
        *sp = PALETTE[(*ip * PALETTE_SIZE) / 256];
    return frame;
}

int display_gimage(Screen *screen, Image *g_img){
    if (screen->width == g_img->width && screen->height == g_img->width && g_img->channels == 1)
        return 0;
    uint8_t *frame_end = (uint8_t*)screen->frame + screen->width * screen->height;
    for (uint8_t *sp = (uint8_t*)screen->frame, *ip = g_img->data; sp != frame_end; ++sp, ++ip)
        *sp = PALETTE[(*ip * PALETTE_SIZE) / 255];
    return 1;
}

void release(Screen* screen) {
    free(screen->frame);
    endwin();
}
