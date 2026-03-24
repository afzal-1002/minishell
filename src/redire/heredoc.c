/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal <mafzal@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06                                  #+#    #+#         */
/*   Updated: 2026/03/24                                  ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		*get_next_line(int fd);

static int	wait_and_prepare_heredoc(pid_t pid, t_redir *redir)
{
	int		status;
	char	*old_file;

	if (waitpid(pid, &status, 0) == -1)
		return (setup_signals(), -1);
	setup_signals();
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		g_signal_state = -1;
		return (-1);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		g_signal_state = -1;
		return (-1);
	}
	old_file = redir->file;
	redir->file = ft_strdup(".heredoc_tmp");
	free(old_file);
	if (!redir->file)
		return (-1);
	return (0);
}

/*
** SAFE LINE READER (using read)
*/
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

/*
** HEREDOC WRITER
*/
static int	write_heredoc_lines(int write_fd, char *delim, t_global *global)
{
	char	*line;
	char	*expanded;
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
		if (!line)
		{
			write(1, "warning: heredoc delimited by EOF\n", 34);
			break ;
		}
		if (ft_strcmp(line, clean) == 0)
			break ;
		expanded = line;
		if (expand)
		{
			expanded = expand_word(line, global);
			if (!expanded)
				return (free(clean), -1);
		}
		write(write_fd, expanded, ft_strlen(expanded));
		write(write_fd, "\n", 1);
		if (expand)
			free(expanded);
	}
	free(clean);
	return (0);
}

/*
** MAIN HEREDOC FUNCTION
*/
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
	return (wait_and_prepare_heredoc(pid, redir));
}

/*
** PROCESS ALL HEREDOCS
*/
int	process_heredoc(t_cmd *cmd, t_global *global)
{
	t_redir *redir;

	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == T_HEREDOC)
			{
				if (apply_heredoc(redir, global) == -1)
					return (-1);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}