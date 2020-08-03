#pragma once

typedef struct {
  u16_t current_band;
  u16_t area_code;
  char current_operator[100];
  u16_t mcc;
  u16_t mnc;
  char cellid_hex[100];
  char ip_address[100];
  /*
  u16_t ue_mode;
  u16_t lte_mode;
  u16_t nbiot_mode;
  u16_t gps_mode;
  u16_t date_time;
  u16_t apn;
  u16_t cellid_dec;

  u16_t uicc;
  u16_t iccid;
  u16_t imsi;
  */

  char modem_fw[100];
  u16_t battery;
  u16_t imei;
} modem_t;

void modem_init();

void modem_sample(modem_t *modem);
