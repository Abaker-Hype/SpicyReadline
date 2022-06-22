/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <abaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 10:55:13 by abaker            #+#    #+#             */
/*   Updated: 2022/06/22 13:22:37 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spicyreadline.h"

typedef struct s_hooks	t_hooks;
struct s_hooks{
	t_keys	key;
	void	(*func)(t_keys, t_srl *);
	t_hooks	*next;
};

static t_hooks	**g_hooks(void)
{
	static t_hooks	*hooks = NULL;

	return (&hooks);
}

static void	srl_add_hook(t_keys key, void (*func)(t_keys, t_srl *))
{
	t_hooks	*new;
	t_hooks	*curr;

	new = ft_calloc(1, sizeof(*new));
	if (!new)
		return ;
	new->key = key;
	new->func = func;
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

static t_hooks	*srl_init_hooks(void)
{
	if (!*g_hooks())
	{
		srl_add_hook(K_ENTER, srl_hook_exit);
		srl_add_hook(K_CTRLBS, NULL);
		srl_add_hook(K_CTRLC, srl_hook_exit);
		srl_add_hook(K_CTRLD, srl_hook_exit);
		srl_add_hook(K_DEL, srl_hook_del);
		srl_add_hook(K_DELF, srl_hook_del);
		srl_add_hook(K_ESC, NULL);
		srl_add_hook(K_TAB, NULL);
		srl_add_hook(K_UP, srl_hook_history);
		srl_add_hook(K_DOWN, srl_hook_history);
		srl_add_hook(K_LEFT, srl_hook_cursor);
		srl_add_hook(K_RIGHT, srl_hook_cursor);
		srl_add_hook(K_END, srl_hook_cursor);
		srl_add_hook(K_HOME, srl_hook_cursor);
	}
	return (*g_hooks());
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
	*g_hooks() = NULL;
}

bool	srl_check_hooks(t_srl *srl, long key)
{
	t_hooks	*curr;

	curr = srl_init_hooks();
	while (curr)
	{
		if ((long)curr->key == key)
		{
			if (curr->func)
				(*curr->func)(curr->key, srl);
			return (true);
		}
		curr = curr->next;
	}
	return (false);
}
