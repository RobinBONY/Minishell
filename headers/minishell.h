/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:19:41 by rbony             #+#    #+#             */
/*   Updated: 2022/06/08 14:38:37 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <sys/types.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include "../src/libft/libft.h"

enum e_type
{
	STRING,
	OPERATOR
};

typedef struct s_source
{
	char			*str;
	enum e_type		type;
	int				used;
	struct s_source	*next;
}	t_source;

typedef struct s_env
{
	struct s_var	*head_var;
	struct s_exp	*head_exp;
	char			**envp;
}	t_env;

typedef struct s_var
{
	char			*key;
	char			*value;
	struct s_var	*next;
	int				printable;
}	t_var;

typedef struct s_exp
{
	char			*key;
	char			*value;
	struct s_exp	*next;
	struct s_exp	*prev;
}	t_exp;

typedef struct s_heredoc
{
	char				*str;
	struct s_heredoc	*next;
}	t_heredoc;

typedef struct s_cmd
{
	char				*path;
	char				**argv;
	pid_t				pid;
	int					pipex[2];
	int					index;
	int					is_builtin;
	int					is_local;
	int					input;
	int					output;
	struct s_heredoc	*heredocs;
	struct s_cmd		*prev;
	struct s_cmd		*next;
}	t_cmd;

int			g_exit;

/* Parsing */

t_cmd		*make_command(t_source **source, t_env *env, t_cmd *prev);
int			is_builtin(char *cmd);
int			is_local(char *cmd, char **argv);
int			open_append(char *outfile);
int			open_outfile(char *outfile);
int			open_infile(char *infile);
int			find_heredocs(t_cmd *cmd, t_source **source);
int			parse_error(t_source *head);
int			not_interpreted(char *line);
int			find_redirects(t_cmd *cmd, t_source **source, t_env *env);
void		*free_executor(t_cmd *cmd);
void		set_output(t_cmd *cmd, t_source *tmp, int mode, t_env *env);
void		set_input(t_cmd *cmd, t_source *tmp, t_env *env);
void		set_both(int infile, int outfile);
void		set_outfile(t_cmd *cmd, int outfile);
void		set_infile(t_cmd *cmd, int infile);
void		ft_srcclear(t_source **head);
void		assign_type(t_source *source);
t_cmd		*make_executor(t_source	*source, t_env *env);
t_source	*make_source(char *str);
void		find_all_path(t_var *env, t_cmd *cmd);
int			ft_lstsize(t_cmd *cmd);
char		*replace_var(char *str, t_var *head);
int			count_quotes(char *str);
char		*resize_str(char *str);
int			remove_quotes_heredoc(t_heredoc *tmp);
char		*find_var(char *str, t_var *head);
int			get_type(char *tmp);
void		index_commands(t_cmd *cmds);
void		ft_cmdadd_back(t_cmd **alst, t_cmd *new);
void		ft_lstadd_front(t_source **alst, t_source *new);
t_cmd		*ft_lstlast(t_cmd *cmd);
void		ft_push(t_source **src, t_source **dest);
int			set_cmd(t_source **source, t_cmd *new, t_cmd *prev, int len);
int			check_redirects(t_cmd *exec);
int			get_len(t_source *source);
char		*last_exit(char *str, int start);
char		*replace_string(char *str, int start, int len, char *replace);

/* Execution */

void		error_cmd_not_found(char *cmd);
void		execution(t_env *env, t_cmd *cmd);
void		close_pipes_fromfirst(t_cmd *cmd);
void		close_pipes_fromlast(t_cmd *cmd);
void		error_exit(char *msg, int exit_code);
void		ft_exit(char *ex_no);
int			ft_heredoc(t_var *env, t_cmd *cmd);
int			open_pipes(t_cmd **cmd);
int			place_env_var(t_source *source, t_var *head);
int			replace_needed(char *str, t_var *head);
int			remove_quotes(t_source *source);
void		ft_waitpid(t_cmd	*tmp);
void		set_redirect_first(t_cmd *cmd);
void		set_redirect_last(t_cmd *cmd);
void		set_redirect(t_cmd *cmd);
void		set_redirect_solobolo(t_cmd *cmd);

/* Builtins */

int			ft_cd(char *args, t_var *head_env, t_exp *head_exp);
int			ft_pwd(t_var *head);
int			ft_echo(char **arg);
int			check_new_line(char *str);
int			print_env(t_var *head);
int			is_occurring(char *envp);
int			validate_arg(char *arg);
int			list_is_sorted(t_exp *head);
int			ft_unset(t_exp *head_exp, t_var *head_env, char *key);
int			print_export(t_exp *head_exp);
char		*get_key(char *envp);
char		*get_value(char *envp);
char		*get_var(t_var *head, char *key);
void		free_params(char **split);
void		swap_node(t_exp	**env);
void		unset_env(t_var *head_env, char *key);
void		unset_exp(t_exp *head_exp, char *key);
void		replace_exp(t_exp *head, char *str);
void		replace_env(t_var *head, char *str);
void		rep_or_app_env(t_var *head, char *str);
void		rep_or_app_exp(t_exp *head, char *str);
t_var		*init_env(char **envp);
t_var		*append_to_list(t_var *head, char *envp);
t_var		*create_node(char *envp);
t_exp		*init_export(char **envp);
t_exp		*append_to_exp(t_exp *head, char *envp);
t_exp		*create_exp_node(char *envp);
t_exp		*sort_export(t_exp *env);

/* Signals */

void		main_signals(void);
void		child_signals(void);
void		heredoc_signals(void);
void		handler(int signo);
void		handler_child(int signo);
void		handler_heredoc(int signo);

/* Errors */

int			unmanaged_character_error(char c);
int			cmd_not_found(char *str);
int			unclosed_quote(char c);
int			syntax_error(char *c);

#endif
