/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:17:08 by aybiouss          #+#    #+#             */
/*   Updated: 2023/03/14 19:09:02 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	exit_error(char **cmd, int flag)
{
	if (flag)
	{
		printf("exit\n");
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	else
	{
		printf("exit\n");
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": too many arguments\n", 2);
		exit(1);
	}
}

void	noexit(char **cmd, int flag)
{
	if (flag)
	{
		printf("exit\n");
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	else
	{
		printf("exit\n");
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": too many arguments\n", 2);
	}
}

void	exit_done(char **cmd, int flag)
{
	if (!flag && g_status == 999)
		g_status = ft_atoi(cmd[1]);
	else if (!flag)
	{
		printf("exit\n");
		exit(ft_atoi(cmd[1]));
	}
	else if (g_status == 999)
	{
		printf("exit\n");
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	else
	{
		printf("exit\n");
		exit(0);
	}
}

void	elseexit(char **cmd, int i)
{
	while (cmd[1][i])
	{
		if (ft_isdigit(cmd[1][i]) && (long)atoi(cmd[1]) <= LLONG_MAX)
			i++;
		else
			exit_error(cmd, 1);
	}
	noexit(cmd, 0);
	g_status = 1;
}

void	exit_flag(char **cmd, int i)
{
	if (cmd[1])
	{
		if (cmd[1][i] == '\0')
			exit_error(cmd, 1);
		if (!cmd[2])
		{
			while (cmd[1][i])
			{
				if (cmd[1][0] == '+' || cmd[1][0] == '-')
					i++;
				else if (ft_isdigit(cmd[1][i])
						&& (long)atoi(cmd[1]) <= LLONG_MAX)
					i++;
				else
					exit_error(cmd, 1);
			}
			exit_done(cmd, 0);
		}
		else
			elseexit(cmd, i);
	}
	else
		exit_done(cmd, 1);
}
