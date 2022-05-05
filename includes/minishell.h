/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:19:41 by rbony             #+#    #+#             */
/*   Updated: 2022/05/04 14:32:27 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <limits.h>
# include <sys/types.h>
# include <signal.h>

typedef struct s_cmd
{
	char			*path;
	char			**argv;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_heredoc
{
	char				*delim;
	struct s_heredoc	*next;
}	t_heredoc;

typedef struct s_redirect
{
	int					is_input;
	int					is_output;
	int					is_append;
	char				*filename;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_input
{
	struct s_cmd		*cmds;
	struct s_heredoc	*heredocs;
	struct s_redirect	*redirects;
}	t_input;

typedef struct s_var
{
	char			*key;
	char			*value;
	struct s_var	*next;
	int				printable;
}	t_var;

typedef struct s_exp
{
	char			*key;
	char			*value;
	struct s_exp	*next;
	struct s_exp	*prev;
}	t_exp;

int			g_exit;

void		free_tab(char **tab);
char		*get_env(char *var, char **env, int n);
int			env_len(char **env);
int			ft_export(t_var *head, char *key, char *value);
int			ft_echo(char **arg);
int			check_new_line(char *str);
int			parse_line(char *line, t_var *head_env, t_exp *head_exp);
int			is_occurring(char *envp);
int			validate_arg(char *arg);
int			ft_pwd(t_var *head);
int			ft_cd(char *args, t_var *head);
int			ft_unset(t_exp *head_exp, t_var *head_env, char *key);
void		print_env(t_var *head);
void		print_export(t_exp *head);
void		sort_list(t_var *head);
void		free_list(t_var	*head);
void		sort_char_tab(char	**str, int len);
void		swap_node(t_exp	**env);
void		handler(int signo);
t_var		*init_env(char **envp);
t_exp		*init_export(char **envp);
t_var		*append_to_list(t_var *head, char *envp);
t_exp		*append_to_exp(t_exp *head, char *envp);
t_exp		*init_export(char **envp);
t_exp		*sort_export(t_exp *head_exp);
char		*get_key(char *envp);
char		*get_value(char *envp);
char		*ft_strcpy(char *dest, char *src);
char		*ft_strcat(char *dest, char *src);
char		*get_var(t_var *head, char *key);
int			list_is_sorted(t_exp *head);

// static int	pwd_store(void);
// static int	cd_home(void);
// static int	cd_args(char *args);

int			not_interpreted(char *line);
int			unmanaged_character_error(char c);
int			check_quotes(char *str);
int			replace_needed(char *str);
char		**ft_cmd_split(const char *s);
int			unmanaged_character_error(char c);
int			place_env_var(char **words, t_var *env);

t_cmd		*ft_cmdnew(char *path, char **argv);
void		ft_cmdadd_back(t_cmd **alst, t_cmd *new);
void		ft_cmdclear(t_cmd **lst);
t_heredoc	*ft_docnew(char *content);
void		ft_docadd_back(t_heredoc **alst, t_heredoc *new);
void		ft_docclear(t_heredoc **lst);
t_redirect	*ft_rednew(int input, int output, int append, char *filename);
void		ft_redadd_back(t_redirect **alst, t_redirect *new);
void		ft_redclear(t_redirect **lst);

size_t		ft_divlen(char *s);

#endif
