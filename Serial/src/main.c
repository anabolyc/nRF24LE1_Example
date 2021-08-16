#include "reg24le1.h"
#include "gpio.h"
#include "rf.h"
#include "uart.h"

#define PINS_COUNT 13

gpio_pin_id_t pins[] = {
	GPIO_PIN_ID_P0_0,
	GPIO_PIN_ID_P0_1,
	GPIO_PIN_ID_P0_2,
	//GPIO_PIN_ID_P0_3, UART TX
	//GPIO_PIN_ID_P0_4, UART RX
	GPIO_PIN_ID_P0_5,
	GPIO_PIN_ID_P0_6,
	GPIO_PIN_ID_P0_7,

	GPIO_PIN_ID_P1_0,
	GPIO_PIN_ID_P1_1,
	GPIO_PIN_ID_P1_2,
	GPIO_PIN_ID_P1_3,
	GPIO_PIN_ID_P1_4,
	GPIO_PIN_ID_P1_5,
	GPIO_PIN_ID_P1_6};

void setup(void)
{

	// Setup UART pins
	gpio_pin_configure(GPIO_PIN_ID_FUNC_RXD,
			GPIO_PIN_CONFIG_OPTION_DIR_INPUT |
			GPIO_PIN_CONFIG_OPTION_PIN_MODE_INPUT_BUFFER_ON_NO_RESISTORS);

	gpio_pin_configure(GPIO_PIN_ID_FUNC_TXD,
			GPIO_PIN_CONFIG_OPTION_DIR_OUTPUT |
			GPIO_PIN_CONFIG_OPTION_OUTPUT_VAL_SET |
			GPIO_PIN_CONFIG_OPTION_PIN_MODE_OUTPUT_BUFFER_NORMAL_DRIVE_STRENGTH);

	uart_configure_8_n_1_19200();

	//puts("Starting up\r\n");

	for (uint8_t i = 0; i < PINS_COUNT; i++)
	{
		gpio_pin_configure(
			pins[i],
			GPIO_PIN_CONFIG_OPTION_DIR_OUTPUT |
				GPIO_PIN_CONFIG_OPTION_OUTPUT_VAL_CLEAR |
				GPIO_PIN_CONFIG_OPTION_PIN_MODE_OUTPUT_BUFFER_NORMAL_DRIVE_STRENGTH);
	}
}

uint8_t state = 0;

void loop()
{
	uint8_t i = state++ % PINS_COUNT;
	uart_rx_disable();
	putchar('0' + i);
	putchar('\r');
	putchar('\n');
	uart_rx_enable();
	gpio_pin_val_set(pins[i]);
	delay_ms(250);
	gpio_pin_val_clear(pins[i]);
}

void main()
{
	setup();
	while (1)
		loop();
}
