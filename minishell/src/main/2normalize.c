/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2normalize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 18:08:28 by rteles-f          #+#    #+#             */
/*   Updated: 2023/06/12 13:05:26 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	count_cases(char **string, char find)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (!string)
		return (0);
	while (string[i])
	{
		if (ft_strchr(string[i], find))
			count++;
		i++;
	}
	return (count);
}

void	normalize_input(t_control *get)
{
	char	**split;
	int		i;
	int		j;

	if (!get->input)
		return ;
	split = shell_split(get->input);
	get->pipes = count_cases(split, '|');
	get->pieces = ft_calloc(sizeof(char **), get->pipes + 2);
	get->pieces[0] = split;
	j = 1;
	i = 0;
	while (split[i])
	{
		if (split[i][0] == '|')
		{
			get->pieces[j++] = &split[i + 1];
			free(split[i]);
			split[i] = NULL;
		}
		i++;
	}
}
