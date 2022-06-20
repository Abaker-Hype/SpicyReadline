/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hookfuncs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <abaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:35:25 by abaker            #+#    #+#             */
/*   Updated: 2022/06/10 17:21:07 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spicyreadline.h"

void	srl_hook_return(t_keys key, t_spicyrl *srl)
{
	if (key == K_CTRLC || key == K_CTRLD)
	{
		if (srl->buff->saved)
			free(srl->buff->saved);
		srl->buff->saved = NULL;
		if (key == K_CTRLD)
			srl->buff->saved = ft_strdup("exit");
		else
			write(STDERR_FILENO, "^C", 2);
	}
	srl->exit = true;
}

void	srl_hook_del(t_keys key, t_spicyrl *srl)
{
	if (key == K_DELF)
	{
		if (srl->buff->cursor == srl->buff->chars)
			return ;
		srl->buff->cursor++;
	}
	if (srl->buff->cursor == 0)
		return ;
	srl->redisplay = srl_rmv_buffer(srl->buff);
}

void	srl_hook_cursor(t_keys key, t_spicyrl *srl)
{
	if (key == K_END)
		srl->buff->cursor = srl->buff->chars;
	else if (key == K_LEFT)
	{
		if (srl->buff->cursor == 0)
			return ;
		srl->buff->cursor--;
	}
	else
	{
		if (srl->buff->cursor == srl->buff->chars)
			return ;
		srl->buff->cursor++;
	}
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
	srl->buff->cursor = srl->buff->chars;
	srl->redisplay = true;
}
