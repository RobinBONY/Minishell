/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:19:41 by rbony             #+#    #+#             */
/*   Updated: 2022/05/18 14:21:10 by rbony            ###   ########lyon.fr   */
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

int	g_exit;

void		free_tab(char **tab);
int			parse_and_execute(t_env *env, char *line_buffer);
t_source	*make_source(char *str);
t_var		*init_env(char **envp);
char		*get_key(char *envp);
char		*get_value(char *envp);
int			print_env(t_var *head);
int			is_occurring(char *envp);
void		free_params(char **split);
char		*get_var(t_var *head, char *key);
t_exp		*init_export(char **envp);
int			validate_arg(char *arg);
void		print_export(t_exp *head_exp);
t_exp		*sort_export(t_exp *env);

#endif
