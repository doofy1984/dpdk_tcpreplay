#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <rte_eal.h>
#include <rte_log.h>
#include <rte_common.h>

#include "tcpreplay_args.h"
#include "tcpreplay_log.h"

int main(int argc, char *argv[])
{
    printf("the tcpreplay begin run......\n");
    int ret;
    struct arguments argument;

    /** Init DPDK Environment Abstraction Layer (EAL)*/
    ret = rte_eal_init(argc, argv);
    if (ret < 0)
        rte_exit(EXIT_FAILURE, "DPDK Eal Init Error, will exit\n");

    argc += ret;
    argv += ret;

    /** Init Tcpreplay Args*/
    (void)memset(&argument, 0, sizeof(struct arguments));
    ret = tcpreplay_args_init(&argument, argc, argv);
    if (ret == RET_ERROR)
        rte_exit(EXIT_FAILURE, "Tcpreplay Args Init Error, will exit\n");

    /** Check Tcpreplay Args*/
    ret = tcpreplay_args_check(&argument);
    if (ret == RET_ERROR)
        rte_exit(EXIT_FAILURE, "Tcpreplay Args Check Error, will exit\n");

    /** Init Tcpreplay log*/
    ret = tcpreplay_log_init(&argument);
    if (ret == RET_ERROR)
        rte_exit(EXIT_FAILURE, "Tcpreplay Log Init Error, will exit\n");
    
    return 0;
}
