/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <abaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 13:35:56 by abaker            #+#    #+#             */
/*   Updated: 2022/06/24 11:13:01 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spicyreadline.h"

t_buff	*srl_new_buffer(bool blank)
{
	t_buff	*new;

	new = ft_calloc(1, sizeof(*new));
	if (!new)
		return (NULL);
	if (!blank)
		srl_clone_history(new);
	return (new);
}

void	srl_add_buff(t_buff *buff, char *str)
{
	char	*new;
	int		len;

	len = ft_strlen(str);
	new = ft_calloc(buff->size + len + 1, sizeof (*new));
	if (!new)
		return ;
	buff->size += len;
	ft_strlcpy(new, buff->buff, buff->ins + 1);
	ft_strlcpy(&new[buff->ins], str, buff->size + 1);
	if (buff->buff)
	{
		ft_strlcpy(&new[buff->ins + len], &buff->buff[buff->ins],
			buff->size + 1);
		free(buff->buff);
	}
	buff->buff = new;
	buff->chars += ft_charcount(str);
	buff->ins += len;
	buff->pos += ft_charcount(str);
	buff->update = true;
}

void	srl_rmv_buff(t_buff *buff, bool left)
{
	int		charsize;

	if ((left && buff->pos == 0) || (!left && buff->pos == buff->chars))
		return ;
	if (left)
		srl_update_buff_ins(buff, true, false);
	charsize = ft_charsize(buff->buff[buff->ins]);
	buff->size -= charsize;
	ft_memmove(&buff->buff[buff->ins], &buff->buff[buff->ins + charsize], buff->size - buff->ins);
	ft_bzero(&buff->buff[buff->size], charsize);
	buff->chars--;
	buff->update = true;
}

void	srl_update_buff_ins(t_buff *buff, bool left, bool end)
{
	int	offset;

	offset = 1;
	if (left)
		offset = -1;
	if (buff->ins + offset < 0 || buff->ins + offset > buff->size)
		return ;
	if (end)
	{
		buff->ins = !left * buff->size;
		buff->pos = !left * buff->chars;
	}
	else
	{
		buff->ins += offset;
		buff->pos += offset;
		while (ft_charsize(buff->buff[buff->ins]) == -1)
			buff->ins += offset;
	}
	buff->update = true;
}
