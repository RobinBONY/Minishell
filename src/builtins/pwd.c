/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:42:05 by alakhdar          #+#    #+#             */
/*   Updated: 2022/03/29 11:29:41 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(void)
{
	char	str[PATH_MAX];

	if (getcwd(str, sizeof(str)) == NULL)
		return (1);
	printf("%s\n", str);
	return (0);
}
