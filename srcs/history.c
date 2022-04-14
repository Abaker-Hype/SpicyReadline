/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <abaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:36:00 by abaker            #+#    #+#             */
/*   Updated: 2022/04/14 13:13:59 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spicyreadline.h"

static t_buff	**g_history(void)
{
	static t_buff	*hist = NULL;

	return (&hist);
}

t_buff	*srl_new_history(void)
{
	t_buff	*new;
	t_buff	*curr;

	new = ft_calloc(1, sizeof(*new));
	if (!new)
		return (NULL);
	curr = *g_history();
	if (!curr)
		*g_history() = new;
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = new;
		new->prev = curr;
	}
	return (new);
}

void	srl_del_history(t_buff *del)
{
	t_buff	*next;
	bool	all;

	all = !del;
	if (!del)
		del = *g_history();
	while (del)
	{
		next = del->next;
		if (!del->prev)
			*g_history() = next;
		else
			del->prev->next = next;
		if (next)
			next->prev = del->prev;
		if (del->saved)
			free(del->saved);
		free(del);
		if (!all)
			return ;
		del = next;
	}
}

void	srl_update_history(t_buff *buff, bool hist)
{
	t_buff	*b;

	if (!hist)
		return (srl_del_history(buff));
	if (!buff->next)
	{
		b = buff->prev;
		if (!buff->saved
			|| (b && ft_strncmp(buff->saved, b->saved, b->size + 1) == 0))
			return (srl_del_history(buff));
	}
	else
	{
		b = buff->next;
		while (b->next)
			b = b->next;
		if (b->prev == buff)
			return (srl_del_history(b));
		free(b->saved);
		b->saved = ft_strdup(buff->saved);
		b->size = buff->size;
		b->chars = buff->chars;
	}
}
