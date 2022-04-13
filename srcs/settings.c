/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <abaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:51:44 by abaker            #+#    #+#             */
/*   Updated: 2022/04/08 15:29:23 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spicyreadline.h"

static t_srl_settings	*g_settings(void)
{
	static t_srl_settings	settings;

	return (&settings);
}

int	srl_settings(int c, char **v)
{
	t_srl_settings	*settings;

	printf("Readline: Settings not yet coded\n");
	return (1);
	if (c > 1 && v)
		v = NULL;
	settings = g_settings();
	if (settings)
		settings = NULL;
	return (0);
}
