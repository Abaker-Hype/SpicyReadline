/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <abaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 20:19:21 by abaker            #+#    #+#             */
/*   Updated: 2022/06/22 18:43:52 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spicyreadline.h"
#include <sys/ioctl.h>

static void	srl_enable_raw(t_term *term)
{
	struct termios	raw;
	int				noblock;

	noblock = 1;
	term->rawfd = open(ttyname(STDERR_FILENO), O_RDWR | O_NOCTTY | O_NDELAY);
	tcgetattr(term->rawfd, &term->orig);
	raw.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
			| INLCR | IGNCR | ICRNL | IXON);
	raw.c_oflag &= ~OPOST;
	raw.c_cflag &= ~(CSIZE | PARENB);
	raw.c_cflag |= CS8;
	raw.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	tcsetattr(term->rawfd, TCSANOW, &raw);
	ioctl(term->rawfd, FIONBIO, &noblock);
}

static int	srl_get_cursor_col(int rawfd)
{
	int		col;
	char	c;
	bool	b;

	c = '\0';
	b = false;
	col = 0;
	read(rawfd, NULL, 0);
	write(rawfd, "\e[6n", 5);
	while (c != 'R')
	{
		if (read(rawfd, &c, 1) == -1)
			break ;
		if (c == ';')
			b = true;
		else if (b && ft_isdigit(c))
			col = col * 10 + c - '0';
	}
	tcflush(rawfd, TCIOFLUSH);
	return (col);
}

void	srl_disable_raw(t_term *term)
{
	int	block;

	block = 0;
	ioctl(term->rawfd, FIONBIO, &block);
	tcsetattr(term->rawfd, TCSANOW, &term->orig);
	close(term->rawfd);
}

bool	srl_update_term_width(t_term *term)
{
	struct winsize	win;

	ioctl(term->rawfd, TIOCGWINSZ, &win);
	if (win.ws_col != term->width)
	{
		term->width = win.ws_col;
		term->update = true;
		return (true);
	}
	return (false);
}

void	srl_init_term(t_term *term)
{
	srl_enable_raw(term);
	srl_update_term_width(term);
	if (srl_get_cursor_col(term->rawfd) > 1)
		write(term->rawfd, "\e[7;1m%\e[0m\r\n", 13);
}
