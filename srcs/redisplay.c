/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redisplay.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <abaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:04:42 by abaker            #+#    #+#             */
/*   Updated: 2022/06/24 15:08:07 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spicyreadline.h"

void	srl_redisplay(t_srl *srl)
{
	char	*cursor;
	char	*num;

	if (!(srl_update_term_width(&srl->term) || srl->buffer->update))
		return ;
	srl_update_banner(srl);
	if (srl->blank)
		ft_putstr_fd("\e[25l\r\e[0J", srl->term.rawfd);
	else
		ft_putstr_fd("\e[25l\e[1F\e[0J", srl->term.rawfd);
	ft_putstr_fd(srl->banner.banner, srl->term.rawfd);
	ft_putstr_fd(srl->buffer->buff, srl->term.rawfd);
	cursor = ft_calloc(15, sizeof(*cursor));
	if (srl->buffer->pos < srl->buffer->chars)
	{
		num = ft_itoa(srl->buffer->chars - srl->buffer->pos);
		ft_strlcat(cursor, "\e[", 15);
		ft_strlcat(cursor, num, 15);
		ft_strlcat(cursor, "D", 15);
		free(num);
	}
	ft_strlcat(cursor, "\e[25h", 10);
	ft_putstr_fd(cursor, srl->term.rawfd);
	free(cursor);
	srl->buffer->update = false;
	srl->term.update = false;
}
