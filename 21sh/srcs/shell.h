/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 10:02:52 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/07 12:40:38 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "../libft/libft.h"
# include <term.h>
# include <termios.h>
# include <signal.h>
# include <sys/ioctl.h>

typedef struct		s_hist
{
	char			*histo;
	struct s_hist	*next;
	struct s_hist	*prev;
}					t_hist;

typedef struct		s_index
{
	char			*line;
	char			**environ;
	int				prompt;
	int				i;
	int				x;
}					t_index;

# define RIGHT_ARROW 185
# define LEFT_ARROW 186
# define UP_ARROW 183
# define DOWN_ARROW 184
# define HOME 190
# define END	188
# define SHIFT_RIGHT 343
# define SHIFT_LEFT 344
# define SHIFT_UP 341
# define SHIFT_DOWN 342
# define ALT_C -150
# define ALT_V -252
# define ALT_S -158
# define DEL 127
# define ENTER 10
# define ESCAPE 27

char				*ft_getenv(char **env, char *elem);
char				*ft_move(t_hist **list, char ***environ);
char				*promptchar(char *buffer, t_index **index);
char				**ft_cd(char *path, char ***environ);
char				**ft_envcpy(char **env);
char				**ft_splitwhite(char const *s);
char				**ft_unsetenv(char *name, char **environ);
char				**split_line(char *line);
char				**split_paths(char **paths, char **environ);
char				**split_semicolon(char *line);

int					env_len(char **env);
int					ft_putin(int c);
int					go_to_left(int i);
int					shift_up(int i, struct winsize size);

t_hist				*ft_lstcreate(void const *content);
t_hist				*stock_history(char *line, t_hist *list);

void				back_history(t_index **index, t_hist **list);
void				begin(t_index **index);
void				call_delchar(t_index **index);
void				call_fork(char **stock, char **paths, char **environ);
void				copy_char(t_index **index, char **stock);
void				copy_n_paste(t_index **index);
void				copy_select(char *stock, t_index **index);
void				delchar(t_index **index);
void				delete_lines(char **stock);
void				delinline(t_index **index);
void				end(t_index **index, struct winsize size);
void				exec_path(char **stock, char **environ);
void				ft_echo(char **stock);
void				ft_env(char **env);
void				ft_lstaddnew(t_hist **alst, t_hist *new);
void				ft_putstrin(char *str);
void				ft_setenv(char *name, char *value, char ***environ);
void				go_to_right(t_index **index, struct winsize size);
void				history(t_index **index, t_hist **list);
void				home(t_index **index, struct winsize size);
void				insertchar(t_index **index, char *buffer);
void				other_case(t_index **index, char *buffer);
void				select_mode(t_index **index);
void				shift_down(t_index **index);
void				shift_left(t_index **index);
void				shift_right(t_index **index);

#endif
