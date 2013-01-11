
#ifndef __AP_HAL_VRBRAIN_UARTDRIVER_H__
#define __AP_HAL_VRBRAIN_UARTDRIVER_H__

#include <AP_HAL_VRBRAIN.h>
#include <hwf4/usart.h>

class VRBRAIN::VRBRAINUARTDriver : public AP_HAL::UARTDriver
{
public:
  VRBRAINUARTDriver(struct usart *dev);

  /* VRBRAIN implementations of UARTDriver virtual methods */
  void begin(uint32_t b);
  void begin(uint32_t b, uint16_t rxS, uint16_t txS);
  void end();
  void flush();
  bool is_initialized();
  void set_blocking_writes(bool blocking);
  bool tx_pending();

  /* VRBRAIN implementations of BetterStream virtual methods */
  void print_P(const prog_char_t *pstr);
  void println_P(const prog_char_t *pstr);
  void printf(const char *pstr, ...);
  void _printf_P(const prog_char *pstr, ...);

  void vprintf(const char* fmt, va_list ap);
  void vprintf_P(const prog_char* fmt, va_list ap);

  /* VRBRAIN implementations of Stream virtual methods */
  int16_t available();
  int16_t txspace();
  int16_t read();
  int16_t peek();

  /* VRBRAIN implementations of Print virtual methods */
  size_t write(uint8_t c);

private:
  struct usart *m_dev;
  bool m_initialized;
  bool m_blocking;
};

#endif // __AP_HAL_VRBRAIN_UARTDRIVER_H__