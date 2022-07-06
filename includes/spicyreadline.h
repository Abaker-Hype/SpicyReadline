/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spicyreadline.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaker <abaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 20:14:32 by abaker            #+#    #+#             */
/*   Updated: 2022/06/24 15:08:49 by abaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPICYREADLINE_H
# define SPICYREADLINE_H

# include "libft.h"
# include <termios.h>

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
	K_ENTER = '\r',
	K_END = 4610843,
	K_HOME = 4741915
}	t_keys;

typedef struct s_pos{
	int	col;
	int	row;
}	t_pos;

typedef struct s_term{
	int				rawfd;
	struct termios	orig;
	int				width;
	bool			update;
}	t_term;

typedef struct s_buff	t_buff;
struct s_buff{
	char	*buff;
	int		size;
	int		chars;
	int		ins;
	int		pos;
	bool	update;
	t_buff	*prev;
	t_buff	*next;
};

typedef struct s_banner{
	char	*banner;
	char	*prompt;
	char	*user;
	char	*pwd;
	int		size;
	int		promptlen;
	int		userlen;
	int		pwdlen;
}	t_banner;


typedef struct s_srl
{
	t_term		term;
	t_buff		*buffer;
	t_banner	banner;
	bool		exit;
	bool		blank;
}	t_srl;

//spicyreadline.c
char	*spicy_readline(char *prompt, char *user, char *pwd, bool blank);
void	srl_clean_up(void);

//terminal.c
void	srl_init_term(t_term *term, bool nl);
void	srl_disable_raw(t_term *term);
bool	srl_update_term_width(t_term *term);

//hooks.c
void	srl_del_hooks(void);
bool	srl_check_hooks(t_srl *srl, long key);

//hookfunc.c
void	srl_hook_exit(t_keys key, t_srl *srl);
void	srl_hook_del(t_keys key, t_srl *srl);
void	srl_hook_cursor(t_keys key, t_srl *srl);
void	srl_hook_history(t_keys key, t_srl *srl);

//history.c
void	srl_add_history(t_buff *buff);
void	srl_clone_history(t_buff *new);
void	srl_clear_history(t_buff *buff);

//buffer.c
t_buff	*srl_new_buffer(bool blank);
void	srl_add_buff(t_buff *buff, char *str);
void	srl_rmv_buff(t_buff *buff, bool left);
void	srl_update_buff_ins(t_buff *buff, bool left, bool full);

//redisplay.c
void	srl_redisplay(t_srl *srl);

//banner.c
void	srl_update_banner(t_srl *srl);
#endif