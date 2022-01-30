/**
 * @brief - implements idsm events interface
 *
 * @author - Devendra Naga (devendra.aaru@gmail.com)
 * @copyright - 2022-present All rights reserved proprietary
 */
#ifndef __IDSM_EVENTS_H__
#define __IDSM_EVENTS_H__

#include <stdint.h>

namespace idsm {

struct idsm_event_buf {
    uint32_t buf_size;
    uint8_t buff[4096];
};

enum class idsm_timestamp_source {
    eautosar_classic_ts,
    eautosar_ara_tsync_ts,
    eoem_specific,
};

enum class idsm_signature_alg {
    ehmac_256,
    eecdsa_256,
};

struct idsm_timestamp {
    uint32_t sec;
    uint32_t nsec;
};

struct idsm_context_data {
    uint32_t context_data_len;
    uint8_t context_data[4096];
};

struct idsm_event {
    uint32_t ids_msg_id;
    uint8_t protocol_version;
    bool has_timestamp;
    bool has_signature;
    bool has_context_data;
    uint32_t idsm_instance_id;
    uint32_t sensor_instance_id;
    uint32_t event_definition_id;
    idsm_timestamp_source ts_src;
    idsm_timestamp ts;
    idsm_signature_alg sign_alg;
    idsm_context_data ctx_data;

    explicit idsm_event() = default;
    ~idsm_event() = default;

    int serialize(idsm_event_buf *buff);
    int deserialize(idsm_event_buf *buff);
};

}

#endif

