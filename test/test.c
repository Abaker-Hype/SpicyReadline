#include "spicyreadline.h"

void	printbuff(t_buff *buff)
{
	printf("Buff = %s\n", buff->saved);
	printf("Size = %i\n", buff->size);
	printf("insert = %i\n", buff->insert);
}

int	main(void)
{
	t_buff	buff;
	long	key;

	ft_bzero(&buff, sizeof(t_buff));
}
