/* ---------- Reset Button ------------------- */
#include <zephyr.h>
#include <device.h>
#include <drivers/gpio.h>
#include <sys/reboot.h>

static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET_OR(DT_ALIAS(sw0), gpios, {0});
static struct gpio_callback button_cb_data;
static struct k_work_delayable buttons_debounce;

static void reset()
{
  printk("Reboot now!\n");
  sys_reboot(SYS_REBOOT_COLD);
}

static void buttons_debounce_fn(struct k_work *work)
{
  if (gpio_pin_get_dt(&button) == true)
  {
    reset();
  }
}

void button_pressed(const struct device *dev, struct gpio_callback *cb,
                    uint32_t pins)
{
  printk("Button pressed at %" PRIu32 "\n", k_cycle_get_32());
  k_work_reschedule(&buttons_debounce, K_MSEC(5 * 1000)); // Debounce the Button
}

void init_reset_button(){
  //Init Reset Button
  gpio_pin_configure_dt(&button, GPIO_INPUT);
  gpio_pin_interrupt_configure_dt(&button, GPIO_INT_EDGE_TO_ACTIVE);
  gpio_init_callback(&button_cb_data, button_pressed, BIT(button.pin));
  gpio_add_callback(button.port, &button_cb_data);
  k_work_init_delayable(&buttons_debounce, buttons_debounce_fn);
}


/* ---------------------- Base128 Unsigned Compression ------------------------ */

#include <zephyr.h>
#include <sys/printk.h>
#include <stdio.h>
#include <string.h>

/**
 * Write unsigned LEB128 data
 * @dst: the address where the ULEB128 data is to be stored
 * @val: value to be stored
 *
 * Encode an unsigned LEB128 encoded datum. The algorithm is taken
 * from Appendix C of the DWARF 3 spec. For information on the
 * encodings refer to section "7.6 - Variable Length Data". Return
 * the number of bytes written.
 */
size_t szl_encode_uleb128(uint64_t val, uint8_t * dst){
	static uint8_t count;
	static uint8_t byte;
  count = 0;
	do {
		byte = val & 0x7f;
		val >>= 7;

		if (val != 0)
		byte |= 0x80;  // mark this byte to show that more bytes will follow

		memcpy(dst+count,&byte,1);

		count++;
  	} while (val != 0);
	return count;
}

/**
 * Read unsigned LEB128 data
 * @addr: the address where the ULEB128 data is stored
 * @ret: address to store the result
 *
 * Decode an unsigned LEB128 encoded datum. The algorithm is taken
 * from Appendix C of the DWARF 3 spec. For information on the
 * encodings refer to section "7.6 - Variable Length Data". Return
 * the number of bytes read.
 */
size_t szl_decode_uleb128(uint8_t* addr, uint64_t* ret) {
  static uint8_t byte;
  static uint64_t result;
  static int shift;
  static size_t count;

  shift = 0;
  count = 0;
  result = 0;

  while (1) {
    byte = addr[count];
    count++;

    result |= (byte & 0x7f) << shift;
    shift += 7;

    if (!(byte & 0x80)) break;
  }

  memcpy(ret,&result,count);

  return count;
}

/* ---------------------- Sponge Data Protocol ------------------------ */

#include <zephyr.h>

//Data structure
struct Smart_Meter_data_t {
    uint16_t Strom_L1;
    uint16_t Strom_L2;
    uint16_t Strom_L3;
    uint32_t Wirkleistungsbezug;
    uint32_t Wirkenergiebezug_Tarif_1;
    uint32_t Wirkenergiebezug_Tarif_2;
};

//Number of struct elements for new_data_bitmask = n_data / 8 -> round up to byte
uint8_t new_data_bitmask[1];  

//Data
const struct Smart_Meter_data_t Smart_Meter_data_init;
struct Smart_Meter_data_t Smart_Meter_data;

/**
 * Encode the buffer with sponge
 * @buffer: buffer to encode into
 * @ret: size of encoded bytes
 */
