/* main.c - Application main entry point */

/*
 * Copyright (c) 2015-2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/types.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <sys/printk.h>
#include <sys/byteorder.h>
#include <zephyr.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/conn.h>
#include <bluetooth/uuid.h>
#include <bluetooth/gatt.h>
#include <bluetooth/services/bas.h>
#include <bluetooth/services/hrs.h>

#include <drivers/i2c.h>

#include "main_ble.h"

#include "MAX30105.h"
#include "heartRate.h"
#include "spo2_algorithm.h"

#include "MAX30205.h"

float human_temp = 0;

extern "C" {

float get_heartrate() {
  return human_temp;
}

}
void main(void)
{
	int err;

        const device *i2c_dev;

        i2c_dev = device_get_binding("I2C_1");
        if (i2c_dev == NULL) {
            printk("I2C Init Failed!\n");
            return;
        }

        // I2C Scan
        printk("I2C scan start!\n");
        for (uint8_t addr = 0x02; addr < /*128*/ 0; ++addr) {
          uint8_t cmd = 1;
          int error = i2c_write(i2c_dev, &cmd, 1, addr);
          if (error == 0) {
            printk("I2C device found at addr 0x%2X!\n", addr);
          }
        }
        printk("I2C scan end!\n");

        MAX30205 max30205(i2c_dev);
        if (!max30205.scanAvailableSensors()) {
          printk("MAX30205 not found!\n");
          return;
        }
      
        printk("MAX30205 found!\n");

        max30205.begin();
        max30205.printRegisters();
        
        float temp = max30205.getTemperature();
        printk("\nMAX30102 temp: %d.%2df C!\n", (int) temp, (int) (100.0 * temp) % 100);
        
        // MAX30102 Init
        //MAX30105 max30102;
        //if (!max30102.begin(i2c_dev)) {
        //  printk("MAX30102 init failed!\n");
        //  return;
        //}

        //printk("MAX30102 init OK!\n");

	err = bt_enable(NULL);
	if (err) {
		printk("Bluetooth init failed (err %d)\n", err);
		return;
	}

	bt_ready();

	bt_conn_cb_register(&conn_callbacks);
	bt_conn_auth_cb_register(&auth_cb_display);

	/* Implement notification. At the moment there is no suitable way
	 * of starting delayed work so we do it here
	 */
	while (1) {
		k_sleep(K_SECONDS(1));

		/* Heartrate measurements simulation */
                human_temp = max30205.getTemperature();
		hrs_notify();

		/* Battery level simulation */
		bas_notify();
	}
}
