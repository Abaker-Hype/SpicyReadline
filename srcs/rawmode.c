/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rawmode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <abaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 20:19:21 by abaker            #+#    #+#             */
/*   Updated: 2022/03/30 13:26:06 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spicyreadline.h"

void	srl_enable_raw(t_termdata	*term)
{
	struct termios	raw;

	tcgetattr(STDIN_FILENO, term->original);
	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
	term->flags = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, term->flags | O_NONBLOCK);
}

void	srl_disable_raw(t_termdata	*term)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, term->original);
	fcntl(STDIN_FILENO, F_SETFL, term->flags);
}
