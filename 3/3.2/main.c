#include <stdlib.h>
#include <time.h>
#include "network.h"
#include "ui.h"

#define EXPECTED_ARGUMENT_COUNT 4

static int parse_packet_count(const char text[], long *packet_count) {
    char *end;
    long value = strtol(text, &end, 10);

    if (end == text || *end != '\0' || value <= 0) {
        return 0;
    }

    *packet_count = value;

    return 1;
}

int main(int argc, char *argv[]) {
    uint32_t gateway;
    uint32_t mask;
    long packet_count;

    if (argc != EXPECTED_ARGUMENT_COUNT) {
        show_usage(argv[0]);
        return 1;
    }

    if (!parse_ipv4(argv[1], &gateway)) {
        show_error("Некорректный адрес шлюза.");
        return 1;
    }

    if (!parse_subnet_mask(argv[2], &mask)) {
        show_error("Некорректная маска подсети.");
        return 1;
    }

    if (!parse_packet_count(argv[3], &packet_count)) {
        show_error("Некорректное количество пакетов.");
        return 1;
    }

    srand((unsigned int)time(NULL));

    long local_packets = 0;
    long external_packets = 0;

    for (long i = 0; i < packet_count; i++) {
        uint32_t destination = generate_random_ipv4();

        int belongs_to_subnet = is_same_subnet(gateway, destination, mask);

        show_packet(destination, belongs_to_subnet);

        if (belongs_to_subnet) {
            local_packets++;
        } else {
            external_packets++;
        }
    }

    show_statistics(local_packets, external_packets);

    return 0;
}
