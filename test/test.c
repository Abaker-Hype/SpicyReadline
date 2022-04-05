#include "spicyreadline.h"
#include <stdio.h>

int	main(void)
{
	char *line;

	while (true)
	{
		line = spicy_readline("FUCK>", true);
		printf("Returned Line = %s\n", line);
		if (line)
		{
			if (!ft_strncmp("exit", line, 5))
				break ;
			free(line);
		}
	}
	free(line);
}
