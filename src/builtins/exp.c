/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:37:00 by alakhdar          #+#    #+#             */
/*   Updated: 2022/04/12 10:39:38 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	export_print(t_var *env_list)
{
	t_var	*cursor;

	cursor = env_list->next;
	while (cursor)
	{
		printf("declare -x %s", cursor->key);
		if (cursor->value)
			printf("=\"%s\"\n", cursor->value);
		else
			printf("\n");
		cursor = cursor->next;
	}
}

static int	validate_arg(char *arg)
{
	char	*cursor;

	if (ft_strlen(arg) == 0)
		return (export_error(arg));
	cursor = arg;
	if (ft_isdigit(*cursor) || *cursor == '=' || *cursor == '+')
		return (export_error(arg));
	while (*cursor && (ft_isalnum(*cursor) || *cursor == '_'))
		cursor++;
	if (*cursor == '\0' || *cursor == '=' || !ft_strncmp(cursor, "+=", 2))
		return (0);
	else
		return (export_error(arg));
}

static int	builtin_export_core(char *arg, t_sh_var *sh_var)
{
	char	*cursor;
	char	*key;
	char	*value;

	if (validate_arg(arg))
		return (1);
	if (!ft_strchr(arg, '='))
		set_env_valueue(arg, NULL, sh_var);
	else
	{
		cursor = arg;
		while (*cursor && (ft_isalnum(*cursor) || *cursor == '_'))
			cursor++;
		key = ft_xstrndup(arg, cursor - arg);
		value = ft_xstrdup(cursor + 1 + (*cursor == '+'));
		if (*cursor == '=')
			set_env_valueue(key, value, sh_var);
		else
			append_env_valueue(key, value, sh_var);
		free(key);
		free(value);
	}
	return (0);
}

int	builtin_export(t_proc *proc, t_sh_var *sh_var)
{
	int		ret;
	int		idx;

	idx = 1;
	if (proc->command[idx] == NULL)
	{
		sort_env_list(sh_var->env_list->next);
		builtin_export_print(sh_var->env_list);
		return (fd_error_handler("export"));
	}
	else
	{
		ret = 0;
		while (proc->command[idx])
		{
			if (builtin_export_core(proc->command[idx], sh_var))
				ret = 1;
			idx++;
		}
		return (ret);
	}
}