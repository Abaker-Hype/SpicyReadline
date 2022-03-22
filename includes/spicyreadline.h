/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spicyreadline.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <HypeSwarm>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 20:14:32 by abaker            #+#    #+#             */
/*   Updated: 2022/03/22 23:09:34 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPICYREADLINE_H
# define SPICYREADLINE_H

# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <termios.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <strings.h>

typedef struct s_termdata{
	struct termios	term;
	int				flags;
}	t_termdata;

typedef struct s_buff{
	char	*saved;
	int		chars;
	int		inputpos;
}	t_buff;

char	*spicy_readline(char *prompt, bool add_history);

void	enable_raw_mode(struct termios *original);
void	disable_raw_mode(struct termios *original);

#endif