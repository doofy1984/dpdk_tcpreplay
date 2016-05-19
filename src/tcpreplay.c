#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <rte_eal.h>
#include <rte_log.h>
#include <rte_common.h>

#include "tcpreplay_args.h"
#include "tcpreplay_log.h"
#include "tcpreplay_global.h"
#include "tcpreplay_netport.h"

int main(int argc, char *argv[])
{
    int ret;
    struct arguments  *args = NULL;
    struct global_cfg *global = NULL;
    /** Init DPDK Environment Abstraction Layer (EAL)*/
    ret = rte_eal_init(argc, argv);
    if (ret < 0)
        rte_exit(EXIT_FAILURE, "DPDK Eal Init Error, will exit\n");

    argc += ret;
    argv += ret;

    args   = tcpreplay_get_args();
    global = tcpreplay_get_global();

    if (args == NULL || global == NULL)
        rte_exit(EXIT_FAILURE, "...............\n");
    
    /** Init Tcpreplay Args*/
    (void)memset(args, 0, sizeof(struct arguments));
    ret = tcpreplay_args_init(args, argc, argv);
    if (ret == RET_ERROR)
        rte_exit(EXIT_FAILURE, "Tcpreplay Args Init Error, will exit\n");

    /** Check Tcpreplay Args*/
    ret = tcpreplay_args_check(args);
    if (ret == RET_ERROR)
        rte_exit(EXIT_FAILURE, "Tcpreplay Args Check Error, will exit\n");

    /** Init Tcpreplay log*/
    ret = tcpreplay_log_init(args);
    if (ret == RET_ERROR)
        rte_exit(EXIT_FAILURE, "Tcpreplay Log Init Error, will exit\n");

    /** Init Tcpreplay Netport*/
    ret = tcpreplay_netport_init(args);
    if (ret == RET_ERROR)
        rte_exit(EXIT_FAILURE, "Tcpreplay Netport Init Error, will exit\n");
    
    return 0;
}
