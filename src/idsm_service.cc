/**
 * @brief - implements idsm service
 *
 * @author - Devendra Naga (devendra.aaru@gmail.com)
 * @copyright - All rights reserved 2022-present Proprietary
 */
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include <fstream>
#include <idsm_service.h>

namespace idsm {

idsm_service::idsm_service()
{
    int ret;

    // parse configuration
    ret = idsm_config::instance()->parse(IDSM_CONFIG);
    if (ret != 0) {
        throw std::runtime_error("failed to parse configuration\n");
    }

    idsm_log::instance()->info("parse config %s ok\n", IDSM_CONFIG);

    // create local server for messages from the sensors
    local_conn_ = std::make_unique<idsm_local_service_intf>();
}

idsm_service::~idsm_service()
{

}

void idsm_service::run()
{
    local_conn_->run();
}

}

int main()
{
    idsm::idsm_service serv;

    serv.run();
}
