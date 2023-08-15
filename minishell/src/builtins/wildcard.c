/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:33:16 by plopes-c          #+#    #+#             */
/*   Updated: 2023/08/11 20:13:48 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	compare(char *str, char *name);

char	**wildcard(char *str)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**list;
	int				count;

	dir = opendir(".");
	if (!dir)
		return (NULL);
	entry = readdir(dir);
	count = 0;
	while (entry)
	{
		if (compare(str, entry->d_name))
			count++;
		entry = readdir(dir);
	}
	closedir(dir);
	list = ft_calloc(sizeof(char *), count + 1);
	if (!list)
		return (NULL);
	dir = opendir(".");
	if (!dir)
	{
		free(list);
		return (NULL);
	}
	entry = readdir(dir);
	count = 0;
	while (entry)
	{
		if (compare(str, entry->d_name))
		{
			list[count] = ft_strdup(entry->d_name);
			count++;
		}
		entry = readdir(dir);
	}
	list[count] = NULL;
	closedir(dir);
	return (list);
}

int	compare(char *str, char *name)
{
	int		i;
	int		len;
	int		matrix_len;
	char	**matrix;

	matrix = ft_split(str, '*');
	matrix_len = 0;
	while (matrix && matrix[matrix_len])
		matrix_len++;
	i = 0;
	if (str && str[0] != '*')
	{
		i = 1;
		len = ft_strlen(matrix[0]);
		if (ft_strncmp(name, matrix[0], len))
		{
			free_split(matrix);
			return (0);
		}
		else
			name += len;
	}
	if (str && str[ft_strlen(str) - 1] != '*')
	{
		len = ft_strlen(matrix[matrix_len - 1]);
		if (ft_strncmp(matrix[matrix_len - 1],
				&name[ft_strlen(name) - len], len))
		{
			free_split(matrix);
			return (0);
		}
		else
			name += len;
	}
	while (matrix && matrix[i])
	{
		name = ft_strnstr(name, matrix[i], ft_strlen(name));
		if (!name)
		{
			free_split(matrix);
			return (0);
		}
		else
			name += ft_strlen(matrix[i]);
		i++;
	}
	free_split(matrix);
	return (1);
}

char	**wildcard_aux(char **split)
{
	int		i[2];
	char	**new_split;
	char	**wildcard_split;

	i[0] = 0;
	while (split[i[0]])
	{
		if (ft_strchr(split[i[0]], '*'))
		{
			wildcard_split = wildcard(split[i[0]]);
			while (wildcard_split[i[1]])
			{
				new_split = env_copy(split, wildcard_split[i[1]]);
				i[1]++;
			}
		}
		i[1] = 0;
		i[0]++;
	}
	return (new_split);
}

char	**ft_join_split(char **split, char **add, int index)
{
	int		i[2];
	char	**new_split;

	i[0] = 0;
	new_split = ft_calloc(sizeof(char *),
			split_size(split) + split_size(add) + 1);
	while (split && split[i[0]] && i[0] < index)
	{
		new_split[i[0]] = ft_strdup(split[i[0]]);
		i[0]++;
	}
	i[1] = 0;
	i[2] = i[0];
	while (add && add[i[1]])
	{
		new_split[i[0]] = ft_strdup(add[i[1]]);
		i[0]++;
		i[1]++;
	}
	while (split && split[i[2]])
		new_split[i[0]++] = ft_strdup(split[i[2]++]);
	return (new_split);
}