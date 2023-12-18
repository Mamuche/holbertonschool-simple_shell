#include "main.h"


/**
 * exit_shell - command for exiting the shell.
 * @command: arguments passed by utilisateur.
*/

void exit_shell(char *command)
{
    if (strcmp(command, "exit") == 0)
	{
        printf("Exiting shell...\n");
        exit(0);
    }
}


/**
 * _printlineTyped - Basic function for interactive input in a shell.
 *
 * Description:
 * Displays a prompt, reads user input from stdin using getline,
 * and prints the entered line.
 * Exits the shell if getline returns -1 (EOF or an error).
 * Dynamically allocates memory for input and frees it at the end.
 *
 * Return:
 *  0 on success, -1 on shell exit or error.
 */
int _printlineTyped(void)
{
	char *prompt = "$ ";
	char *lineptr = NULL;
	char **tokens = NULL;
	size_t n = 0;
	ssize_t nchars_read;

	while (1)
	{
		printf("%s", prompt);
		nchars_read = getline(&lineptr, &n, stdin);
		if (nchars_read == -1)
		{
			free(lineptr);
			return (-1);
		}
		if (nchars_read > 0 && lineptr[nchars_read - 1] == '\n')
		{
			lineptr[nchars_read - 1] = '\0';
		}
		tokens = process_command(lineptr);
		exit_shell(tokens[0]);
		exec_command(tokens);
	}
	free(lineptr);
	return (0);
}

/**
 * startShell - Init a shell in either interactive or non-interactive mode.
 *
 * Description:
 * Checks if standard input is associated with a terminal.
 * If true, initiates an interactive shell.
 * using _printlineTyped function. If not,
 * indicates non-interactive mode with a message.
 *
 * Return:
 * Always returns 0.
 */
int startShell(void)
{
	if (isatty(fileno(stdin)))
	{
		_printlineTyped();
	}
	else
	{
		printf("non-interactive mode\n");
	}
	return (0);
}

/**
 * exec_command - execute command.
 *
 * @tokens: arguments passed for utilisateurs.
*/
void exec_command(char **tokens)
{
	pid_t pid;

	if (tokens == NULL)
	{
		return;
	}

	pid = fork();
	if (pid < 0)
	{
		perror("Forks fail");
	}
	else if (pid == 0)
	{
		if (execve(tokens[0], tokens, NULL) == -1)
		{
			perror("./hsh");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
}
