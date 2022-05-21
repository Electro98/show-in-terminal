//
// Created by Electro98 on 01.04.2022.
//

#ifndef SHOWINTERMINAL_MAIN_H
#define SHOWINTERMINAL_MAIN_H

#define USE_VECTOR
#include "src/console_screen.h"
#define LOG_FILE log_file
#include "src/utils.h"

FILE* log_file;
Screen screen;
char* input_file;

void process_args(int argc, char** argv);

Gif* load_grayscale_gif();

int main(int argc, char** argv);

void run_gif(Gif* gif);

#endif //SHOWINTERMINAL_MAIN_H
