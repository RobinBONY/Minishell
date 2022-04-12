/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:03:12 by alakhdar          #+#    #+#             */
/*   Updated: 2022/04/12 15:34:45 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_var	*head_env;
	t_var	*head_exp;
	char	*line_buffer;

	(void)argc;
	printf("%s", "             ____________________________________________________\n");
	usleep(50000);
	printf("%s", "            /                                                     \\\n");
	usleep(50000);
	printf("%s", "           |    _____________________________________________     |\n");
	usleep(50000);
	printf("%s", "           |   |                                             |    |\n");
	usleep(50000);
	printf("%s", "           |   |                                             |    |\n");
	usleep(50000);
	printf("%s", "           |   |  C:\\> _                                     |    |\n");
	usleep(50000);
	printf("%s", "           |   |                                             |    |\n");
	usleep(50000);
	printf("%s", "           |   |                                             |    |\n");
	usleep(50000);
	printf("%s", "           |   |                                             |    |\n");
	usleep(50000);
	printf("%s", "           |   |                                             |    |\n");
	usleep(50000);
	printf("%s", "           |   |                 $>MINISHELL                 |    |\n");
	usleep(50000);
	printf("%s", "           |   |                                             |    |\n");
	usleep(50000);
	printf("%s", "           |   |                                             |    |\n");
	usleep(50000);
	printf("%s", "           |   |                                             |    |\n");
	usleep(50000);
	printf("%s", "           |   |                                             |    |\n");
	usleep(50000);
	printf("%s", "           |   |                                             |    |\n");
	usleep(50000);
	printf("%s", "           |   |                                             |    |\n");
	usleep(50000);
	printf("%s", "           |   |_____________________________________________|    |\n");
	usleep(50000);
	printf("%s", "           |                                                      |\n");
	usleep(50000);
	printf("%s", "           \\_____________________________________________________/\n");
	usleep(50000);
	printf("%s", "                   \\_______________________________________/\n");
	usleep(50000);
	printf("%s", "                _______________________________________________\n");
	usleep(50000);
	printf("%s", "             _-    .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.  --- `-_\n");
	usleep(50000);
	printf("%s", "          _-.-.-. .---.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.  .-.-.`-_\n");
	usleep(50000);
	printf("%s", "       _-.-.-.-. .---.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-`__`. .-.-.-.`-_\n");
	usleep(50000);
	printf("%s", "    _-.-.-.-.-. .-----.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-----. .-.-.-.-.`-_\n");
	usleep(50000);
	printf("%s", " _-.-.-.-.-.-. .---.-. .-----------------------------. .-.---. .---.-.-.-.`-_\n");
	usleep(50000);
	printf("%s", ":-----------------------------------------------------------------------------:\n");
	usleep(50000);
	printf("%s", "|---._.-----------------------------------------------------------------._.---_|\n");
	usleep(10000);
	printf("\n");
	printf("%s", "An Rbony & Alakhdar collaboration.\n");
	printf("\n");
	head_env = init_env(envp);
	head_exp = init_export(envp);
	head_exp = sort_export(head_exp);
	while (1)
	{
		line_buffer = readline("$> ");
		if (line_buffer && *line_buffer)
		{
			add_history(line_buffer);
			if (parse_line(line_buffer, head_env, head_exp) == 1)
				printf("%s/n", "Error");
		}
		free(line_buffer);
	}
	return (0);
}
