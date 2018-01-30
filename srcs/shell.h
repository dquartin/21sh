/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 10:02:52 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/30 10:34:12 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "../libft/libft.h"
# include <term.h>
# include <termios.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>

typedef struct		s_all
{
	char	*line;
	char	**stock;
	char	**paths;
}					t_all;

typedef struct		s_std
{
	int		stout;
	int		stin;
	int		sterr;
}					t_std;

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
	t_list			*list;
	t_list			*start;
	int				prompt;
	int				i;
	int				x;
}					t_index;

typedef enum		e_type
{
	PIPE, SEMICOLON, REDIRL, REDIRR, DREDIRL, DREDIRR, DATA
}					t_type;

typedef struct		s_tree
{
	struct s_tree	*left;
	struct s_tree	*right;
	t_type			type;
	char			*content;
}					t_tree;

typedef struct		s_truct
{
	t_tree			*tree;
	t_hist			*list;
	t_std			*std;
	struct termios	term;
}					t_truct;

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
# define CTRL_C 3
# define CTRL_D 4
# define TAB 9

char				ft_analyse(char *line);
char				*ctrl_c_move(t_index *index, char buff[]);
char				*dquote(char *line, char c, char ***environ, t_hist *list);
char				*ft_getenv(char **env, char *elem);
char				*ft_move(t_hist **list, char ***environ);
char				*promptchar(char *buffer, t_index **index);
char				**cd_back(char ***environ, char *buf);
char				**cd_less(char ***environ, char *buff);
char				**cd_p(char ***environ, char *option, char *path,
					char *buff);
char				**cpy_environ(char **av, char **env);
char				**ft_cd(char *path, char *option, char ***environ);
char				**ft_envcpy(char **env);
char				**ft_splitwhite(char const *s);
char				**ft_unsetenv(char *name, char **environ);
char				**set_environ(void);
char				**split_line(char *line);
char				**split_paths(char **paths, char **environ);
char				**split_semicolon(char *line);

int					advanced_red(char ***stock, int i);
int					check_redir(char **arr, char ***env);
int					closing_redir(char **arr, int i);
int					env_len(char **env);
int					ft_putin(int c);
int					go_to_left(int i);
int					handle_data(t_tree *tree, char ***paths, char ***stock,
					char ***environ);
int					other(char **arr, int i, int *fd);
int					othercase(char ***stock, int i);
int					reverse_bis(char **arr, int i, int *fd);
int					shift_up(int i, t_index *index, struct winsize size);

t_hist				*ft_lstcreate(void const *content);
t_hist				*get_history(char **environ);
t_hist				*init_list(char ***environ, char **av, char **env,
					t_std **std);
t_hist				*stock_history(char *line, t_hist *list);
t_tree				*new_parser(char *line);

t_list				*get_bin_entry(void);
t_list				*get_entry(char *path);
t_list				*get_executable_v2(char *path);
t_list				*get_executable(char *path);
t_list				*get_matching_entry(char *path, t_list *entry);

void				alloc(t_all **all, t_truct **str, char ***environ);
void				back_history(t_index **index, t_hist **list);
void				begin(t_index **index);
void				call_delchar(t_index **index);
void				call_fork(char **stock, char **paths, char **environ);
void				call_function(char **stock, char **paths,
					char ***environ, int quote);
void				call_major(char ***paths, char ***stock, t_tree **tree,
					char ***environ);
void				cd(char ***environ, char **path, char *option, char *buff);
void				cd_l(char ***environ, char **path, char *option);
void				close_all(char **arr, int i);
void				completion(t_index **index);
void				complete_line(t_index **index);
void				copy_char(t_index **index, char **stock);
void				copy_n_paste(t_index **index);
void				copy_select(char *stock, t_index **index);
void				create_history(char ***environ);
void				ctrl_c(int i);
void				ctrl_c_bis(int i);
void				ctrl_d(t_index *index, char buff[]);
void				delchar(t_index **index);
void				delete_lines(char ***stock);
void				delinline(t_index **index);
void				del_opt_path(char **option, char **path);
void				del_paths_n_stock(char ***paths, char ***stock);
void				del_quotes(char **new, char **prompt);
void				double_redir(char **arr, int i, int fd);
void				end(t_index **index, struct winsize size);
void				env_null(char ***environ);
void				error_case1(char *path);
void				exec_path(char **stock, char **environ);
void				ft_echo(char **stock, int quote);
void				ft_env(char ***environ, char **stock, char **paths);
void				ft_lst_add_end(t_list **alst, t_list *new);
void				ft_lstaddnew(t_hist **alst, t_hist *new);
void				ft_lst_clear(t_list **begin_list);
void				ft_major(t_tree *tree, char ***paths, char ***stock,
					char ***environ);
void				ft_putstrin(char *str);
void				ft_setenv(char *name, char *value, char ***environ);
void				free_index(t_index **index);
void				free_tree(t_tree **tree);
void				go_to_right(t_index **index, struct winsize size);
void				handle_semicolon(t_tree *tree, char ***path, char ***stock,
					char ***environ);
void				handle_pipe(t_tree *tree, char ***stock, char ***paths,
					char ***environ);
void				handle_segv(pid_t fath);
void				heredoc(char ***stock, int i, char ***environ);
void				history(t_index **index, t_hist **list);
void				home(t_index **index, struct winsize size);
void				if_exit(char **environ, char ***paths, t_hist **list);
void				init_line(char **line, char ***environ, t_hist **list,
					t_tree **tree);
void				init_std(t_std **std);
void				insertchar(t_index **index, char *buffer);
void				main_check_line(t_all **all, char ***environ,
					t_truct **str);
void				open_file(char **arr, int i, int fd);
void				open_files(char **arr, int i, int fd);
void				other_case(t_index **index, char *buffer,
					struct winsize size);
void				parse(t_tree **tree, char *line, int size);
void				parse_quote(char ***stock);
void				print_prompt(char ***environ);
void				read_script(char **av, char **env);
void				save_history(t_hist *list, char **environ);
void				set_null(t_tree **tree, t_all **all, t_hist **list, int ac);
void				set_signal_father(pid_t father);
void				set_std(t_std *std, char **line, char ***environ);
void				set_terminal(t_all *all, t_truct *str, char ***environ);
void				select_mode(t_index **index);
void				shift_down(t_index **index);
void				shift_left(t_index **index);
void				shift_right(t_index **index);

#endif
