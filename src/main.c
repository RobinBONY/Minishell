#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char **buf;
	int		i;
	(void)envp;
	// (void)argv;
	(void)argc;
	i = 1;
	buf = malloc(sizeof(char *) * argc + 1);
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
	while (i <= argc)
	{
		buf[i] = argv[i];
		ft_echo(buf);
		i++;
	}
	//  set_envp(envp);
	//  print_env();
	// while (envp[i])
	// {
	// 	printf("%s\n", envp[i]);
	// 	i++;
	// }
	// wuhile (50000)
	// {
	// 	prompt_msg();
	// 	//parse input
	// 	//exec cmd
	// 	//free
	// 	//if (problem) break;
	// }
	//free
	return (0);
}
