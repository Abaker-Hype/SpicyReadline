#include "spicyreadline.h"

int	main(void)
{
	char	*line;

	while (true)
	{
		line = spicy_readline("test>", false);
		if (!line)
			break ;
	}
	return (EXIT_SUCCESS);
}
