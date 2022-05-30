/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:19:41 by rbony             #+#    #+#             */
/*   Updated: 2022/05/26 15:34:19 by alakhdar         ###   ########lyon.fr   */
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
	char			*path;
	char			**argv;
	pid_t			pid;
	int				pipex[2];
	int				index;
	int				is_builtin;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_executor
{
	int					input;
	int					output;
	struct s_heredoc	*heredocs;
	struct s_cmd		*commands;
}	t_executor;

int			g_exit;

/* Parsing */

int			make_commands(t_executor *exec, t_source **source, t_env *env);
int			is_builtin(char *cmd);
int			open_append(char *outfile);
int			open_outfile(char *outfile);
int			open_infile(char *infile);
int			find_heredocs(t_executor *exec, t_source **source);
int			parse_error(t_source *head);
int			not_interpreted(char *line);
int			find_redirects(t_executor *exec, t_source **source);
void		*free_executor(t_executor **exec);
void		set_output(t_executor *exec, t_source *tmp, int mode);
void		set_input(t_executor *exec, t_source *tmp);
void		set_both(int infile, int outfile);
void		set_outfile(t_cmd *cmd, int outfile);
void		set_infile(t_cmd *cmd, int infile);
void		ft_srcclear(t_source **head);
void		assign_type(t_source *source);
t_executor	*make_executor(t_source	*source, t_env *env);
t_source	*make_source(char *str);
void		find_all_path(t_var *env, t_cmd *cmd);
int			ft_lstsize(t_cmd *cmd);
char		*replace_var(char *str, t_var *head);
int			count_quotes(char *str);
char		*resize_str(char *str);
int			remove_quotes_heredoc(t_heredoc *tmp);

/* Execution */

void		error_cmd_not_found(char *cmd);
void		execution(t_env *env, t_executor *exec);
void		close_pipes_fromfirst(t_cmd *cmd);
void		close_pipes_fromlast(t_cmd *cmd);
void		ft_heredoc(t_var *env, t_executor *exec);
void		error_exit(char *msg, int exit_code);
int			open_pipes(t_cmd **cmd);
int			place_env_var(t_source *source, t_var *head);
int			replace_needed(char *str);
int			remove_quotes(t_source *source);

/* Builtins */

int			ft_cd(char *args, t_var *head);
int			ft_pwd(t_var *head);
int			ft_echo(char **arg);
int			check_new_line(char *str);
int			print_env(t_var *head);
int			is_occurring(char *envp);
int			validate_arg(char *arg);
int			list_is_sorted(t_exp *head);
int			ft_unset(t_exp *head_exp, t_var *head_env, char *key);
char		*get_key(char *envp);
char		*get_value(char *envp);
char		*get_var(t_var *head, char *key);
void		free_params(char **split);
void		print_export(t_exp *head_exp);
void		swap_node(t_exp	**env);
void		unset_env(t_var *head_env, char *key);
void		unset_exp(t_exp *head_exp, char *key);
void		handler(int signo);
t_var		*init_env(char **envp);
t_var		*append_to_list(t_var *head, char *envp);
t_var		*create_node(char *envp);
t_exp		*init_export(char **envp);
t_exp		*append_to_exp(t_exp *head, char *envp);
t_exp		*create_exp_node(char *envp);
t_exp		*sort_export(t_exp *env);

#endif
