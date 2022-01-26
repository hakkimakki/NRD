#include <zephyr.h>
#include <usb/usb_device.h>

void szl_init_usb_cdc_acm()
{
	usb_enable(NULL);
}