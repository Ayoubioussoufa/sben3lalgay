/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 18:28:01 by aybiouss          #+#    #+#             */
/*   Updated: 2023/03/14 16:15:07 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	ft_execute(t_shell *shell, t_env *env)
{
	pid_t	pid;

	exec_redir(shell);
	check_fd(shell->cmd);
	if (if_directory(shell->cmds[0]))
		return ;
	if (check_builtins(shell->cmds[0]) == 1)
		ft_which_cmd(shell->cmds, env, 1);
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
		}
	}
}
			// close(shell->cmd->fd.in);
			// close(shell->cmd->fd.out);

void	child(t_shell *shell, t_env *env, int fd[2])
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler);
	close(fd[0]);
	exec_redir(shell);
	dup_close(&shell->cmd->fd);
	if (shell->next != NULL)
		close(shell->cmd->fd.out);
	if (check_builtins(shell->cmds[0]))
		ft_which_cmd(shell->cmds, env, 0);
	else
		execute_cmd(shell, env->env);
	exit(EXIT_SUCCESS);
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

void	executings(t_shell *shell, t_env *env, int in, int out)
{
	int		fd[2];
	pid_t	pid;

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
				child(shell, env, fd);
			else
				parent(shell, fd);
				shell = shell->next;
				status = 999;
		}
		ft_execute(shell, env);
		waitchilds(in, out);
	}
}

void	execute(t_shell *shell, t_env *env)
{
	int		orig_stdin;
	int		orig_stdout;

	orig_stdin = dup(STDIN_FILENO);
	orig_stdout = dup(STDOUT_FILENO);
	open_heredocs(shell, env);
	executings(shell, env, orig_stdin, orig_stdout);
}
