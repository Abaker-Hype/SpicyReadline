/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redisplay.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <abaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:04:42 by abaker            #+#    #+#             */
/*   Updated: 2022/07/12 14:49:57 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spicyreadline.h"

#define HIDE "\e[25l"
#define SHOW "\e[25h"
#define CURSORSIZE 25

static void	srl_cursor_start(t_srl *srl)
{
	char	*print;
	char	*num;
	int		i;

	i = 1;
	while (i * srl->term.width <= srl->banner.promptlen + srl->lastpos + 2)
		i++;
	if (srl->blank)
		i--;
	print = ft_memcpy(ft_calloc(CURSORSIZE, sizeof(*print)), HIDE, CURSORSIZE);
	if (i == 0)
		ft_strlcat(print, "\r\e[0J", CURSORSIZE);
	else
	{
		ft_strlcat(print, "\e[", CURSORSIZE);
		num = ft_itoa(i);
		ft_strlcat(print, num, CURSORSIZE);
		free(num);
		ft_strlcat(print, "F\e[0J", CURSORSIZE);
	}
	ft_putstr_fd(print, srl->term.rawfd);
	free(print);
	srl->lastpos = srl->buffer->pos;
}

static void	srl_cursor_str(char *dst, t_term *term, t_buff *buff, int plen)
{
	char	*num;
	int		i;

	i = (buff->chars + plen) / term->width - (buff->pos + plen) / term->width
		- ((buff->chars + plen) % term->width == 0);
	if (i)
	{
		num = ft_itoa(i);
		ft_strlcat(dst, num, CURSORSIZE);
		ft_strlcat(dst, "F\e[", CURSORSIZE);
		free(num);
	}
	num = ft_itoa(((buff->pos + plen) % term->width) + 1);
	ft_strlcat(dst, num, CURSORSIZE);
	ft_strlcat(dst, "G", CURSORSIZE);
	free(num);
}

static void	srl_cursor_set(t_term *term, t_buff *buffer, int promptlen)
{
	char	*print;

	print = ft_memcpy(ft_calloc(CURSORSIZE, sizeof(*print)), "\e[", CURSORSIZE);
	if (buffer->chars - buffer->pos)
		srl_cursor_str(print, term, buffer, promptlen);
	else if ((buffer->pos + promptlen) % term->width == 0)
		ft_strlcat(print, "E", CURSORSIZE);
	ft_strlcat(print, SHOW, CURSORSIZE);
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
