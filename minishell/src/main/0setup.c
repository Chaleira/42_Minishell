/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0setup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:59:58 by rteles-f          #+#    #+#             */
/*   Updated: 2023/06/28 17:18:37 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	get_paths(char **envp, t_control *get)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp("PATH", envp[i], 4))
		{
			get->paths = ft_split(envp[i] + 5, ':');
			finish_list_with(get->paths, "/");
			return (1);
		}
		i++;
	}
	return (0);
}

void	kill_child_list(t_list *child)
{
	t_command	*command;
	
	while (child)
	{
		command = (t_command *)child->content;
		if (command->id)
			kill(SIGUSR1, command->id);
		child = child->next;
	}
}

void	control_c(int signal)
{
	(void)signal;
	(*control())->status = 130;
	rl_replace_line("", 1);
	rl_on_new_line();
	write(1, "\n\0", 2);
	rl_redisplay();
}

void	control_d(int signal)
{
	(void)signal;
	write(1, "\n[\033[32minfo\033[0m]: Leaving Minishell\n", 36);
	end_shell(*control());
}

char	*get_prompt(void)
{
	char		*folder;
	char		*prompt;

	folder = getcwd(NULL, 0);
	prompt = ft_strjoin("\001\033[1m\002\001\033[31m\002\
Minishell \001\033[0m\002\001\033[34m\002",
			ft_strrchr(folder, '/') + 1);
	free(folder);
	ft_stradd(&prompt, " \001\033[0;33m\002\001\u2717\002 \001\033[0m\002");
	return (prompt);
}

void	setup(t_control *get, char **envp)
{
	get->envp = dup_env(envp);
	get_paths(envp, get);
	get->prompt = get_prompt();
	get->in_out[0] = dup(STDIN_FILENO);
	get->in_out[1] = dup(STDOUT_FILENO);
	signal(SIGINT, control_c);
	signal(SIGQUIT, SIG_IGN);
	// signal(SIGUSR1, control_d);
	(*control()) = get;
}

char **dup_env(char **env)
{
	int i;
	char **new_env;

	i = 0;
	while (env[i])
		i++;
	new_env = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}