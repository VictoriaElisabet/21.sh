/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2020/09/16 15:15:23 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	set_pipe_fd(t_command *command, int fdin, int fd[3])
{
	int pipefd[2];
	int fdout;

	dup2(fdin, 0);
	close(fdin);
	if (!(command->ctrl_op & PIPE_OP))
		fdout = dup(fd[1]);
	else
	{
		pipe(pipefd);
		fdout = pipefd[1];
		fdin = pipefd[0];
	}
	dup2(fdout, 1);
	close(fdout);
}

int		create_pipe(t_command **commands, char ***env, int *i)
{
	pid_t	pid;
	int		status;
	int		fdin;
	int		fd[3];

	status = 0;
	set_fd(fd);
	fdin = dup(fd[0]);
	while (commands[(*i)] != NULL)
	{
		set_pipe_fd(commands[(*i)], fdin, fd);
		if ((pid = fork()) == 0)
			exit((status = exec_command(commands[*i], commands, pid, env)));
		if ((commands[*i]->ctrl_op & PIPE_OP) == 0)
			break ;
		(*i)++;
	}
	reset_redirections(fd);
	while ((pid = wait(&status)) > 0)
	{
	}
	return (status);
}
