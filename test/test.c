#include "spicyreadline.h"
#include <stdio.h>

int	main(void)
{
	char *line = spicy_readline("FUCK>", false);
	printf("Returned line = %s\n", line);
}
