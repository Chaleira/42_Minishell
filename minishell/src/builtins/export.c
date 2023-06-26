/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:56:31 by plopes-c          #+#    #+#             */
/*   Updated: 2023/06/26 16:21:26 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void export_execute_no_input(char *print, char **flags, char **env);
static void export_execute_with_input(char *str, char **flags, char **env);
static void split_with_one_equal(char *str, char **env);
char **find_var(char *name, char **env);
char **env_copy(char **env, char *new_str);

void export_prepare(t_command *command, int index)
{
	int i;
	int len;

	if (!command->terminal[index + 1])
		export_execute_no_input(NULL, NULL, command->main->envp);
	else
	{
		len = 0;
		while (command->terminal[len])
			len++;
		command->flags = ft_calloc(sizeof(char *), len);
		if (!command->flags)
			return;
		// command->execute = export_execute_with_input;
		index++;
		i = 0;
		while (command->terminal[index])
		{
			if (ft_isdigit(command->terminal[index][0]))
			{
				ft_printf("Minishell: export: '%s': not a valid identifier\n", command->terminal[index]);
			}
			else
			{
				command->flags[i] = ft_strdup(command->terminal[index]);
				i++;
			}
			command->terminal[index][0] = 0;
			index++;
		}
		export_execute_with_input(NULL, command->flags, command->main->envp);
	}
}

static void export_execute_no_input(char *print, char **flags, char **env)
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

static void export_execute_with_input(char *str, char **flags, char **env)
{
	int i;

	(void)str;
	i = 0;
	while (flags[i])
	{
		split_with_one_equal(flags[i], env);
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
	var = find_var(name, env);
	printf("var: %s\n", var[0]);
	if (var && value)
	{
		free(*var);
		*var = ft_strdup(str);
	}
	else if (!var && value)
	{
		HERE;
		env = env_copy(env, str);
	}
	ft_printf("name: %s\n", name);
	ft_printf("value: %s\n", value);

}

char **find_var(char *name, char **env)
{
	int i;
	int	len;

	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(name, env[i], len))
			return (&env[i]);
		i++;
	}
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
