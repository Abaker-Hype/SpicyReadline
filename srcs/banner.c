/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <abaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 22:53:16 by abaker            #+#    #+#             */
/*   Updated: 2022/04/08 15:45:15 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spicyreadline.h"

static char	*srl_add_fill(char *str, int count)
{
	while (count-- > 0)
		str = ft_strjoinfree(str, "═", true, false);
	return (str);
}

static char	*srl_add_info(char *str, char *info, int *len)
{
	str = ft_strjoinfree(str, "╡\e[38;2;255;255;0m", true, false);
	str = ft_strjoinfree(str, info, true, false);
	str = ft_strjoinfree(str, "\e[1;38;2;0;255;255m╞", true, false);
	str = srl_add_fill(str, 5);
	*len += ft_strlen(info) + 7;
	return (str);
}

char	*srl_banner(t_spicyrl *srl)
{
	char	*rtn;
	int		i;

	rtn = ft_strdup("\e[1;38;2;0;255;255m╞");
	rtn = srl_add_fill(rtn, 5);
	i = 7;
	if (srl->user)
		rtn = srl_add_info(rtn, srl->user, &i);
	if (srl->pwd)
		rtn = srl_add_info(rtn, srl->pwd, &i);
	if (i < srl->term.win.ws_col)
		rtn = srl_add_fill(rtn, srl->term.win.ws_col - i);
	rtn = ft_strjoinfree(rtn, "╡╘╡\e[0m", true, false);
	return (rtn);
}
