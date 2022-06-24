/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spicyreadline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <abaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 20:14:45 by abaker            #+#    #+#             */
/*   Updated: 2022/06/24 11:14:52 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spicyreadline.h"

static t_srl	*srl_init(char *prompt, char *user, char *pwd, bool blank)
{
	t_srl	*srl;

	srl = ft_calloc(1, sizeof(*srl));
	if (!srl)
		return (NULL);
	srl_init_term(&srl->term);
	srl->buffer = srl_new_buffer(blank);
	srl->banner.prompt = prompt;
	srl->banner.user = user;
	srl->banner.pwd = pwd;
	srl->blank = blank;
	return (srl);
}

static char	*srl_exit(t_srl *srl)
{
	char	*rtn;

	rtn = NULL;
	if (srl->buffer->chars)
	{
		rtn = ft_strdup(srl->buffer->buff);
		srl_add_history(srl->buffer);
	}
	srl_clear_history(srl->buffer);
	write(srl->term.rawfd, "\e[E", 4);
	srl_disable_raw(&srl->term);
	free(srl);
	return (rtn);
}

void	srl_clean_up(void)
{
	srl_del_hooks();
	srl_clear_history(NULL);
}

char	*spicy_readline(char *prompt, char *user, char *pwd, bool blank)
{
	t_srl	*srl;
	long	input;

	srl = srl_init(prompt, user, pwd, blank);
	if (!srl)
		return (NULL);
	while (!srl->exit)
	{
		input = 0;
		srl_redisplay(srl);
		if (read(srl->term.rawfd, &input, sizeof(long) - 1) > 0
			&& !srl_check_hooks(srl, input))
			srl_add_buff(srl->buffer, (char *)&input);
	}
	return (srl_exit(srl));
}
