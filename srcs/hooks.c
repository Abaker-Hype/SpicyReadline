/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <abaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 10:55:13 by abaker            #+#    #+#             */
/*   Updated: 2022/04/21 12:19:52 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spicyreadline.h"

static t_hooks	**g_hooks(void)
{
	static t_hooks	*hooks = NULL;

	return (&hooks);
}

static void	srl_add_hook(t_keys key, void (*f)(t_keys, t_spicyrl *))
{
	t_hooks	*new;
	t_hooks	*curr;

	new = ft_calloc(1, sizeof(*new));
	if (!new)
		return ;
	new->key = key;
	new->f = f;
	curr = *g_hooks();
	if (!curr)
		*g_hooks() = new;
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}

void	srl_init_hooks(void)
{
	if (*g_hooks())
		return ;
	srl_add_hook(K_ENTER, srl_hook_return);
	srl_add_hook(K_CTRLBS, NULL);
	srl_add_hook(K_CTRLC, srl_hook_return);
	srl_add_hook(K_CTRLD, srl_hook_return);
	srl_add_hook(K_DEL, srl_hook_del);
	srl_add_hook(K_DELF, srl_hook_del);
	srl_add_hook(K_ESC, NULL);
	srl_add_hook(K_TAB, NULL);
	srl_add_hook(K_UP, srl_hook_history);
	srl_add_hook(K_DOWN, srl_hook_history);
	srl_add_hook(K_LEFT, srl_hook_cursor);
	srl_add_hook(K_RIGHT, srl_hook_cursor);
	srl_add_hook(K_END, NULL);
	srl_add_hook(K_HOME, NULL);
}

void	srl_del_hooks(void)
{
	t_hooks	*next;

	while (*g_hooks())
	{
		next = (*g_hooks())->next;
		free(*g_hooks());
		*g_hooks() = next;
	}
}

bool	srl_check_hooks(t_spicyrl *srl, long key)
{
	t_hooks	*curr;

	curr = *g_hooks();
	while (curr)
	{
		if ((long)curr->key == key)
		{
			if (curr->f)
				(*curr->f)(curr->key, srl);
			return (true);
		}
		curr = curr->next;
	}
	return (false);
}
