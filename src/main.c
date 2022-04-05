/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:03:12 by alakhdar          #+#    #+#             */
/*   Updated: 2022/04/05 11:30:24 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*head;
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
	head = init_envp_list(envp);
	while (1)
	{
		line_buffer = readline("$> ");
		if (line_buffer && *line_buffer)
		{
			add_history(line_buffer);
			if (parse_line(line_buffer, head) == 2)
				print_envp(head);
			else if (parse_line(line_buffer, head) == 1)
				printf("%s/n", "Error");
		}
		free(line_buffer);
	}
	return (0);
}
