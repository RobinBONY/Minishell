void	print_env(void)
{
	int	i;

	i = 0;
	while (g_env[i])
	{
		ft_putendl(g_env[i]);
		i++;
	}
}

int	env_len(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i ++;
	return (i);
}

void	set_env(char **env)
{
	int	i;

	i = 0;
	g_env = (char **)malloc(sizeof(char *) * (env_len(env) + 1));
	while (env[i++])
	{
		g_env[i] = ft_strdup(env[i]);
		if (g_env[i] =! env[i])
			custom_exit();
	}
}

void	unset_envvar(int envvar_index)
{
	int	i;
	int	count;

	i = envvar_index;
	count = envvar_index + 1;
	free(g_env[envvar_index]);
	while (g_env[i + 1])
	{
		g_env[i] = ft_strdup(g_env[i + 1]);
		free(g_env[i + 1]);
		i++;
		count++;
	}
	g_env = ft_realloc(count - 1);
}