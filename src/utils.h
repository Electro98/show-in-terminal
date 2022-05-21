//
// Created by Electro98 on 01.04.2022.
//

#ifndef SHOWINTERMINAL_UTILS_H
#define SHOWINTERMINAL_UTILS_H

#include <errno.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define log_msg(msg) flog_msg(LOG_FILE, (msg))

void flog_msg(FILE *log_file, const char* msg);

int msleep(long msec);

void exit_if_null(void *data, const char *msg);

#endif //SHOWINTERMINAL_UTILS_H
