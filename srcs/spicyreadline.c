/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spicyreadline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <abaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 20:14:45 by abaker            #+#    #+#             */
/*   Updated: 2022/06/10 17:38:40 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spicyreadline.h"

static	void	srl_init(t_spicyrl *srl, char *prompt, char *user, char *pwd)
{
	ft_bzero(srl, sizeof(*srl));
	srl_init_term(&srl->term);
	srl_init_hooks();
	srl_init_banner(&srl->banner, user, pwd, prompt);
	srl->buff = srl_new_history();
	srl->redisplay = true;
}

static char	*srl_exit(t_spicyrl *srl)
{
	char	*rtn;

	write(srl->term.rawfd, "\r\n", 2);
	srl_disable_raw(&srl->term);
	rtn = NULL;
	if (srl->buff->saved)
	{
		rtn = ft_strdup(srl->buff->saved);
		srl_update_history(srl->buff, srl->hist);
	}
	if (srl->banner.banner)
		free(srl->banner.banner);
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

	srl_init(&srl, prompt, user, pwd);
	srl.hist = hist;
	while (!srl.exit)
	{
		input = 0;
		srl_redisplay(&srl);
		while (read(srl.term.rawfd, &input, sizeof(long) - 1) > 0)
		{
			if (!srl_check_hooks(&srl, input))
				srl.redisplay = srl_add_buffer(srl.buff, (char *)&input);
			input = 0;
		}
	}
	return (srl_exit(&srl));
}
