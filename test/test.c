#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "libft.h"

typedef struct s_cursor{
	int	row;
	int	col;
}	t_cursor;

typedef struct s_termdata{
	int				rawfd;
	int				flags;
	struct termios	old;
	struct winsize	win;
	t_cursor		cursor;
	bool			changed;
}	t_termdata;

static char	*srl_move_cmd(int val, char *p, char *n)
{
	char	*rtn;
	char	*num;
	bool	neg;

	rtn = ft_strdup("\e[");
	neg = false;
	if (val < 0)
	{
		val *= -1;
		neg = true;
	}
	rtn = ft_strjoinfree(rtn, ft_itoa(val), true, true);
	if (!neg)
		rtn = ft_strjoinfree(rtn, p, true, false);
	else
		rtn = ft_strjoinfree(rtn, n, true, false);
	return (rtn);
}

void	srl_set_cursor(t_cursor new, t_termdata *term)
{
	char	*out;

	if (new.col == term->cursor.col && new.row == term->cursor.row)
		return ;
	if (new.row != term->cursor.row)
	{
		out = srl_move_cmd(new.row - term->cursor.row, "B", "A");
		write(term->rawfd, out, ft_strlen(out));
		free(out);
	}
	if (new.col != term->cursor.col)
	{
		out = srl_move_cmd(new.col - term->cursor.col, "C", "D");
		write(term->rawfd, out, ft_strlen(out));
		free(out);
	}
	term->cursor = new;
}

int	main(void)
{
	t_termdata	data;
	t_cursor	c;

	ft_bzero(&data, sizeof(data));
	ft_bzero(&c, sizeof(c));
	data.rawfd = STDOUT_FILENO;
	c.col = 10;
	srl_set_cursor(c, &data);
	data.cursor.col += write(data.rawfd, "A", 1);
	c.row = 1;
	srl_set_cursor(c, &data);
	data.cursor.col += write(data.rawfd, "B", 1);
	srl_set_cursor(c, &data);
	data.cursor.col += write(data.rawfd, "C", 1);
	return (0);
}
