/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 11:12:54 by alakhdar          #+#    #+#             */
/*   Updated: 2022/03/17 13:33:30 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"

char	**g_env;
void	print_env(void);
int		env_len(char **env);
void	set_env(char **env);
char	*get_env(char *var, char **env, int n);
void	unset_envvar(int envvar_index);

#endif
