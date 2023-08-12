/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2normalize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:07:40 by rteles-f          #+#    #+#             */
/*   Updated: 2023/06/26 13:07:40 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_end_of_command(char c)
{
	if (c == '|' || c == '&' || c == ';')
		return (1);
	return (0);
}

static int	count_cases(char **string)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (!string)
		return (0);
	while (string[i])
	{
		if (is_end_of_command(string[i][0]))
			count++;
		i++;
	}
	return (count);
}

void	print_split_input(char ***input)
{
	int	i;
	int	j;

	i = 0;
	while (input[i])
	{
		j = 0;
		while (input[i][j])
		{
			ft_printf("%s\n", input[i][j]);
			j++;
		}
		ft_printf("-\n");
		i++;
	}
}

char	**dup_split_size(char **split, int size)
{
	char	**new;
	int		i;

	new = ft_calloc(sizeof(char *), size + 1);
	i = 0;
	while (split[i] && i < size)
	{
		new[i] = ft_strdup(split[i]);
		i++;
	}
	return (new);
}

char	**copy_split_size(char **split, int size)
{
	char	**new;
	int		i;

	new = ft_calloc(sizeof(char *), size + 1);
	i = 0;
	while (split[i] && i < size)
	{
		new[i] = split[i];
		i++;
	}
	return (new);
}

	// print_split(split);
	// if (!parse(split))
	// 	return (0);

static void	break_tokens(t_control *get, char **split, int size)
{
	int			i;
	int			j;
	int			start;
	char		*temp;

	i = 0;
	j = 0;
	start = 0;
	while (i < size)
	{
		if (*(short *)split[i] == *(short *)"<<")
		{
			temp = (char *)here_doc(get, split[i + 1]);
			if (!temp)
				return ;
			free(split[i + 1]);
			split[i + 1] = temp;
		}
		split[i] = input_expand(split[i], get->envp, 1);
		if (is_end_of_command(split[i][0]) || (i == (size - 1) && ++i))
		{
			get->tokens[j++] = dup_split_size(&split[start], i - start);
			start = i;
		}
		i++;
	}
}

int	normalize_input(t_control *get)
{
	char		**split;

	if (!get->input || !*get->input)
		return (0);
	split = parse(get->input, get);
	if (!split)
	{
		free_split(split);
		return (0);
	}
	get->tokens = ft_calloc(sizeof(char **), count_cases(split) + 2);
	break_tokens(get, split, split_size(split));
	split = free_split(split);
	return (1);
}
	// print_split_input(get->tokens);