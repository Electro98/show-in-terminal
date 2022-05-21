//
// Created by Electro98 on 01.04.2022.
//

#include "utils.h"

void flog_msg(FILE *log_file, const char* msg)
{
    static time_t timer;
    static struct tm* parsed_time;
    time(&timer);
    parsed_time = localtime(&timer);
    printf("[%02d:%02d:%02d][LOG]: %s\n", parsed_time->tm_hour, parsed_time->tm_min, parsed_time->tm_sec, msg);
    if (log_file)
        fprintf(log_file, "[%02d:%02d:%02d][LOG]: %s\n", parsed_time->tm_hour, parsed_time->tm_min, parsed_time->tm_sec, msg);
}

int msleep(long msec)
{
    struct timespec req;
    struct timespec rem;
    int res;

    if (msec < 0)
    {
        errno = EINVAL;
        return -1;
    }

    rem.tv_sec = msec / 1000;
    rem.tv_nsec = (msec % 1000) * 1000000;
    do {
        req = rem;
        res = nanosleep(&req, &rem);
    } while (res && errno == EINTR);
    return res;
}

inline void exit_if_null(void *data, const char *msg) {
    if (data == NULL) {
        printf("NullPointerError: %s\n", msg);
        exit(1);
    }
}
