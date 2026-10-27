#include <stdio.h>
#include <stdlib.h>
#include "network.h"

int parse_ipv4(const char text[], uint32_t *address) {
    unsigned int b1, b2, b3, b4;
    char extra;

    if (sscanf(text, "%u.%u.%u.%u%c", &b1, &b2, &b3, &b4, &extra) != 4) {
        return 0;
    }

    if (b1 > 255 || b2 > 255 || b3 > 255 || b4 > 255) {
        return 0;
    }

    *address = ((uint32_t)b1 << 24)
        | ((uint32_t)b2 << 16)
        | ((uint32_t)b3 << 8)
        | (uint32_t)b4;

    return 1;
}

void ipv4_to_string(uint32_t address, char output[IPV4_STRING_SIZE]) {
    unsigned int b1 = (address >> 24) & 255;
    unsigned int b2 = (address >> 16) & 255;
    unsigned int b3 = (address >> 8) & 255;
    unsigned int b4 = address & 255;

    snprintf(output, IPV4_STRING_SIZE, "%u.%u.%u.%u", b1, b2, b3, b4);
}

static int is_valid_subnet_mask(uint32_t mask) {
    int zero_found = 0;

    for (int bit = IPV4_BIT_COUNT - 1; bit >= 0; bit--) {
        int current_bit = (mask >> bit) & 1;

        if (current_bit == 0) {
            zero_found = 1;
        } else if (zero_found) {
            return 0;
        }
    }

    return 1;
}

int parse_subnet_mask(const char text[], uint32_t *mask) {
    if (text[0] != '/') {
        uint32_t parsed_mask;

        if (!parse_ipv4(text, &parsed_mask)) {
            return 0;
        }

        if (!is_valid_subnet_mask(parsed_mask)) {
            return 0;
        }

        *mask = parsed_mask;

        return 1;
    }

    char *end;
    long prefix = strtol(text + 1, &end, 10);

    if (end == text + 1 || *end != '\0' || prefix < 0 || prefix > IPV4_BIT_COUNT) {
        return 0;
    }

    *mask = (prefix == 0) ? 0 : (UINT32_MAX << (IPV4_BIT_COUNT - prefix));

    return 1;
}

int is_same_subnet(uint32_t gateway, uint32_t destination, uint32_t mask) {
    return (gateway & mask) == (destination & mask);
}

uint32_t generate_random_ipv4(void) {
    uint32_t b1 = (uint32_t)(rand() % 256);
    uint32_t b2 = (uint32_t)(rand() % 256);
    uint32_t b3 = (uint32_t)(rand() % 256);
    uint32_t b4 = (uint32_t)(rand() % 256);

    return (b1 << 24) | (b2 << 16) | (b3 << 8) | b4;
}