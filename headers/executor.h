/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:56:00 by rbony             #+#    #+#             */
/*   Updated: 2022/05/10 14:47:51 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h> /**/
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <sys/types.h>
# include <signal.h>
# include <unistd.h>
# include "parser.h"
# include "../src/libft/libft.h"

int			g_exit;

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

char	*search_path(char *cmd, char *env_path);
char	*get_var(t_var *head, char *key);
int		do_exec_cmd(int argc, char **argv, t_var *head_env, t_exp *head_exp);
int		do_simple_command(t_node *node, t_var *head_env, t_exp *head_exp);
void	free_params(char **split);
char	*get_key(char *envp);
char	*get_value(char *envp);
int		is_occurring(char *envp);
t_var	*init_env(char **envp);
int		validate_arg(char *arg);
t_exp	*init_export(char **envp);
int		is_builtin(char *str);
void	launch_builtin(char *path, char **argv,
			t_var *head_env, t_exp *head_exp);

void	print_export(t_exp *head_exp);
int		print_env(t_var *head);
int		ft_pwd(t_var *head);
int		ft_cd(char *args, t_var *head);
int		ft_echo(char **arg);
int		ft_unset(t_exp *head_exp, t_var *head_env, char *key);

#endif