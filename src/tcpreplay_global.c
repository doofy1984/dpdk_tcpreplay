
#include "tcpreplay_global.h"

struct global_cfg global;

struct global_cfg*
tcpreplay_get_global(void)
{
    return &global;
}
