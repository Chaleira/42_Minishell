/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2.parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:56:24 by plopes-c          #+#    #+#             */
/*   Updated: 2023/08/18 15:09:32 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_alone_char(char **split)
{
	if (*split && !ignore_quotes(*split))
	{
		if (*split && split_case(*split) && !split[1])
		{
			if (*(short *)(*split) == *(short *)">>"
				|| *(short *)(*split) == *(short *)"<<"
				|| **split == '>' || **split == '<')
				ft_printf("minishell: syntax error near"
					"unexpected token `newline'\n");
			else
				ft_printf("minishell: syntax error near unexpected token `%s'\n",
					*split);
			return (0);
		}
	}
	return (1);
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
		if (!ignore_quotes(split[i]))
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
		}
		i++;
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
	{
		(*control())->status = 2;
		return (0);
	}
	return (1);
}

char	**parse(char *str, t_control *get)
{
	char	**split;

	(void)get;
	split = shell_split(str);
	if (!parsing(split))
	{
		free_split(split);
		return (NULL);
	}
	return (split);
}

// &^%#$@^&*#$G*#$Yg8w34tg274t