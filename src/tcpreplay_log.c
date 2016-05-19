#include <stdio.h>
#include <stdlib.h>

#include <rte_log.h>
#include <rte_common.h>

#include "tcpreplay_args.h"
#include "tcpreplay_log.h"

int
tcpreplay_log_init(struct arguments* args)
{
    int ret = 0;    
    FILE * log_fd;
    
    /* Set log level */
    rte_set_log_type(TCPREPLAY_LOG_TYPE, 1);
    rte_set_log_level(RTE_LOG_DEBUG);

    /* Change log stream if needed */
    if (args->logs_file) {
        log_fd = fopen(args->logs_file, "w");
        if (!log_fd) {
            rte_log(RTE_LOG_ERR, TCPREPLAY_LOG_TYPE, "Error: Could not open log file: (%d) %s\n",
                errno, strerror(errno));
            return RET_ERROR;
        }
        
        ret = rte_openlog_stream(log_fd);
        if (ret) {
            rte_log(RTE_LOG_ERR, TCPREPLAY_LOG_TYPE, "Error: Could not change log stream: (%d) %s\n",
                errno, strerror(errno));
            fclose(log_fd);
            return RET_ERROR;
        }
    }
    return RET_SUCCESS;
}

