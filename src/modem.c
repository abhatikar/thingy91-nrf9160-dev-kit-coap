#include <zephyr.h>
#include <modem/lte_lc.h>
#include <modem/modem_info.h>
#include <logging/log.h>

#include "modem.h"

#define LOG_LEVEL CONFIG_MODEM_LOG_LEVEL
LOG_MODULE_REGISTER(MODEM);

struct modem_param_info modem_param;

void modem_init() {
  int err;

#if defined(CONFIG_LTE_LINK_CONTROL)
  if (!IS_ENABLED(CONFIG_LTE_AUTO_INIT_AND_CONNECT)) {
    LOG_INF("LTE Link Connecting...");
    err = lte_lc_init_and_connect();
    __ASSERT(err == 0, "LTE link could not be established.");
    LOG_INF("LTE Link Connected!");
  }
#endif /* defined(CONFIG_LTE_LINK_CONTROL) */

  err = modem_info_init();
  __ASSERT(err == 0, "Modem info module could not be initialized.");
  err = modem_info_params_init(&modem_param);
  __ASSERT(err == 0, "Modem info parameter structure could not be initialized.");
}

void modem_sample(modem_t *modem) {
  int err;

  // Null out

  err = modem_info_params_get(&modem_param);
  if (err == 0) {
    modem->current_band = modem_param.network.current_band.value;
    modem->area_code = modem_param.network.area_code.value;
    memcpy(&modem->current_operator, &modem_param.network.current_operator.value_string, 100);
    modem->mcc = modem_param.network.mcc.value;
    modem->mnc = modem_param.network.mnc.value;
    memcpy(&modem->cellid_hex, &modem_param.network.cellid_hex.value_string, 100);
    memcpy(&modem->ip_address, &modem_param.network.ip_address.value_string, 100);
    memcpy(&modem->modem_fw, &modem_param.device.modem_fw.value_string, 100);
    modem->battery = modem_param.device.battery.value;
    modem->imei = modem_param.device.imei.value;
  }
}