int sponge_encode(uint8_t *buffer) {
    //Encode Message 
    int pos = 0;
    //printk("Bitmask: %u\n",new_data_bitmask[0]); 
    pos += szl_encode_uleb128(new_data_bitmask[0],&buffer[pos]);
    if (new_data_bitmask[0] & (1 << 0))
    {
      pos += szl_encode_uleb128(Smart_Meter_data.Strom_L1,&buffer[pos]);
    }
    if (new_data_bitmask[0] & (1 << 1))
    {
      pos += szl_encode_uleb128(Smart_Meter_data.Strom_L2,&buffer[pos]);
    }
    if (new_data_bitmask[0] & (1 << 2))
    {
      pos += szl_encode_uleb128(Smart_Meter_data.Strom_L3,&buffer[pos]);
    }
    if (new_data_bitmask[0] & (1 << 3))
    {
      pos += szl_encode_uleb128(Smart_Meter_data.Wirkleistungsbezug,&buffer[pos]);
    }
    if (new_data_bitmask[0] & (1 << 4))
    {
      pos += szl_encode_uleb128(Smart_Meter_data.Wirkenergiebezug_Tarif_1,&buffer[pos]);
    }
    if (new_data_bitmask[0] & (1 << 5))
    {
      pos += szl_encode_uleb128(Smart_Meter_data.Wirkenergiebezug_Tarif_2,&buffer[pos]);
    } 
    printk("Message Encoded Size: %u\n",pos);   
    return pos;
}

/**
 * Decode the buffer with sponge
 * @buffer: buffer to decode from
 * @ret: size of decoded bytes
 */
int sponge_decode(uint8_t *buffer) { 
    //Smart_Meter_data = Smart_Meter_data_init;   
    static int pos;
    pos = 0;
    pos += szl_decode_uleb128(&buffer[pos],&new_data_bitmask[0]);
    //printk("Bitmask: %u\n",new_data_bitmask[0]);
    if (new_data_bitmask[0] & (1 << 0))
    {
      pos += szl_decode_uleb128(&buffer[pos],&Smart_Meter_data.Strom_L1);
    }
    if (new_data_bitmask[0] & (1 << 1))
    {
      pos += szl_decode_uleb128(&buffer[pos],&Smart_Meter_data.Strom_L2);
    }
    if (new_data_bitmask[0] & (1 << 2))
    {
      pos += szl_decode_uleb128(&buffer[pos],&Smart_Meter_data.Strom_L3);
    }
    if (new_data_bitmask[0] & (1 << 3))
    {
      pos += szl_decode_uleb128(&buffer[pos],&Smart_Meter_data.Wirkleistungsbezug);
    }
    if (new_data_bitmask[0] & (1 << 4))
    {
      pos += szl_decode_uleb128(&buffer[pos],&Smart_Meter_data.Wirkenergiebezug_Tarif_1);
    }
    if (new_data_bitmask[0] & (1 << 5))
    {
      pos += szl_decode_uleb128(&buffer[pos],&Smart_Meter_data.Wirkenergiebezug_Tarif_2);
    } 
    //printk("Message Decoded Size: %u\n",pos); 
    //printk("Current L3: %u\n",Smart_Meter_data.Strom_L3);  
    return pos;
}

/* ---------------------- LoRa ------------------------ */
/* Requires the following overlay: */
/*
&spi1 {
   status = "okay";
        sck-pin = <47>; 
     mosi-pin = <2>;
     miso-pin = <29>;
     cs-gpios = <&gpio1 13 GPIO_ACTIVE_LOW>; 

      lora: sx1276@0 {
       compatible = "semtech,sx1276";
       reg = <0>;
       label = "sx1276";
       reset-gpios = <&gpio0 31 GPIO_ACTIVE_LOW>;
       dio-gpios = <&gpio1 10 (GPIO_PULL_DOWN | GPIO_ACTIVE_HIGH)>,<&gpio0 10 (GPIO_PULL_DOWN | GPIO_ACTIVE_HIGH)>;
       spi-max-frequency = <1000000>;
       power-amplifier-output = "pa-boost";
   };
};
/ {
   aliases {
      lora0 = &lora;
 };
};
*/
/* Requires the following Konfig: */
/*
CONFIG_LOG=y
CONFIG_SPI=y
CONFIG_GPIO=y
CONFIG_LORA=y
CONFIG_LORA_SX12XX=y
CONFIG_PRINTK=y
*/
#include <device.h>
#include <drivers/lora.h>
#include <errno.h>
#include <sys/util.h>
#include <zephyr.h>
#include <sys/crc.h>
#include <logging/log.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_RADIO_NODE DT_ALIAS(lora0)
BUILD_ASSERT(DT_NODE_HAS_STATUS(DEFAULT_RADIO_NODE, okay),
             "No default LoRa radio specified in DT");
#define DEFAULT_RADIO DT_LABEL(DEFAULT_RADIO_NODE)

#define MAX_DATA_LEN 255

