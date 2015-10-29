
/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Jeroen Domburg <jeroen@spritesmods.com> wrote this file. As long as you retain 
 * this notice you can do whatever you want with this stuff. If we meet some day, 
 * and you think this stuff is worth it, you can buy me a beer in return. 
 * ----------------------------------------------------------------------------
 */


#include <esp8266.h>

#define PIRGPIO 3 /* RX */
#define LEDGPIO 2  /* VCC -> LED -> 220 ohm -> GPIO2 */
#define BTNGPIO 0  /* button to gnd w/10K pullup, keep GPIO0 for >5 seconds. The module will reboot into
its STA+AP mode.  */

static ETSTimer resetBtntimer;
static int resetCnt=0, old_pir_state = 0, led_state = 0;

void ICACHE_FLASH_ATTR ioLed(int ena) {
	if (ena) {
	  led_state = 1;
		} else {
	  led_state = 0;
	}
}

static void ICACHE_FLASH_ATTR resetBtnTimerCb(void *arg) {
	int pir_state = GPIO_INPUT_GET(PIRGPIO);

	if (old_pir_state != pir_state) {
		/* toggle LED */
		led_state ^= 1;
		old_pir_state = pir_state;
		}
	gpio_output_set((led_state ^ 1) << LEDGPIO, led_state << LEDGPIO, 1 << LEDGPIO, 0);

	if (!GPIO_INPUT_GET(BTNGPIO)) {  /* read AP button */
		resetCnt++;
	} else {
		if (resetCnt >= (5 * 2)) { //5 sec pressed
			wifi_station_disconnect();
			wifi_set_opmode(STATIONAP_MODE); //reset to AP+STA mode
			os_printf("Reset to AP mode. Restarting system...\n");
			system_restart();
		}
		resetCnt=0;
	}
}

void ioInit() {
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, FUNC_GPIO2);
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO0_U, FUNC_GPIO0);
	PIN_PULLUP_EN(PERIPHS_IO_MUX_GPIO0_U);
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_U0RXD_U, FUNC_GPIO3);  /* RX Pin */
	PIN_PULLUP_DIS(PERIPHS_IO_MUX_U0RXD_U);
	/* set, clear, enable, disable */
	gpio_output_set(1 << LEDGPIO, 0, 1 << LEDGPIO,	0);
	gpio_output_set(0, 0, 0, 1 << BTNGPIO);
	gpio_output_set(0, 0, 0, 1 << PIRGPIO);
	os_timer_disarm(&resetBtntimer);
	os_timer_setfn(&resetBtntimer, resetBtnTimerCb, NULL);
	os_timer_arm(&resetBtntimer, 500, 1);  /* 2nd param is in ms */
}
