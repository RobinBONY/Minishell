/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:40:58 by alakhdar          #+#    #+#             */
/*   Updated: 2022/06/09 13:44:21 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_pwd(t_var *head)
{
	char	name[PATH_MAX];

	if (getcwd(name, PATH_MAX) == NULL)
		return (1);
	printf("%s\n", name);
	return (0);
}

static int	cd_home(t_var *head_var, t_exp *head_exp)
{
	int		hold;
	char	*path;
	char	*tmp;
	char	pwd[PATH_MAX];

	path = get_var(head_var, "HOME");
	if (path == NULL)
		return (1);
	hold = chdir(path);
	if (getcwd(pwd, PATH_MAX) == NULL)
		return (1);
	tmp = ft_strjoin("PWD=", pwd);
	replace_env(head_var, tmp);
	replace_exp(head_exp, tmp);
	free(tmp);
	return (0);
}

static int	cd_args(char *args, t_var *head_var, t_exp *head_exp)
{
	int		hold;
	char	*path;
	char	*tmp;
	char	pwd[PATH_MAX];

	path = ft_strdup(args);
	if (path == NULL)
		return (1);
	hold = chdir(path);
	if (hold < 0)
	{
		free(path);
		return (1);
	}
	if (getcwd(pwd, PATH_MAX) == NULL)
		return (1);
	tmp = ft_strjoin("PWD=", pwd);
	replace_env(head_var, tmp);
	replace_exp(head_exp, tmp);
	free(tmp);
	free(path);
	return (0);
}

void	change_oldpwd(t_var *head_var, t_exp *head_exp, char *pwd)
{
	char	*tmp;

	tmp = ft_strjoin("OLDPWD=", pwd);
	replace_env(head_var, tmp);
	replace_exp(head_exp, tmp);
	free(tmp);
}

int	ft_cd(char *args, t_var *head_var, t_exp *head_exp)
{
	char	pwd[PATH_MAX];
	DIR		*test;

	if (getcwd(pwd, PATH_MAX) == NULL)
		return (1);
	change_oldpwd(head_var, head_exp, pwd);
	if (!args)
		return (cd_home(head_var, head_exp));
	else
	{
		test = opendir(args);
		if (!test)
			perror("Error");
		else
			closedir(test);
		return (cd_args(args, head_var, head_exp));
	}
	return (1);
}
