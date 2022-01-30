# idsm_autosar

test implementation of AutoSAR IDSM

## configuration definitions

| configuration item  | configuration meaning |
|---------------------|-----------------------|
| enable | enable or disable this service |
| local_server_conn_type | type of local server (unix for now) |
| unix.server_addr | unix server address |
| max_event_storage_size_kbytes | maximum size of events in kbytes |
| reporting_mode | one of reporting modes : off, brief, detailed, brief_bypassing_filters, detailed_bypassing_filters |
