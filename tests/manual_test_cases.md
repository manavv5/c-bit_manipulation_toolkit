# Manual Test Cases

Run `bit_toolkit.exe`, choose option `9` to load the starting value, and then try the operation in the table.

| Purpose | Starting value | Operation | Expected result |
|---|---:|---|---|
| Set a clear bit | `0x00000000` | Set bit 0 | `0x00000001` |
| Set most-significant bit | `0x00000000` | Set bit 31 | `0x80000000` |
| Clear a bit | `0x000000FF` | Clear bit 3 | `0x000000F7` |
| Toggle a bit on | `0x00000000` | Toggle bit 5 | `0x00000020` |
| Read a set bit | `0x00000008` | Read bit 3 | `1` |
| Read a clear bit | `0x00000008` | Read bit 2 | `0` |
| Read a field | `0x0000ABCD` | LSB 4, width 4 | `0x0000000C` |
| Write a field | `0xFFFF00FF` | LSB 8, width 8, value `0x12` | `0xFFFF12FF` |
| Count set bits | `0x00000F0F` | Count | `8` |
| Reject bad input | any | Bit position 32 / width 0 / field value too wide | Error message; register remains unchanged |

The automated tests in `test_bit_toolkit.c` cover these operations plus invalid arguments.
