/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 18:28:01 by aybiouss          #+#    #+#             */
/*   Updated: 2023/03/12 09:49:08 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

// void	dup_close(t_fd *fd)
// {
// 	if (fd->in != STDIN_FILENO && fd->in > 0)
// 	{
// 		if (dup2(fd->in, STDIN_FILENO) == -1)
// 			error("dup2", errno);
// 		if (close(fd->in) == -1)
// 			error("close", errno);
// 	}
// 	if (fd->out != STDOUT_FILENO && fd->out > 1)
// 	{
// 		if (dup2(fd->out, STDOUT_FILENO) == -1)
// 			error("dup2", errno);
// 		if (close(fd->out) == -1)
// 			error("close", errno);
// 	}
// }

// int	exec_redir_in(char *infile, int *in)
// {
// 	if (access(infile, F_OK) == 0)
// 	{
// 		if (*in != STDIN_FILENO && *in > 0)
// 		{
// 			if (close(*in) == -1)
// 				error("close", errno);
// 		}
// 		if ((*in = open(infile, O_RDONLY, 0666)) == -1)
// 			error("open", errno);
// 		return (1);
// 	}
// 	else
// 	{
// 		*in = -1;
// 		write(2, "minishell: \n", 12);
// 		printf("%s\n", infile);
// 		ft_perror(infile, ": No such file or directory");
// 		return (0);
// 	}
// }

// void	check_fd(t_cmd *cmd)
// {
// 	if (cmd && cmd->fd.in != STDIN_FILENO)
// 	{
// 		if (dup2(cmd->fd.in, STDIN_FILENO) == -1)
// 			error("dup2", errno);
// 		if (close(cmd->fd.in) == -1)
// 			error("close", errno);
// 	}
// 	if (cmd && cmd->fd.out != STDOUT_FILENO)
// 	{
// 		if (dup2(cmd->fd.out, STDOUT_FILENO) == -1)
// 			error("dup2", errno);
// 		if (close(cmd->fd.out) == -1)
// 			error("close", errno);
// 	}
// }

// void	exec_redir(t_shell *shell)
// {
// 	t_redire	*redir;

// 	redir = shell->redir;
// 	if (!redir)
// 		return ;
// 	while (redir)
// 	{
// 		if (redir->type == INFILE)
// 			exec_redir_in(redir->infile, &shell->cmd->fd.in);
// 		else if (redir->type == OUTFILE || redir->type == APPEND)
// 		{
// 			close(shell->cmd->fd.out);
// 			if (redir->type == OUTFILE)
// 				shell->cmd->fd.out = open(redir->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 			else if (redir->type == APPEND)
// 				shell->cmd->fd.out = open(redir->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 			if (shell->cmd->fd.out == -1)
// 				error("open", errno);
// 		}
// 		else if (redir->type == DELIMITER)
// 		{
// 			close(shell->cmd->fd.in);
// 			shell->cmd->fd.in = open("/tmp/minishell", O_RDWR , 0644);
// 		}
// 		redir = redir->next;
// 	}
// }

int	if_directory(char *str)
{
	if (!opendir(str))
		return (0);
	ft_putstr_fd("Minishell", 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": is a directory\n", 2);
	status = 126;
	return (1);
}

// void	parent(t_shell *shell)
// {
// 	if (shell->cmd->fd.in != STDIN_FILENO)
// 		close(shell->cmd->fd.in);
// 	if (shell->cmd->fd.out != STDOUT_FILENO)
// 		close(shell->cmd->fd.out);
// }

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
			close(shell->cmd->fd.in);
			close(shell->cmd->fd.out);
		}
	}
}

void	child(t_shell *shell, t_env *env)
{
	exec_redir(shell);
	dup_close(&shell->cmd->fd);
	if (shell->next != NULL) // close the pipe ends
		close(shell->cmd->fd.out);
	if (check_builtins(shell->cmds[0]))
		ft_which_cmd(shell->cmds, env);
	else
		execute_cmd(shell, env->env);
	exit(EXIT_SUCCESS);
}

void waitchilds(int orig_stdin, int orig_stdout, int pid)
{
    pid_t res;

    res = 0;
    signal(SIGINT, sigint_handler);
    while (res != -1)
    {
        res = waitpid(-1, &status, 0);
		if (res == pid)
		{
			if (WIFEXITED(status))
            	status = WEXITSTATUS(status);
        	else if (WIFSIGNALED(status))
            	status = WTERMSIG(status) + 128;
		}
    }
    if (errno == ENOENT) // executable file not found
        status = 126;
    dup2(orig_stdin, STDIN_FILENO);
    dup2(orig_stdout, STDOUT_FILENO);
}

void	execute(t_shell *shell, t_env *env)
{
	int		fd[2];
	pid_t	pid;
	int		orig_stdin, orig_stdout;

	printf("START WIH %d\n", status);
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
		waitchilds(orig_stdin, orig_stdout, pid);
		printf("EXIT WITH %d\n", status);
	}
}

// void	waitchilds(void)
// {
// 	while (wait(NULL) != -1);
// }
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