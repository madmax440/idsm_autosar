/**
 * @brief - implements idsm configuration parsing
 *
 * @author - Devendra Naga (devendra.aaru@gmail.com)
 * @copyright - All rights reserved 2022-present Proprietary
 */
#include <iostream>
#include <fstream>
#include <string>
#include <idsm_config.h>
#include <jsoncpp/json/json.h>

namespace idsm {

int idsm_config::parse(const std::string config_file)
{
    Json::Value root;
    std::ifstream conf(config_file, std::ifstream::binary);

    conf >> root;

    enable = root["enable"].asBool();
    auto local_conn_type_str = root["local_server_conn_type"].asString();
    if (local_conn_type_str == "unix") {
        conn_type = idsm_local_conn_type::eUNIX;
        unix_conn.server_addr = root["unix"]["server_addr"].asString();
    } else {
        idsm_log::instance()->error("invalid local_conn_type_str %s\n", local_conn_type_str.c_str());
        return -1;
    }
    max_evt_storage_size_kbytes = root["max_event_storage_size_kbytes"].asUInt();

    return 0;
}

}

