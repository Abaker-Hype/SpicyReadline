/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <abaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:55:42 by abaker            #+#    #+#             */
/*   Updated: 2022/04/01 11:36:00 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spicyreadline.h"

void	srl_redisplay(t_spicyrl *srl)
{
	int	i;

	if (!srl->redisplay)
		return ;
	write(STDOUT_FILENO, "\e[25l\r\e[0J", 11);
	write(STDOUT_FILENO, srl->prompt, ft_strlen(srl->prompt));
	if (srl->buff.size > 0)
		write(STDOUT_FILENO, srl->buff.saved, srl->buff.size);
	i = srl->buff.chars - srl->cursor;
	while (i-- > 0)
		write(STDOUT_FILENO, "\e[1D", 5);
	write(STDOUT_FILENO, "\e[25h", 6);
	srl->redisplay = false;
}
