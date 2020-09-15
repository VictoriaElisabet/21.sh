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

int create_pipe(t_command **commands, char ***env)
{
	int     pipefd[2];
	pid_t   pid;
	//pid_t   pid2;
	int     status;
	int		fdout;
	int		fdin;
	int		i;
	int		fd[3];

	status = 0;
	i = 0;
	set_fd(fd);
	fdin = dup(fd[0]);
	while (commands[i] != NULL)
	{
		dup2(fdin, 0);
		close(fdin);
		if (commands[i + 1] == NULL)
		{
			write(fd[1], "fe", 4);
			fdout = dup(fd[1]);
		}
		else
		{
			write(fd[1], "test", 4);
			pipe(pipefd);
			fdout = pipefd[1];
			fdin = pipefd[0];
		}
		dup2(fdout, 1);
		close(fdout);
		if ((pid = fork()) == 0)
		{
			ft_printf("vart");
			status = exec_command(commands[i], commands, pid, env);
			exit (0);
		}
		i++;
	}
	dup2(fd[0], 0);
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
	while ((pid = wait(&status)) > 0)
	{
		ft_printf("wait");
	}
	//	waitpid(pid, &status, 0);
	//	waitpid(pid, &status, 0);
		/*while(commands[i] != NULL && (commands[i]->ctrl_op & PIPE_OP))
		{
		if(pipe(pipefd) != -1)
		{
			if((pid1 = fork()) == -1)
				return(EXIT_FAILURE); //print error?
			else if (pid1 == 0)
			{
				//close(pipefd[0]);
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[0]);
				status = exec_command(commands[i], commands, pid1, env);
				exit(0);
			}
			if((pid2 = fork()) == -1)
				return(EXIT_FAILURE); //print error?
			else if (pid2 == 0)
			{
				//close(pipefd[1]);
				dup2(pipefd[0], STDIN_FILENO);
				close(pipefd[1]);
				status = exec_command(commands[i + 1], commands, pid2, env);
				exit(0);	
			}

		}	
		else
		{
			return (EXIT_FAILURE);
		//print pipe error? bara print här å änder status ti -1 ?
		}
		i++;
		}
			close(pipefd[0]);
			close(pipefd[1]);
			pid1 = waitpid(pid1, &status, 0);
			pid2 = waitpid(pid2, &status, 0);
	*/
	return (status);
}