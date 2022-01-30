/**
 * @brief - implements idsm_log utility
 *
 * @author - Devendra Naga (devendra.aaru@gmail.com)
 * @copyright - 2022-present All rights reserved proprietary
 */
#ifndef __IDSM_LOG_H__
#define __IDSM_LOG_H__

namespace idsm {

enum class idsm_log_type {
    eINFO,
    eWARN,
    eERROR,
    eFATAL,
};

class idsm_log {
    public:
        ~idsm_log() = default;

        static idsm_log *instance()
        {
            static idsm_log log;
            return &log;
        }

        void info(const char *fmt, ...);
        void warn(const char *fmt, ...);
        void error(const char *fmt, ...);
        void fatal(const char *fmt, ...);

    private:
        explicit idsm_log() = default;
        void log_msg(const char *fmt, idsm_log_type type, va_list ap);
};

}

#endif
