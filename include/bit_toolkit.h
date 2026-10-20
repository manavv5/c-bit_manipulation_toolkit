#ifndef REGTOOL_H
#define REGTOOL_H

#include <stdbool.h>
#include <stdint.h>

/* A 32-bit register is modelled as a uint32_t value. These functions do not
 * access physical hardware; they provide safe operations for register-like
 * values in embedded software and simulations.
 */

bool reg_set_bit(uint32_t value, unsigned bit, uint32_t *result);
bool reg_clear_bit(uint32_t value, unsigned bit, uint32_t *result);
bool reg_toggle_bit(uint32_t value, unsigned bit, uint32_t *result);
bool reg_read_bit(uint32_t value, unsigned bit, bool *result);

/* Field positions are zero-based. Width must be 1..32 and the field must fit
 * entirely inside the 32-bit value. write_field rejects values that do not
 * fit within the requested field width.
 */
bool reg_read_field(uint32_t value, unsigned lsb, unsigned width,
                    uint32_t *result);
bool reg_write_field(uint32_t value, unsigned lsb, unsigned width,
                     uint32_t field_value, uint32_t *result);

unsigned reg_count_set_bits(uint32_t value);
void reg_print_binary(uint32_t value);

#endif
