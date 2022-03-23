/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spicyreadline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <HypeSwarm>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 20:14:45 by abaker            #+#    #+#             */
/*   Updated: 2022/03/24 09:15:17 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spicyreadline.h"

static	void	init_readline(t_spicyrl *spicyrl)
{
	ft_bzero(spicyrl, sizeof(*spicyrl));
	enable_raw_mode(&spicyrl->original.term);
	spicyrl->original.flags = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, spicyrl->original.flags | O_NONBLOCK);
}

static char	*exit_readline(t_spicyrl *spicyrl, bool add_history)
{
	disable_raw_mode(&spicyrl->original.term);
	fcntl(STDIN_FILENO, F_SETFL, spicyrl->original.flags);
	if (spicyrl->buffer.saved)
		free(spicyrl->buffer.saved);
	if (add_history)
		add_history = false;
	return (NULL);
}

char	*spicy_readline(char *prompt, bool add_history)
{
	t_spicyrl	spicyrl;
	long		input;

	init_readline(&spicyrl);
	write(STDOUT_FILENO, prompt, ft_strlen(prompt));
	while (true)
	{
		input = 0;
		if (read(STDIN_FILENO, &input, sizeof(long) - 1) != -1)
		{
			if (input == (long) '\r' && write(STDIN_FILENO, "\r\n", 2))
				break ;
		}
	}
	return (exit_readline(&spicyrl, add_history));
}
