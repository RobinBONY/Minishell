/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:40:58 by alakhdar          #+#    #+#             */
/*   Updated: 2022/04/18 15:04:38 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_var *head)
{
	char	name[PATH_MAX];
	char	*path;

	if (getcwd(name, PATH_MAX) == NULL)
		return (1);
	printf("%s\n", name);
	/*if (get_var(head, path) == NULL)
	{
		free(path);
		return (1);
	}
	printf("%s\n", path);*/
	return (0);
}

static int	cd_home(t_var *head)
{
	int		hold;
	char	*path;

	path = get_var(head, "HOME");
	if (path == NULL)
		return (1);
	hold = chdir(path);
	return (0);
}

static int	cd_args(char *args)
{
	int		hold;
	char	*path;

	path = ft_strdup(args);
	if (path == NULL)
		return (1);
	hold = chdir(path);
	if (hold < 0)
	{
		//error_print("cd error.\n", 1);
		free(path);
		return (1);
	}
	free(path);
	return (0);
}

int	ft_cd(char *args, t_var *head)
{
	int		hold;

	hold = 0;
	if (!args)
		hold = cd_home(head);
	else
		hold = cd_args(args);
	if (hold == 1)
		return (1);
	if (ft_pwd(head) == 1)
		return (1);
	return (hold);
}
