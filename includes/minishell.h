/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 11:12:54 by alakhdar          #+#    #+#             */
/*   Updated: 2022/03/29 13:55:17 by rbony            ###   ########lyon.fr   */
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

char		**g_env;
char		*get_env(char *var, char **env, int n);
int			env_len(char **env);
int			set_envp(char **env);
int			ft_echo(char **arg);
int			check_new_line(char *str);
// int			ft_pwd(void);
// int			ft_cd(char *args);
void		unset_envp(int envvar_index);
void		print_envp(void);

// static int	pwd_store(void);
// static int	cd_home(void);
// static int	cd_args(char *args);
char		**ft_cmd_split(const char *s);
size_t		ft_divlen(char *s);

#endif
