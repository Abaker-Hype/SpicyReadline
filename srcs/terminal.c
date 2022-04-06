/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <abaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 20:19:21 by abaker            #+#    #+#             */
/*   Updated: 2022/04/06 16:03:00 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spicyreadline.h"

void	srl_enable_raw(t_termdata	*term)
{
	struct termios	raw;

	tcgetattr(STDIN_FILENO, &term->original);
	raw.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
			| INLCR | IGNCR | ICRNL | IXON);
	raw.c_oflag &= ~OPOST;
	raw.c_cflag &= ~(CSIZE | PARENB);
	raw.c_cflag |= CS8;
	raw.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	tcsetattr(STDIN_FILENO, TCSANOW, &raw);
	term->flags = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, term->flags | O_NONBLOCK);
}

void	srl_disable_raw(t_termdata	*term)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &term->original);
	fcntl(STDIN_FILENO, F_SETFL, term->flags);
}

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
	tcsetattr(0, TCSANOW, &saved);
	return (pos);
}

void	srl_set_cursor_pos(t_cursor pos)
{
	pos.row = 69;
}
