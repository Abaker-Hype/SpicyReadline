/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <abaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:55:42 by abaker            #+#    #+#             */
/*   Updated: 2022/04/05 13:47:52 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spicyreadline.h"

static char	*strjoinfree(char *s1, char *s2, bool f1, bool f2)
{
	char	*rtn;

	rtn = ft_strjoin(s1, s2);
	if (f1)
		free(s1);
	if (f2)
		free(s2);
	return (rtn);
}

void	srl_redisplay(t_spicyrl *srl)
{
	char	*out;

	if (!srl->redisplay)
		return ;
	out = strjoinfree("\e[25l\e[u\e[0J", srl->prompt, false, false);
	if (srl->buff->saved)
		out = strjoinfree(out, srl->buff->saved, true, false);
	if (srl->cursor < srl->buff->chars)
	{
		out = strjoinfree(out, "\e[", true, false);
		out = strjoinfree(out, ft_itoa(srl->buff->chars - srl->cursor), true, true);
		out = strjoinfree(out, "D", true, false);
	}
	out = strjoinfree(out, "\e[25h", true, false);
	write(STDOUT_FILENO, out, ft_strlen(out));
	srl->redisplay = false;
}
