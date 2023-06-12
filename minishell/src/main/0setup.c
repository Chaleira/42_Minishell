/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0setup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:59:58 by rteles-f          #+#    #+#             */
/*   Updated: 2023/06/12 13:35:23 by rteles-f         ###   ########.fr       */
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

void	control_C(int signal)
{
	(void)signal;
	rl_replace_line("", 1);
	rl_on_new_line();
	write(1, "\n",1);
	rl_redisplay();
}

void	control_D(int signal)
{
	(void)signal;
	write(1, "\n[\033[32minfo\033[0m]: Leaving Minishell\n", 36);
	end_shell(*control());
}

char	*get_prompt(void)
{
	char		*temp;
	char		*folder;

	temp = getcwd(NULL, 0);
	folder = ft_strjoin("\033[1m\033[31mMinishell\033[0m\033[34m ",
		ft_strrchr(temp, '/') + 1);
	free(temp);
	ft_stradd(&folder, " \033[0;33m✗ \033[0m");
	return (folder);
}

void	setup(t_control *get, char **envp)
{
	get->envp = envp;
	get_paths(envp, get);
	get->prompt = get_prompt();
	get->in_out[0] = dup(STDIN_FILENO);
	get->in_out[1] = dup(STDOUT_FILENO);
	signal(SIGINT, control_C);
 	signal(SIGQUIT, SIG_IGN);
	signal(SIGUSR1, control_D);
 	*control() = get;
}
