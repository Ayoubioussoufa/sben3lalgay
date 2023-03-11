/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:13:14 by aybiouss          #+#    #+#             */
/*   Updated: 2023/03/11 16:38:57 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	set_dir(t_env *ev, char *cwd, char *owd)
{
	t_env_elem	*env_elem;

	env_elem = search_env_elem(ev, "PWD");
	if (!env_elem)
		return ;
	env_elem->value = ft_strdup(cwd);
	env_elem = search_env_elem(ev, "OLDPWD");
	if (!env_elem)
		return ;
	env_elem->value = ft_strdup(owd);
}

int	cd_continuation(char **cmd, t_env *env)
{
	if (!ft_strcmp(cmd[1], "~") || !ft_strcmp(cmd[1], "--"))
	{
		if (chdir(expand_env("$HOME", env->env)) != 0)
			return (ft_puterr(cmd[0],
					expand_env("$HOME", env->env), NULL, 1));
	}
	else if (!ft_strcmp(cmd[1], "-"))
	{
		if (chdir(expand_env("$OLDPWD", env->env)) != 0)
			return (ft_puterr(cmd[0],
					expand_env("$OLDPWD", env->env), NULL, 1));
	}
	else if (chdir(cmd[1]) != 0)
		return (ft_puterr(cmd[0], cmd[1], NULL, 1));
	return (0);
}

int	cd_builtin(char **cmd, t_env *env)
{
	char	cwd[524];
	char	owd[524];

	getcwd(owd, sizeof(owd));
	if (!cmd[1])
	{
		if (chdir(expand_env("$HOME", env->env)) != 0)
			return (ft_puterr(cmd[0],
					expand_env("$HOME", env->env), NULL, 1));
	}
	else
		cd_continuation(cmd, env);
	getcwd(cwd, sizeof(cwd));
	set_dir(env, cwd, owd);
	status = EXIT_SUCCESS;
	env->env = convert_array(env);
	return (0);
}
