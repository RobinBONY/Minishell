/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:03:12 by alakhdar          #+#    #+#             */
/*   Updated: 2022/04/13 15:52:29 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sig_handler(int sig)
{
	kill(0, 1);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*head;
	char	*line_buffer;
	int		pid;

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
	signal(SIGINT, sig_handler);
	g_exit = 0;
	while (1)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return (EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			line_buffer = readline("$> ");
			if (line_buffer && *line_buffer)
			{
				add_history(line_buffer);
				if (parse_line(line_buffer, head) == 1)
					printf("%s/n", "Error");
			}
			free(line_buffer);
		}
		else
			waitpid(pid, &g_exit, WCONTINUED);
	}
	return (0);
}
