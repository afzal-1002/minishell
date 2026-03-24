/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal < mafzal@student.42warsaw.pl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 21:57:09 by mafzal            #+#    #+#             */
/*   Updated: 2026/03/24 22:32:46 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*read_line_stdin(void)
{
	char	buffer[1024];
	int		bytes;
	int		i;
	char	*line;

	bytes = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
	if (bytes <= 0)
		return (NULL);
	buffer[bytes] = '\0';
	i = 0;
	while (i < bytes && buffer[i] != '\n')
		i++;
	if (i < bytes)
		buffer[i] = '\0';
	if (i > 0 && buffer[i - 1] == '\r')
		buffer[i - 1] = '\0';
	line = ft_strdup(buffer);
	return (line);
}

static int	handle_heredoc_eof(char *line)
{
	if (!line)
	{
		write(1, "warning: heredoc delimited by EOF\n", 34);
		return (1);
	}
	return (0);
}

static int	expand_and_write_line(int write_fd, char *line, int expand,
		t_global *global)
{
	char	*expanded;

	expanded = line;
	if (expand)
	{
		expanded = expand_word(line, global);
		if (!expanded)
			return (-1);
	}
	write(write_fd, expanded, ft_strlen(expanded));
	write(write_fd, "\n", 1);
	if (expand)
		free(expanded);
	return (0);
}

static int	write_heredoc_lines(int write_fd, char *delim, t_global *global)
{
	char	*line;
	char	*clean;
	int		expand;

	expand = (ft_strchr(delim, '\'') == NULL && ft_strchr(delim, '"') == NULL);
	clean = handle_delim(delim);
	if (!clean)
		return (-1);
	while (1)
	{
		write(1, "> ", 2);
		line = read_line_stdin();
		if (handle_heredoc_eof(line))
			break ;
		if (ft_strcmp(line, clean) == 0)
			break ;
		if (expand_and_write_line(write_fd, line, expand, global) == -1)
			return (free(clean), -1);
	}
	free(clean);
	return (0);
}

int	apply_heredoc(t_redir *redir, t_global *global)
{
	int		fd;
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return (setup_signals(), -1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		g_signal_state = 1;
		fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			exit(1);
		if (write_heredoc_lines(fd, redir->file, global) == -1)
		{
			close(fd);
			exit(1);
		}
		close(fd);
		exit(0);
	}
	return (prepare_heredoc(pid, redir));
}
