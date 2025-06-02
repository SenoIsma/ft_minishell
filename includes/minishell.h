/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhlel <ibouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:02:28 by ibouhlel          #+#    #+#             */
/*   Updated: 2024/11/22 19:25:36 by ibouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/stat.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>

extern int	g_waiting;

enum e_bool
{
	FALSE,
	TRUE
};

enum e_token
{
	NOTHING,
	CMD,
	STRING,
	OUTFILE,
	OUTFILE_D,
	HERE_DOC,
	INFILE,
	PIPE,
	FICHIER,
	LIM
};

typedef struct s_token
{
	int				type;
	char			*content;
	int				space;
	struct s_token	*next;
}			t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*prev;
	struct s_env	*next;
}			t_env;

typedef struct s_pipex
{
	int		r_in;
	int		r_out;
	int		nb_cmd;
	int		sigint;
	int		sigquit;
	pid_t	*pid;
	int		**fds;
}			t_pipex;

typedef struct s_data
{
	char	*line;
	char	**envp;
	t_token	*token;
	t_token	*start;
	t_env	*env;
	t_pipex	pipex;
	int		status;
}			t_data;

void		ft_free_onetoken(t_token *freeable);
int			ft_verif_token(t_token **args);
int			check_key(char *arg);
int			ft_checkalnum(char c);
int			ft_tokensize_without_redir(t_token **args);
int			open_outfile(t_token *tmp);
int			open_infile(t_token *tmp);
char		*ft_double_quote(char *line, t_data *data);
void		set_parent_exec_signals(void);
void		set_child_signals(void);
void		get_args_or_cmd(t_data *data);
void		ft_printtoken(t_token *lst);
void		which_exec(t_data *data);
void		exec_builtins(t_data *data);
char		*get_pwd(void);
void		update_pwd(t_env **env, char *pwd);
int			ft_cd(t_token **args, t_env **env);
int			get_fd(t_token **args);
int			is_n_flag(const char *str);
void		echo_print(t_token **args, int fd);
int			ft_echo(t_token **args);
int			ft_env(t_token *args, t_data *data);
t_env		*key_exist(t_env **env, char *key);
void		update_envp(t_env *env, t_data *data);
long long	ft_atol_exit(const char *str, int *flg);
int			is_num(char *str);
int			ft_exit(t_data *data, t_token **args);
void		print_env(t_env *env, int fd);
void		get_key_value(t_token *args, char **key, char **value);
void		add_value(t_env *env, char *key, char *value);
int			ft_export(t_token **args, t_env *env, t_data *data);
int			ft_pwd(t_data *data);
void		rm_env_node(t_env **env, char *key);
int			ft_unset(t_token **args, t_env *env, t_data *data);
int			cmd_size(t_token *cur);
char		**join_cmd(t_token **args);
char		*get_path(t_env *env);
char		*ft_returnline(char *s);
void		exit_exec(char **path, int ret, char **cmd, t_data *data);
char		*get_cmd_path(char *path, char *cmd);
void		ft_exec(t_data *data);
void		go_to_cmd(t_data *data);
int			ft_conversions(va_list args, char c);
int			ft_itoa_printf(int n);
int			ft_putchar(char c);
int			ft_putstr(char *str);
int			ft_putnbr(int n);
int			ft_putunsigned(unsigned int n);
int			printr(const char *str, ...);
int			ft_puthex(unsigned int n, int maj);
int			ft_syntax_analysis(char *line);
int			parsing_redir_bis(char *line, t_token **args, int *i);
int			parsing_redir(char *line, t_token **args, int *i);
int			parsing_pipe(char *line, int *i, t_data *data);
int			parsing_other(char *line, t_token **args, int *i, t_data *data);
int			parsing_simple(char *line, t_token **args, int *i);
int			parsing_double(char *line, int *i, t_data *data);
int			parsing_dollar(char *line, int *i, t_data *data);
int			parsing(char *line, t_token **args, t_data *data);
char		*choose_key(char *line, t_data *data);
char		*get_key(char *line, t_data *data);
int			show_last_type(t_token **args);
int			choose_type(t_token **args);
// int			open_fd(t_token **args, t_data *data);
int			ft_isalnum(char c);
void		ft_free(char *content);
void		ft_clean(t_data *data);
void		ft_clean_loop(t_data *data);
void		ft_free_tab(char **tab);
int			is_whitespace(char c);
int			is_token(char c);
int			is_stoken(char c);
int			is_builtin(t_token *args);
char		*ft_strdup(const char *s);
char		*ft_itoa(int n);
char		*ft_strchr(const char *s, int c);
void		ft_bzero(void *s, size_t n);
int			ft_strlenln(char *s);
void		ft_strln(char *cmd, char *s);
t_token		*ft_tokennew(int type, char *content, int space);
void		ft_tokenadd(t_token **lst, t_token *new);
t_token		*ft_tokenlast(t_token *lst);
void		ft_free_token(t_token *lst);
int			ft_tokensize(t_token *lst);
t_env		*ft_lstnew(char *key, char *value);
void		ft_lstadd(t_env **lst, t_env *new);
t_env		*ft_lstlast(t_env *lst);
void		ft_printlst(t_env *lst);
void		ft_free_lst(t_env *lst);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strlen(const char *str);
char		*ft_strjoin(char const *s1, char const *s2);
char		**ft_split(char *str, char c);
void		ft_putstr_fd(char *s, int fd);
char		*ft_substr(char *s, unsigned int start, size_t len);
int			ft_atoi(char *nptr);
int			count_cmd(t_token **args);
void		rm_heredocs(t_token **args, int h);
void		check_heredocs(t_token **args);
int			print_in_file(int fd, char *lim);
int			ft_heredoc(t_token **args, char *lim, t_data *data);
int			run_command_with_pipes(t_data *data, int i);
void		split_env(t_env **lst, char **envp);
void		handle_sigint(int sig);
int			**create_pipes(int cmd_count);
void		close_pipes(int **fds, int cmd_count);
int			ft_wait(t_pipex *pipex, int count_cmd);
int			ft_init_fd(t_token *cur);
int			ft_fork(t_data *data);
void		ft_verif(t_data *data);
int			minishell(t_data *data);
void		malloc_envp(char **env, t_data *data);
void		ft_signal(void);
void		handle_fork(int sig);

#endif