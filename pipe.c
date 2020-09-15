/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2019/10/31 13:49:20 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_pipe(t_command **commands, char ***env, int *i)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;
	int		fdout;
	int		fdin;
	int		fd[3];

	status = 0;
	set_fd(fd);
	fdin = dup(fd[0]);
	while (commands[(*i)] != NULL)
	{
		dup2(fdin, 0);
		close(fdin);
		if (!(commands[*i]->ctrl_op & PIPE_OP))
			fdout = dup(fd[1]);
		else
		{
			pipe(pipefd);
			fdout = pipefd[1];
			fdin = pipefd[0];
		}
		dup2(fdout, 1);
		close(fdout);
		if ((pid = fork()) == 0)
			exit((status = exec_command(commands[*i], commands, pid, env)));
		if (!(commands[*i]->ctrl_op & PIPE_OP))
			break ;
		(*i)++;
	}
	dup2(fd[0], 0);
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
	while ((pid = wait(&status)) > 0)
	{
	}
	return (status);
}
