# User Input Handling Utility in C

This project contains a small utility function and example usage demonstrating **safe reading of user input** from `stdin`. It ensures the input buffer is not overflowed and unwanted leftover characters are discarded, which helps prevent common input handling bugs.

---

## Features

- **Safe line input reading**: Reads up to a specified number of characters, discarding any extra characters beyond the buffer size.
- **Handles EOF gracefully**: Detects end-of-file (e.g., Ctrl+D) and exits cleanly.
- **Validates user input**:
  - Accepts only single-character numeric input within a specified range (1-6).
  - Accepts only single 'y' or 'n' character inputs for yes/no prompts.
- **Prevents leftover input issues** by discarding extra characters on the same input line.

---

## Function: `get_choice_input`

### Purpose

Reads a line of input from the user, storing at most `bufsiz - 1` characters in `str` and discards any excess characters until newline.

### Parameters

- `str`: Buffer to store the input string.
- `bufsiz`: Size of the buffer (including null terminator).

### Returns

Number of characters stored, or `-1` if EOF is encountered before newline.

### Behavior

- Stops reading when newline or EOF is encountered.
- Null-terminates the input string.
- Prevents buffer overflow and clears remaining input on the line.

---

## Usage Examples

### Example 1: Numeric menu choice input

- Prompts the user to enter a number between 1 and 6.
- Validates the input ensuring:
  - Only one character is entered.
  - The character is within the allowed numeric range.
- Re-prompts on invalid input.
- Handles EOF to exit gracefully.

### Example 2: Yes/No confirmation input

- Prompts the user for a yes/no answer (`y` or `n`).
- Validates single-character input case-insensitively.
- Re-prompts on invalid input.
- Handles EOF to exit gracefully.

---

## Notes

The buffer size is deliberately small to demonstrate strict input control.
You can adapt buffer sizes and validation rules as needed.
This pattern is useful for command-line programs requiring reliable and robust input.

---

## License

This project is provided for educational purposes.
Feel free to modify and extend it as needed.
