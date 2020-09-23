/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2020/09/16 15:14:30 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	reset_redirections(int fd[3])
{
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	dup2(fd[2], STDERR_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
}

void	set_fd(int fd[3])
{
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	fd[2] = dup(STDERR_FILENO);
}

int		dup2_fd(int n, int fd, int dash, int r_type)
{
	if (fd == -1)
		return (print_redir_error(FILE_ERR));
	if (r_type == G || r_type == GG || r_type == L
	|| r_type == LL || r_type == LL_H)
	{
		if (dup2(fd, n) == -1)
			return (print_redir_error(DUP2_FAIL));
	}
	else if (r_type == G_AND || r_type == L_AND)
	{
		if ((dup2(fd, n)) == -1)
			return (print_redir_error(DUP2_FAIL));
		if (dash == 1 || r_type == G_AND_H || r_type == L_AND_H)
		{
			if (close(fd) == -1)
				return (print_redir_error(CLOSE_ERR));
		}
	}
	else if (r_type == G_AND_H || r_type == L_AND_H)
	{
		if (close(n) == -1)
			return (print_redir_error(CLOSE_ERR));
	}
	return (0);
}

int		open_fd(t_token *tmp, int fd, int r_type, int *dash)
{
	if (tmp->next == NULL || tmp->next->type != WORD)
		return (print_redir_error(SYNTAX_ERR));
	if (r_type == G || r_type == G_AND || r_type == L_AND)
	{
		if (*dash == 1)
			return (print_redir_error(SYNTAX_ERR));
		if (r_type == G_AND || r_type == G)
			return ((fd = open(tmp->next->token, O_WRONLY | O_CREAT |
			O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)));
		else if (r_type == L_AND)
			return ((fd = open(tmp->next->token, O_RDONLY)));
	}
	else if (r_type == GG)
		return ((fd = open(tmp->next->token, O_WRONLY | O_CREAT |
		O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)));
	else if (r_type == L)
		return ((fd = open(tmp->next->token, O_RDONLY)));
	return (fd);
}

int		open_heredoc_fd(t_token *tmp, int n, int dash, int r_type)
{
	int fds[2];
	int fd;
	int status;

	if (pipe(fds) == -1)
		return (print_redir_error(PIPE_ERR));
	write(fds[1], tmp->next->token, ft_strlen(tmp->next->token));
	close(fds[1]);
	fd = fds[0];
	status = dup2_fd(n, fd, dash, r_type);
	close(fds[0]);
	return (status);
}
