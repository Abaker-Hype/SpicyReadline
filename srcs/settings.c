/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <HypeSwarm>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:51:44 by abaker            #+#    #+#             */
/*   Updated: 2022/04/06 23:08:25 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spicyreadline.h"

static t_srl_settings	*g_settings(void)
{
	static t_srl_settings	settings;

	return (&settings);
}

int	builtin_srl_settings(int c, char **v)
{
	t_srl_settings	*settings;

	if (c > 1 && v)
		v = NULL;
	settings = g_settings();
	if (settings)
		settings = NULL;
	return (0);
}
