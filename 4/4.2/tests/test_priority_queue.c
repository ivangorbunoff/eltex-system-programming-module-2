#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "unity.h"
#include "priority_queue.h"

#define GENERATED_MESSAGE_COUNT 15

static PriorityQueue queue;

static const char* get_traffic_type(int priority) {
    if (priority <= 31) {
        return "VoIP-пакет";
    }

    if (priority <= 95) {
        return "Загрузка видео";
    }

    if (priority <= 159) {
        return "Загрузка аудио";
    }

    return "Передача текста";
}

static void run_generated_messages_demo(void) {
    PriorityQueue demo_queue = {0};
    char text[MAX_MESSAGE_LENGTH];

    srand((unsigned int) time(NULL));

    printf("\nСгенерированные сообщения:\n\n");

    for (int i = 0; i < GENERATED_MESSAGE_COUNT; i++) {
        int priority = rand() % 256;

        snprintf(text, sizeof(text), "%s #%d", get_traffic_type(priority), i + 1);
        printf("%2d. [%3d] %s\n", i + 1, priority, text);

        if (!queue_push(&demo_queue, text, priority)) {
            printf("Не удалось добавить сообщение.\n");
            queue_clear(&demo_queue);
            return;
        }
    }

    printf("\nОчередь обработки:\n\n");

    const MessageNode* current = demo_queue.head;
    int position = 1;

    while (current != NULL) {
        printf("%2d. [%3d] %s\n", position, (int) current->message.priority, current->message.text);

        current = current->next;
        position++;
    }

    Message extracted;

    printf("\nPOP FIRST:\n");

    if (queue_pop_first(&demo_queue, &extracted)) {
        printf("Извлечено: [%3d] %s\n", (int) extracted.priority, extracted.text);
        printf("Осталось сообщений: %d\n", demo_queue.count);
    } else {
        printf("Очередь пуста.\n");
    }

    printf("\nPOP NOT LOWER 70:\n");

    if (queue_pop_not_lower(&demo_queue, 70, &extracted)) {
        printf("Извлечено: [%3d] %s\n", (int) extracted.priority, extracted.text);
        printf("Осталось сообщений: %d\n", demo_queue.count);
    } else {
        printf("Подходящее сообщение не найдено.\n");
    }

    current = demo_queue.head;
    int middle_index = demo_queue.count / 2;

    for (int i = 0; i < middle_index && current != NULL; i++) {
        current = current->next;
    }

    if (current != NULL) {
        int exact_priority = current->message.priority;

        printf("\nPOP PRIORITY %d:\n", exact_priority);

        if (queue_pop_priority(&demo_queue, exact_priority, &extracted)) {
            printf("Извлечено: [%3d] %s\n", (int) extracted.priority, extracted.text);
            printf("Осталось сообщений: %d\n", demo_queue.count);
        }
    }

    printf("\nОчередь после трёх операций POP:\n\n");

    current = demo_queue.head;
    position = 1;

    while (current != NULL) {
        printf("%2d. [%3d] %s\n", position, (int) current->message.priority, current->message.text);

        current = current->next;
        position++;
    }

    queue_clear(&demo_queue);
    printf("\n");
}

void setUp(void) {
    queue.head = NULL;
    queue.count = 0;
}

void tearDown(void) {
    queue_clear(&queue);
}

void test_queue_push_should_sort_messages_by_priority(void) {
    TEST_ASSERT_TRUE(queue_push(&queue, "Загрузка аудио", 120));
    TEST_ASSERT_TRUE(queue_push(&queue, "VoIP-пакет", 10));
    TEST_ASSERT_TRUE(queue_push(&queue, "Загрузка видео", 50));

    TEST_ASSERT_EQUAL_INT(3, queue.count);

    MessageNode* current = queue.head;

    TEST_ASSERT_NOT_NULL(current);
    TEST_ASSERT_EQUAL_UINT8(10, current->message.priority);
    TEST_ASSERT_EQUAL_STRING("VoIP-пакет", current->message.text);

    current = current->next;

    TEST_ASSERT_NOT_NULL(current);
    TEST_ASSERT_EQUAL_UINT8(50, current->message.priority);
    TEST_ASSERT_EQUAL_STRING("Загрузка видео", current->message.text);

    current = current->next;

    TEST_ASSERT_NOT_NULL(current);
    TEST_ASSERT_EQUAL_UINT8(120, current->message.priority);
    TEST_ASSERT_EQUAL_STRING("Загрузка аудио", current->message.text);

    current = current->next;

    TEST_ASSERT_NULL(current);
}

void test_queue_pop_first_should_remove_first_message(void) {
    queue_push(&queue, "Загрузка аудио", 120);
    queue_push(&queue, "VoIP-пакет", 10);
    queue_push(&queue, "Загрузка видео", 50);

    Message message;

    TEST_ASSERT_TRUE(queue_pop_first(&queue, &message));
    TEST_ASSERT_EQUAL_UINT8(10, message.priority);
    TEST_ASSERT_EQUAL_STRING("VoIP-пакет", message.text);
    TEST_ASSERT_EQUAL_INT(2, queue.count);
    TEST_ASSERT_EQUAL_UINT8(50, queue.head->message.priority);
}

void test_queue_pop_priority_should_remove_requested_priority(void) {
    queue_push(&queue, "Загрузка аудио", 120);
    queue_push(&queue, "VoIP-пакет", 10);
    queue_push(&queue, "Загрузка видео", 50);

    Message message;

    TEST_ASSERT_TRUE(queue_pop_priority(&queue, 50, &message));
    TEST_ASSERT_EQUAL_UINT8(50, message.priority);
    TEST_ASSERT_EQUAL_STRING("Загрузка видео", message.text);
    TEST_ASSERT_EQUAL_INT(2, queue.count);

    TEST_ASSERT_EQUAL_UINT8(10, queue.head->message.priority);
    TEST_ASSERT_EQUAL_UINT8(120, queue.head->next->message.priority);
}

void test_queue_pop_not_lower_should_remove_next_numeric_priority(void) {
    queue_push(&queue, "Загрузка аудио", 30);
    queue_push(&queue, "VoIP-пакет", 10);
    queue_push(&queue, "Загрузка видео", 16);

    Message message;

    TEST_ASSERT_TRUE(queue_pop_not_lower(&queue, 15, &message));
    TEST_ASSERT_EQUAL_UINT8(16, message.priority);
    TEST_ASSERT_EQUAL_STRING("Загрузка видео", message.text);
    TEST_ASSERT_EQUAL_INT(2, queue.count);

    TEST_ASSERT_EQUAL_UINT8(10, queue.head->message.priority);
    TEST_ASSERT_EQUAL_UINT8(30, queue.head->next->message.priority);
}

int main(void) {
    run_generated_messages_demo();

    UNITY_BEGIN();

    RUN_TEST(test_queue_push_should_sort_messages_by_priority);
    RUN_TEST(test_queue_pop_first_should_remove_first_message);
    RUN_TEST(test_queue_pop_priority_should_remove_requested_priority);
    RUN_TEST(test_queue_pop_not_lower_should_remove_next_numeric_priority);

    return UNITY_END();
}