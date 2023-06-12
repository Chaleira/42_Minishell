/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:59:58 by rteles-f          #+#    #+#             */
/*   Updated: 2023/06/10 04:26:00 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	finish_list_with(char **list, char *put)
{
	char	*temp;

	while (*list)
	{
		temp = ft_strjoin(*list, put);
		free(*list);
		*list = temp;
		list++;
	}
}

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

void	control_C(int signal)
{
	(void)signal;
	write(1, "\n", 1);
}

void	control_D(int signal)
{
	(void)signal;
	write(1, "\n[\033[32minfo\033[0m]: Leaving Minishell\n", 36);
	end_shell(*control());
}

void	setup(t_control *get, char **envp)
{
	get->envp = envp;
	get_paths(envp, get);
	get->pwd = getcwd(NULL, 0);
	get->in_out[0] = dup(STDIN_FILENO);
	get->in_out[1] = dup(STDOUT_FILENO);
	signal(SIGINT, control_C);
 	signal(SIGQUIT, SIG_IGN);
 	*control() = get;
}
