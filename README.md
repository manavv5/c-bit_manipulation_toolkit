# Bit Manipulation Toolkit in C
**A tiny interactive tool for exploring how individual bits work.**
**Created by [Manav Sharma](https://github.com/manavv5)** · ECE undergraduate at IIIT Nagpur
---
## What it does
Bit Manipulation Toolkit is a beginner-friendly, menu-driven C program for experimenting with bitwise operations. Enter a number, choose an operation, and see the result in decimal, hexadecimal, and binary.

### Features

- **Set** a selected bit to `1`.
- **Clear** a selected bit to `0`.
- **Toggle** a selected bit (`0` becomes `1`, and `1` becomes `0`).
- **Check** whether a bit is set or clear.
- Display a number in decimal, hexadecimal, and grouped binary.
- Count the number of set bits (`1`s) in a number.
- Change the working number without restarting the program.
- Validate input and reject negative values and invalid bit positions.
- Detect the width of `unsigned int` at compile time instead of assuming it is always 32 bits.

## Why I built it

I'm an ECE student interested in digital design, FPGA development, embedded systems, and RTL verification. This project is a small way to practise the bitwise operations used when working with hardware registers, masks, and low-level data.

## Run it in VS Code

This is a single-file C project, so it works well with a normal VS Code C setup.

1. Download or clone this repository and open its folder in VS Code.
2. Open `bit_toolkit.c`.
3. Use the **Run Code** button if your C runner is configured to support console input. If it displays output but won't accept typing, run it in VS Code's integrated **Terminal** instead.

With GCC installed, you can compile and run from VS Code's integrated terminal:

**Windows (GCC / MinGW):**

```powershell
gcc -std=c99 -Wall -Wextra -Wpedantic bit_toolkit.c -o bit_toolkit.exe
.\bit_toolkit.exe
```

**Linux / macOS:**

```bash
gcc -std=c99 -Wall -Wextra -Wpedantic bit_toolkit.c -o bit_toolkit
./bit_toolkit
```

> If VS Code reports that `gcc` is not recognized, install/configure a C compiler first. The program itself does not need any third-party C libraries.

## Example session

```text
Bit Manipulation Toolkit (32-bit unsigned int)
Enter an initial non-negative integer: 13

Current value:
Decimal: 13
Hex:     0xD
Binary: 0000 0000 0000 0000 0000 0000 0000 1101

===== BIT MANIPULATION TOOLKIT =====
1. Set a bit
2. Clear a bit
3. Toggle a bit
4. Check a bit
5. Show the current number
6. Change the current number
7. Count set bits (bits equal to 1)
0. Exit
Choose an option: 7
Number of set bits: 3
```

The bit width and binary display depend on the platform. The example above assumes a 32-bit `unsigned int`.

## Bitwise operations used

Let `n` be the current number and `p` a valid bit position. `mask = 1U << p` creates a mask with only bit `p` set.

| Operation | C expression | Effect |
|---|---|---|
| Set | `n |= mask` | Forces bit `p` to `1`. |
| Clear | `n &= ~mask` | Forces bit `p` to `0`. |
| Toggle | `n ^= mask` | Flips bit `p`. |
| Check | `(n >> p) & 1U` | Extracts bit `p` as `0` or `1`. |
| Count | Repeatedly test `n & 1U`, then shift right | Counts how many bits are `1`. |

**Bit positions start at zero**, with position `0` being the rightmost (least-significant) bit. The program only accepts positions from `0` to `bit_width - 1`.

## Test checklist

See [`tests/manual_test_cases.md`](tests/manual_test_cases.md) for example operations and edge cases. A small smoke-test script is also included and runs in GitHub Actions when code is pushed or a pull request is opened.

## What I learned / practised

- Bitwise operators: `|`, `&`, `^`, `~`, and `<<`.
- Bit masks, shifting, and least-significant-bit indexing.
- Unsigned integers and platform-dependent integer width.
- Functions, pointers, loops, and `switch` statements.
- Parsing user input and handling invalid values.
- Testing edge cases rather than relying only on a successful run.

## Possible next improvements

- Add a bit-reversal operation.
- Add signed-integer examples and explain sign extension.
- Add unit tests for the bitwise operations.
- Add a register-field editor to connect this tool to embedded systems concepts.

## License

Released under the [MIT License](LICENSE).

---

<div align="center">

Made for learning low-level programming, one bit at a time.
