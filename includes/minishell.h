/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 11:12:54 by alakhdar          #+#    #+#             */
/*   Updated: 2022/04/14 14:35:18 by alakhdar         ###   ########lyon.fr   */
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

int			g_exit;

char		*get_env(char *var, char **env, int n);
int			env_len(char **env);
int			ft_export(t_var *head, char *key, char *value);
int			ft_echo(char **arg);
int			check_new_line(char *str);
int			parse_line(char *line, t_var *head_env, t_exp *head_exp);
int			is_occurring(char *envp);
int			validate_arg(char *arg);
// int			ft_pwd(void);
// int			ft_cd(char *args);
void		unset_env(t_var *head_env, t_var *head_exp, char *key);
void		print_env(t_var *head);
void		print_export(t_exp *head);
void		sort_list(t_var *head);
void		free_list(t_var	*head);
void		sort_char_tab(char	**str, int len);
void		swap_node(t_exp	**env);
t_var		*init_env(char **envp);
t_exp		*init_export(char **envp);
t_var		*append_to_list(t_var *head, char *envp);
t_exp		*append_to_exp(t_exp *head, char *envp);
t_exp		*init_export(char **envp);
t_exp		*sort_export(t_exp *head_exp);
char		*get_key(char *envp);
char		*get_value(char *envp);
char		*ft_strcpy(char *dest, char *src);
char		*ft_strcat(char *dest, char *src);
char		*get_var(t_var *head, char *key);
int			list_is_sorted(t_exp *head);

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
