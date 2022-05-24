/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <abaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 22:53:16 by abaker            #+#    #+#             */
/*   Updated: 2022/05/23 13:02:46 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spicyreadline.h"

static char	*srl_add_fill(char *str, int count)
{
	char	*fill;
	int		size;

	if (count < 1)
		return (str);
	size = count * 4 + 1;
	fill = ft_calloc(size, sizeof(*fill));
	if (!fill)
		return (str);
	while (count-- > 0)
		ft_strlcat(fill, "═", size);
	return (ft_strjoinfree(str, fill, true, true));
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

void	srl_gen_banner(t_spicyrl *srl)
{
	int		i;

	if (srl->banner)
		free(srl->banner);
	srl->banner = ft_strdup("\e[25l\e[u\e[0J\e[1;38;2;0;255;255m╞");
	srl->banner = srl_add_fill(srl->banner, 5);
	i = 8;
	if (srl->user)
		srl->banner = srl_add_info(srl->banner, srl->user, &i);
	if (srl->pwd)
		srl->banner = srl_add_info(srl->banner, srl->pwd, &i);
	if (i < srl->term.win.ws_col)
		srl->banner = srl_add_fill(srl->banner, srl->term.win.ws_col - i);
	srl->banner = ft_strjoinfree(srl->banner, "╡\r\n╘╡\e[0m", true, false);
	srl->banner = ft_strjoinfree(srl->banner, srl->prompt, true, false);
}
