/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:58:45 by rbony             #+#    #+#             */
/*   Updated: 2022/05/30 12:59:59 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define    LIBFT_H

# include <unistd.h>
# include <stdlib.h>

char		*ft_strcat(char *dest, char *src);
size_t		ft_strlen(const char *str);
char		*ft_strchr(const char *s, int c);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin_cmd(const char *s1, const char *s2);
char		*ft_strcpy(char *dest, char *src);
char		**ft_split(const char *s, char c);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_realloc(void *ptr, size_t newsize);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		ft_tolower(char *str);
int			ft_isalnum(int c);
int			ft_isdigit(int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strdup(const char *src);
char		**ft_cmd_split(const char *s);
char		**ft_src_split(const char *s);
int			ft_isoperator(char c);
char		*ft_itoa(int n);
void		ft_putstr_fd(char *s, int fd);
char		*ft_strncat(char *dest, char *src, unsigned int nb);
char		*ft_strjoin(const char *s1, const char *s2);

#endif