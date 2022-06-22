/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hookfuncs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <abaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 13:15:58 by abaker            #+#    #+#             */
/*   Updated: 2022/06/22 16:38:42 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spicyreadline.h"

void	srl_hook_exit(t_keys key, t_srl *srl)
{
	if (key == K_CTRLD)
		srl->buffer->buff = ft_strdup("exit");
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
