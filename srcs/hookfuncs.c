/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hookfuncs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <abaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 13:15:58 by abaker            #+#    #+#             */
/*   Updated: 2022/07/13 11:07:36 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spicyreadline.h"

void	srl_hook_exit(t_keys key, t_srl *srl)
{
	srl_update_buff_ins(srl->buffer, false, true);
	srl_redisplay(srl);
	if (key != K_ENTER)
	{
		srl_clear_buff(srl->buffer);
		if (!srl->blank)
		{
			if (key == K_CTRLC)
				ft_putstr_fd("^C", srl->term.rawfd);
			else
			{
				srl_add_buff(srl->buffer, "exit");
				srl_redisplay(srl);
			}
		}
		else
		{
			if (key == K_CTRLC)
				srl_add_buff(srl->buffer, "\xc0\xe0");
			else
				srl_add_buff(srl->buffer, "\xc2\xc2");
		}
	}
	srl->exit = true;
}

void	srl_hook_del(t_keys key, t_srl *srl)
{
	srl_rmv_buff(srl->buffer, key == K_DEL);
}

void	srl_hook_cursor(t_keys key, t_srl *srl)
{
	srl_update_buff_ins(srl->buffer,
		key == K_LEFT || key == K_HOME, key == K_HOME || key == K_END);
}

void	srl_hook_history(t_keys key, t_srl *srl)
{
	if (srl->blank)
		return ;
	if (key == K_UP && srl->buffer->prev)
	{
		srl->buffer = srl->buffer->prev;
		srl->buffer->update = true;
	}
	else if (key == K_DOWN && srl->buffer->next)
	{
		srl->buffer = srl->buffer->next;
		srl->buffer->update = true;
	}
}
