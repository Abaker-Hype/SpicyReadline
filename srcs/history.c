/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <HypeSwarm>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:36:00 by abaker            #+#    #+#             */
/*   Updated: 2022/04/04 17:00:43 by abaker           ###   ########.fr       */
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

void	srl_del_history(void)
{
	t_buff	*next;

	while (*g_history())
	{
		next = (*g_history())->next;
		if ((*g_history())->saved)
			free((*g_history())->saved);
		free(*g_history());
		*g_history() = next;
	}
}
