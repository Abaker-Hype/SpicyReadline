/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <abaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 20:19:21 by abaker            #+#    #+#             */
/*   Updated: 2022/06/24 11:00:02 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spicyreadline.h"
#include <fcntl.h>
#include <sys/ioctl.h>

static void	srl_enable_raw(t_term *term)
{
	struct termios	raw;
	int				noblock;

	noblock = 1;
	term->rawfd = open(ttyname(STDIN_FILENO), O_RDWR);
	tcgetattr(term->rawfd, &term->orig);
	raw = term->orig;
	raw.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
			| INLCR | IGNCR | ICRNL | IXON);
	raw.c_oflag &= ~OPOST;
	raw.c_cflag &= ~(CSIZE | PARENB);
	raw.c_cflag |= CS8;
	raw.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;
	tcsetattr(term->rawfd, TCSANOW, &raw);
}

static int	srl_get_cursor_col(int rawfd)
{
	char	output[20];
	int		i;

	i = 0;
	write(rawfd, "\e[6n", 5);
	write(rawfd, "WHY DO I NEED THIS???", 0);
	ft_bzero(output, sizeof(output));
	if (read(rawfd, &output, sizeof(output) - 1) > 0)
		while (output[i])
			if (output[i++] == ';')
				return (ft_atoi(&output[i]));
	return (-1);
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
	if (srl_get_cursor_col(term->rawfd) > 1)
		write(term->rawfd, "\e[7;1m%\e[0m\r\n", 13);
}
