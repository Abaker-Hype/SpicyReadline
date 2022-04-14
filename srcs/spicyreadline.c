/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spicyreadline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <abaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 20:14:45 by abaker            #+#    #+#             */
/*   Updated: 2022/04/14 12:39:02 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spicyreadline.h"

static	void	srl_init(t_spicyrl *srl)
{
	srl->buff = srl_new_history();
	srl->cursor_init = srl_get_cursor_pos();
	if (srl->cursor_init.col > 1)
	{
		write(STDOUT_FILENO, "\e[7;1m%\e[0m\n", 13);
		srl->cursor_init.col = 1;
		srl->cursor_init.row++;
	}
	write(STDOUT_FILENO, "\e[s", 4);
	srl_get_term_width(&srl->term);
	srl_init_hooks();
	srl_redisplay(srl);
	srl_enable_raw(&srl->term);
}

static char	*srl_exit(t_spicyrl *srl)
{
	char	*rtn;

	srl_disable_raw(&srl->term);
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

char	*spicy_readline(char *prompt, char *user, char *pwd, bool hist)
{
	t_spicyrl	srl;
	long		input;

	ft_bzero(&srl, sizeof(t_spicyrl));
	srl.prompt = prompt;
	srl.user = user;
	srl.pwd = pwd;
	srl.hist = hist;
	srl_init(&srl);
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
