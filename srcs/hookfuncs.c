/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hookfuncs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <abaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 13:15:58 by abaker            #+#    #+#             */
/*   Updated: 2022/07/11 14:02:25 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spicyreadline.h"

void	srl_hook_exit(t_keys key, t_srl *srl)
{
	srl_update_buff_ins(srl->buffer, false, true);
	if (key == K_CTRLC)
	{
		srl_add_buff(srl->buffer, "^C");
		srl_redisplay(srl);
	}
	if (key != K_ENTER)
		srl_clear_buff(srl->buffer);
	if (key == K_CTRLD)
		srl_add_buff(srl->buffer, "exit");
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
