/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:28:39 by aybiouss          #+#    #+#             */
/*   Updated: 2023/03/14 11:46:57 by aybiouss         ###   ########.fr       */
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
	ft_putstr_fd("Minishell", 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": is a directory\n", 2);
	status = 126;
	return (status);
}

int	check_builtins(char *cmd)
{
	if (cmd && !ft_strcmp(cmd, "export"))
		return (1);
	else if (cmd && !ft_strcmp(cmd, "unset"))
		return (1);
	else if (cmd && !ft_strcmp(cmd, "pwd"))
		return (1);
	else if (cmd && !ft_strcmp(cmd, "exit"))
		return (1);
	else if (cmd && !ft_strcmp(cmd, "cd"))
		return (1);
	else if (cmd && !ft_strcmp(cmd, "env"))
		return (1);
	else if (cmd && !ft_strcmp(cmd, "echo"))
		return (1);
	return (0);
}

void	ft_which_cmd(char **cmd, t_env *env)
{
	if (cmd[0] && !ft_strcmp(cmd[0], "export"))
		export_builtin(cmd, env);
	else if (cmd[0] && !ft_strcmp(cmd[0], "unset"))
		unset_builtin(cmd, env);
	else if (cmd[0] && !ft_strcmp(cmd[0], "pwd"))
		pwd_builtin(*cmd);
	else if (cmd[0] && !ft_strcmp(cmd[0], "exit"))
		exit_builtin(cmd, env);
	else if (cmd[0] && !ft_strcmp(cmd[0], "cd"))
		cd_builtin(cmd, env);
	else if (cmd[0] && !ft_strcmp(cmd[0], "env"))
		env_builtin(cmd, env);
	else if (cmd[0] && !ft_strcmp(cmd[0], "echo"))
		echo_builtin(cmd);
}
