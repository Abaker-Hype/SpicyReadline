/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <abaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:12:57 by abaker            #+#    #+#             */
/*   Updated: 2022/06/24 15:07:10 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spicyreadline.h"

#define B_START "\e[1;38;2;0;255;255m╞"
#define B_END "╡\e[0m"
#define B_INFO "╡\e[38;2;255;255;0m"
#define B_NL "╡\e[1E╘"
#define B_FILL "═"

static int	srl_calc_banner_size(t_banner *banner, int width, bool blank)
{
	int	size;

	size = ft_strlen(B_START) + ft_strlen(B_END) + banner->promptlen;
	if (!blank)
	{
		size += ft_strlen(B_NL);
		width -= 2;
		if (banner->user)
		{
			size += ft_strlen(B_INFO) + banner->userlen + ft_strlen(B_START);
			width -= 2 + ft_charcount(banner->user);
		}
		if (banner->pwd)
		{
			size += ft_strlen(B_INFO) + banner->pwdlen + ft_strlen(B_START);
			width -= (2 + ft_charcount(banner->pwd));
		}
		if (width > 0)
			size += ft_strlen(B_FILL) * width;
	}
	return (size);
}

static int	srl_add_info(t_banner *banner, char *info, int offset)
{
	int	i;

	i = 0;
	while (i++ < 5)
		offset += ft_strlcpy(&banner->banner[offset], B_FILL, banner->size);
	offset += ft_strlcpy(&banner->banner[offset], B_INFO, banner->size);
	offset += ft_strlcpy(&banner->banner[offset], info, banner->size);
	offset += ft_strlcpy(&banner->banner[offset], B_START, banner->size);
	return (offset);
}

static void	srl_gen_new_banner(t_banner *banner, int width, bool blank)
{
	int	offset;

	banner->size = srl_calc_banner_size(banner, width, blank);
	banner->banner = ft_calloc(banner->size + 1, sizeof(*banner->banner));
	if (!banner->banner)
		return ;
	offset = ft_strlcpy(banner->banner, B_START, banner->size);
	if (!blank)
	{
		if (banner->user)
		{
			offset = srl_add_info(banner, banner->user, offset);
			width -= 7 + ft_charcount(banner->user);
		}
		if (banner->pwd)
		{
			offset = srl_add_info(banner, banner->pwd, offset);
			width -= 7 + ft_charcount(banner->pwd);
		}
		while (width-- > 2)
			offset += ft_strlcpy(&banner->banner[offset], B_FILL, banner->size);
		offset += ft_strlcpy(&banner->banner[offset], B_NL, banner->size);
	}
	offset += ft_strlcpy(&banner->banner[offset], B_END, banner->size);
	ft_strlcpy(&banner->banner[offset], banner->prompt, banner->size + 1);
}

void	srl_update_banner(t_srl *srl)
{
	if (srl->banner.banner && (srl->blank || !srl->term.update))
		return ;
	if (srl->banner.banner)
		free(srl->banner.banner);
	srl_gen_new_banner(&srl->banner, srl->term.width, srl->blank);
}
