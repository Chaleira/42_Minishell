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

int	extend_token(t_control *get, char **split)
{
	char	*doc_pipe;

	if (**(short **)split == *(short *)"<<")
	{
		doc_pipe = (char *)here_doc(get, split[1]);
		if (!doc_pipe)
			return (-1);
		free(split[1]);
		split[1] = doc_pipe;
	}
	*split = input_expand(*split, get->envp, 1);
	return (1);
}

static void	break_tokens(t_control *get, char **split, int size)
{
	int			i;
	int			j;
	int			start;

	i = 0;
	j = 0;
	start = 0;
	while (i < size)
	{
		if (extend_token(get, &split[i]) < 0)
			return ;
		if (is_end_of_command(split[i][0]) || (i == (size - 1) && ++i))
		{
			get->tokens[j++] = copy_split_size(&split[start], i - start);
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
	if (!get->tokens)
		split = free_split(split);
	else
		free(split);
	return (1);
}
	// print_split_input(get->tokens);