/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:09:29 by aybiouss          #+#    #+#             */
/*   Updated: 2023/03/14 17:45:45 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	unset_env(char *cmd, t_env *env)
{
	t_env_elem	*elem;

	elem = NULL;
	if (cmd && !ft_isalpha(cmd[0]))
	{
		printf("minishell: unset: `%s`: not a valid identifier\n",
			cmd);
		g_status = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
	else
	{
		elem = search_env_elem(env, cmd);
		if (elem)
			del_env_elem(env, elem);
	}
}

int	unset_builtin(char **cmd, t_env *env)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		unset_env(cmd[i], env);
		i++;
	}
	env->env = convert_array(env);
	g_status = EXIT_SUCCESS;
	return (g_status);
}
		// free(cmd[i]);