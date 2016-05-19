#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <signal.h>
#include <argp.h>
#include <inttypes.h>

#include <rte_log.h>

#include "tcpreplay_args.h"
#include "tcpreplay_log.h"

struct arguments argument;

const char *argp_program_version = "tcpreplay 1.0";

const char *argp_program_bug_address = "<chenchong0617@gmail.com>";

/*
 *  PARSER. Field 2 in ARGP.
 *  Order of parameters: KEY, ARG, STATE.
 */

static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
    struct arguments* args = state->input;
    char *end;

    switch (key) {
        case 'p':
            /* parse hexadecimal string */
            args->port_mask = strtoul(arg, &end, 16);
            if (errno != 0 || *end != '\0' ||
                    (args->port_mask == ULONG_MAX && errno == ERANGE)) {
                rte_log(RTE_LOG_ERR, TCPREPLAY_LOG_TYPE, "Invalid portmask '%s' (could not convert to "\
                    "unsigned long)\n", arg);
                return RET_ERROR;
            }
            if (args->port_mask == 0) {
                    rte_log(RTE_LOG_ERR, TCPREPLAY_LOG_TYPE, "Invalid portmask '%s', no port used\n", arg);
                return RET_ERROR;
            }
            break;
        case 'f':
            /* parse pcap file string */
            if (arg)
                args->pcap_file = strdup(arg);
            break;
        case 'c':
            /* parse per_port_cores_num string */
            args->per_port_cores_num = atoi(arg);
            break;
        case 't':
            /* parse send_times string */
            args->send_times = atoi(arg);
            break;
        case 's':
            /* parse send_speed string */
            args->send_speed= atoi(arg);
            break;
        case 'l':
            /* parse logs_file string */
            if (arg)
                args->logs_file= strdup(arg);
            break;
        default:
            return RET_ERROR;
    }
    return RET_SUCCESS;
}

int
tcpreplay_args_init(struct arguments* args, int argc, char *argv[])
{
    /*
     *  OPTIONS.  Field 1 in ARGP.
     *  Order of fields: {NAME, KEY, ARG, FLAGS, DOC}.
     *  */
    static struct
    argp_option options[] = {
      { "port_mask",           'p',  "PORT_MASK",          0, "The core where to bind the program ", 0 },
      { "pcap_file",           'f',  "PCAP_FILE",          0, "The pcap file path", 0 },
      { "per_port_cores_num",  'c',  "NB_CORES_PER_PORT",  0, "Number of cores per port used for send packet (default: 1)", 0 },
      { "send_times",          't',  "SEND_TIMES",         0, "Send pcap file packet times (default: 1)", 0 },
      { "send_speed",          's',  "SEND_SPEED",         0, "Send packets speed (default MAX speed)", 0 },
      { "logs_file",           'l',  "LOGS_FILE",          0, "Writes the logs into FILE instead of stderr", 0},
      { 0 } };
      
    /*
     *  ARGS_DOC. Field 3 in ARGP.
     *  A description of the non-option command-line arguments
     *  that we accept.
     *  */
    static char args_doc[] = "\0";
      
    /*
     *  DOC.  Field 4 in ARGP.
     *  Program documentation.
     *  */
    static char doc[] =
        "tcprepaly -- A program to send packets in pcap file with DPDK.";

    /*
     *  The ARGP structure itself.
     *  */
    static struct argp arg = {options, parse_opt, args_doc, doc, 0, 0, 0};

    /* Set argument defaults */
    args->port_mask  = 0;
    args->pcap_file  = NULL;
    args->logs_file  = NULL;
    args->send_speed = 0;
    args->send_times = 1;
    args->per_port_cores_num = 1;

    /* parse the args*/
    argp_parse(&arg, argc, argv, 0, 0, args);

    return RET_SUCCESS;
}

int
tcpreplay_args_check(struct arguments* args)
{
    if (args)
        return RET_SUCCESS;
    return RET_SUCCESS;
}

struct arguments*
tcpreplay_get_args(void)
{
    return &argument;
}


