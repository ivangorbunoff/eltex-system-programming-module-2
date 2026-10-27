#ifndef NETWORK_H
#define NETWORK_H

#include <stdint.h>

#define IPV4_STRING_SIZE 16
#define IPV4_BIT_COUNT 32

int parse_ipv4(const char text[], uint32_t *address);

void ipv4_to_string(uint32_t address, char output[IPV4_STRING_SIZE]);

int parse_subnet_mask(const char text[], uint32_t *mask);

int is_same_subnet(uint32_t gateway, uint32_t destination, uint32_t mask);

uint32_t generate_random_ipv4(void);

#endif
