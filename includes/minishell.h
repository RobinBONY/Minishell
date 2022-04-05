/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 11:12:54 by alakhdar          #+#    #+#             */
/*   Updated: 2022/04/05 14:43:41 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <limits.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

int			g_exit;

char		*get_env(char *var, char **env, int n);
int			env_len(char **env);
int			set_envp(t_env *head, char *key, char *value);
int			ft_echo(char **arg);
int			check_new_line(char *str);
int			parse_line(char *line, t_env *head);
// int			ft_pwd(void);
// int			ft_cd(char *args);
void		ft_unset(t_env *head, char *key);
void		print_envp(t_env *envp);
t_env		*init_envp_list(char **envp);
t_env		*append_to_envp(t_env *head, char *envp);
char		*get_key(char *envp);
char		*get_value(char *envp);

// static int	pwd_store(void);
// static int	cd_home(void);
// static int	cd_args(char *args);
char		**ft_cmd_split(const char *s);
size_t		ft_divlen(char *s);

#endif
