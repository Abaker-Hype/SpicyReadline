/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spicyreadline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <abaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 20:14:45 by abaker            #+#    #+#             */
/*   Updated: 2022/03/30 13:38:33 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spicyreadline.h"

static	void	srl_init(t_spicyrl *spicyrl)
{
	ft_bzero(spicyrl, sizeof(*spicyrl));
	srl_enable_raw(&spicyrl->original.term);
	srl_enable_noblock(&spicyrl->original);
}

static char	*srl_exit(t_spicyrl *spicyrl, bool add_history)
{
	srl_disable_raw(&spicyrl->original.term);
	return (NULL);
}

char	*spicy_readline(char *prompt, bool add_history)
{
	t_spicyrl	srl;
	long		input;

	srl_init(&spicyrl);
	write(STDOUT_FILENO, prompt, ft_strlen(prompt));
	while (true)
	{
		input = 0;
		if (read(STDIN_FILENO, &input, sizeof(long) - 1) != -1)
		{
			if (input == (long) '\r' && write(STDOUT_FILENO, "\r\n", 2))
				break ;
			if (!srl_check_hooks(&srl, input))
				write(STDOUT_FILENO, &input, ft_strlen((char *)&input));
		}
	}
	return (srl_exit(&srl, add_history));
}

char	*tmp_readline(char *prompt, bool add)
{
	char	*line;

	line = readline(prompt);
	if (add && line && line[0])
		add_history(line);
	return (line);
}
