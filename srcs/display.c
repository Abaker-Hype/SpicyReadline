/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <abaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:55:42 by abaker            #+#    #+#             */
/*   Updated: 2022/06/10 17:39:14 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spicyreadline.h"

static void	srl_clear_display(t_termdata *term)
{
	t_cursor	start;

	write(term->rawfd, "\e[25l", 6);
	ft_bzero(&start, sizeof(start));
	srl_set_cursor(start, term);
	write(term->rawfd, "\e[0J", 5);
}

void	srl_redisplay(t_spicyrl *srl)
{
	char	*out;
	bool	update;

	if (!srl->redisplay)
		return ;
	update = srl_update_term_width(&srl->term) || srl->banner.banner == NULL;
	if (!srl->banner.banner)
		srl_gen_banner(&srl->banner, &srl->term);
	out = ft_strdup(srl->banner.banner);
	if (srl->buff->saved)
		out = ft_strjoinfree(out, srl->buff->saved, true, false);
	srl_clear_display(&srl->term);
	write(STDERR_FILENO, out, ft_strlen(out));
	srl->term.cursor = srl_calc_cursor_pos(srl->banner.size,
			srl->buff->chars, &srl->term);
	srl_set_cursor(srl_calc_cursor_pos(srl->banner.size,
			srl->buff->cursor, &srl->term), &srl->term);
	free(out);
	srl->redisplay = false;
}
