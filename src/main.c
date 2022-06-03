/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:14:46 by rbony             #+#    #+#             */
/*   Updated: 2022/06/03 16:26:23 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	welcome(void)
{
	printf("___  ____       _     _          _ _ \n");
	printf("|  \\/  (_)     (_)   | |        | | |\n");
	printf("| .  . |_ _ __  _ ___| |__   ___| | |\n");
	printf("| |\\/| | | '_ \\| / __| '_ \\ / _ \\ | |\n");
	printf("| |  | | | | | | \\__ \\ | | |  __/ | |\n");
	printf("\\_|  |_/_|_| |_|_|___/_| |_|\\___|_|_|\n");
	printf("\n");
}

int	parse_and_execute(t_env *env, char *line_buffer)
{
	t_source	*source;
	t_executor	*exec;

	if (not_interpreted(line_buffer))
		return (1);
	source = make_source(line_buffer);
	if (!source)
		return (1);
	assign_type(source);
	if (parse_error(source))
	{
		ft_srcclear(&source);
		return (1);
	}
	exec = make_executor(source, env);
	if (!exec)
		return (1);
	ft_srcclear(&source);
	execution(env, exec);
	free_executor(&exec);
	return (0);
}

t_env	init(char **envp)
{
	t_env		env;

	env.envp = envp;
	env.head_var = init_env(envp);
	env.head_exp = init_export(envp);
	if (!env.head_exp)
		return (env);
	env.head_exp = sort_export(env.head_exp);
	return (env);
}

int	main(int argc, char **argv, char **envp)
{
	t_env		env;
	char		*line_buffer;

	main_signals();
	welcome();
	env = init(envp);
	while (1)
	{
		line_buffer = readline("Minishell2.0$> ");
		if (line_buffer == NULL)
			break ;
		if (line_buffer && *line_buffer)
		{
			add_history(line_buffer);
			parse_and_execute(&env, line_buffer);
			free(line_buffer);
		}
	}
	ft_putstr_fd("exit\n", 2);
	free(line_buffer);
	return (0);
}
