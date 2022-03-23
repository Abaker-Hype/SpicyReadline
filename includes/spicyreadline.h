/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spicyreadline.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <HypeSwarm>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 20:14:32 by abaker            #+#    #+#             */
/*   Updated: 2022/03/23 23:27:55 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPICYREADLINE_H
# define SPICYREADLINE_H

# include "libft.h"
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <termios.h>
# include <stdio.h>
# include <fcntl.h>

typedef enum keys{
	K_DEL = 2117294875,
	K_BACKSPACE = 127,
	K_UP = 4283163,
	K_DOWN = 4348699,
	K_LEFT = 4479771,
	K_RIGHT = 4414235,
	K_CTRLBS = 28,
	K_CTRLC = 3,
	K_CTRLD = 4,
	K_TAB = 9
}	t_keys;

typedef struct s_termdata{
	struct termios	term;
	int				flags;
}	t_termdata;

typedef struct s_buff{
	char	*saved;
	int		size;
	int		chars;
	int		insert;
}	t_buff;

typedef struct s_spicyrl{
	t_buff		buffer;
	t_termdata	original;

}	t_spicyrl;

char	*spicy_readline(char *prompt, bool add_history);

void	enable_raw_mode(struct termios *original);
void	disable_raw_mode(struct termios *original);

void	move_cursor(t_buff *buff, t_keys key);
void	add_buffer(t_buff *buff, char *str);
void	del_buffer(t_buff *buff);

#endif