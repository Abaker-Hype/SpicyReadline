/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <abaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 20:19:21 by abaker            #+#    #+#             */
/*   Updated: 2022/06/10 17:31:03 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spicyreadline.h"

static void	srl_enable_raw(t_termdata *term)
{
	struct termios	raw;

	term->rawfd = open(ttyname(STDERR_FILENO), O_RDWR);
	term->flags = fcntl(term->rawfd, F_GETFL, 0);
	tcgetattr(term->rawfd, &term->original);
	raw.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
			| INLCR | IGNCR | ICRNL | IXON);
	raw.c_oflag &= ~OPOST;
	raw.c_cflag &= ~(CSIZE | PARENB);
	raw.c_cflag |= CS8;
	raw.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	tcsetattr(term->rawfd, TCSANOW, &raw);
	fcntl(term->rawfd, F_SETFL, term->flags | O_NONBLOCK);
}

void	srl_disable_raw(t_termdata *term)
{
	fcntl(term->rawfd, F_SETFL, term->flags);
	tcsetattr(term->rawfd, TCSANOW, &term->original);
	close(term->rawfd);
}

bool	srl_update_term_width(t_termdata *term)
{
	struct winsize	new;

	ioctl(term->rawfd, TIOCGWINSZ, &new);
	if (new.ws_col != term->win.ws_col)
	{
		term->win = new;
		return (true);
	}
	return (false);
}

void	srl_init_term(t_termdata *term)
{
	if (!term)
		return ;
	ft_bzero(term, sizeof(*term));
	srl_enable_raw(term);
	srl_update_term_width(term);
	term->cursor = srl_get_cursor_pos(term);
	if (term->cursor.col > 0 && write(term->rawfd, "\e[7;1m%\e[0m\n", 13))
		ft_bzero(&term->cursor, sizeof(term->cursor));
}
