#include <stdio.h>
#include "pico/stdlib.h"
#include "tusb.h"

void https_get(char *url)
{
    stdio_filter_driver(&stdio_usb);
    printf("%s\n", url); fflush(stdout);
    stdio_filter_driver(&stdio_uart);
    printf("%s\n", url); fflush(stdout);
    while (!feof(stdin))
    {
      char buf[256];
      int rd = fread(buf, 1, 256, stdin);
      stdio_filter_driver(&stdio_usb);
      fputc('@', stdout); // stone age debug
      fwrite(buf, rd, 1, stdout); fflush(stdout);
      stdio_filter_driver(&stdio_uart);
    }
    stdio_filter_driver(&stdio_usb);
    fflush(stdout);
}

int main()
{
    stdio_init_all();
    gpio_pull_up(1);
    while (!tud_cdc_connected()) {}

sleep_ms(3000);

    https_get("https://stamm-wilbrandt.de/cgi-bin/sol.English.pl?60000");

    https_get("https://stamm-wilbrandt.de/cgi-bin/sol.English.pl?10000");

    for(;;){}

    return 0;
}
