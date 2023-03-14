/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:40:06 by aybiouss          #+#    #+#             */
/*   Updated: 2023/03/14 19:10:35 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	add_env_elemi(t_env *env, t_env_elem *new)
{
	t_env_elem	*tmp;

	tmp = env->head;
	if (!env->head)
		env->head = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		env->size++;
		tmp->next = new;
		new->prev = tmp;
		new->next = NULL;
	}
}

void	free_array(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		free(env[i++]);
	// free(env);
}

void	add_var(t_env **env, char *cmd)
{
	t_env_elem	*new;
	t_env_elem	*newl;

	newl = new_env_elem(cmd);
	new = search_env_elem(*env, newl->key);
	printf("%s \t %s\n", newl->key, newl->value);
	if (new)
	{
		free(new->value);
		free(newl->key);
		new->value = newl->value;
	}
	else
		add_env_elem(*env, newl);
	if ((*env)->env)
		free_array((*env)->env);
	(*env)->env = convert_array(*env);
}

int	check_alpha(char *cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (ft_isalnum(cmd[i]) || cmd[i] == '_')
			i++;
		else if (cmd[i] == '=')
			return (1);
		else
			return (0);
	}
	return (1);
}

// char	**convert_array(t_env *env)
// {
// 	t_env_elem	*tmp;
// 	char		**arr;
// 	int			i;

// 	i = -1;
// 	tmp = env->head;
// 	arr = malloc((env->size + 1) * sizeof(char *));
// 	if (!arr)
// 	{
// 		free(arr);
// 		return (NULL);
// 	}
// 	while (++i <= env->size)
// 	{
// 		arr[i] = ft_strdup(tmp->key);
// 		if (tmp->value)
// 		{
// 			arr[i] = ft_strjoinfree(arr[i], "=");
// 			arr[i] = ft_strjoinfree(arr[i], tmp->value);
// 		}
// 		tmp = tmp->next;
// 	}
// 	arr[i] = 0;
// 	return (arr);
// }

int	export_builtin(char **cmd, t_env *env)
{
    int	i;

    i = 1;
    if (!cmd[1])
        print_sorted_env(env);
    else
    {
        while (cmd[i])
        {
            if (!ft_isalpha(cmd[i][0]) && cmd[i][0] != '_')
                ft_puterr(cmd[0], cmd[i], "not a valid identifier", EXIT_FAILURE);
            else if (!check_alpha(cmd[i]))
                ft_puterr(cmd[0], cmd[i], "not a valid identifier", EXIT_FAILURE);
            else
                add_var(&env, cmd[i]);
            i++;
        }
    }
    g_status = EXIT_SUCCESS;
    return (g_status);
}

// int	export_builtin(char **cmd, t_env *env)
// {
// 	int	i;

// 	i = 1;
// 	if (!cmd[1])
// 		print_sorted_env(env);
// 	else
// 	{
// 		while (cmd[i])
// 		{
// 			if (!ft_isalpha(cmd[i][0]) && cmd[i][0] != '_')
// 				ft_puterr(cmd[0], cmd[i],
// 					"not a valid identifier", EXIT_FAILURE);
// 			else if (!check_alpha(cmd[i]))
// 				ft_puterr(cmd[0], cmd[i],
// 					"not a valid identifier", EXIT_FAILURE);
// 			else
// 				add_var(&env, cmd[i]);
// 			i++;
// 		}
// 	}
// 	env->env = convert_array(env);
// 	g_status = EXIT_SUCCESS;
// 	return (g_status);
// }
