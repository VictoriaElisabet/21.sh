/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2020/09/16 15:14:30 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int		print_redir_error(char *str)
{
	ft_printf("%s\n", str);
	return(EXIT_FAILURE);
}

int		is_digits(t_token *tmp, int *dash)
{
	int len;

	len = ft_strlen(tmp->token) - 1;
	if (tmp->token[len] == '-')
	{
		len--;
		*dash = 1;
	}
	while (len > 0)
	{
		if (ft_isdigit(tmp->token[len]) == 0)
			return (0);
		len--;
	}
	return (1);
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
		if (dup2(fd, n) == -1)
			return (print_redir_error(DUP2_FAIL));
		if (dash == 1)
			if (close(n) == -1)
				return (print_redir_error(CLOSE_ERR));
	}
	else if (r_type == G_AND_H || r_type == L_AND_H)
		if (close(n) == -1)
			return (print_redir_error(CLOSE_ERR));
	close(fd);
	return (0);
}

void	reset_redirections(int fd[3])
{
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	dup2(fd[2], STDERR_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
}

int		open_fd(t_token *tmp, int fd, int r_type)
{
	if (tmp->next == NULL)
		return(print_redir_error(SYNTAX_ERR));
	if ((r_type == G || r_type == G_AND) && tmp->next != NULL)
	{
		if ((fd = open(tmp->next->token, O_WRONLY | O_CREAT |
		O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
			return (-1);
	}
	else if (r_type == GG && tmp->next != NULL)
	{
		if ((fd = open(tmp->next->token, O_WRONLY | O_CREAT |
		O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
			return (-1);
	}
	else if ((r_type == L || r_type == L_AND) && tmp->next != NULL)
	{
		if ((fd = open(tmp->next->token, O_RDONLY)) == -1)
			return (-1);
	}
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

int		set_redir_out(t_token *tmp, int r_type)
{
	int n;
	int fd;
	int dash;

	dash = 0;
	fd = 1;
	if (tmp->prev != NULL)
		n = tmp->prev->type == IO_NUM ? ft_atoi(tmp->token) : STDOUT_FILENO;
	if ((r_type == G || r_type == GG) && tmp->next != NULL)
		fd = open_fd(tmp, fd, r_type);
	else if (r_type == G_AND && tmp->next != NULL)
	{
		if (n == 1 && is_digits(tmp->next, &dash) == 0)
		{
			if (dash == 1)
				return (print_redir_error(SYNTAX_ERR));
			fd = open_fd(tmp, fd, r_type);
			dup2_fd(2, fd, dash, r_type);
		}
		else
		{
			if (isatty((fd = ft_atoi(tmp->next->token)) == 0))
				return (print_redir_error(FD_ERR));
		}
	}
	return (dup2_fd(n, fd, dash, r_type));
}

int		set_redir_in(t_token *tmp, int r_type)
{
	int n;
	int fd;
	int dash;

	dash = 0;
	fd = 0;
	if (tmp->prev != NULL)
		n = tmp->prev->type == IO_NUM ? ft_atoi(tmp->token) : STDIN_FILENO;
	if (r_type == L && tmp->next != NULL)
		fd = open_fd(tmp, fd, r_type);
	else if ((r_type == LL || r_type == LL_H) && tmp->next != NULL)
		return (open_heredoc_fd(tmp, n, dash, r_type));
	else if (r_type == L_AND && tmp->next != NULL)
	{
		if (n == 0 && is_digits(tmp->next, &dash) == 0)
		{
			if (dash == 1)
				return (print_redir_error(SYNTAX_ERR));
			fd = open_fd(tmp, fd, r_type);
		}
		else
		{
			if (isatty((fd = ft_atoi(tmp->next->token)) == 0))
				return (print_redir_error(FD_ERR));
		}
	}
	return (dup2_fd(n, fd, dash, r_type));
}

int		set_redir_in_out(t_token *tmp)
{
	int status;

	status = 0;
	status = set_redir_in(tmp, L);
	status = set_redir_out(tmp, G);
	return (status);
}

int		is_redir_in(int r_type)
{
	if (r_type == L || r_type == LL || r_type == L_AND
	|| r_type == L_AND_H || r_type == LL_H)
		return (1);
	return (0);
}

int		is_redir_out(int r_type)
{
	if (r_type == G || r_type == GG || r_type == G_AND
	|| r_type == G_AND_H || r_type == CLOBBER)
		return (1);
	return (0);
}

void	set_redir_list(char redir[11][4])
{
	ft_strcpy(redir[0], "<");
	ft_strcpy(redir[1], "<<");
	ft_strcpy(redir[2], "<&");
	ft_strcpy(redir[3], "<&-");
	ft_strcpy(redir[4], "<<-");
	ft_strcpy(redir[5], "<>");
	ft_strcpy(redir[6], ">");
	ft_strcpy(redir[7], ">>");
	ft_strcpy(redir[8], ">&");
	ft_strcpy(redir[9], ">&-");
	ft_strcpy(redir[10], ">|");
}

int		get_redir(char *token)
{
	int		i;
	char	redir[11][4];

	i = 0;
	set_redir_list(redir);
	while (i < 11)
	{
		if (ft_strcmp(token, redir[i]) == 0)
			return (i);
		i++;
	}
	return (0);
}

void	set_fd(int fd[3])
{
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	fd[2] = dup(STDERR_FILENO);
}

int		set_redirections(t_command *command)
{
	t_token	*tmp;
	int		r_type;
	int		status;

	tmp = command->tokens;
	r_type = 0;
	set_fd(command->fd);
	status = 0;
	while (tmp != NULL)
	{
		if (tmp->type == REDIR)
		{
			r_type = get_redir(tmp->token);
			if (is_redir_in(r_type) == 1)
				status = set_redir_in(tmp, r_type);
			else if (is_redir_out(r_type) == 1)
				status = set_redir_out(tmp, r_type);
			else if (r_type == LG)
				status = set_redir_in_out(tmp);
		}
		tmp = tmp->next;
	}
	return (status);
}
