/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:43:39 by aybiouss          #+#    #+#             */
/*   Updated: 2023/03/14 17:25:15 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	exit_builtin(char **cmd, int flag)
{
	int	i;

	i = 0;
	if (flag)
		exit_flag(cmd, i);
	else
	{
		if (!cmd[1])
			exit(EXIT_SUCCESS);
		while (cmd[1][i])
		{
			if (cmd[1][0] == '+' || cmd[1][0] == '-')
				i++;
			if (ft_isdigit(cmd[1][i]) && (long)atoi(cmd[1]) <= LLONG_MAX)
				i++;
			else
				exit_error(cmd, 1);
		}
		if (cmd[2])
			exit_error(cmd, 0);
		exit(EXIT_SUCCESS);
	}
	return (1);
}
