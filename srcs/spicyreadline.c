/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spicyreadline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <abaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 20:14:45 by abaker            #+#    #+#             */
/*   Updated: 2022/04/05 13:35:28 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spicyreadline.h"

static	void	srl_init(t_spicyrl *srl, char *prompt, bool hist)
{
	write(STDOUT_FILENO, "\e[s", 5);
	ft_bzero(srl, sizeof(t_spicyrl));
	srl->buff = srl_new_history();
	srl->prompt = prompt;
	srl->hist = hist;
	srl->redisplay = true;
	srl_redisplay(srl);
	srl_enable_raw(&srl->original);
	srl_init_hooks();
}

static char	*srl_exit(t_spicyrl *srl)
{
	char	*rtn;

	srl_disable_raw(&srl->original);
	rtn = NULL;
	if (srl->buff->saved)
		rtn = ft_strdup(srl->buff->saved);
	srl_update_history(srl->buff, srl->hist);
	return (rtn);
}

void	srl_clean_up(void)
{
	srl_del_hooks();
	srl_del_history(NULL);
}

char	*spicy_readline(char *prompt, bool hist)
{
	t_spicyrl	srl;
	long		input;

	srl_init(&srl, prompt, hist);
	while (!srl.exit)
	{
		input = 0;
		srl_redisplay(&srl);
		while (read(STDIN_FILENO, &input, sizeof(long) - 1) > 0)
		{
			if (!srl_check_hooks(&srl, input))
				srl.redisplay = srl_add_buffer(srl.buff,
						(char *)&input, &srl.cursor);
			input = 0;
		}
	}
	write(STDOUT_FILENO, "\r\n", 2);
	return (srl_exit(&srl));
}
