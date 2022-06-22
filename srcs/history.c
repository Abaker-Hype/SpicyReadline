/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <abaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 13:37:51 by abaker            #+#    #+#             */
/*   Updated: 2022/06/22 16:46:06 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spicyreadline.h"

static t_buff	**g_history(void)
{
	static t_buff	*history = NULL;

	return (&history);
}

static t_buff	*srl_clone_buff(t_buff *buff)
{
	t_buff	*clone;

	clone = ft_calloc(1, sizeof(*clone));
	if (!clone)
		return (NULL);
	if (buff->buff)
		srl_add_buff(clone, buff->buff);
	return (clone);
}

void	srl_add_history(t_buff *buff)
{
	t_buff	*last;

	if (!(buff->buff && buff->chars))
		return ;
	last = *g_history();
	while (last && last->next)
		last = last->next;
	if (!last)
		*g_history() = srl_clone_buff(buff);
	else if (ft_strncmp(last->buff, buff->buff, last->size + 1))
	{
		buff = srl_clone_buff(buff);
		buff->prev = last;
		last->next = buff;
	}
}

void	srl_clone_history(t_buff *add)
{
	t_buff	*clone;
	t_buff	*curr;

	clone = NULL;
	curr = *g_history();
	while (curr)
	{
		if (!clone)
			clone = srl_clone_buff(curr);
		else
		{
			clone->next = srl_clone_buff(curr);
			clone->next->prev = clone;
			clone = clone->next;
		}
		curr = curr->next;
	}
	add->prev = clone;
	if (clone)
		clone->next = add;
}

void	srl_clear_history(t_buff *buff)
{
	t_buff	*next;

	if (!buff)
	{
		buff = *g_history();
		*g_history() = NULL;
	}
	while (buff && buff->prev)
		buff = buff->prev;
	while (buff)
	{
		next = buff->next;
		if (buff->buff)
			free(buff->buff);
		free(buff);
		buff = next;
	}
}
