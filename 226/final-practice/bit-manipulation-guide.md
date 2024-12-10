# Bit Manipulation Guide

## Understanding Number Representations

### Decimal, Binary, and Hexadecimal

```python
# Decimal: Base 10 (0-9)
decimal = 255

# Binary: Base 2 (0-1)
binary = 0b11111111     # 255 in decimal
binary = 0b1111_1111    # Underscores for readability

# Hexadecimal: Base 16 (0-9, A-F)
hexadecimal = 0xFF      # 255 in decimal
```

## Common Bit Operations

### Getting Specific Bytes

#### From a 4-byte number (0x12345678):

```python
number = 0x12345678

# First byte (leftmost)
first_byte = (number >> 24) & 0xFF      # Result: 0x12

# Second byte
second_byte = (number >> 16) & 0xFF     # Result: 0x34

# Third byte
third_byte = (number >> 8) & 0xFF       # Result: 0x56

# Last byte (rightmost)
last_byte = number & 0xFF               # Result: 0x78
```

#### From a 2-byte number (0x1234):

```python
number = 0x1234

# First byte
first_byte = (number >> 8) & 0xFF       # Result: 0x12

# Last byte
last_byte = number & 0xFF               # Result: 0x34
```

### Getting Multiple Bytes at Once

```python
number = 0x12345678

# First two bytes
first_two = (number >> 16) & 0xFFFF     # Result: 0x1234

# Last two bytes
last_two = number & 0xFFFF              # Result: 0x5678
```

### Getting Specific Bits

#### Last N bits

```python
number = 0b10101010

# Last 5 bits
last_5 = number & 0b11111              # Result: 0b01010
# OR
last_5 = number & 0x1F                 # Same result using hex

# Last 3 bits
last_3 = number & 0b111                # Result: 0b010
```

#### First N bits

```python
number = 0b10101010

# First 5 bits (from 8-bit number)
first_5 = (number >> 3) & 0b11111      # Result: 0b10101
```

### Bit Shifting

```python
number = 0b10101010

# Left shift (multiply by 2^n)
shifted_left = number << 2              # Result: 0b1010101000

# Right shift (divide by 2^n)
shifted_right = number >> 2             # Result: 0b00101010
```

## Common Bit Masks

```python
# Single byte masks
0xFF        # All 8 bits (11111111)
0x0F        # Last 4 bits (00001111)
0xF0        # First 4 bits (11110000)
0b11111     # Last 5 bits (00011111)
0b111       # Last 3 bits (00000111)

# Two byte masks
0xFFFF      # All 16 bits
0xFF00      # First byte of two bytes
0x00FF      # Last byte of two bytes
```

## Combining and Extracting Bits

### Concatenating Bytes

```python
byte1 = 0xAA    # 10101010
byte2 = 0xBB    # 10111011

# Combine into 16-bit number
combined = (byte1 << 8) | byte2    # Result: 0xAABB
```

### Setting/Clearing Specific Bits

```python
byte = 0b10000000

# Set bit 3 to 1 (counting from right, 0-based)
byte = byte | (1 << 3)            # OR with shifted 1

# Clear bit 3 (set to 0)
byte = byte & ~(1 << 3)           # AND with inverted shifted 1
```

## Converting Between Types

### Bytes to Integer

```python
# Convert bytes object to integer
bytes_obj = b'\x12\x34\x56\x78'
number = int.from_bytes(bytes_obj, 'big')     # big-endian
number = int.from_bytes(bytes_obj, 'little')  # little-endian
```

### Integer to Bytes

```python
number = 0x12345678
bytes_obj = number.to_bytes(4, 'big')         # big-endian
bytes_obj = number.to_bytes(4, 'little')      # little-endian
```

## Tips and Tricks

1. When working with bits, draw them out on paper first
2. Remember bit positions are counted from right to left, starting at 0
3. Use binary literals (0b...) for better readability when working with bits
4. Use hex literals (0x...) for better readability when working with bytes
5. For long binary numbers, use underscores for readability (0b1111_0000)
6. Always mask after shifting to ensure clean results

## Common Patterns

### Check if a bit is set

```python
is_set = bool(number & (1 << bit_position))
```

### Combining two 4-bit numbers into a byte

```python
first = 0b1010    # 4 bits
second = 0b0101   # 4 bits
byte = (first << 4) | second    # Result: 0b10100101
```

### Getting bits from the middle

```python
# Get bits 3-6 from: 0b10111010
byte = 0b10111010
middle = (byte >> 2) & 0b1111    # Shift right by 2, mask with 4 bits
```
