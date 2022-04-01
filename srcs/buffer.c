/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <abaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 19:24:01 by abaker            #+#    #+#             */
/*   Updated: 2022/04/01 13:49:58 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spicyreadline.h"

static int	srl_char_pos(char *str, int pos)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	if (!str)
		return (0);
	while (str[i] && c++ != pos)
		i += ft_charsize(str[i]);
	return (i);
}

bool	srl_add_buffer(t_buff *buff, char *str, int *cursor)
{
	char	*tmp;
	int		size;

	size = buff->size + ft_strlen(str) + 1;
	tmp = ft_calloc(size, sizeof(char));
	if (!tmp)
		return (false);
	ft_strlcat(tmp, buff->saved, srl_char_pos(buff->saved, *cursor) + 1);
	ft_strlcat(tmp, str, size);
	ft_strlcat(tmp, &buff->saved[srl_char_pos(buff->saved, *cursor)], size);
	if (buff->saved)
		free(buff->saved);
	buff->saved = tmp;
	buff->size = size - 1;
	size = ft_charcount(str);
	buff->chars += size;
	*cursor += size;
	return (true);
}

bool	srl_rmv_buffer(t_buff *buff, int *cursor)
{
	char	*tmp;
	int		size;

	size = buff->size
		- ft_charsize(buff->saved[srl_char_pos(buff->saved, *cursor)]);
	tmp = ft_calloc(size + 1, sizeof(char));
	if (!tmp)
		return (false);
	ft_strlcat(tmp, buff->saved, srl_char_pos(buff->saved, *cursor - 1) + 1);
	ft_strlcat(tmp, &buff->saved[srl_char_pos(buff->saved, *cursor)], size + 1);
	if (buff->saved)
		free(buff->saved);
	buff->saved = tmp;
	buff->size = size;
	buff->chars--;
	(*cursor)--;
	return (true);
}
