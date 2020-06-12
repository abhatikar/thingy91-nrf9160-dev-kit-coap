#include <zephyr.h>
#include <modem/lte_lc.h>
#include <logging/log.h>

#include "modem.h"

#define LOG_LEVEL CONFIG_MODEM_LOG_LEVEL
LOG_MODULE_REGISTER(MODEM);

void modem_init(void) {
#if defined(CONFIG_LTE_LINK_CONTROL)
  if (!IS_ENABLED(CONFIG_LTE_AUTO_INIT_AND_CONNECT)) {
    int err;

    LOG_INF("LTE Link Connecting...");
    err = lte_lc_init_and_connect();
    __ASSERT(err == 0, "LTE link could not be established.");
    LOG_INF("LTE Link Connected!");
  }
#endif /* defined(CONFIG_LTE_LINK_CONTROL) */
}
