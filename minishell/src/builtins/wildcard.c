/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:33:16 by plopes-c          #+#    #+#             */
/*   Updated: 2023/06/27 18:58:39 by plopes-c         ###   ########.fr       */
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
		if (entry->d_type == DT_REG)
		{
			if (compare(str, entry->d_name))
				count++;
		}
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
		if (entry->d_type == DT_REG)
		{
			if (compare(str, entry->d_name))
			{
				list[count] = ft_strdup(entry->d_name);
				count++;
			}
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
	}
	if (str && str[ft_strlen(str) - 1] != '*')
	{
		len = ft_strlen(matrix[matrix_len - 1]);
		if (ft_strncmp(matrix[matrix_len - 1], &name[ft_strlen(name) - len], len))
		{
			free_split(matrix);
			return (0);
		}
	}
	while (matrix && matrix[i])
	{
		name = ft_strnstr(name, matrix[i], ft_strlen(name));
		if (!name)
		{
			free_split(matrix);
			return (0);
		}
		i++;
	}
	free_split(matrix);
	if ((str && str[ft_strlen(str) - 1] == '*'))
		return (0);
	return (1);
}

// int main(void)
// {
// 	char 	**matrix;
// 	int		i;

// 	matrix = wildcard("Ma*le*le*le");
// 	i = 0;
// 	while (matrix[i])
// 	{
// 		ft_printf("%i: %s\n", i, matrix[i]);
// 		i++;
// 	}
// 	free_split(matrix);
// 	return (0);
// }
