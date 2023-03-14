/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:07:54 by aybiouss          #+#    #+#             */
/*   Updated: 2023/02/19 11:07:54 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	pwd_builtin(char *cmd)
{
	char	cwd[256];
	char	*dir;

	(void)cmd;
	dir = getcwd(cwd, sizeof(cwd));
	if (!dir)
	{
		perror("minishell: pwd: ");
		g_status = EXIT_FAILURE;
		return (-1);
	}
	printf("%s\n", dir);
	g_status = EXIT_SUCCESS;
	return (g_status);
}
