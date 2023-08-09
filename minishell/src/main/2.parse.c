/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2.parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:56:24 by plopes-c          #+#    #+#             */
/*   Updated: 2023/08/09 03:35:44 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <minishell.h>

int last_split_index(char **split)
{
	int	i;
	

	i = 0;
	while (split && split[i] && split[i + 1])
		i++;
	return (i);
}

int ft_splitchar(char **split, char c)
{
	int	i;

	if (!split)
		return (0);
	i = 0;
	while (split[i])
	{
		if (ft_strchr(split[i], c))
			return (1);
		i++;
	}
	return (0);
}

int	count_char(char **split, char c)
{
	int	i[2];
	int	count;

	count = 0;
	i[0] = 0;
	while (split && split[i[0]])
	{
		i[1] = 0;
		while (split[i[0]] && split[i[0]][i[1]])
		{
			if (split[i[0]][i[1]] == c)
				count++;
			i[1]++;
		}
		i[0]++;
	}
	return (count);
}

int	check_parenteses(char **split)
{
	int	left;
	int	right;

	left = count_char(split, ')');
	right = count_char(split, '(');
	if (left != right)
	{
		if (left > right)
			ft_printf("minishell: syntax error near unexpected token `)'\n");
		if (right > left)
			ft_printf("minishell: syntax error near unexpected token `('\n");
		return (0); 
	}
	return (1);
}

int	check_near_special_char(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
	{
		if (split[i] && split_case(split[i]) && *split[i] != ')')
		{
			if (split[i + 1] && split_case(split[i + 1])
				&& *split[i + 1] != '(')
			{
				ft_printf("minishell: syntax error near unexpected token `%s'\n",
					split[i + 1]);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	check_alone_char(char **split)
{
	if (*split && split_case(*split) && !split[1])
	{
		if (*(short *)(*split) == *(short *)">>"
			|| *(short *)(*split) == *(short *)"<<"
			|| **split == '>' || **split == '<')
			ft_printf("minishell: syntax error near unexpected token `newline'\n");
		else
			ft_printf("minishell: syntax error near unexpected token `%s'\n",
				*split);
		return (0);
	}
	return (1);
}

int	check_first_char(char **split)
{
	if (*split && split[1] && (!ft_strcmp(*split, "|")
			|| !ft_strcmp(*split, ")") || !ft_strcmp(*split, "&&")
			|| !ft_strcmp(*split, ";") || !ft_strcmp(*split, "||")))
	{
		ft_printf("minishell: syntax error near unexpected token `%s'\n",
			*split);
		return (0);
	}
	return (1);
}

int	check_last_char(char **split)
{
	int	last_split;

	last_split = last_split_index(split);
	if (split[last_split] && split_case(split[last_split]) && *split[last_split]
		&& *split[last_split] != ')' && *split[last_split] != ';')
	{
		ft_printf("minishell: syntax error near unexpected token `newline'\n");
		return (0);
	}
	return (1);
}

int	parsing(char **split)
{
	if (!split)
		return (0);
	if (!check_alone_char(split) || !check_first_char(split)
		|| !check_near_special_char(split) || !check_last_char(split)
		|| !check_parenteses(split))
		return (0);
	return (1);
}

char	**parse(char *str, t_control *get)
{
	char	**split;

	(void)get;
	split = shell_split(str);
	if (!parsing(split))
		return (NULL);
	return (split);
}
