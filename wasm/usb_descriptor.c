#include <stdint.h>

/* JS writes raw bytes here; the output is read back as uint16_t values. */
static uint8_t g_buf[64];
static uint16_t g_out[14];

__attribute__((export_name("usb_buf_ptr")))
uint32_t usb_buf_ptr(void) {
  return (uint32_t)(uintptr_t)g_buf;
}

__attribute__((export_name("usb_out_ptr")))
uint32_t usb_out_ptr(void) {
  return (uint32_t)(uintptr_t)g_out;
}

static uint16_t le16(const uint8_t *p) {
  return (uint16_t)(p[0] | ((uint16_t)p[1] << 8));
}

static uint16_t be16(const uint8_t *p) {
  return (uint16_t)(((uint16_t)p[0] << 8) | p[1]);
}

static int32_t parse_device_descriptor(uint32_t len, uint8_t big_endian) {
  if (len < 18) {
    return -1;
  }
  if (g_buf[0] != 18) {
    return -2;
  }
  if (g_buf[1] != 0x01) {
    return -3;
  }

  g_out[0] = g_buf[0];
  g_out[1] = g_buf[1];
  g_out[2] = big_endian ? be16(&g_buf[2]) : le16(&g_buf[2]);
  g_out[3] = g_buf[4];
  g_out[4] = g_buf[5];
  g_out[5] = g_buf[6];
  g_out[6] = g_buf[7];
  g_out[7] = big_endian ? be16(&g_buf[8]) : le16(&g_buf[8]);
  g_out[8] = big_endian ? be16(&g_buf[10]) : le16(&g_buf[10]);
  g_out[9] = big_endian ? be16(&g_buf[12]) : le16(&g_buf[12]);
  g_out[10] = g_buf[14];
  g_out[11] = g_buf[15];
  g_out[12] = g_buf[16];
  g_out[13] = g_buf[17];

  return 18;
}

__attribute__((export_name("usb_parse_device_descriptor")))
int32_t usb_parse_device_descriptor(uint32_t len) {
  return parse_device_descriptor(len, 0);
}

__attribute__((export_name("usb_parse_as_big_endian")))
int32_t usb_parse_as_big_endian(uint32_t len) {
  return parse_device_descriptor(len, 1);
}
