/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redisplay.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <abaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:04:42 by abaker            #+#    #+#             */
/*   Updated: 2022/07/11 16:26:28 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spicyreadline.h"

#define HIDE "\e[25l"
#define SHOW "\e[25h"

static void	srl_cursor_start(t_srl *srl)
{
	char	*print;
	int		i;

	i = 1;
	while (i * srl->term.width <= srl->banner.promptlen + srl->lastpos + 2)
		i++;
	if (srl->blank)
		i--;
	print = ft_strdup(HIDE);
	if (i == 0)
		print = ft_strjoinfree(print, "\r\e[0J", true, false);
	else
	{
		print = ft_strjoinfree(print, "\e[", true, false);
		print = ft_strjoinfree(print, ft_itoa(i), true, true);
		print = ft_strjoinfree(print, "F\e[0J", true, false);
	}
	ft_putstr_fd(print, srl->term.rawfd);
	free(print);
	srl->lastpos = srl->buffer->pos;
}

static void	srl_cursor_set(t_term *term, t_buff *buffer, int promtlen)
{
	char	*print;
	int		c;
	int		r;

	print = ft_strdup("\e[");
	c = (buffer->pos + promtlen) % term->width;
	r = (buffer->chars + promtlen) / term->width - (buffer->pos + promtlen)
		/ term->width;
	if (buffer->chars - buffer->pos)
	{
		if ((buffer->chars + promtlen) % term->width == 0)
			r--;
		if (r)
		{
			print = ft_strjoinfree(print, ft_itoa(r), true, true);
			print = ft_strjoinfree(print, "F\e[", true, false);
		}
		print = ft_strjoinfree(print, ft_itoa(c + 1), true, true);
		print = ft_strjoinfree(print, "G", true, false);
	}
	else if (c == 0)
		print = ft_strjoinfree(print, "E", true, false);
	print = ft_strjoinfree(print, SHOW, true, false);
	ft_putstr_fd(print, term->rawfd);
	free(print);
}

void	srl_redisplay(t_srl *srl)
{
	if (!(srl_update_term_width(&srl->term) || srl->buffer->update))
		return ;
	srl_update_banner(srl);
	srl_cursor_start(srl);
	write(srl->term.rawfd, srl->banner.banner, srl->banner.size);
	write(srl->term.rawfd, srl->buffer->buff, srl->buffer->size);
	srl_cursor_set(&srl->term, srl->buffer, srl->banner.promptlen + 2);
	srl->buffer->update = false;
	srl->term.update = false;
}
