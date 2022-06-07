/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:14:46 by rbony             #+#    #+#             */
/*   Updated: 2022/06/07 17:43:17 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	welcome(void)
{
	printf("\033[92m___  ____       _     _          _ _ \033[0m\n");
	printf("\033[92m|  \\/  (_)     (_)   | |        | | |\033[0m\n");
	printf("\033[92m| .  . |_ _ __  _ ___| |__   ___| | |\033[0m\n");
	printf("\033[92m| |\\/| | | '_ \\| / __| '_ \\ / _ \\ | |\033[0m\n");
	printf("\033[92m| |  | | | | | | \\__ \\ | | |  __/ | |\033[0m\n");
	printf("\033[92m\\_|  |_/_|_| |_|_|___/_| |_|\\___|_|_|\033[0m\n");
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
	int			fd;

	env.envp = dup_env(envp);
	if (!env.envp)
		return (env);
	env.head_var = init_env(env.envp);
	env.head_exp = init_export(env.envp);
	if (!env.head_exp)
		return (env);
	env.head_exp = sort_export(env.head_exp);
	fd = open_outfile("/tmp/.heredoc");
	if (fd)
		close(fd);
	return (env);
}

int	main(int argc, char **argv, char **envp)
{
	t_env		env;
	char		*line_buffer;

	welcome();
	if (!*envp)
		return (1);
	main_signals();
	env = init(envp);
	while (1)
	{
		line_buffer = readline("Minishell-3.5$ ");
		if (line_buffer == NULL)
			break ;
		if (line_buffer && *line_buffer)
		{
			add_history(line_buffer);
			parse_and_execute(&env, line_buffer);
			free(line_buffer);
		}
	}
	unlink("/tmp/.heredoc");
	ft_putstr_fd("exit\n", 2);
	free(line_buffer);
	return (0);
}
