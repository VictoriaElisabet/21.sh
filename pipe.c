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

int create_pipe(t_command *command1, t_command *command2, t_command **commands, char ***env)
{
	int     pipefd[2];
	pid_t   pid1;
	pid_t   pid2;
	int     status;

	status = 0;
	if(pipe(pipefd) != -1)
	{
		if((pid1 = fork()) == -1)
			return(EXIT_FAILURE); //print error?
		else if (pid1 == 0)
		{
			close(pipefd[0]);
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
			status = exec_command(command1, commands, pid1, env);
			//if((execve("/bin/cat", command1->argv, *env)) == -1)
			//	exit(0);
			//status = exec_command(command1, command_list, env);
		}
		if((pid2 = fork()) == -1)
			return(EXIT_FAILURE); //print error?
		else if (pid2 == 0)
		{
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			status = exec_command(command2, commands, pid2, env);
			//if((execve("/bin/grep", command2->argv, *env)) == -1)
			//	exit(0);	
			//status = exec_command(command2, command_list, env);
		}
						close(pipefd[0]);
				close(pipefd[1]);
			pid1 = waitpid(pid1, &status, 0);
			pid2 = waitpid(pid2, &status, 0);

		//wait(NULL);
		//wait(NULL);
		
				//wait(NULL);
			
	}
	else
	{
		return (EXIT_FAILURE);
		//print pipe error? bara print här å änder status ti -1 ?
	}
	return (status);
}