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

int		is_digits(t_token *tmp, int *dash)
{
	int len;

	len = ft_strlen(tmp->token);
	if (tmp->token[len - 1] == '-')
	{
		len--;
		*dash = 1;
	}
	while (len > 0)
	{
		if (ft_isdigit(tmp->token[len - 1]) == 0)
			return (0);
		len--;
	}
	return (1);
}

int		set_redir_out(t_token *tmp, int r_type, int dash)
{
	int n;
	int fd;

	fd = 1;
	n = STDOUT_FILENO;
	if (tmp->prev != NULL && tmp->prev->type == IO_NUM)
		n = ft_atoi(tmp->prev->token);
	if ((r_type == G || r_type == GG) && tmp->next != NULL)
		if ((fd = open_fd(tmp, fd, r_type, &dash)) == -1)
			return (-1);
	if (r_type == G_AND && tmp->next != NULL)
	{
		if (n == 1 && is_digits(tmp->next, &dash) == 0)
		{
			if ((fd = open_fd(tmp, fd, r_type, &dash)) == -1)
				return (-1);
			dup2(fd, 2);
		}
		else if (is_digits(tmp->next, &dash) == 1)
		{
			if ((isatty(fd = ft_atoi(tmp->next->token))) == 0)
				return (print_redir_error(FD_ERR));
		}
	}
	return (dup2_fd(n, fd, dash, r_type));
}

int		set_redir_in(t_token *tmp, int r_type, int dash)
{
	int n;
	int fd;

	fd = 0;
	n = STDIN_FILENO;
	if (tmp->prev != NULL && tmp->prev->type == IO_NUM)
		n = ft_atoi(tmp->prev->token);
	if (r_type == L && tmp->next != NULL)
		if ((fd = open_fd(tmp, fd, r_type, &dash)) == -1)
			return (-1);
	if ((r_type == LL || r_type == LL_H) && tmp->next != NULL)
		return (open_heredoc_fd(tmp, n, dash, r_type));
	if (r_type == L_AND && tmp->next != NULL)
	{
		if (n == 0 && is_digits(tmp->next, &dash) == 0)
		{
			if ((fd = open_fd(tmp, fd, r_type, &dash)) == -1)
				return (-1);
		}
		else if (is_digits(tmp->next, &dash) == 1)
			if ((isatty(fd = ft_atoi(tmp->next->token))) == 0)
				return (print_redir_error(FD_ERR));
	}
	return (dup2_fd(n, fd, dash, r_type));
}

int		set_redir_in_out(t_token *tmp, int dash)
{
	int status;

	status = 0;
	status = set_redir_in(tmp, L, dash);
	status = set_redir_out(tmp, G, dash);
	return (status);
}

int		set_redirections(t_command *command)
{
	t_token	*tmp;
	int		r_type;
	int		status;
	int		dash;

	tmp = command->tokens;
	r_type = 0;
	set_fd(command->fd);
	status = 0;
	dash = 0;
	while (tmp != NULL)
	{
		if (tmp->type == REDIR)
		{
			r_type = get_redir(tmp->token);
			if (is_redir_in(r_type) == 1)
				status = set_redir_in(tmp, r_type, dash);
			else if (is_redir_out(r_type) == 1)
				status = set_redir_out(tmp, r_type, dash);
			else if (r_type == LG)
				status = set_redir_in_out(tmp, dash);
		}
		tmp = tmp->next;
	}
	return (status);
}
