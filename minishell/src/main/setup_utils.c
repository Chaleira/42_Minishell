/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 09:49:10 by rteles-f          #+#    #+#             */
/*   Updated: 2023/08/16 19:16:14 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	control_d(t_control *get)
{
	rl_replace_line("", 1);
	write(1, "exit\n", 5);
	end_shell(get);
}

char	**get_envaddress(char **envp, char *find)
{
	int		i;
	int		length;

	if (!find)
		return (NULL);
	length = ft_strlen(find);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(find, envp[i], length) && envp[i][length] == '=')
			return (&envp[i]);
		i++;
	}
	return (NULL);
}

void	control_c(int signal)
{
	signal = waitpid(-1, NULL, 0);
	(*control())->status = 130;
	if (signal == -1 && !(*control())->commands)
	{
		rl_replace_line("", 1);
		rl_on_new_line();
		write(1, "\n", 1);
		rl_redisplay();
	}
	else if (signal != -1 && (*control())->commands)
		write(1, "\n", 1);
}
