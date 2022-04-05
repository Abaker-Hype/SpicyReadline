/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hookfuncs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <abaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:35:25 by abaker            #+#    #+#             */
/*   Updated: 2022/04/05 11:56:10 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spicyreadline.h"

void	srl_hook_return(t_keys key, t_spicyrl *srl)
{
	if (key == K_ENTER)
		srl->exit = true;
}

void	srl_hook_del(t_keys key, t_spicyrl *srl)
{
	if (key == K_DELF)
	{
		if (srl->cursor == srl->buff->chars)
			return ;
		srl->cursor++;
	}
	if (srl->cursor == 0)
		return ;
	srl->redisplay = srl_rmv_buffer(srl->buff, &srl->cursor);
}

void	srl_hook_cursor(t_keys key, t_spicyrl *srl)
{
	if (key == K_LEFT)
	{
		if (srl->cursor == 0)
			return ;
		srl->cursor--;
	}
	else
	{
		if (srl->cursor == srl->buff->chars)
			return ;
		srl->cursor++;
	}
	write(STDOUT_FILENO, &key, 3);
	srl->redisplay = true;
}

void	srl_hook_history(t_keys key, t_spicyrl *srl)
{
	if (!srl->hist)
		return ;
	if (key == K_UP)
	{
		if (!srl->buff->prev)
			return ;
		srl->buff = srl->buff->prev;
	}
	else
	{
		if (!srl->buff->next)
			return ;
		srl->buff = srl->buff->next;
	}
	srl->cursor = srl->buff->chars;
	srl->redisplay = true;
}
