/**
 * @brief - implements idsm service
 *
 * @author - Devendra Naga (devendra.aaru@gmail.com)
 * @copyright - All rights reserved 2022-present Proprietary
 */
#ifndef __IDSM_SERVICE_H__
#define __IDSM_SERVICE_H__

#include <iostream>
#include <stdarg.h>
#include <memory>
#include <idsm_config.h>
#include <idsm_log.h>
#include <idsm_service_intf.h>

#define IDSM_CONFIG "./idsm_service.json"

namespace idsm {

/**
 * @brief - idsm service definition
 */
class idsm_service {
    public:
        explicit idsm_service();
        ~idsm_service();

        void run();

    private:
        std::unique_ptr<idsm_local_service_intf> local_conn_;
};

}

#endif

