/**
 * @brief - implements idsm storage interface
 *
 * @author - Devendra Naga (devendra.aaru@gmail.com)
 * @copyright - 2022-present All rights reserved proprietary
 */
#include <idsm_storage.h>

namespace idsm {

int idsm_storage::write_event(uint8_t *buff, size_t buff_size)
{

}

void idsm_storage::process_storage_requests()
{
    while (1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

}
