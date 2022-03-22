/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spicyreadline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <HypeSwarm>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 20:14:45 by abaker            #+#    #+#             */
/*   Updated: 2022/03/22 23:20:34 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spicyreadline.h"

static	void	init_readline(t_termdata *original, t_buff *buff)
{
	enable_raw_mode(&original->term);
	original->flags = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, original->flags | O_NONBLOCK);
	bzero(buff, sizeof(*buff));
}

static char	*exit_readline(t_termdata *original, t_buff *buff, bool add_history)
{
	disable_raw_mode(&original->term);
	fcntl(STDIN_FILENO, F_SETFL, original->flags);
	if (buff->saved)
		free(buff->saved);
	return (NULL);
}

char	*spicy_readline(char *prompt, bool add_history)
{
	t_termdata	original;
	t_buff		buff;
	long		input;

	init_readline(&original, &buff);
	write(STDOUT_FILENO, prompt, strlen(prompt));
	while (true)
	{
		input = 0;
		if (read(STDIN_FILENO, &input, sizeof(long) - 1) != -1)
		{
			if (input == (long) '\r' && write(STDIN_FILENO, "\r\n", 2))
				break ;
			if (!chk_cmds(input))
				write(STDIN_FILENO, &input, sizeof(long) - 1);
		}
	}
	return (exit_readline(&original, &buff, add_history));
}
