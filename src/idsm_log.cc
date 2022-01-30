/**
 * @brief - implements idsm logging
 *
 * @author - Devendra Naga (devendra.aaru@gmail.com)
 * @copyright - All rights reserved 2022-present Proprietary
 */
#include <iostream>
#include <stdarg.h>
#include <idsm_log.h>

namespace idsm {

const std::string get_idsm_log_str(idsm_log_type type)
{
    switch (type) {
        case idsm_log_type::eINFO:
            return "Info";
        case idsm_log_type::eWARN:
            return "Warn";
        case idsm_log_type::eERROR:
            return "Error";
        case idsm_log_type::eFATAL:
            return "Fatal";
        default:
            return "Unknown";
    }
}

void idsm_log::log_msg(const char *fmt, idsm_log_type type, va_list ap)
{
    char buff[4096];
    time_t t;
    struct tm *ts;
    struct timespec tp;
    int ret;

    t = time(0);
    ts = gmtime(&t);
    if (!ts) {
        return;
    }

    clock_gettime(CLOCK_REALTIME, &tp);

    ret = snprintf(buff, sizeof(buff), "[%04d-%02d-%02d: %02d:%02d:%02d.%08llu] [%s] ",
                                 ts->tm_year + 1900,
                                 ts->tm_mon + 1,
                                 ts->tm_mday,
                                 ts->tm_hour,
                                 ts->tm_min,
                                 ts->tm_sec,
                                 tp.tv_nsec / 1000ULL,
                                 get_idsm_log_str(type).c_str());
    ret = vsnprintf(buff + ret, sizeof(buff) - ret, fmt, ap);
    fprintf(stderr, "%s", buff);
}

void idsm_log::info(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    log_msg(fmt, idsm_log_type::eINFO, ap);
    va_end(ap);
}

void idsm_log::error(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    log_msg(fmt, idsm_log_type::eERROR, ap);
    va_end(ap);
}

}

