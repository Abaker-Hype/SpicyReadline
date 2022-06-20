/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <abaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 13:06:28 by abaker            #+#    #+#             */
/*   Updated: 2022/06/10 17:22:33 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spicyreadline.h"

static char	*srl_move_cmd(int val, char *p, char *n)
{
	char	*rtn;
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

t_cursor	srl_calc_cursor_pos(t_cursor bsize, int buff, t_termdata *term)
{
	t_cursor	pos;

	pos.row = bsize.row;
	buff += bsize.col;
	while (buff >= term->win.ws_col)
	{
		buff -= term->win.ws_col;
		pos.row++;
	}
	pos.col = buff;
	return (pos);
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

t_cursor	srl_get_cursor_pos(t_termdata *term)
{
	t_cursor		pos;
	char			c;
	bool			col;

	c = '\0';
	col = false;
	ft_bzero(&pos, sizeof(pos));
	write(term->rawfd, "\e[6n", 5);
	while (c != 'R')
	{
		read(term->rawfd, &c, 1);
		if (c == ';')
			col = true;
		else if (ft_isdigit(c))
		{
			if (col)
				pos.col = pos.col * 10 + c - '0';
			else
				pos.row = pos.row * 10 + c - '0';
		}
	}
	return (pos);
}
