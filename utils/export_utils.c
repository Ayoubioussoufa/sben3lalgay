/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 17:15:31 by aybiouss          #+#    #+#             */
/*   Updated: 2023/03/12 17:15:43 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	ft_swap(t_env_elem *a, t_env_elem *b)
{
	char	*key_tmp;
	char	*val_tmp;

	key_tmp = a->key;
	val_tmp = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = key_tmp;
	b->value = val_tmp;
}

void	ft_sort(t_env *env)
{
	t_env_elem	*current;

	current = env->head;
	while (current->next)
	{
		if (ft_strcmp(current->key, current->next->key) > 0)
		{
			ft_swap(current, current->next);
			current = env->head;
		}
		else
			current = current->next;
	}
}

void	print_sorted_env(t_env *env)
{
	t_env		*tmp;
	t_env_elem	*current;

	tmp = env;
	ft_sort(tmp);
	current = tmp->head;
	while (current)
	{
		printf("declare -x %s", current->key);
		if (current->value && current->equal)
			printf("=\"%s\"", current->value);
		else if (current->equal)
			printf("=\"\"");
		printf("\n");
		current = current->next;
	}
}
