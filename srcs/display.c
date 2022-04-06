/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <HypeSwarm>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:55:42 by abaker            #+#    #+#             */
/*   Updated: 2022/04/06 23:17:19 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spicyreadline.h"

static char	*srl_gen_banner(t_spicyrl *srl)
{
	char	*rtn;

	rtn = ft_strdup("\e[25l\e[u\e[0J");
	if (srl->user || srl->pwd)
		rtn = ft_strjoinfree(rtn, srl_banner(srl), true, false);
	return (rtn);
}

static char	*srl_gen_prompt(char *prompt)
{
	return (ft_strdup(prompt));
}

static char	*srl_gen_buff(char *buff)
{
	if (!buff)
		return (NULL);
	return (ft_strdup(buff));
}

static char	*srl_gen_cursor(t_spicyrl *srl)
{
	char	*rtn;

	rtn = NULL;
	if (srl->cursor < srl->buff->chars)
	{
		rtn = ft_strjoinfree("\e[", ft_itoa(srl->buff->chars - srl->cursor),
				false, true);
		rtn = ft_strjoinfree(rtn, "D", true, false);
	}
	return (rtn);
}

void	srl_redisplay(t_spicyrl *srl)
{
	char	*out;
	char	*tmp;

	srl_get_term_width(&srl->term);
	if (!(srl->redisplay || srl->term.changed))
		return ;
	out = ft_strjoinfree(srl_gen_banner(srl), srl_gen_prompt(srl->prompt),
			true, true);
	tmp = srl_gen_buff(srl->buff->saved);
	if (tmp)
		out = ft_strjoinfree(out, tmp, true, true);
	tmp = srl_gen_cursor(srl);
	if (tmp)
		out = ft_strjoinfree(out, tmp, true, true);
	out = ft_strjoinfree(out, "\e[25h", true, false);
	write(STDOUT_FILENO, out, ft_strlen(out));
	srl->redisplay = false;
	srl->term.changed = false;
}
