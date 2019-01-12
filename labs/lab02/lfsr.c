#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void lfsr_calculate(uint16_t *reg) {

  /* YOUR CODE HERE */
  uint16_t b11 = (*reg & (0b1 << 5)) >> 5;
  uint16_t b13 = (*reg & (0b1 << 3)) >> 3;
  uint16_t b14 = (*reg & (0b1 << 2)) >> 2;
  uint16_t b16 = *reg & 0b1;
  uint16_t head_bit = (b11 ^ b13 ^ b14 ^ b16) << 15;
  *reg = (*reg >> 1) | head_bit;
}

int main() {
  int8_t *numbers = (int8_t*) malloc(sizeof(int8_t) * 65535);
  if (numbers == NULL) {
    printf("Memory allocation failed!");
    exit(1);
  }

  memset(numbers, 0, sizeof(int8_t) * 65535);
  uint16_t reg = 0x1;
  uint32_t count = 0;
  int i;

  do {
    count++;
    numbers[reg] = 1;
    if (count < 24) {
      printf("My number is: %u\n", reg);
    } else if (count == 24) {
      printf(" ... etc etc ... \n");
    }
    for (i = 0; i < 32; i++)
      lfsr_calculate(&reg);
  } while (numbers[reg] != 1);

  printf("Got %u numbers before cycling!\n", count);

  if (count == 65535) {
    printf("Congratulations! It works!\n");
  } else {
    printf("Did I miss something?\n");
  }

  free(numbers);

  return 0;
}
