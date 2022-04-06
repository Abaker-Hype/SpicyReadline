/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spicyreadline.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <HypeSwarm>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 20:14:32 by abaker            #+#    #+#             */
/*   Updated: 2022/04/06 22:58:06 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPICYREADLINE_H
# define SPICYREADLINE_H

# include "libft.h"
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <termios.h>
# include <fcntl.h>
# include <sys/ioctl.h>

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

typedef struct s_cursor{
	int	row;
	int	col;
}	t_cursor;

typedef struct s_termdata{
	struct termios	original;
	int				flags;
	struct winsize	win;
	bool			changed;
}	t_termdata;

typedef struct s_buff{
	char			*saved;
	int				size;
	int				chars;
	struct s_buff	*prev;
	struct s_buff	*next;
}	t_buff;

typedef struct s_spicyrl	t_spicyrl;

typedef struct s_hooks{
	t_keys			key;
	void			(*f)(t_keys, struct s_spicyrl *);
	struct s_hooks	*next;
}	t_hooks;

struct s_spicyrl{
	t_termdata	term;
	t_buff		*buff;
	t_cursor	cursor_init;
	char		*prompt;
	char		*pwd;
	char		*user;
	int			cursor;
	bool		hist;
	bool		redisplay;
	bool		exit;
};

typedef struct s_srl_settings{
}	t_srl_settings;

char		*spicy_readline(char *prompt, char *user, char *pwd, bool hist);
void		srl_clean_up(void);

void		srl_enable_raw(t_termdata	*term);
void		srl_disable_raw(t_termdata	*term);

t_cursor	srl_get_cursor_pos(void);
void		srl_set_cursor_pos(t_cursor pos);
void		srl_get_term_width(t_termdata *term);

void		srl_init_hooks(void);
void		srl_del_hooks(void);
bool		srl_check_hooks(t_spicyrl *rl, long key);

t_buff		*srl_new_history(void);
void		srl_del_history(t_buff *del);
void		srl_update_history(t_buff *buff, bool hist);

void		srl_hook_return(t_keys key, t_spicyrl *srl);
void		srl_hook_del(t_keys key, t_spicyrl *srl);
void		srl_hook_cursor(t_keys key, t_spicyrl *srl);
void		srl_hook_history(t_keys key, t_spicyrl *srl);

bool		srl_add_buffer(t_buff *buff, char *str, int *cursor);
bool		srl_rmv_buffer(t_buff *buff, int *cursor);

void		srl_redisplay(t_spicyrl *srl);
char		*srl_banner(t_spicyrl *srl);

#endif