#ifndef __TCPREPLAY_LOG_H__
#define __TCPREPLAY_LOG_H__

#include "tcpreplay_args.h"

#define RET_SUCCESS           1
#define RET_ERROR             0

#define TCPREPLAY_LOG_TYPE    RTE_LOGTYPE_USER1
#define TCPREPLAY             USER1


int tcpreplay_log_init(struct arguments* args);

#endif /**end ifndef __TCPREPLAY_LOG_H__*/

