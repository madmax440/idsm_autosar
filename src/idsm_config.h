/**
 * @brief - implements idsm configuration parsing
 *
 * @author - Devendra Naga (devendra.aaru@gmail.com)
 * @copyright - All rights reserved 2022-present Proprietary
 */
#ifndef __IDSM_CONFIG_H__
#define __IDSM_CONFIG_H__

#include <idsm_log.h>

namespace idsm {

enum class idsm_local_conn_type {
    eUNIX,
    eUDP,
};

struct idsm_unix_conn_config {
    std::string server_addr;
};

struct idsm_config {
    bool enable;
    idsm_local_conn_type conn_type;
    idsm_unix_conn_config unix_conn;
    uint32_t max_evt_storage_size_kbytes;

    ~idsm_config() = default;
    static idsm_config *instance()
    {
        static idsm_config conf;
        return &conf;
    }

    int parse(const std::string config_file);

    private:
        explicit idsm_config() = default;
};

}

#endif
