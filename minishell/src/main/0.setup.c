/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0.setup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:59:58 by rteles-f          #+#    #+#             */
/*   Updated: 2023/08/17 11:26:40 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	increase_shlvl(char **envp)
{
	int		increase;
	char	**shlvl;

	shlvl = get_envaddress(envp, "SHLVL");
	if (!shlvl)
	{
		change_env_variable("SHLVL", "1");
		return ;
	}
	increase = ft_atoi(&(*shlvl)[6]) + 1;
	change_env_variable("SHLVL", sttc_itoa(increase));
}

void	update_paths(char **envp, t_control *get)
{
	char	**paths;

	if (get->paths)
		get->paths = free_split(get->paths);
	paths = get_envaddress(envp, "PATH");
	if (!paths)
		get->paths = ft_calloc(sizeof(char **), 2);
	else
		get->paths = ft_split(*paths + 5, ':');
	finish_list_with(get->paths, "/");
}

char	*get_prompt(void)
{
	char		*folder;
	char		*prompt;

	folder = getcwd(NULL, 0);
	prompt = ft_strjoin("\e\001\033[1m\002\001\033[31m\002\
Minishell \001\033[0m\002\001\033[34m\002",
			ft_strrchr(folder, '/') + 1);
	free(folder);
	ft_stradd(&prompt, " \001\033[0;33m\002\001\u2717\002 \001\033[0m\002");
	return (prompt);
}
// char	*get_prompt(void)
// {
// 	char		*folder;
// 	char		*prompt;

// 	folder = getcwd(NULL, 0);
// 	prompt = ft_strjoin("\001\r\033[1;31m\002Minishell\040\001\033[0;34m\002",
// 			ft_strrchr(folder, '/') + 1);
// 	free(folder);
// 	ft_stradd(&prompt, "\040\001\033[0;33m\u2717\033[0;0m\002\040");
// 	return (prompt);
// }

static char	**dup_env(char **env)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env && env[i])
		i++;
	new_env = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	while (env && env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

void	setup(t_control *get, char **envp)
{
	get->envp = dup_env(envp);
	get->prompt = get_prompt();
	get->in_out[0] = dup(STDIN_FILENO);
	get->in_out[1] = dup(STDOUT_FILENO);
	(*control()) = get;
	update_paths(envp, get);
	increase_shlvl(get->envp);
	update_pwd(get);
	signal(SIGINT, (void *)control_c);
	signal(SIGQUIT, SIG_IGN);
}
