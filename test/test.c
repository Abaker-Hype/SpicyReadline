#include "libft.h"
#include <stdio.h>

typedef struct s_buff{
	char	*saved;
	int		size;
	int		chars;
}	t_buff;

static int	srl_char_pos(char *str, int pos)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	if (!str)
		return (0);
	while (str[i] && c++ != pos)
		i += ft_charsize(str[i]);
	return (i);
}

void	srl_add_buffer(t_buff *buff, char *str, int *pos)
{
	char	*tmp;
	int		size;
	int		i;

	size = buff->size + ft_strlen(str) + 1;
	tmp = ft_calloc(size, sizeof(char));
	if (tmp)
	{
		ft_strlcat(tmp, buff->saved, srl_char_pos(buff->saved, *pos) + 1);
		ft_strlcat(tmp, str, size);
		ft_strlcat(tmp, &buff->saved[srl_char_pos(buff->saved, *pos)], size);
		if (buff->saved)
			free(buff->saved);
		buff->saved = tmp;
		buff->size = size - 1;
		i = 0;
		while (str[i])
		{
			if (ft_charsize(str[i++]) > 0)
			{
				(*pos)++;
				buff->chars++;
			}
		}
	}
}

void	srl_del_buffer(t_buff *buff, int *pos)
{
	char	*tmp;
	int		size;

	if (*pos == 0 || *pos > buff->chars)
		return ;
	size = buff->size - ft_charsize(buff->saved[srl_char_pos(buff->saved, *pos)]) + 1;
	tmp = ft_calloc(size, sizeof(char));
	if (tmp)
	{
		ft_strlcat(tmp, buff->saved, srl_char_pos(buff->saved, *pos - 1) + 1);
		ft_strlcat(tmp, &buff->saved[srl_char_pos(buff->saved, *pos)], size);
		if (buff->saved)
			free(buff->saved);
		buff->saved = tmp;
		buff->size = size - 1;
		buff->chars--;
		(*pos)--;
	}
}

void	printfbuff(t_buff *buff, int i)
{
	printf("Buff = %s\n", buff->saved);
	printf("Size = %i\n", buff->size);
	printf("Chars = %i\n", buff->chars);
	printf("pos = %i\n\n", i);
}

int	main(void)
{
	int	i = 0, j = 0, k = 0;

	while (i < 10)
		if (i++ % 2 == 0 && j++ >= 0)
			k++;
	printf("%i - %i - %i\n", i , j, k);
}
