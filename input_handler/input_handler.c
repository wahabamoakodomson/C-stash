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

	// Track how many characters we store in the buffer
	len = 0;

	// Read characters one-by-one until newline or EOF
	while ((c = getchar()) != EOF) {
		// Stop reading when Enter is pressed
		if (c == '\n')
			break;
		
		// Only store the character if there is space in the buffer
		if (len < bufsiz - 1) {
			str[len++] = c;
			
		// If buffer is full, discard extra characters
		} else {
			continue;
		}
	}

	// If EOF is reached before newline, signal termination
	if (c == EOF)
		return -1;

	// Null-terminate the string
	str[len] = '\0';

	// Return number of characters stored
	return len;
}


int main()
{
	// EXAMPLE 1
	// Loop indefinitely until valid input is received
	while (1) {
		printf(">> ");
	
		// Read up to 2 characters + null terminator into buffer
		// Returns number of characters read, or -1 on EOF
		int read_len = get_choice_input(buf, 3);
	
		// Get actual string length for validation
		size_t len = strlen(buf);
	
		// If user sends EOF (Ctrl+D), exit gracefully
		if (read_len == -1) {
			printf("\n\nExiting...\n\n");
			exit(0);
		}
	
		// If user presses Enter without typing anything, ask again
		if (len == 0)
			continue;
	
		// If user enters more than one character, it’s invalid for this menu
		if (len > 1) {
			printf("\nInvalid input (Enter a number ");
			printf("between 1 to 6.)\n\n");
			continue;
		}
	
		// Convert the single character in buffer to integer
		choice = atoi(buf);
	
		// Validate that user choice falls within acceptable range
		if (choice < 1 || choice > 6) {
			printf("\nInvalid input (Enter a number ");
			printf("between 1 to 6.)\n\n");
			continue;
		}
	
		// Input is valid — exit loop
		break;
	}

	// EXAMPLE 2
	// Loop indefinitely until valid input is received
	while(1){
			printf("\nPerform another action? (y/n): ");

			// Read up to 2 characters + null terminator into buffer
			// Returns number of characters read, or -1 on EOF
			int read_len = get_choice_input(buf, 3);
		
			// Get the number of characters in the buffer
			size_t len = strlen(buf);
		
			// If EOF is encountered, exit the program
			if (read_len == -1) {
				printf("\n\nExiting...\n\n");
				exit(0);
			}
		
			// If more than one character was typed, input is invalid
			if (len > 1) {
				printf("\nInvalid choice; expected one y or n");
				printf(" character\n");
				continue;
			}
		
			// Extract the single character entered
			run = *buf;
		
			// If user enters 'y' or 'n' (case-insensitive), input is valid
			if (run == 'y' || run == 'Y' ||
			    run == 'n' || run == 'N') {
				break;
			}
		
			// Otherwise, notify user of invalid response
			printf("\nInvalid choice. Please enter 'y' or 'n'.\n");
		}
	}

	return 0;
}
