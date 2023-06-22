/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:56:31 by plopes-c          #+#    #+#             */
/*   Updated: 2023/06/23 00:21:12 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_execute_no_input(char *print, char **flags, char **env);
static void	export_execute_with_input(char *str, char** flags, char **env);

void	export_prepare(t_command *command, int index)
{
	(void)index;
	if (!command->terminal[1])
		command->execute = export_execute_no_input;
	else
	{
		command->execute = export_execute_with_input;
		if (ft_isdigit(command->terminal[1][0]))
		{
			ft_printf("Minishell: export: '%s': not a valid identifier\n", command->terminal[1]);
			command->execute = do_nothing;
		}
		command->exec_path = ft_strdup(command->terminal[index + 1]);
		command->terminal[1][0] = 0;
	}
	while (command->terminal[index + 1] && command->terminal[index + 2])
	{
		ft_printf("Minishell: export: '%s': not a valid identifier\n", command->terminal[index + 2]);
		command->terminal[index + 2][0] = 0;
		index++;
	}
}

static void	export_execute_no_input(char *print, char **flags, char **env)
{
	int i;
	
	(void)flags;
	(void)print;
	i = 0;
	while (env[i])
	{
		ft_printf("declare -x %s\n", env[i]);
		i++;
	}
}

static void	export_execute_with_input(char *str, char** flags, char **env)
{
	char *value;
	char **matrix;
	int	i;

	(void)flags;
	i = 0;
	matrix = ft_split(str, '=');
	value = getenv(matrix[0]);
	if (value && matrix[1])
		value = matrix[1];
	while (env[i])
		i++;
	env[i] = ft_strdup(str);
	env[i++] = NULL;
}