const struct device *lora_dev;
struct lora_modem_config config;
static int ret, len;
uint8_t data_crc[MAX_DATA_LEN] = {0};
uint16_t crc, crc_calc;
int16_t rssi;
int8_t snr;

void szl_lora_init()
{

    lora_dev = device_get_binding(DEFAULT_RADIO);
    if (!lora_dev)
    {
        printk("%s Device not found\n", DEFAULT_RADIO);
        return;
    }

    config.frequency = 865100000;
    config.bandwidth = BW_125_KHZ;
    config.datarate = SF_10;
    config.preamble_len = 8;
    config.coding_rate = CR_4_5;
    config.tx_power = 4;
    config.tx = true;

    ret = lora_config(lora_dev, &config);
    if (ret < 0)
    {
        printk("LoRa config failed\n");
        return;
    }
}

void szl_lora_send(uint8_t *data, uint32_t data_len)
{
    if (lora_dev == NULL)
    {
        printk("Could not get LoRa device\n");
        return;
    }

    //Prepare Device for Sending
    config.tx_power = 4;
    config.tx = true;

    ret = lora_config(lora_dev, &config);
    if (ret < 0)
    {
        printk("LoRa config failed\n");
        return;
    }

    // Calc CRC
    crc = crc16_ccitt(0, data, (size_t)data_len);
    // Append CRC    
    memcpy(data_crc, data, (size_t)data_len);                   // copy data
    memcpy(data_crc + (size_t)data_len, &crc, sizeof(crc));      // copy crc

    ret = lora_send(lora_dev, data_crc, (size_t)data_len + sizeof(crc));
    if (ret < 0)
    {
        printk("LoRa send failed\n");
        return;
    }

    printk("Data sent!\n");
}

uint32_t szl_lora_recv(uint8_t *data)
{
    if (lora_dev == NULL)
    {
        printk("Could not get LoRa device\n");
        return 0;
    }

    //Prepare Device for Receiving
    config.tx_power = 14;
    config.tx = false;

    ret = lora_config(lora_dev, &config);
    if (ret < 0)
    {
        printk("LoRa config failed\n");
        return 0;
    }
    /* Block until data arrives */
    len = lora_recv(lora_dev, data_crc, MAX_DATA_LEN, K_FOREVER,
                    &rssi, &snr);   
    if (len <= 0)
    {
        printk("LoRa receive failed\n");
        return 0;
    }
    /* Decode CRC */
    memcpy(&crc, data_crc + (size_t) len - sizeof(crc), sizeof(crc));      // copy crc
    crc_calc = crc16_ccitt(0,data_crc,(size_t) len - sizeof(crc)); // Calculate CRC
    //printk("Received CRC: %u\n",crc);
    //printk("Calculated CRC: %u\n",crc_calc);
    if (crc == 0 && crc_calc == 0)
    {
        printk("Zero Data Received\n");
        return 0;
    }
    if (crc != crc_calc)
    {
        printk("LoRa receive CRC Check failed\n");
        return 0;
    } 
    memcpy(data, data_crc, (size_t) len - sizeof(crc));      // copy data    

    printk("Received data: %s (RSSI:%ddBm, SNR:%ddBm)\n",
           log_strdup(data), rssi, snr);
    return len;
}

/* -------------------- USB CDC ACM -------------------------- */
/* Requires the following overlay: */
/*
 / {
	chosen {
		zephyr,console = &cdc_acm_uart0;
	};
};

&usb0 {
	cdc_acm_uart0: cdc_acm_uart0 {
		compatible = "zephyr,cdc-acm-uart";
		label = "CDC_ACM_0";
	};
}
*/
/* Requires the following Konfig: */
/*
CONFIG_SERIAL=y
CONFIG_CONSOLE=y
CONFIG_UART_CONSOLE=y
CONFIG_STDOUT_CONSOLE=y
CONFIG_USB_DEVICE_STACK=y
CONFIG_USB_DEVICE_PRODUCT="Gateway"
*/
#include <zephyr.h>
#include <usb/usb_device.h>
/* Enables Console Output over USB CDC ACM */
void szl_init_usb_cdc_acm(){
	usb_enable(NULL);
	return;
}

/* ---------------------------- Bluetooth Mesh ------------------------------- */

#include <drivers/hwinfo.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/mesh.h>
#include <bluetooth/mesh/models.h>
#include <bluetooth/mesh/model_types.h>


/* Provisioning */
static int output_number(bt_mesh_output_action_t action, uint32_t number)
{
  printk("OOB Number: %u\n", number);
  return 0;
}

