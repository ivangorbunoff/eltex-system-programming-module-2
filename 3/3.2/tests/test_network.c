#include "unity.h"
#include "network.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_parse_ipv4_should_parse_valid_address(void) {
    uint32_t address = 0;

    int result = parse_ipv4("192.168.1.1", &address);

    TEST_ASSERT_TRUE(result);
    TEST_ASSERT_EQUAL_HEX32(0xC0A80101, address);
}

void test_parse_ipv4_should_reject_large_octet(void) {
    uint32_t address = 0x12345678;

    int result = parse_ipv4("192.256.1.1", &address);

    TEST_ASSERT_FALSE(result);
    TEST_ASSERT_EQUAL_HEX32(0x12345678, address);
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_parse_ipv4_should_parse_valid_address);
    RUN_TEST(test_parse_ipv4_should_reject_large_octet);
    
    return UNITY_END();
}