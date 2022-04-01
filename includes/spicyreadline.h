/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spicyreadline.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <abaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 20:14:32 by abaker            #+#    #+#             */
/*   Updated: 2022/04/01 10:50:05 by abaker           ###   ########.fr       */
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
	K_DELF = 2117294875,
	K_DEL = 127,
	K_ESC = 27,
	K_UP = 4283163,
	K_DOWN = 4348699,
	K_LEFT = 4479771,
	K_RIGHT = 4414235,
	K_CTRLBS = 28,
	K_CTRLC = 3,
	K_CTRLD = 4,
	K_TAB = '\t',
	K_ENTER = '\r'
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
	t_buff				*buff;
	struct s_history	*prev;
	struct s_history	*next;
}	t_history;

typedef struct s_spicyrl	t_spicyrl;

typedef struct s_hooks{
	t_keys			key;
	void			(*f)(t_keys, struct s_spicyrl *);
	struct s_hooks	*next;
}	t_hooks;

struct s_spicyrl{
	t_termdata	original;
	t_buff		buff;
	char		*prompt;
	int			cursor;
	bool		redisplay;
	bool		exit;
};

char	*spicy_readline(char *prompt, bool add_history);
char	*tmp_readline(char *prompt, bool add_history);

void	srl_enable_raw(t_termdata	*term);
void	srl_disable_raw(t_termdata	*term);

void	srl_init_hooks(void);
void	srl_del_hooks(void);
bool	srl_check_hooks(t_spicyrl *rl, long key);

void	srl_hook_return(t_keys key, t_spicyrl *srl);
void	srl_hook_del(t_keys key, t_spicyrl *srl);
void	srl_hook_cursor(t_keys key, t_spicyrl *srl);

bool	srl_add_buffer(t_buff *buff, char *str, int *cursor);
bool	srl_rmv_buffer(t_buff *buff, int *cursor);

void	srl_redisplay(t_spicyrl *srl);

#endif