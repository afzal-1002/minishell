/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolasze <mgolasze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 09:51:19 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/23 18:15:46 by mgolasze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	write_heredoc_lines(int write_fd, char *delim, t_global *global)
{
	char	*line;

	delim = handle_delim(delim);
	while (1)
	{
		if (global->signal_received == 2)
		{
			free(delim);
			return (0);
		}
		line = readline("> ");
		if (!line || ft_strncmp(line, delim, ft_strlen(delim) + 1) == 0)
		{
			free(line);
			free(delim);
			return (0);
		}
		line = expand_word(line, global);
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	return (0);
}

int	apply_heredoc(t_redir *redir, t_global *global)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (-1);
	if (write_heredoc_lines(pipe_fd[1], redir->file, global) == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], redir->fd) == -1)
	{
		close(pipe_fd[0]);
		return (-1);
	}
	close(pipe_fd[0]);
	return (0);
}

void	process_heredoc(t_cmd *cmd, t_global *global)
{
	t_redir	*redir;

	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == T_HEREDOC)
				apply_heredoc(redir, global);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}

void	close_heredoc(t_cmd *cmd)
{
	t_redir	*redir;
	int		saved_stdin;

	saved_stdin = dup(STDIN_FILENO);
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == T_HEREDOC)
				dup2(saved_stdin, redir->fd);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
