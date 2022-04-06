/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 11:12:54 by alakhdar          #+#    #+#             */
/*   Updated: 2022/04/06 15:02:39 by alakhdar         ###   ########lyon.fr   */
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

typedef struct s_var
{
	char			*key;
	char			*value;
	struct t_var	*next;
}	t_var;

int			g_exit;

char		*get_env(char *var, char **env, int n);
int			env_len(char **env);
int			set_envp(t_var *head, char *key, char *value);
int			ft_echo(char **arg);
int			check_new_line(char *str);
int			parse_line(char *line, t_var *head);
// int			ft_pwd(void);
// int			ft_cd(char *args);
void		ft_unset(t_var *head, char *key);
void		print_var(t_var *head);
t_var		*init_var(char **envp);
t_var		*append_to_list(t_var *head, char *envp);
t_var		*init_export(char **envp);
char		*get_key(char *envp);
char		*get_value(char *envp);

// static int	pwd_store(void);
// static int	cd_home(void);
// static int	cd_args(char *args);

int			not_interpreted(char *line);
int			unmanaged_character_error(char c);
int			check_quotes(char *str);
int			replace_needed(char *str);
char		**ft_cmd_split(const char *s);
int			unmanaged_character_error(char c);
int			place_env_var(char **words);

#endif
