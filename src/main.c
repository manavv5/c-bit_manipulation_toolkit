#include "bit_toolkit.h"

#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_BUFFER_SIZE 128

static bool read_number(const char *prompt, uint32_t max_value,
                        uint32_t *result)
{
    char input[INPUT_BUFFER_SIZE];

    for (;;) {
        char *end = NULL;
        unsigned long parsed;

        printf("%s", prompt);
        if (fgets(input, sizeof input, stdin) == NULL) {
            return false;
        }

        errno = 0;
        parsed = strtoul(input, &end, 0);

        if (input == end || errno == ERANGE || parsed > (unsigned long)max_value) {
            printf("Invalid input. Enter a number from 0 to %" PRIu32
                   " (decimal or 0x-prefixed hex).\n", max_value);
            continue;
        }

        while (*end != '\0' && isspace((unsigned char)*end)) {
            ++end;
        }

        if (*end != '\0') {
            puts("Invalid input. Do not add extra characters.");
            continue;
        }

        *result = (uint32_t)parsed;
        return true;
    }
}

static void show_register(uint32_t value)
{
    printf("\nRegister value: 0x%08" PRIX32 " (%" PRIu32 ")\n", value, value);
    printf("Binary:         ");
    reg_print_binary(value);
    putchar('\n');
}

static void show_menu(void)
{
    puts("\n=== C Bit Manipulation Toolkit ===");
    puts("1. Display register");
    puts("2. Set bit");
    puts("3. Clear bit");
    puts("4. Toggle bit");
    puts("5. Read bit");
    puts("6. Read bit field");
    puts("7. Write bit field");
    puts("8. Count set bits");
    puts("9. Load register value");
    puts("0. Exit");
}

static bool read_bit_position(unsigned *bit)
{
    uint32_t input;
    if (!read_number("Bit position (0-31): ", 31U, &input)) {
        return false;
    }
    *bit = (unsigned)input;
    return true;
}

static bool read_field_position(unsigned *lsb, unsigned *width)
{
    uint32_t input;

    if (!read_number("Field start bit / LSB (0-31): ", 31U, &input)) {
        return false;
    }
    *lsb = (unsigned)input;

    if (!read_number("Field width (1-32): ", 32U, &input)) {
        return false;
    }
    *width = (unsigned)input;
    return true;
}

int main(void)
{
    uint32_t reg = 0U;
    uint32_t choice;

    puts("32-bit register simulator for learning embedded C.");
    puts("This program manipulates a software value; it does not access hardware.");

    for (;;) {
        uint32_t result = 0U;
        uint32_t input;
        unsigned bit;
        unsigned lsb;
        unsigned width;
        bool bit_value;
        bool ok = true;

        show_menu();
        if (!read_number("Choose an option: ", 9U, &choice)) {
            putchar('\n');
            break;
        }

        if (choice == 0U) {
            puts("Goodbye.");
            break;
        }

        switch (choice) {
        case 1U:
            show_register(reg);
            break;
        case 2U:
        case 3U:
        case 4U:
            if (!read_bit_position(&bit)) return 0;
            if (choice == 2U) ok = reg_set_bit(reg, bit, &result);
            if (choice == 3U) ok = reg_clear_bit(reg, bit, &result);
            if (choice == 4U) ok = reg_toggle_bit(reg, bit, &result);
            if (ok) {
                reg = result;
                show_register(reg);
            }
            break;
        case 5U:
            if (!read_bit_position(&bit)) return 0;
            if (reg_read_bit(reg, bit, &bit_value)) {
                printf("Bit %u = %u\n", bit, bit_value ? 1U : 0U);
            }
            break;
        case 6U:
            if (!read_field_position(&lsb, &width)) return 0;
            if (!reg_read_field(reg, lsb, width, &result)) {
                puts("Invalid field: it must fit within bits 0-31.");
            } else {
                printf("Field value: 0x%08" PRIX32 " (%" PRIu32 ")\n",
                       result, result);
            }
            break;
        case 7U:
            if (!read_field_position(&lsb, &width)) return 0;
            if (!read_number("New field value: ", UINT32_MAX, &input)) return 0;
            if (!reg_write_field(reg, lsb, width, input, &result)) {
                puts("Cannot write field: check its position, width, and value range.");
            } else {
                reg = result;
                show_register(reg);
            }
            break;
        case 8U:
            printf("Number of set bits: %u\n", reg_count_set_bits(reg));
            break;
        case 9U:
            if (!read_number("New register value: ", UINT32_MAX, &reg)) return 0;
            show_register(reg);
            break;
        default:
            puts("Unknown option.");
            break;
        }
    }

    return 0;
}
