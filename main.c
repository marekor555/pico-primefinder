#include "stdio.h"

#include "pico/stdio_usb.h"
#include "pico/stdlib.h"

#define ARR_SIZE 32768

#define uint unsigned int

const uint delay = 250;
uint primes[ARR_SIZE] = {2, 3, 5, 7, 11};
uint primes_found = 5;
uint current_num = 11;

int main() {
    stdio_init_all();
    stdio_usb_init();
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while (primes_found < ARR_SIZE) {
        current_num += 2;
        printf("%d\n", current_num);
        bool isPrime = true;
        for (uint i = 0; i < primes_found; i++) {
            if (current_num % primes[i] == 0 && primes[i] != 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) {
            primes[primes_found] = current_num;
			primes_found++;
            printf("prime: %d\n", current_num);
        }
    }
    gpio_put(LED_PIN, 1);
    while (true) {
        printf("Last prime: %d\n", primes[primes_found-1]);
        sleep_ms(1000);
    }
}
