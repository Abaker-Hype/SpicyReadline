/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <HypeSwarm>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 19:24:01 by abaker            #+#    #+#             */
/*   Updated: 2022/03/24 09:13:30 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spicyreadline.h"

void	move_cursor(t_buff *buff, t_keys key)
{
	if ((key == K_LEFT && buff->insert == 0)
		|| (key == K_RIGHT && buff->insert == buff->chars))
		return ;
	write(STDOUT_FILENO, &key, 3);
	buff->insert += 1 + (-2 * key == K_LEFT);
}

void	add_buffer(t_buff *buff, char *str)
{
	char	*tmp;
	int		size;

	size = buff->size + ft_strlen(str);
	tmp = ft_calloc(size + 1, sizeof(char));
	if (!tmp)
		return ;
	buff->insert += ft_strlen(str);
}

void	del_buffer(t_buff *buff)
{
	char	*tmp;

	tmp = buff->saved;
	if (tmp)
		return ;
}