static void prov_complete(uint16_t net_idx, uint16_t addr)
{
  printk("Prov complete! Addr: 0x%04x\n", addr);
}

static void prov_reset(void)
{
  printk("Prov reset!\n");
  bt_mesh_prov_enable(BT_MESH_PROV_ADV | BT_MESH_PROV_GATT);
}

static uint8_t dev_uuid[16];

static const struct bt_mesh_prov prov = {
    .uuid = dev_uuid,
    .output_size = 4,
    .output_actions = BT_MESH_DISPLAY_NUMBER,
    .output_number = output_number,
    .complete = prov_complete,
    .reset = prov_reset,
};

/* Sensor Definition definition */

static int rc;

static int get_sensor_data(struct bt_mesh_sensor *sensor,
					struct bt_mesh_msg_ctx *ctx, struct sensor_value *rsp);

static struct bt_mesh_sensor current_L1 = {
	.type = &bt_mesh_sensor_present_input_current,
	.get = get_sensor_data,
};

static struct bt_mesh_sensor current_L2 = {
	.type = &bt_mesh_sensor_present_input_current,
	.get = get_sensor_data,
};

static struct bt_mesh_sensor current_L3 = {
	.type = &bt_mesh_sensor_present_input_current,
	.get = get_sensor_data,
};

static struct bt_mesh_sensor power = {
	.type = &bt_mesh_sensor_present_dev_input_power,
	.get = get_sensor_data,
};

static struct bt_mesh_sensor Energie_Tarif_1 = {
	.type = &bt_mesh_sensor_tot_dev_energy_use,
	.get = get_sensor_data,
};

static struct bt_mesh_sensor Energie_Tarif_2 = {
	.type = &bt_mesh_sensor_tot_dev_energy_use,
	.get = get_sensor_data,
};

static int get_sensor_data(struct bt_mesh_sensor *sensor,
					struct bt_mesh_msg_ctx *ctx, struct sensor_value *rsp)
{
  if (sensor == &current_L1)
  {
    rsp->val1 = (int)(Smart_Meter_data.Strom_L1/1000);
    rsp->val2 = (int)((Smart_Meter_data.Strom_L1 - (rsp->val1*1000))*1000);
    printk("val_1: %d\n",rsp->val1);
    printk("val_2: %d\n",rsp->val2);
  } else if (sensor == &current_L2)
  {
    rsp->val1 = (int)(Smart_Meter_data.Strom_L2/1000);
    rsp->val2 = (int)((Smart_Meter_data.Strom_L2 - (rsp->val1*1000))*1000);
  } else if (sensor == &current_L3)
  {
    rsp->val1 = (int)(Smart_Meter_data.Strom_L3/1000);
    rsp->val2 = (int)((Smart_Meter_data.Strom_L3 - (rsp->val1*1000))*1000);
  } else if (sensor == &power)
  {
    rsp->val1 = (int)(Smart_Meter_data.Wirkleistungsbezug);
    rsp->val2 = 0;
    printk("val_1: %d\n",rsp->val1);
    printk("val_2: %d\n",rsp->val2);
  } else if (sensor == &Energie_Tarif_1)
  {
    rsp->val1 = (int)(Smart_Meter_data.Wirkenergiebezug_Tarif_1/1000);
    rsp->val2 = (int)((Smart_Meter_data.Wirkenergiebezug_Tarif_1 - (rsp->val1*1000))*1000);
    printk("val_1: %d\n",rsp->val1);
    printk("val_2: %d\n",rsp->val2);
  } else if (sensor == &Energie_Tarif_2)
  {
    rsp->val1 = (int)(Smart_Meter_data.Wirkenergiebezug_Tarif_2/1000);
    rsp->val2 = (int)((Smart_Meter_data.Wirkenergiebezug_Tarif_2 - (rsp->val1*1000))*1000);
  }  
  rc = 0;
	return rc;
}

static struct bt_mesh_sensor *const sensors[] = {
	&current_L1,&power,&Energie_Tarif_1};
  static struct bt_mesh_sensor *const sensors_1[] = {
	&current_L2,&Energie_Tarif_2};
  static struct bt_mesh_sensor *const sensors_2[] = {
	&current_L3};

static struct bt_mesh_sensor_srv sensor_srv = BT_MESH_SENSOR_SRV_INIT(sensors, ARRAY_SIZE(sensors));
static struct bt_mesh_sensor_srv sensor_srv_1 = BT_MESH_SENSOR_SRV_INIT(sensors_1, ARRAY_SIZE(sensors_1));
static struct bt_mesh_sensor_srv sensor_srv_2 = BT_MESH_SENSOR_SRV_INIT(sensors_2, ARRAY_SIZE(sensors_2));


