/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:30:52 by aybiouss          #+#    #+#             */
/*   Updated: 2023/03/13 16:15:41 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	parent(t_shell *shell)
{
	if (shell->cmd->fd.in != STDIN_FILENO)
		close(shell->cmd->fd.in);
	if (shell->cmd->fd.out != STDOUT_FILENO)
		close(shell->cmd->fd.out);
}

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

char	*get_cmd(char **paths, char *cmd)
{
	int		i;
	char	*tmp;
	char	*path;

	if (!paths)
		return (ft_strdup(cmd));
	if (ft_strchrr(cmd, '/'))
		return (cmd);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	**get_paths(char **env, t_shell *shell)
{
	char	**paths;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH", 4))
		{
			paths = ft_split(env[i] + 5, ':');
			if (!paths)
				error("Split function failed", 1);
			return (paths);
		}
		i++;
	}
	if (access(shell->cmd->cmd, F_OK) == 0)
		return (NULL);
	ft_putstr_fd("Command not found: ", 2);
	ft_putstr_fd(*shell->cmds, 2);
	ft_putstr_fd("\n", 2);
	exit(127);
	return (NULL);
}

void	execute_cmd(t_shell *shell, char **env)
{
	char	**paths;
	char	*argv;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler);
	paths = NULL;
	argv = NULL;
	paths = get_paths(env, shell);
	argv = get_cmd(paths, shell->cmds[0]);
	if (!argv)
	{
		free_paths(paths);
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(ft_strtrim(shell->cmds[0], "\""), 2);
		ft_putstr_fd(": Command not found", 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
	if (execve(argv, shell->cmds, env) == -1)
		error(NULL, errno);
}
