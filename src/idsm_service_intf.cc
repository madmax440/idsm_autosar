/**
 * @brief - implements idsm service interface
 *
 * @author - Devendra Naga (devendra.aaru@gmail.com)
 * @copyright - All rights reserved 2022-present Proprietary
 */
#include <unistd.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include <string>
#include <memory>
#include <idsm_config.h>
#include <idsm_service_intf.h>
#include <idsm_log.h>

namespace idsm {

idsm_local_unix_sock::idsm_local_unix_sock()
{

}

int idsm_local_unix_sock::init()
{
    idsm_config *conf = idsm_config::instance();
    int ret = -1;

    // initialize unix local server if unix domain
    if (conf->conn_type == idsm_local_conn_type::eUNIX) {
        fd_ = socket(AF_UNIX, SOCK_DGRAM, 0);
        if (fd_ < 0) {
            idsm_log::instance()->error("failed to initialize unix dgram socket\n");
            return -1;
        }

        struct sockaddr_un serv;

        unlink(conf->unix_conn.server_addr.c_str());
        strcpy(serv.sun_path, conf->unix_conn.server_addr.c_str());
        serv.sun_family = AF_UNIX;

        ret = bind(fd_, (struct sockaddr *)&serv, sizeof(serv));
        if (ret < 0) {
            idsm_log::instance()->error("failed to bind unix dgram socket\n");
            unlink(conf->unix_conn.server_addr.c_str());
            close(fd_);
            return -1;
        }
        ret = 0;
    }

    return ret;
}

int idsm_local_unix_sock::send_msg(uint8_t *data, size_t data_size)
{
    return send(fd_, data, data_size, 0);
}

int idsm_local_unix_sock::recv_msg(uint8_t *data, size_t data_size)
{
    return recv(fd_, data, data_size, 0);
}

idsm_local_unix_sock::~idsm_local_unix_sock()
{

}

void idsm_local_service_intf::run()
{
    service_thr_->join();
}

/**
 * @brief - process local service request
 */
void idsm_local_service_intf::process_local_service_requests()
{
    uint8_t buff[4096];
    int ret;

    while (1) {
        ret = unix_conn_->recv_msg(buff, sizeof(buff));
        if (ret < 0) {
            break;
        }
    }
}

/**
 * @brief - setup local service interface
 */
idsm_local_service_intf::idsm_local_service_intf()
{
    int ret;

    // create local server 
    unix_conn_ = std::make_unique<idsm_local_unix_sock>();
    ret = unix_conn_->init();
    if (ret < 0) {
        throw std::runtime_error("failed to init unix local socket\n");
    }

    // create thread to receive messages from sensors
    service_thr_ = std::make_unique<std::thread>(
                            &idsm_local_service_intf::process_local_service_requests,
                            this);

    idsm_log::instance()->info("idsm: local service thread created\n");
}

idsm_local_service_intf::~idsm_local_service_intf()
{

}

}

