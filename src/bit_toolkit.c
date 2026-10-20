#include "bit_toolkit.h"

#include <inttypes.h>
#include <stdio.h>

static bool valid_bit(unsigned bit)
{
    return bit < 32U;
}

static bool valid_field(unsigned lsb, unsigned width)
{
    if (lsb >= 32U || width == 0U || width > 32U) {
        return false;
    }

    return width <= (32U - lsb);
}

static uint32_t field_mask(unsigned width)
{
    if (width == 32U) {
        return UINT32_MAX;
    }

    return (UINT32_C(1) << width) - UINT32_C(1);
}

bool reg_set_bit(uint32_t value, unsigned bit, uint32_t *result)
{
    if (!valid_bit(bit) || result == NULL) {
        return false;
    }

    *result = value | (UINT32_C(1) << bit);
    return true;
}

bool reg_clear_bit(uint32_t value, unsigned bit, uint32_t *result)
{
    if (!valid_bit(bit) || result == NULL) {
        return false;
    }

    *result = value & ~(UINT32_C(1) << bit);
    return true;
}

bool reg_toggle_bit(uint32_t value, unsigned bit, uint32_t *result)
{
    if (!valid_bit(bit) || result == NULL) {
        return false;
    }

    *result = value ^ (UINT32_C(1) << bit);
    return true;
}

bool reg_read_bit(uint32_t value, unsigned bit, bool *result)
{
    if (!valid_bit(bit) || result == NULL) {
        return false;
    }

    *result = ((value >> bit) & UINT32_C(1)) != 0U;
    return true;
}

bool reg_read_field(uint32_t value, unsigned lsb, unsigned width,
                    uint32_t *result)
{
    if (!valid_field(lsb, width) || result == NULL) {
        return false;
    }

    *result = (value >> lsb) & field_mask(width);
    return true;
}

bool reg_write_field(uint32_t value, unsigned lsb, unsigned width,
                     uint32_t field_value, uint32_t *result)
{
    uint32_t mask;

    if (!valid_field(lsb, width) || result == NULL) {
        return false;
    }

    mask = field_mask(width);
    if ((field_value & ~mask) != 0U) {
        return false;
    }

    *result = (value & ~(mask << lsb)) | (field_value << lsb);
    return true;
}

unsigned reg_count_set_bits(uint32_t value)
{
    unsigned count = 0U;

    while (value != 0U) {
        count += (unsigned)(value & UINT32_C(1));
        value >>= 1U;
    }

    return count;
}

void reg_print_binary(uint32_t value)
{
    int bit;

    for (bit = 31; bit >= 0; --bit) {
        putchar(((value >> (unsigned)bit) & UINT32_C(1)) != 0U ? '1' : '0');
        if ((bit % 4) == 0 && bit != 0) {
            putchar(' ');
        }
    }
}
