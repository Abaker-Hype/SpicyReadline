/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <abaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 10:55:13 by abaker            #+#    #+#             */
/*   Updated: 2022/03/31 12:06:06 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spicyreadline.h"

static void	srl_add_hook(t_hooks **hooks, t_keys key, void (*f)(int, *t_spicyrl))
{
	t_hooks	*new;
	t_hooks	*curr;

	new = ft_calloc(1, sizeof(*new));
	if (!new)
		return ;
	new->key = key;
	new->f = f;
	curr = *hooks;
	if (!curr)
		*hooks = new;
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}

void	srl_init_hooks(t_hooks **hooks)
{
	srl_add_hook(hooks, K_CTRLBS, NULL);
	srl_add_hook(hooks, K_CTRLC, NULL);
	srl_add_hook(hooks, K_CTRLD, NULL);
	srl_add_hook(hooks, K_DEL, NULL);
	srl_add_hook(hooks, K_TAB, NULL);
	srl_add_hook(hooks, K_UP, NULL);
	srl_add_hook(hooks, K_DOWN, NULL);
	srl_add_hook(hooks, K_LEFT, NULL);
	srl_add_hook(hooks, K_RIGHT, NULL);
}

void	srl_del_hooks(t_hooks **hooks)
{
	t_hooks	*curr;
	t_hooks	*next;

	curr = *hooks;
	while (curr)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
	*hooks = NULL;
}

bool	srl_check_hooks(t_spicyrl *rl, int key)
{
	t_hooks	*curr;

	curr = rl->hooks;
	while (curr)
	{
		if (curr->key == key)
		{
			if (curr->f)
				(*curr->f)(key, rl);
			return (true);
		}
		curr = curr->next;
	}
	return (false);
}
