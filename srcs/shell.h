/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 13:44:49 by hlely             #+#    #+#             */
/*   Updated: 2018/03/01 13:38:16 by dquartin         ###   ########.fr       */
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

/*
** DEFINE TERMCAPS
*/

# define GO(x) tputs(tgetstr(x, NULL), 0, ft_putin)
# define LEFT "le"
# define RIGHT "nd"
# define UP "up"
# define DOWN "do"
# define SUP "dc"
# define CLR "cd"

/*
** DEFINE EDITION DE LIGNE
*/

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

/*
** DEFINE FONCTIONS
*/

# define SAVETERM tcsetattr(0, TCSANOW, &g_save_attr)
# define SETPROMPT(x) ft_setenv("PROMPT", (x), environ)
# define CHECKMC(x) if (!(x)) return (NULL)
# define CHECKNEXT ((*index)->line[(*index)->i + 1] > 32)
# define CHECKCHAR ((*index)->line[(*index)->i] > 32)
# define CHECKSIZE(x) ((x) + (*index)->prompt) % size.ws_col
# define ERROR(x) ft_puterror(x)
# define TRUNC O_RDWR | O_TRUNC | O_CREAT, 0644
# define APPEND O_RDWR | O_APPEND | O_CREAT, 0644
# define PARSE_ERROR i - 1 < 0 || arr[i + 1] == NULL

/*
** DEFINE PARSING
*/

# define SIMPLE_RED '>'
# define REVERSE_RED '<'
# define LESS '-'
# define AND '&'
# define SEMI ';'
# define TUBE '|'

/*
** GLOBALES
*/

int					g_nbproc;
int					g_status;
int					g_heredoc;
struct termios		g_save_attr;

/*
** STRUCTURES
*/

typedef struct		s_int
{
	int				index;
	struct s_int	*next;
}					t_int;

typedef struct		s_alias
{
	char			*name;
	char			*value;
	struct s_alias	*next;
}					t_alias;

t_alias				*g_alias;

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

t_hist				*g_list;

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
	PIPE, SEMICOLON, ET, OU, DATA
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
	t_std			*std;
	struct termios	term;
}					t_truct;

char				ft_analyse(char *line);
char				*ctrl_c_move(t_index *index, char buff[]);
char				*dquote(char *line, char c, char ***environ, t_hist *list);
char				**ft_cd_bis(char *path, char *option, char ***environ,
					char*buff);
char				*ft_getenv(char **env, char *elem);
char				*ft_move(t_hist **list, char ***environ);
char				*promptchar(char *buffer, t_index **index);
char				**cd_back(char ***environ);
char				**cd_less(char ***environ, char *buff);
char				**cd_l(char ***environ, char **path, char *option);
char				**cd_p(char ***environ, char *option, char *buff);
char				**cpy_environ(char **av, char **env);
char				**ft_cd(char **stock, char ***environ);
char				**ft_envcpy(char **env);
char				**ft_splitwhite(char const *s);
char				**ft_unsetenv(char *name, char **environ);
char				**set_environ(void);
char				**split_line(char *line);
char				**split_paths(char **paths, char **environ);
char				**split_semicolon(char *line);

int					advanced_red(char ***stock, int i);
int					check_existing_alias(t_alias *alias, char *name);
int					check_hist_env(char **environ);
int					check_quote(char *line, char c, int *j, int size);
int					check_redir(char **arr, char ***env);
int					closing_redir(char **arr, int i);
int					error_environ(char **environ, char *path, char *option);
int					env_len(char **env);
int					ft_lst_size(t_hist *list);
int					ft_putin(int c);
int					go_to_left(int i);
int					handle_data(t_tree *tree, char ***paths, char ***stock,
					char ***environ);
int					other(char **arr, int i, int *fd);
int					othercase(char ***stock, int i);
int					return_cd_bis(char *path, char *option, char ***environ,
					char buff[]);
int					return_usage(char *path, char *option);
int					return_dot(char *path, char *option);
int					reverse_bis(char **arr, int i, int *fd);
int					shift_up(int i, t_index *index, struct winsize size);

t_alias				*init_alias(char **env);
t_alias				*new_node_alias(t_alias *alias, char *line);

t_hist				*ft_lstcreate(void const *content);
t_hist				*get_history(char **environ);
t_hist				*init_list(char ***environ, char **av, char **env,
					t_std **std);
