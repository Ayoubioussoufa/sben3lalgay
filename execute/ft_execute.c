/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 18:28:01 by aybiouss          #+#    #+#             */
/*   Updated: 2023/03/13 11:48:56 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	if_directory(char *str)
{
	if (!ft_strncmp(".", str, 2))
	{
		ft_putstr_fd("Minishell", 2);
		ft_putstr_fd(": .: filename argument required\n", 2);
		ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
		status = 2;
		return (status);
	}
	else if (!ft_strncmp("..", str, 3))
	{
		ft_putstr_fd("Minishell", 2);
		ft_putstr_fd(": ..: command not found\n", 2);
		status = 127;
		return (status);
	}
	if (!opendir(str))
		return (0);
	else
	{
		ft_putstr_fd("Minishell", 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": is a directory\n", 2);
		status = 126;
		return (status);
	}
	return (1);
}

void	ft_execute(t_shell *shell, t_env *env)
{
	pid_t	pid;

	exec_redir(shell);
	check_fd(shell->cmd);
	if (if_directory(shell->cmds[0]))
		return ;
	if (check_builtins(shell->cmds[0]) == 1)
		ft_which_cmd(shell->cmds, env);
	else
	{
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
			execute_cmd(shell, env->env);
		else
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				status = WTERMSIG(status);
			close(shell->cmd->fd.in);
			close(shell->cmd->fd.out);
		}
	}
}

void	child(t_shell *shell, t_env *env)
{
	exec_redir(shell);
	dup_close(&shell->cmd->fd);
	if (shell->next != NULL)
		close(shell->cmd->fd.out);
	if (check_builtins(shell->cmds[0]))
		ft_which_cmd(shell->cmds, env);
	else
		execute_cmd(shell, env->env);
}

void	waitchilds(int orig_stdin, int orig_stdout)
{
	signal(SIGINT, sigint_handler);
	while (wait(NULL) != -1)
		;
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
 	else if (WIFSIGNALED(status))
		status = WTERMSIG(status);
	dup2(orig_stdin, STDIN_FILENO);
	dup2(orig_stdout, STDOUT_FILENO);
}

// void	executing(t_Shell)
// {
// 	while (shell && shell->next)
// 	{
// 		if (pipe(fd) == -1)
// 			error("pipe", errno);
// 		shell->cmd->fd.out = fd[1];
// 		shell->next->cmd->fd.in = fd[0];
// 		pid = fork();
// 		if (pid == -1)
// 			error("fork", errno);
// 		if (pid == 0)
// 		{
// 			close(fd[0]);
// 			child(shell, env);
// 		}
// 		else
// 		{
// 			parent(shell);
// 			close(fd[1]);
// 			shell = shell->next;
// 		}
// 	}
// }

void	execute(t_shell *shell, t_env *env)
{
	int		fd[2];
	pid_t	pid;
	int		orig_stdin;
	int		orig_stdout;

	orig_stdin = dup(STDIN_FILENO);
	orig_stdout = dup(STDOUT_FILENO);
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
		ft_execute(shell, env);
		// printf("BINATHOM %d\n", status);
		waitchilds(orig_stdin, orig_stdout);
	}
}
