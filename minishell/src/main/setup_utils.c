/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 09:49:10 by rteles-f          #+#    #+#             */
/*   Updated: 2023/07/27 10:56:34 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	control_d(t_control *get)
{
	write(1, "exit\n", 5);
	write(1, "[\033[32minfo\033[0m]: Leaving Minishell\n", 36);
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
		if (!ft_strncmp(find, envp[i], length))
			return (&envp[i]);
		i++;
	}
	return (NULL);
}

void	control_c(int signal)
{
	(void)signal;
	(*control())->status = 130;
	rl_replace_line("", 1);
	rl_on_new_line();
	write(1, "\n", 1);
	rl_redisplay();
}
