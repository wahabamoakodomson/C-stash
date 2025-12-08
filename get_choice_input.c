// Safely reads a line of input representing a single user choice,
// ensuring that characters beyond the buffer limit are discarded.
// This prevents leftover data from remaining in stdin when the user
// types more than one character.
// Arguments:
// str - pointer to the buffer where the input will be stored.
// bufsiz - maximum size of the buffer (including null terminator).
// Return: Number of characters stored.
int get_choice_input(char *str, int bufsiz)
{
	int len;
	int c;

	len = 0;

	while ((c = getchar()) != EOF) {
		if (c == '\n')
			break;

		if (len < bufsiz - 1) {
			str[len++] = c;
		} else {
			continue;
		}
	}

	if (c == EOF)
		return -1;


	str[len] = '\0';

	return len;
}
