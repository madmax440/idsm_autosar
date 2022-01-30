/**
 * @brief - implements idsm library
 *
 * @author - Devendra Naga (devendra.aaru@gmail.com)
 * @copyright - All rights reserved 2022-present Proprietary
 */
#ifndef __IDSM_H__
#define __IDSM_H__

#include <memory>

namespace idsm {

/**
 * @brief - idsm configuration
 * 
 */
struct idsm_config {
    bool has_timestamp_;
    bool has_signature_;
    bool has_context_data_;
    int proto_version_;
};

/**
 * @brief - sender type
 */
enum class idsm_sender_type {
    eCAN,
    eEthernet,
};

class idsm_sender_if {
    public:
        explicit idsm_sender_if() = default;
        ~idsm_sender_if() = default;
};

class idsm_sender_if_factory {
    public:
        static idsm_sender_if_factory *instance()
        {
            static idsm_sender_if_factory fact;
            return &fact;
        }

        std::unique_ptr<idsm_sender_if> create(idsm_sender_type type);
};

enum class idsm_timestamp_source {
    eAutoSAR_Classic_Ts,
    eAutoSAR_ARA_TSYNC_Ts,
    eOEM_Specific,
};

enum class signature_alg {
    eHmac_256,
    eEcdsa_256,
};

struct idsm_context_data {
    uint32_t context_data_len;
    uint8_t context_data[0];
} __attribute__((__packed__));

struct idsm_msg {
    uint32_t                    ids_msg_id;
    uint32_t                    ids_instance_id;
    uint32_t                    sensor_instance_id;
    uint32_t                    event_definition_id;
    idsm_timestamp_source       ts_source;
    uint32_t                    ts_sec;
    uint32_t                    ts_nsec;
    signature_alg               sign_alg;
    idsm_context_data           ctx_data;
} __attribute__((__packed__));

/**
 * @brief - creates idsm interface
 */
class idsm_intf {
    public:
        explicit idsm_intf(idsm_config &conf);
        ~idsm_intf();

        int raise_event(idsm_msg &msg);

    private:
        idsm_config conf_;
        std::unique_ptr<idsm_sender_if> sender_if_;
};

}

#endif

