/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spicyreadline.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <abaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 20:14:32 by abaker            #+#    #+#             */
/*   Updated: 2022/03/30 13:57:49 by abaker           ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>

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
	struct termios	original;
	int				flags;
}	t_termdata;

typedef struct s_buff{
	char	*saved;
	int		size;
	int		chars;
}	t_buff;

typedef struct s_history{
	struct s_history	*prev;
	struct s_history	*next;
	t_buff				buff;
}	t_history;

typedef struct s_spicyrl	t_spicyrl;

typedef struct s_hooks{
	t_keys			key;
	void			(*f)(int key, struct s_spicyrl *rl);
	struct s_hooks	*next;
}	t_hooks;

struct s_spicyrl{
	t_termdata	original;
	t_history	*hist;
	t_hooks		*hooks;
	int			cursor;
};

char	*spicy_readline(char *prompt, bool add_history);
char	*tmp_readline(char *prompt, bool add_history);

void	srl_enable_raw(struct termios *original);
void	srl_disable_raw(struct termios *original);

void	srl_init_hooks(t_hooks **hooks);
void	srl_del_hooks(t_hooks **hooks);
bool	srl_check_hooks(t_spicyrl *rl, int key);

#endif