/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:07:29 by aybiouss          #+#    #+#             */
/*   Updated: 2023/03/14 13:18:06 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	error(char *str, int n)
{
	if (str)
	{
		ft_putstr_fd(strerror(n), 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
	exit(n);
}

int	ft_perror(char *msg, char *utils)
{
	write(2, msg, ft_strlen(msg));
	if (utils)
		write(2, utils, ft_strlen(utils));
	write(2, "\n", 1);
	return (EXIT_FAILURE);
}

int	ft_puterr(char *cmd, char *arg, char *msg, int errnum)
{
	write(2, "Minishell: ", ft_strlen("minishell: "));
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, arg, ft_strlen(arg));
	write(2, ": ", 2);
	if (!msg)
		perror("");
	else
		write(2, arg, ft_strlen(arg));
	status = errnum;
	return (errnum);
}
