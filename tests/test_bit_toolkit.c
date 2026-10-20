#include "bit_toolkit.h"

#include <inttypes.h>
#include <stdio.h>

static unsigned tests_run;
static unsigned tests_failed;

#define CHECK(name, condition) do { \
    ++tests_run; \
    if (condition) { \
        printf("[PASS] %s\n", name); \
    } else { \
        printf("[FAIL] %s\n", name); \
        ++tests_failed; \
    } \
} while (0)

int main(void)
{
    uint32_t result = 0U;
    bool bit = false;

    CHECK("set bit 0", reg_set_bit(0U, 0U, &result) && result == 1U);
    CHECK("set bit 31", reg_set_bit(0U, 31U, &result) && result == UINT32_C(0x80000000));
    CHECK("reject bit 32", !reg_set_bit(0U, 32U, &result));
    CHECK("clear bit", reg_clear_bit(UINT32_C(0xFF), 3U, &result) && result == UINT32_C(0xF7));
    CHECK("toggle bit on", reg_toggle_bit(0U, 5U, &result) && result == UINT32_C(0x20));
    CHECK("toggle bit off", reg_toggle_bit(UINT32_C(0x20), 5U, &result) && result == 0U);
    CHECK("read set bit", reg_read_bit(UINT32_C(0x8), 3U, &bit) && bit);
    CHECK("read clear bit", reg_read_bit(UINT32_C(0x8), 2U, &bit) && !bit);
    CHECK("read field", reg_read_field(UINT32_C(0xABCD), 4U, 4U, &result) && result == 0xCU);
    CHECK("write field preserves unrelated bits",
          reg_write_field(UINT32_C(0xFFFF00FF), 8U, 8U, 0x12U, &result) &&
          result == UINT32_C(0xFFFF12FF));
    CHECK("write full-width field", reg_write_field(0U, 0U, 32U, UINT32_MAX, &result) && result == UINT32_MAX);
    CHECK("reject field crossing bit 31", !reg_read_field(0U, 31U, 2U, &result));
    CHECK("reject value too wide for field", !reg_write_field(0U, 4U, 4U, 0x10U, &result));
    CHECK("reject zero-width field", !reg_read_field(0U, 0U, 0U, &result));
    CHECK("count bits in zero", reg_count_set_bits(0U) == 0U);
    CHECK("count bits in 0xF0F", reg_count_set_bits(UINT32_C(0xF0F)) == 8U);
    CHECK("count bits in all-ones value", reg_count_set_bits(UINT32_MAX) == 32U);
    CHECK("reject null output pointer", !reg_set_bit(0U, 0U, NULL));

    printf("\n%u tests run, %u failed.\n", tests_run, tests_failed);
    return tests_failed == 0U ? 0 : 1;
}
