/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spicyreadline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <HypeSwarm>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 20:14:45 by abaker            #+#    #+#             */
/*   Updated: 2022/04/04 17:01:01 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spicyreadline.h"

//WHY DO I NEED THAT WRITE THERE TO NOT BREAK SHIT!?!?!?
static	void	srl_init(t_spicyrl *srl, char *prompt)
{
	write(STDOUT_FILENO, "", 0);
	ft_bzero(srl, sizeof(t_spicyrl));
	srl_enable_raw(&srl->original);
	srl_init_hooks();
	srl->buff = srl_new_history();
	srl->prompt = prompt;
	srl->redisplay = true;
}

static char	*srl_exit(t_spicyrl *srl, bool add_history)
{
	char	*rtn;

	if (add_history)
		add_history = false;
	srl_disable_raw(&srl->original);
	rtn = NULL;
	if (srl->buff->size > 0)
		rtn = ft_strdup(srl->buff->saved);
	return (rtn);
}

void	srl_clean_up(void)
{
	srl_del_hooks();
	srl_del_history();
}

char	*spicy_readline(char *prompt, bool add_history)
{
	t_spicyrl	srl;
	long		input;

	srl_init(&srl, prompt);
	while (!srl.exit)
	{
		input = 0;
		srl_redisplay(&srl);
		while (read(STDIN_FILENO, &input, sizeof(long) - 1) > 0)
		{
			if (!srl_check_hooks(&srl, input))
				srl.redisplay = srl_add_buffer(srl.buff,
						(char *)&input, &srl.cursor);
			input = 0;
		}
	}
	write(STDOUT_FILENO, "\r\n", 2);
	return (srl_exit(&srl, add_history));
}

/*char	*tmp_readline(char *prompt, bool add)
{
	char	*line;

	line = readline(prompt);
	if (add && line && line[0])
		add_history(line);
	return (line);
}*/
