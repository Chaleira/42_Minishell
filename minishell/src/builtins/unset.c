/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:02:01 by plopes-c          #+#    #+#             */
/*   Updated: 2023/06/29 11:28:17 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_execute(char *str, char **flags)
{
	char		**var;
	int			index;
	int			size;
	int			i;

	(void)str;
	i = 0;
	while (flags[i])
	{
		var = find_var(flags[i], (*control())->envp, &index, &size);
		if (var)
		{
			free(*var);
			ft_memmove(&((*control())->envp[index]),
				&((*control())->envp[index + 1]),
				sizeof(char *) * (size - index));
		}
		i++;
	}
}

void	unset_prepare(t_command *command, int index)
{
	int	i;
	int	len;

	if (command->terminal[1])
	{
		len = 0;
		while (command->terminal[len])
			len++;
		command->flags = ft_calloc(sizeof(char *), len);
		i = 0;
		while (command->terminal[++index])
		{
			command->flags[i++] = ft_strdup(command->terminal[index]);
			command->terminal[index][0]= 0;
		}
		unset_execute(NULL, command->flags);
	}
}
