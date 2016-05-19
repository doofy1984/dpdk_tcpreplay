#ifndef __TCPREPLAY_ARGS_H__
#define __TCPREPLAY_ARGS_H__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <signal.h>
#include <argp.h>
#include <inttypes.h>

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

struct arguments* tcpreplay_get_args(void);

#endif /**end ifndef __TCPREPLAY_ARGS_H__*/
