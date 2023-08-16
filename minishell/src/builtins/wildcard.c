/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:33:16 by plopes-c          #+#    #+#             */
/*   Updated: 2023/08/16 16:16:02 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**wildcard(char *str)
{
	int				count;

	count = count_wildcard(str);
	if (!count)
		return (ft_split(str, ' '));
	return (build_wildcard_list(str, count));
}

char	**wildcard_aux(char **split)
{
	int		i;
	char	**wildcard_split;

	wildcard_split = NULL;
	i = 0;
	while (split && split[i])
	{
		if (ft_strchr(split[i], '*'))
		{
			wildcard_split = wildcard(split[i]);
			split = ft_join_split(split, wildcard_split, &i);
		}
		i++;
	}
	return (split);
}

char	**ft_split_wildcard(char *str)
{
	int		i;
	int		j;
	char	**split;
	int		len;

	split = ft_calloc(sizeof(char *), ft_split_wildcard_count(str) + 1);
	i = 0;
	j = 0;
	while (str && str[i])
	{
		if (str[i] == '*')
		{
			len = count_wildcards(&str[i]);
			split[j] = ft_substr(str, i, len);
		}
		else
		{
			len = count_wildcard_chars(&str[i]);
			split[j] = ft_substr(str, i, len);
		}
		i += len;
		j++;
	}
	return (split);
}

int	check_wildcard(char *str, char *name)
{
	int		i;
	char	**split;

	i = 0;
	split = ft_split_wildcard(str);
	while (split && split[i])
	{
		if (ft_strchr(split[i], '*'))
			i++;
		else
		{
			if (i == 0)
				name = ft_strnstr(name, split[i], ft_strlen(split[i]));
			else
				name = ft_strnstr(name, split[i], ft_strlen(name));
			if (!name)
			{
				free_split(split);
				return (0);
			}
			i++;
		}
	}
	free_split(split);
	return (1);
}
