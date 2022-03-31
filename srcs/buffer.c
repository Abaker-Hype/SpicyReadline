/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <abaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 19:24:01 by abaker            #+#    #+#             */
/*   Updated: 2022/03/30 15:20:43 by abaker           ###   ########.fr       */
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

static int	srl_update_chars(t_buff *buff, char *str, int pos)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_charsize(str[i++]) > 0)
		{
			buff->chars++;
			pos++;
		}
	}
	return (pos);
}

int	srl_add_buffer(t_buff *buff, char *str, int pos)
{
	char	*tmp;
	int		size;

	size = buff->size + ft_strlen(str) + 1;
	tmp = ft_calloc(size, sizeof(char));
	if (!tmp)
		return (pos);
	ft_strlcat(tmp, buff->saved, srl_char_pos(buff->saved, pos) + 1);
	ft_strlcat(tmp, str, size);
	ft_strlcat(tmp, &buff->saved[srl_char_pos(buff->saved, pos)], size);
	if (buff->saved)
		free(buff->saved);
	buff->saved = tmp;
	buff->size = size - 1;
	return (srl_update_chars(buff, str, pos));
}

int	srl_del_buffer(t_buff *buff, int pos)
{
	char	*tmp;
	int		size;

	if (pos == 0 || pos > buff->chars)
		return ;
	size = buff->size
		- ft_charsize(buff->saved[srl_char_pos(buff->saved, pos)]);
	tmp = ft_calloc(size + 1, sizeof(char));
	if (!tmp)
		return (pos);
	ft_strlcat(tmp, buff->saved, srl_char_pos(buff->saved, pos - 1) + 1);
	ft_strlcat(tmp, &buff->saved[srl_char_pos(buff->saved, pos)], size + 1);
	if (buff->saved)
		free(buff->saved);
	buff->saved = tmp;
	buff->size = size;
	buff->chars--;
	pos--;
	return (pos);
}