t_hist				*stock_history(char *line, t_hist *list);

t_tree				*create_node(void);
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
void				call_handle(t_tree *tree, char ***paths, char ***stock,
					char ***environ);
void				call_major(char ***paths, char ***stock, t_tree **tree,
					char ***environ);
void				cd(char ***environ, char **path, char *buff);
void				cd_l_bis(char ***environ, char **path, char *buff);
void				check_cd(char *path, char ***environ,
					char *buff);
void				close_all(char **arr, int i);
void				cmd_history(char **stock);
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
void				delete_alias(t_alias *alias, char **env);
void				delete_lines(char ***stock);
void				delete_tree(t_tree **tree);
void				delinline(t_index **index);
void				del_opt_path(char **option, char **path);
void				del_paths_n_stock(char ***paths, char ***stock);
void				del_quotes(char **new, char **prompt);
void				double_redir(char **arr, int i, int fd);
void				end(t_index **index, struct winsize size);
void				env_null(char ***environ);
void				error_case1(char *path);
void				error_case2(char *path);
void				error_unsetenv(void);
void				exec_path(char **stock, char **environ);
void				exit_atty(void);
void				ft_echo(char **stock, int quote);
void				ft_env(char ***environ, char **stock, char **paths);
void				ft_env_launch(char **stock, char ***environ,
					char **paths);
void				ft_hst_clear(t_hist **list);
void				ft_lst_add_end(t_list **alst, t_list *new);
void				ft_lstaddnew(t_hist **alst, t_hist *new);
void				ft_lst_clear(t_list **begin_list);
void				ft_major(t_tree *tree, char ***paths, char ***stock,
					char ***environ);
void				ft_print_env(char ***environ);
void				ft_putstrin(char *str);
void				ft_setenv(char *name, char *value, char ***environ);
void				free_index(t_index **index);
void				free_tree(t_tree **tree);
char				**get_shlvl(char **environ);
void				go_to_right(t_index **index, struct winsize size);
void				handle_alias(char **stock);
void				handle_and(t_tree *tree, char ***paths, char ***stock,
					char ***environ);
void				handle_or(t_tree *tree, char ***paths, char ***stock,
					char ***environ);
void				handle_pipe(t_tree *tree, char ***stock, char ***paths,
					char ***environ);
void				handle_semicolon(t_tree *tree, char ***path, char ***stock,
					char ***environ);
void				handle_segv(pid_t fath);
void				help_env(void);
void				heredoc(char ***stock, int i, char ***environ);
void				history(t_index **index, t_hist **list);
void				history_operation(char **stock, char **environ);
void				home(t_index **index, struct winsize size);
void				if_exit(char **environ, char ***paths, char ***stock,
					t_hist **list);
void				init_line(char **line, char ***environ, t_hist **list,
					t_tree **tree);
void				init_std(t_std **std);
void				insertchar(t_index **index, char *buffer);
void				main_check_line(t_all **all, char ***environ,
					t_truct **str);
void				normalize_pwd(char ***environ, int i);
void				open_file(char **arr, int i, int fd);
void				open_files(char **arr, int i, int fd);
void				other_case(t_index **index, char *buffer,
					struct winsize size);
void				parse(t_tree **tree, char *line, int size);
void				parse_alias(char **stock);
void				parse_dollar(char ***stock, char ***environ);
void				parse_or(t_tree **tree, char *line, int size);
void				parse_pipe(t_tree **tree, char *line, int size, int i);
void				parse_quote(char **line);
void				parse_tild(char ***stock, char ***environ);
void				print_prompt(char ***environ);
void				read_script(char **av, char **env);
void				remove_alias_bis(t_alias *alias);
void				remove_alias_bisbis(t_alias *alias);
void				save_history(t_hist *list, char **environ);
void				search_prompt(char *tmp);
void				set_null(t_tree **tree, t_all **all, t_hist **list, int ac);
void				set_old_dir(char *tmp2, char **path, char ***environ);
void				set_signal_father(pid_t father);
void				set_std(t_std *std, char **line, char ***environ);
void				set_terminal(t_all *all, char ***environ);
void				set_termios(void);
void				set_up_setenv(char *name, char *value, char **stock,
					char ***environ);
void				select_mode(t_index **index);
void				shift_down(t_index **index);
void				shift_left(t_index **index);
void				shift_right(t_index **index);
void				waitall(int nbproc);

#endif
