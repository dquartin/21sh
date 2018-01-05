/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 10:02:52 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/05 16:37:46 by dquartin         ###   ########.fr       */
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

char                *ft_getenv(char **env, char *elem);
char                *ft_move(t_hist **list, char ***environ);
char                *promptchar(char *buffer, char *line, int *x);
char                **ft_cd(char *path, char ***environ);
char                **ft_envcpy(char **env);
char                **ft_splitwhite(char const *s);
char                **ft_unsetenv(char *name, char **environ);
char                **split_line(char *line);
char                **split_paths(char **paths, char **environ);
char                **split_semicolon(char *line);

int                 back_history(int i, int *x, char **line, t_hist **list);
int                 begin(int i, int *x, int prompt, char *line);
int                 call_delchar(int i, int *x, char *line);
int                 end(int i, int x, struct winsize size, char **environ);
int                 env_len(char **env);
int                 ft_putin(int c);
int                 go_to_right(int i, int x, int prompt, struct winsize size);
int                 go_to_left(int i);
int                 history(int i, int *x, char **line, t_hist **list);
int                 home(int i, int x, struct winsize size, char **environ);
int                 other_case(char **line, int i, int *x, char *buffer);
int                 shift_down(int i, int *x, int prompt, char **environ);
int                 shift_left(int i, char *line);
int                 shift_right(int i, int x, int prompt, char *line);
int                 shift_up(int i, struct winsize size);

t_hist              *ft_lstcreate(void const *content);
t_hist              *stock_history(char *line, t_hist *list);

void                call_fork(char **stock, char **paths, char **environ);
void                copy_char(char *line, int *i, char **stock);
void                copy_n_paste(char **line, int *i, int *x, char ***environ);
void                copy_select(char *stock, int *x, char ***environ);
void                delchar(int i, int prompt, char *line);
void                delete_lines(char **stock);
void                delinline(int i, char **line);
void                exec_path(char **stock, char **environ);
void                ft_echo(char **stock);
void                ft_env(char **env);
void                ft_lstaddnew(t_hist **alst, t_hist *new);
void                ft_putstrin(char *str);
void                ft_setenv(char *name, char *value, char ***environ);
void                insertchar(int i, char **line, char *buffer);
void                insert_char(int i, int prompt, char *line);
void                select_mode(char *line, int *i, int *x, char ***environ);

#endif
