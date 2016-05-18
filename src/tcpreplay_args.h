#ifndef __TCPREPLAY_ARGS_H__
#define __TCPREPLAY_ARGS_H__

/* This structure is used by main to communicate with parse_opt. */
typedef struct arguments {
    uint64_t   port_mask;
    char      *pcap_file;
    uint32_t   per_port_cores_num;
    uint32_t   send_times;
    uint32_t   send_speed;
    char      *logs_file;
} arguments;


int tcpreplay_args_init(struct arguments* args, int argc, char *argv[]);

int tcpreplay_args_check(struct arguments* args);


#endif /**end ifndef __TCPREPLAY_ARGS_H__*/
