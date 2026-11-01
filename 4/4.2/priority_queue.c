#include <stdlib.h>
#include <string.h>

#include "priority_queue.h"


int queue_push(PriorityQueue* queue, const char text[], int priority) {
    if (queue == NULL || text == NULL || priority < 0 || priority > 255) {
        return 0;
    }

    if (text[0] == '\0' || strlen(text) >= MAX_MESSAGE_LENGTH) {
        return 0;
    }

    MessageNode* new_node = malloc(sizeof(MessageNode));

    if (new_node == NULL) {
        return 0;
    }

    new_node->message.priority = (uint8_t) priority;
    strcpy(new_node->message.text, text);
    new_node->next = NULL;

    if (queue->head == NULL || priority < queue->head->message.priority) {
        new_node->next = queue->head;
        queue->head = new_node;
        queue->count++;

        return 1;
    }

    MessageNode* current = queue->head;

    while (current->next != NULL && current->next->message.priority <= priority) {
        current = current->next;
    }

    new_node->next = current->next;
    current->next = new_node;
    queue->count++;

    return 1;
}

int queue_pop_first(PriorityQueue* queue, Message* message) {
    if (queue == NULL || message == NULL || queue->head == NULL) {
        return 0;
    }

    MessageNode* removed_node = queue->head;

    *message = removed_node->message;
    queue->head = removed_node->next;

    free(removed_node);
    queue->count--;

    return 1;
}

int queue_pop_priority(PriorityQueue* queue, int priority, Message* message) {
    if (queue == NULL || message == NULL || priority < 0 || priority > 255) {
        return 0;
    }

    MessageNode* current = queue->head;
    MessageNode* prev = NULL;

    while (current != NULL && current->message.priority < priority) {
        prev = current;
        current = current->next;
    }

    if (current == NULL || current->message.priority != priority) {
        return 0;
    }

    *message = current->message;

    if (prev == NULL) {
        queue->head = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
    queue->count--;

    return 1;
}

int queue_pop_not_lower(PriorityQueue* queue, int priority, Message* message) {
    if (queue == NULL || message == NULL || priority < 0 || priority > 255) {
        return 0;
    }

    MessageNode* current = queue->head;
    MessageNode* prev = NULL;

    while (current != NULL && current->message.priority < priority) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        return 0;
    }

    *message = current->message;

    if (prev == NULL) {
        queue->head = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
    queue->count--;

    return 1;
}

void queue_clear(PriorityQueue* queue) {
    if (queue == NULL) {
        return;
    }

    MessageNode* current = queue->head;

    while (current != NULL) {
        MessageNode* next = current->next;
        free(current);
        current = next;
    }

    queue->head = NULL;
    queue->count = 0;
}