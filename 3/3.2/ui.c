#include <stdio.h>
#include "network.h"
#include "ui.h"

void show_usage(const char program_name[]) {
    printf("Использование: %s <шлюз> <маска> <количество пакетов>\n", program_name);
}

void show_packet(uint32_t destination, int belongs_to_subnet) {
    char address[IPV4_STRING_SIZE];

    ipv4_to_string(destination, address);

    printf("%-15s -> %s\n", address, belongs_to_subnet ? "своя сеть" : "другая сеть");
}

void show_statistics(long local_packets, long external_packets) {
    long total = local_packets + external_packets;
    double local_percent = (double)local_packets * 100 / total;
    double external_percent = (double)external_packets * 100 / total;

    printf("\nСтатистика:\n");
    printf("Своя сеть: %ld (%.2f%%)\n", local_packets, local_percent);
    printf("Другие сети: %ld (%.2f%%)\n", external_packets, external_percent);
}

void show_error(const char message[]) {
    fprintf(stderr, "Ошибка: %s\n", message);
}
