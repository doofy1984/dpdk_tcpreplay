#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <rte_ethdev.h>

#include "tcpreplay_log.h"
#include "tcpreplay_args.h"
#include "tcpreplay_global.h"
#include "tcpreplay_netport.h"

int
tcpreplay_netport_init(struct arguments *args)
{   
    int ret;
    uint8_t rss_key [40];
    struct rte_eth_link link;
    struct rte_eth_dev_info dev_info;
    struct rte_eth_rss_conf rss_conf;
    struct rte_eth_fdir fdir_conf;
    
    /* Retreiving and printing device infos */
    rte_eth_dev_info_get(i, &dev_info);
    printf("Name:%s\n\tDriver name: %s\n\tMax rx queues: %d\n\tMax tx queues: %d\n", dev_info.pci_dev->driver->name,dev_info.driver_name, dev_info.max_rx_queues, dev_info.max_tx_queues);
    printf("\tPCI Adress: %04d:%02d:%02x:%01d\n", dev_info.pci_dev->addr.domain, dev_info.pci_dev->addr.bus, dev_info.pci_dev->addr.devid, dev_info.pci_dev->addr.function);
    
    /* Configure device with '1' rx queues and 1 tx queue */
    ret = rte_eth_dev_configure(i, 1, 1, &port_conf);
    if (ret < 0) rte_panic("Error configuring the port\n");
    
    /* For each RX queue in each NIC */
    /* Configure rx queue j of current device on current NUMA socket. It takes elements from the mempool */
    ret = rte_eth_rx_queue_setup(i, 0, RX_QUEUE_SZ, rte_socket_id(), &rx_conf, pktmbuf_pool);
    if (ret < 0) FATAL_ERROR("Error configuring receiving queue\n");
    /* Configure mapping [queue] -> [element in stats array] */
    ret = rte_eth_dev_set_rx_queue_stats_mapping    (i, 0, 0);
    if (ret < 0) FATAL_ERROR("Error configuring receiving queue stats\n");
    
    
    /* Configure tx queue of current device on current NUMA socket. Mandatory configuration even if you want only rx packet */
    ret = rte_eth_tx_queue_setup(i, 0, TX_QUEUE_SZ, rte_socket_id(), &tx_conf);
    if (ret < 0) FATAL_ERROR("Error configuring transmitting queue. Errno: %d (%d bad arg, %d no mem)\n", -ret, EINVAL ,ENOMEM);
    
    /* Start device */      
    ret = rte_eth_dev_start(i);
    if (ret < 0) FATAL_ERROR("Cannot start port\n");
    
    /* Enable receipt in promiscuous mode for an Ethernet device */
    rte_eth_promiscuous_enable(i);
    
    /* Print link status */
    rte_eth_link_get_nowait(i, &link);
    if (link.link_status)   printf("\tPort %d Link Up - speed %u Mbps - %s\n", (uint8_t)i, (unsigned)link.link_speed,(link.link_duplex == ETH_LINK_FULL_DUPLEX) ?("full-duplex") : ("half-duplex\n"));
    else            printf("\tPort %d Link Down\n",(uint8_t)i);
    
    /* Print RSS support, not reliable because a NIC could support rss configuration just in rte_eth_dev_configure whithout supporting rte_eth_dev_rss_hash_conf_get*/
    rss_conf.rss_key = rss_key;
    ret = rte_eth_dev_rss_hash_conf_get (i,&rss_conf);
    if (ret == 0) printf("\tDevice supports RSS\n"); else printf("\tDevice DOES NOT support RSS\n");
    
    /* Print Flow director support */
    ret = rte_eth_dev_fdir_get_infos (i, &fdir_conf);
    if (ret == 0) printf("\tDevice supports Flow Director\n"); else printf("\tDevice DOES NOT support Flow Director\n"); 

    if (args)
        return 1;
    return 1;
}

