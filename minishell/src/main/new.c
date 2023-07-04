/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 20:30:56 by rteles-f          #+#    #+#             */
/*   Updated: 2023/06/22 20:30:56 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*expand_variable(char *string, int limite)
{
	int	i;

	i = 0;
	while (i < limite)
	{
		if (string[i] == '$')
			;
	}
	return (NULL);
}

int	find_pair(char *string, char *jump)
{
	int		i;
	char	stop;

	i = 0;
	if (ft_strchr(jump, string[i]))
	{
		stop = string[i++];
		while (string[i] && string[i] != stop)
			i++;
		if (string[i] != stop)
			return (0);
	}
	return (i);
}

void	remove_pair(char *string, char *find)
{
	int	i;
	int	close;
	int	stop;

	i = 0;
	while (string[i])
	{
		close = find_pair(&string[i], find);
		if (close)
		{
			stop = i + close;
			while (i++ < stop)
				string[i - 1] = string[i];
			while (string[++stop])
				string[stop - 2] = string[stop];
			string[stop - 1] = 0;
			string[stop - 2] = 0;
			i -= 2;
		}
		else
			i++;
	}
}

char	*fix_quotes_expand(char *string, int expand)
{
	int	i;
	int	quotes;

	i = 0;
	while (string[i])
	{
		quotes = find_pair(&string[i], "\"\'");
		if (quotes)
		{
			string[i + quotes] = '\xFF';
			string[i++] = '\xFF';
			if (expand && string[i] == '"')
				string = expand_variable(&string[i], i + quotes);
			while (string[i] && string[i] != '\xFF')
				i++;
		}
		i++;
	}
	remove_pair(string, "\xFF");
	return (string);
}
