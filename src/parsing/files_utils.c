/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:07:07 by alakhdar          #+#    #+#             */
/*   Updated: 2022/05/25 13:36:10 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	open_infile(char *infile)
{
	int	fd_file;

	if (access(infile, F_OK) == -1 || access(infile, R_OK) == -1)
	{
		perror("Error");
		return (-1);
	}
	else
	{
		fd_file = open(infile, O_RDONLY);
		if (fd_file == -1)
			return (-1);
	}
	return (fd_file);
}

int	open_outfile(char *outfile)
{
	int	fd_file;

	if (access(outfile, F_OK) == 0 && access(outfile, W_OK) == -1)
	{
		perror("Error");
		return (-1);
	}
	else
	{
		fd_file = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (fd_file == -1)
			return (-1);
	}
	return (fd_file);
}

int	open_append(char *outfile)
{
	int	fd_file;

	if (access(outfile, F_OK) == 0 && access(outfile, W_OK) == -1)
	{
		perror("Error");
		return (-1);
	}
	else
	{
		fd_file = open(outfile, O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (fd_file == -1)
			return (-1);
	}
	return (fd_file);
}
