/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mianni <mianni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:13:26 by mianni            #+#    #+#             */
/*   Updated: 2024/11/13 15:35:12 by mianni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset(char **command)
{
	t_env	*env;
	t_env	*env_ptr;
	int		i;

	i = 1;
	if (!command[i])
		return ;
	while (command[i])
	{
		env = get_env(NULL);
		env_ptr = env;
		while (env_ptr)
		{
			if (env_ptr->name && ft_strcmp(env_ptr->name, command[i]) == 0)
			{
				env_ptr->content = NULL;
				env_ptr->name = NULL;
			}
			env_ptr = env_ptr->next;
		}
		i++;
	}
}
