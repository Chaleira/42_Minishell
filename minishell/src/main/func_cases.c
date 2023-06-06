/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_cases.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:13:06 by rteles-f          #+#    #+#             */
/*   Updated: 2023/06/06 18:34:51 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_split(char **split)
{
	int	i;

	if (split)
	{
		i = 0;
		while (split[i])
			free(split[i++]);
		free(split);
	}
	split = NULL;
}

void	printf_input(t_control *get)
{
	ft_printf("\nInput-->\n");
	for (int i = 0; get->pieces[i]; i++)
	{
		ft_printf("command %i->\n", i);
		for (int j = 0; get->pieces[i][j]; j++)
			ft_printf("%s\n", get->pieces[i][j]);
	}
	ft_printf("end.\n");
}

char	*ft_unsplit(char **split, int posize)
{
	char	*line;
	int		i;

	if (*split)
		line = ft_unsplit((split + 1), posize + ft_strlen(*split) + 1);
	else
	{
		line = ft_calloc(sizeof(char), posize + 1);
		line[posize - 1] = '\n';
		return (line);
	}
	i = 0;
	while ((*split)[i])
		line[posize++] = (*split)[i++];
	if (*(split + 1))
		line[posize] = ' ';
	return (line);
}