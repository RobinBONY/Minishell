#include <stdio.h>
#include <stdlib.h>

typedef struct	s_env
{
	char	*key;
	char	*value;
	struct 	t_env	*next;
}	t_env;

void	print_envp(t_env *head) 
{
    t_env	*current_node;

	current_node = head;
   	while ( current_node != NULL) {
		printf("%s", current_node->key);
		printf("=");
		printf("%s\n", current_node->value);
		current_node = current_node->next;
    }
}

char	*get_key(char *envp)
{
	char	*buf;
	int		i;
	int		j;

	i = 0;
	while (envp && envp[i] != "=")
		i++;
	buf = malloc(sizeof(char) * i + 1);
	if (!buf)
		exit (0);
	j = 0;
	while (j <= i)
	{
		buf[j] = envp[i];
		j++;
		i++;
	}
	buf[j] = '\0';
	return (buf);
}

char	*get_value(char *envp)
{
	char	*buf;
	int		i;
	int		j;
	int		len;

	i = 0;
	while (envp[i] && envp[i] != "=")
		i++;
	i++;
	j = i;
	while (envp[i])
		i++;
	len = i;
	buf = malloc(sizeof(char) * len + 1);
	if (!buf)
		exit (0);
	i = 0;
	while (envp[j])
	{
		buf[i] = envp[j];
		i++;
		j++;
	}
	buf[i] = '\0';
	return (buf);
}

t_env   *create_env_node(t_env *next, char *envp)
{
    t_env   *new_env;

    new_env = (t_env *)malloc(sizeof(t_env));
    if (!new_env)
    {
        printf("Error in adding new environment variable\n");
        exit (0);
    }
    new_env->key = get_key(envp);
    new_env->value = get_value(envp);
    new_env->next = next;

    return (new_env);
}

t_env   *append_to_envp(t_env *head, char *envp)
{
    t_env   *cursor;
    t_env   *new_env;

    cursor = head;
    while(cursor->next != NULL)
        cursor = cursor->next;
    new_env = create_env_node(envp, NULL);
    cursor->next = new_env;
    return (head);
}

t_env	*init_envp_list(char **envp)
{
    int		i;
    t_env	*head;

    i = 0;
	head = create_env_node(envp[i], NULL);
    while (envp[++i])
		append_to_envp(head, envp[i]);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*head;

	head = init_envp_list(envp);
	print_envp(head);
	return (0);
}