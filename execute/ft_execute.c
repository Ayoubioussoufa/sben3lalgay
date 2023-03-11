/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 18:28:01 by aybiouss          #+#    #+#             */
/*   Updated: 2023/03/11 16:42:30 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	if_directory(char *str)
{
	if (!opendir(str))
		return ;
	ft_putstr_fd("Minishell", 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": is a directory\n", 2);
	status = 126;
	exit(126);
}

void	ft_execute(t_shell *shell, t_env *env)
{
	pid_t	pid;

	exec_redir(shell);
	check_fd(shell->cmd);
	if (check_builtins(shell->cmds[0]) == 1)
		ft_which_cmd(shell->cmds, env);
	else
	{
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
		{
			if_directory(shell->cmds[0]);
			execute_cmd(shell, env->env);
		}
		else
		{
			if (shell->cmd->fd.in != 0)
				close(shell->cmd->fd.in);
			if (shell->cmd->fd.out != 1)
				close(shell->cmd->fd.out);
			waitpid(pid, &status, 0);
		}
	}
}

void	child(t_shell *shell, t_env *env)
{
	exec_redir(shell);
	dup_close(&shell->cmd->fd);
	if (shell->next != NULL) 	// close the pipe ends
		close(shell->cmd->fd.out);
	if (check_builtins(shell->cmds[0]))
		ft_which_cmd(shell->cmds, env);
	else
		execute_cmd(shell, env->env);
	exit(EXIT_SUCCESS);
}

void	waitchilds(void)
{
	while (wait(NULL) != -1);
	// if (WIFEXITED(status))
	// 	status =  WEXITSTATUS(status);
	// else if (WIFSIGNALED(status))
	// 	status += 128;
	// else if (WIFSTOPPED(status))
	// 	status =  WSTOPSIG(status);
	// else if (WIFCONTINUED(status))
	// 	printf("Child process continued\n");
	// if (WIFEXITED(status))
	//     printf("Child process exited with status %d\n", WEXITSTATUS(status));
	// if (status > 256)
	// 	printf("status after %d\n", status / 256);
	// else
	// printf("status after %d\n", status);
}

void	execute(t_shell *shell, t_env *env)
{
	int		fd[2];
	pid_t	pid;

	open_heredocs(shell, env);
	if (shell && shell->type == 3)
	{
		while (shell && shell->next)
		{
			if (pipe(fd) == -1)
				error("pipe", errno);
			shell->cmd->fd.out = fd[1];
			shell->next->cmd->fd.in = fd[0];
			pid = fork();
			if (pid == -1)
				error("fork", errno);
			if (pid == 0)
			{
				close(fd[0]);
				child(shell, env);
			}
			else
			{
				parent(shell);
				close(fd[1]);
				shell = shell->next;
			}
		}
		if (shell)
			ft_execute(shell, env);
		// waitchilds();
	}
}