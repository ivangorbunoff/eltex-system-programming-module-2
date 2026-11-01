#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stdint.h>

#define MAX_MESSAGE_LENGTH 100

typedef struct {
    uint8_t priority;
    char text[MAX_MESSAGE_LENGTH];
} Message;

typedef struct MessageNode {
    Message message;
    struct MessageNode* next;
} MessageNode;

typedef struct {
    MessageNode* head;
    int count;
} PriorityQueue;

int queue_push(PriorityQueue* queue, const char text[], int priority);

int queue_pop_first(PriorityQueue* queue, Message* message);

int queue_pop_priority(PriorityQueue* queue, int priority, Message* message);

int queue_pop_not_lower(PriorityQueue* queue, int priority, Message* message);

void queue_clear(PriorityQueue* queue);

#endif
