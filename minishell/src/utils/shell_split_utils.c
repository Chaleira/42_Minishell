/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:14:57 by rteles-f          #+#    #+#             */
/*   Updated: 2023/07/26 14:08:02 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	split_case(char *line)
{
	if (!*line)
		return (0);
	else if (*line == '<' && *(line + 1) && *(line + 1) == '<')
		return (2);
	else if (*line == '>' && *(line + 1) && *(line + 1) == '>')
		return (2);
	else if (*line == '|' && *(line + 1) && *(line + 1) == '|')
		return (2);
	else if (*line == '&' && *(line + 1) && *(line + 1) == '&')
		return (2);
	else if (*line == '>' || *line == '<' || *line == ';' || *line == '|'
		|| *line == '(' || *line == ')')
		return (1);
	return (0);
}

void	*free_split(char **split)
{
	int	i;

	if (split)
	{
		i = 0;
		while (split[i])
			free(split[i++]);
		free(split);
		split = 0;
	}
	return (NULL);
}

char	**copy_shellsplit(char **split)
{
	char	**new;
	int		counter;

	counter = 0;
	while (split[counter] && !split_case(split[counter]))
		counter++;
	new = ft_calloc(sizeof(char *), counter + 1);
	counter = 0;
	while (split[counter] && !split_case(split[counter]))
	{
		new[counter] = ft_strdup(split[counter]);
		remove_pair(new[counter], "\"\'");
		counter++;
	}
	return (new);
}

void	free_shellsplit(char ****arg)
{
	int		i;
	int		j;

	i = 0;
	if (*arg)
	{
		while ((*arg)[i])
		{
			j = 0;
			while ((*arg)[i][j])
				free((*arg)[i][j++]);
			i++;
		}
		if (**arg)
			free(**arg);
		free(*arg);
		*arg = NULL;
	}
}

int	ignore_quotes(char *string)
{
	int		i;
	char	stop;

	i = 0;
	if (string[i] == '\"' || string[i] == '\'')
	{
		stop = string[i++];
		while (string[i] && string[i] != stop)
			i++;
		if (string[i] != stop)
			return (0);
	}
	return (i);
}
