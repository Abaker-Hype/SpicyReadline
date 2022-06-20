/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <abaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 22:53:16 by abaker            #+#    #+#             */
/*   Updated: 2022/06/10 17:22:13 by abaker           ###   ########.fr       */
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

static char	*srl_add_info(char *str, char *info)
{
	str = ft_strjoinfree(str, "╡\e[38;2;255;255;0m", true, false);
	str = ft_strjoinfree(str, info, true, false);
	return (ft_strjoinfree(str, "\e[1;38;2;0;255;255m╞", true, false));
}

void	srl_gen_banner(t_banner *banner, t_termdata *term)
{
	int		i;

	if (banner->banner)
		free(banner->banner);
	banner->banner = ft_strdup("\e[25l\e[u\e[0J\e[1;38;2;0;255;255m╞");
	banner->banner = srl_add_fill(banner->banner, 5);
	i = 8;
	if (banner->user)
	{
		banner->banner = srl_add_info(banner->banner, banner->user);
		banner->banner = srl_add_fill(banner->banner, 5);
		i += ft_strlen(banner->user) + 7;
	}
	if (banner->pwd)
	{
		banner->banner = srl_add_info(banner->banner, banner->pwd);
		i += ft_strlen(banner->pwd) + 2;
	}
	if (i < term->win.ws_col)
		banner->banner = srl_add_fill(banner->banner, term->win.ws_col - i);
	banner->banner = ft_strjoinfree(banner->banner, "╡\r\n╘╡\e[0m", true, false);
	banner->banner = ft_strjoinfree(banner->banner,
			banner->prompt, true, false);
}

void	srl_init_banner(t_banner *banner, char *user, char *pwd, char *prompt)
{
	banner->banner = NULL;
	banner->user = user;
	banner->pwd = pwd;
	banner->prompt = prompt;
	banner->size.row = 1;
	banner->size.col = ft_strlen(prompt + 2);
}
