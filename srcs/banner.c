/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <HypeSwarm>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 22:53:16 by abaker            #+#    #+#             */
/*   Updated: 2022/04/06 23:19:28 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spicyreadline.h"

char	*srl_banner(t_spicyrl *srl)
{
	char	*rtn;

	rtn = ft_calloc(srl->term.win.ws_col + 1, sizeof(*rtn));
	rtn = ft_memset(rtn, '-', srl->term.win.ws_col);
	return (rtn);
}
