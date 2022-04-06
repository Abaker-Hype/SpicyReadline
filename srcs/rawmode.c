/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rawmode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <HypeSwarm>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 21:43:23 by abaker            #+#    #+#             */
/*   Updated: 2022/04/06 21:43:42 by abaker           ###   ########.fr       */
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
