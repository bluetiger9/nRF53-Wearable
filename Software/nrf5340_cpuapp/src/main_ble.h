#ifndef MAIN_BLE_H
#define MAIN_BLE_H

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/conn.h>
#include <bluetooth/uuid.h>
#include <bluetooth/gatt.h>
#include <bluetooth/services/bas.h>
#include <bluetooth/services/hrs.h>

#ifdef __cplusplus
extern "C" {
#endif

static const struct bt_data ad[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
	BT_DATA_BYTES(BT_DATA_UUID16_ALL,
		      BT_UUID_16_ENCODE(BT_UUID_HRS_VAL),
		      BT_UUID_16_ENCODE(BT_UUID_BAS_VAL),
		      BT_UUID_16_ENCODE(BT_UUID_DIS_VAL))
};

void connected(struct bt_conn *conn, uint8_t err);

void disconnected(struct bt_conn *conn, uint8_t reason);

static struct bt_conn_cb conn_callbacks = {
	.connected = connected,
	.disconnected = disconnected,
};

void bt_ready(void);

void auth_cancel(struct bt_conn *conn);

static struct bt_conn_auth_cb auth_cb_display = {
	.cancel = auth_cancel,
};

void bas_notify(void);

void hrs_notify(void);

extern float get_heartrate();

#ifdef __cplusplus
}
#endif

#endif