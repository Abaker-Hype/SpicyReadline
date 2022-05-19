/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <abaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:55:42 by abaker            #+#    #+#             */
/*   Updated: 2022/05/19 16:34:35 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spicyreadline.h"

static void	srl_gen_banner(t_spicyrl *srl)
{
	if (srl->banner)
		free(srl->banner);
	srl->banner = ft_strdup("\e[25l\e[u\e[0J");
	if (srl->user || srl->pwd)
		srl->banner = ft_strjoinfree(srl->banner, srl_banner(srl), true, true);
	srl->banner = ft_strjoinfree(srl->banner, srl->prompt, true, false);
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
	if (srl->term.changed || !srl->banner)
		srl_gen_banner(srl);
	out = ft_strdup(srl->banner);
	if (srl->buff->saved)
		out = ft_strjoinfree(out, srl->buff->saved, true, false);
	tmp = srl_gen_cursor(srl);
	if (tmp)
		out = ft_strjoinfree(out, tmp, true, true);
	out = ft_strjoinfree(out, "\e[25h", true, false);
	write(STDOUT_FILENO, out, ft_strlen(out));
	free(out);
	srl->redisplay = false;
	srl->term.changed = false;
}
