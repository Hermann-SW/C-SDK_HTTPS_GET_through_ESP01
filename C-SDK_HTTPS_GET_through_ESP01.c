#include <stdio.h>
#include "pico/stdlib.h"
#include "tusb.h"

#define TIMEOUT_S 2

void https_get(char *url)
{
    int rd;
    char buf[256];

    printf("%s\n", url); fflush(stdout);
    uart_puts(uart0, url); uart_putc_raw(uart0, '\n');

    while (rd = uart_is_readable_within_us(uart0, TIMEOUT_S*1000000) > 0)
    {
      if (rd>256)  rd=256;
      uart_read_blocking(uart0, buf, rd);
      fwrite(buf, rd, 1, stdout); fflush(stdout);
    }
}

int main()
{
    stdio_init_all();
    stdio_filter_driver(&stdio_usb);
    while (!tud_cdc_connected()) {}

    for(;;)
    {
        https_get("https://stamm-wilbrandt.de/cgi-bin/sol.English.pl?60000");

        https_get("https://stamm-wilbrandt.de/cgi-bin/sol.English.pl?10000");
    }

    return 0;
}
