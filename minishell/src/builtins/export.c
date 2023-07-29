/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:56:31 by plopes-c          #+#    #+#             */
/*   Updated: 2023/07/26 10:10:16 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void export_execute_no_input(char *print, char **flags, char **env);
static void export_execute_with_input(char *str, char **flags);
static void split_with_one_equal(char *str, char **env);
char **env_copy(char **env, char *new_str);

void export_prepare(t_command *command, int index)
{
	int i;
	int len;

	if (!command->terminal[index + 1] && !command->status)
		command->execute = export_execute_no_input;
	else
	{
		len = 0;
		while (command->terminal[len])
			len++;
		command->flags = ft_calloc(sizeof(char *), len);
		if (!command->flags)
			return;
		i = 0;
		while (command->terminal[++index])
		{
			if (!ft_isalpha(command->terminal[index][0]))
				ft_printf("Minishell: export: '%s': not a valid identifier\n", command->terminal[index]);
			else
				command->flags[i++] = ft_strdup(command->terminal[index]);
			command->terminal[index][0] = 0;
		}
	if (!command->status)
		command->execute = export_execute_with_input;
	if (execute_now(command))
		command->status = PARENT;
	}
}

static void export_execute_no_input(char *print, char **flags, char **env)
{
	int i;
	int j;
	int	counter;

	(void)flags;
	(void)print;
	i = 0;
	while (env && env[i])
	{
		counter = 0;
		j = 0;
		write(1, "declare -x ", 11);
		while (env[i][j])
		{
			write(1, &env[i][j], 1);
			if (env[i][j] == '=' && !counter)
			{
				write(1, "\"", 1);
				counter++;
			}
			j++;
		}
		if (counter)
			write(1, "\"", 1);
		write(1, "\n", 1);
		i++;
	}
}

static void export_execute_with_input(char *str, char **flags)
{
	int i;

	(void)str;
	i = 0;
	while (flags[i])
	{
		split_with_one_equal(flags[i], (*control())->envp);
		i++;
	}
}

static void split_with_one_equal(char *str, char **env)
{
	char 	**var;
	char	*value;
	char	*name;

	name = ft_strdup(str);
	value = ft_strchr(name, '=');
	if (value)
		*value++ = 0;
	var = find_var(name, env, NULL, NULL);
	if (var && value)
	{
		free(*var);
		*var = ft_strdup(str);
	}
	else if (!var && value)
		(*control())->envp = env_copy(env, ft_strdup(str));
	else if (!var && !value)
		(*control())->envp = env_copy(env, ft_strdup(name));
	free(name);
}

char **find_var(char *name, char **env, int *index, int *size)
{
	int i;
	int	j;

	i = 0;
	while (env[i])
		i++;
	if (size)
		*size = i;
	i = 0;
	while (env[i])
	{
		j = 0;
		while (name[j] && name[j] == env[i][j])
			j++;
		if (!name[j])
		{
			if (index)
				*index = i;
			return (&env[i]);
		}
		i++;
	}
	if (index)
		*index = -1;
	return (NULL);
}

char **env_copy(char **env, char *new_str)
{
	int	i;
	char **new_env;

	i = 0;
	while (env && env[i])
		i++;
	new_env = ft_calloc(sizeof(char *), i + 2);
	i = 0;
	while (env && env[i])
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = new_str;
	free(env);
	return (new_env);
}
