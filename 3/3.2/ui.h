#ifndef UI_H
#define UI_H

#include <stdint.h>

void show_usage(const char program_name[]);

void show_packet(uint32_t destination, int belongs_to_subnet);

void show_statistics(long local_packets, long external_packets);

void show_error(const char message[]);

#endif