/* Health Server definition */

static void attention_on(struct bt_mesh_model *model)
{
  printk("attention_on!\n");
}
static void attention_off(struct bt_mesh_model *model)
{
  printk("attention_off!\n");
}
static const struct bt_mesh_health_srv_cb health_srv_cb = {
    .attn_on = attention_on,
    .attn_off = attention_off,
};
static struct bt_mesh_health_srv health_srv = {
    .cb = &health_srv_cb,
};
BT_MESH_HEALTH_PUB_DEFINE(health_pub, 0);

/* Define all Elements */
static struct bt_mesh_elem elements[] = {
    BT_MESH_ELEM(1, BT_MESH_MODEL_LIST(BT_MESH_MODEL_CFG_SRV, BT_MESH_MODEL_HEALTH_SRV(&health_srv, &health_pub), BT_MESH_MODEL_SENSOR_SRV(&sensor_srv)),BT_MESH_MODEL_NONE),
    BT_MESH_ELEM(1, BT_MESH_MODEL_LIST(BT_MESH_MODEL_SENSOR_SRV(&sensor_srv_1)),BT_MESH_MODEL_NONE),
    BT_MESH_ELEM(1, BT_MESH_MODEL_LIST(BT_MESH_MODEL_SENSOR_SRV(&sensor_srv_2)),BT_MESH_MODEL_NONE),
};

/* Create Composition */
static const struct bt_mesh_comp comp = {
    .cid = CONFIG_BT_COMPANY_ID,
    .elem = elements,
    .elem_count = ARRAY_SIZE(elements),
};

/* Bluetooth */
static void bt_ready(int err)
{
  if (err)
  {
    printk("Bluetooth init failed (err %d)\n", err);
    return;
  }

  printk("Bluetooth initialized\n");

  err = bt_mesh_init(&prov, &comp);
  if (err)
  {
    printk("Initializing mesh failed (err %d)\n", err);
    return;
  }

  if (IS_ENABLED(CONFIG_SETTINGS))
  {
    settings_load();
  }

  /* --------------- Reset Mesh ------------*/
	if(gpio_pin_get_dt(&button)){
		printk("Reset Mesh!\n");
		bt_mesh_reset();
	}

  /* This will be a no-op if settings_load() loaded provisioning info */
  bt_mesh_prov_enable(BT_MESH_PROV_ADV | BT_MESH_PROV_GATT);

  printk("Mesh initialized\n");
}

//Init Bluetooth Mesh
static void bluetooth_mesh_init()
{
  static int err;
  if (IS_ENABLED(CONFIG_HWINFO)) {
		err = hwinfo_get_device_id(dev_uuid, sizeof(dev_uuid));
	}
	if (err < 0) {
		dev_uuid[0] = 0xdd;
		dev_uuid[1] = 0xdd;
	}
  //Init Bluetooth
	bt_enable(bt_ready);
}


/* ------------------- Main App ---------------------------- */

void main(void)
{
  //Init Reset Button
  init_reset_button();
  //Init USB CDC ACM
  szl_init_usb_cdc_acm();
  k_msleep(1000); //Sleep for syncing buffers
  // Start Application
  printk("Starting Application...\n");
  //Init LoRa
  szl_lora_init();
  bluetooth_mesh_init();
  while (1)
  {
    static uint8_t buffer[255];
    static uint8_t buf_size;
    // Wait for the Receive LoRa
    buf_size = szl_lora_recv(buffer);
    if (buf_size == 0){
      printk("No Valid Data Received\n");
      continue;
    }
    //Decode Message 
    sponge_decode(buffer); 
    //printk("Message Decoded Size: %u\n",pos); 
    printk("Wirkenergiebezug_Tarif_1: %u\n",Smart_Meter_data.Wirkenergiebezug_Tarif_1); 
    printk("Wirkenergiebezug_Tarif_2: %u\n",Smart_Meter_data.Wirkenergiebezug_Tarif_2); 
    printk("Wirkleistungsbezug      : %u\n",Smart_Meter_data.Wirkleistungsbezug); 
    printk("Strom_L1                : %u\n",Smart_Meter_data.Strom_L1); 
    printk("Strom_L2                : %u\n",Smart_Meter_data.Strom_L2); 
    printk("Strom_L3                : %u\n",Smart_Meter_data.Strom_L3);
  }  
}