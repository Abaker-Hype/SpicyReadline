#include "spicyreadline.h"
#include <string.h>

int	main(void)
{
	char *line;

	while (true)
	{
		line = spicy_readline("MiniShell> ", "Abaker", "/home/fuck/you", false);
		printf("%s[%zi] - Was Returned\n", line, ft_strlen(line));
		if (line && ft_strncmp("exit", line, 5) == 0)
			break ;
		free(line);
	}
	srl_clean_up();
	free(line);
	check_leaks();
}
