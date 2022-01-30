/**
 * @brief - implements idsm storage interface
 *
 * @author - Devendra Naga (devendra.aaru@gmail.com)
 * @copyright - 2022-present All rights reserved proprietary
 */
#ifndef __IDSM_STORAGE_H__
#define __IDSM_STORAGE_H__

#include <memory>
#include <thread>
#include <mutex>
#include <queue>
#include <idsm_events.h>

namespace idsm {

class idsm_storage {
    public:
        ~idsm_storage() = default;
        static idsm_storage *instance()
        {
            static idsm_storage storage;
            return &storage;
        }

        int write_event(uint8_t *buff, size_t buff_size);

    private:
        std::unique_ptr<std::thread> storage_thr_;
        std::queue<idsm_event_buf> events_;
        std::mutex lock_;
        void process_storage_requests();
        explicit idsm_storage() = default;
};

}

#endif

