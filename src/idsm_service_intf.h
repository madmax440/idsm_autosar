/**
 * @brief - implements idsm configuration parsing
 *
 * @author - Devendra Naga (devendra.aaru@gmail.com)
 * @copyright - All rights reserved 2022-present Proprietary
 */
#ifndef __IDSM_SERVICE_INTF_H__
#define __IDSM_SERVICE_INTF_H__

#include <thread>

namespace idsm {

/**
 * @brief - defines local unix socket message abstraction
 */
class idsm_local_unix_sock {
    public:
        explicit idsm_local_unix_sock();
        ~idsm_local_unix_sock();

        int init();

        /**
         * @brief - get socket underlying
         *
         * @returns socket descriptor
         */
        int get_socket() { return fd_; }
        int send_msg(uint8_t *data, size_t data_len);
        int recv_msg(uint8_t *data, size_t data_len);

    private:
        int fd_;
};

/**
 * @brief - defines local service interface
 */
class idsm_local_service_intf {
    public:
        explicit idsm_local_service_intf();
        ~idsm_local_service_intf();

        void run();

    private:
        std::unique_ptr<idsm_local_unix_sock> unix_conn_;
        std::unique_ptr<std::thread> service_thr_;
        void process_local_service_requests();
};

}

#endif

