/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <abaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 20:19:21 by abaker            #+#    #+#             */
/*   Updated: 2022/04/08 15:10:46 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spicyreadline.h"

static struct termios	srl_raw_output(void)
{
	struct termios	raw;
	struct termios	save;

	tcgetattr(STDOUT_FILENO, &save);
	raw = save;
	raw.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDOUT_FILENO, TCSANOW, &raw);
	return (save);
}

t_cursor	srl_get_cursor_pos(void)
{
	struct termios	saved;
	t_cursor		pos;
	char			c;
	bool			col;

	c = '\0';
	col = false;
	ft_bzero(&pos, sizeof(pos));
	saved = srl_raw_output();
	write(STDOUT_FILENO, "\e[6n", 5);
	while (c != 'R')
	{
		read(STDOUT_FILENO, &c, 1);
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
	tcsetattr(STDOUT_FILENO, TCSANOW, &saved);
	return (pos);
}

void	srl_set_cursor_pos(t_cursor pos)
{
	if (pos.row != 69)
		pos.row = 69;
}

void	srl_get_term_width(t_termdata *term)
{
	struct winsize	new;

	ioctl(STDIN_FILENO, TIOCGWINSZ, &new);
	if (new.ws_col != term->win.ws_col)
	{
		term->win = new;
		term->changed = true;
	}
}
