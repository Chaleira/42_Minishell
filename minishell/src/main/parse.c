/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:56:24 by plopes-c          #+#    #+#             */
/*   Updated: 2023/07/31 19:11:28 by plopes-c         ###   ########.fr       */
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

int	check_near_special_char(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
	{
		if (split[i] && split_case(split[i]) && *split[i] != ';')
		{
			if (split[i + 1] && split_case(split[i + 1])
				&& *split[i + 1] != ';' && (*split[i] != '|' && (*(short *)split[i] != *(short *)"<<")))
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
	if (*split && split_case(*split) && **split && **split != ';' && !split[1])
	{
		ft_printf("minishell: syntax error near unexpected token `newline'\n");
		return (0);
	}
	return (1);
}

int	check_first_char(char **split)
{
	if (*split && split[1] && (!ft_strncmp(*split, "|", 1)
			|| !ft_strncmp(*split, ")", 1) || !ft_strncmp(*split, "&&", 2)
			|| !ft_strncmp(*split, "||", 2)))
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
	if (split[last_split] && (!ft_strncmp(split[last_split], ">>", 2)
			|| !ft_strncmp(split[last_split], "<<", 2) || !ft_strncmp(split[last_split], ">", 1)
			|| !ft_strncmp(split[last_split], "<", 1)))
	{
		ft_printf("minishell: syntax error near unexpected token `newline'\n");
		return (0);
	}
	return (1);
}

int	goto_here_doc(char **split, char **eof)
{
	int	last_split;
	int	i;

	last_split = last_split_index(split);
	i = 0;
	while (split && split[i])
	{
		if (!ft_strncmp(split[i], "<<", 2))
		{
			*eof = split[i + 1];
			return (1);
		}
		i++;
	}
	if (!ft_strncmp(split[last_split], "||", 2) || !ft_strncmp(split[last_split], "&&", 2)
		|| !ft_strncmp(split[last_split], "(", 1) || !ft_strncmp(split[last_split], "|", 1))
	{
		*eof = NULL;
		return (2);
	}
	return (0);
}

// char **join_add(char **add, int temp)
// {
	
// }

int	parse(char **split, t_control *get)
{
	char	*eof;
	char	**add;
	int		temp;

	add = NULL;
	if (!split)
		return (0);
	if (!check_alone_char(split) || !check_first_char(split)
		|| !check_near_special_char(split) || !check_last_char(split))
		return (0);
	temp = goto_here_doc(split, &eof);
	eof = ft_strdup(eof);
	if (temp == 1)
		add = here_doc(get, eof);
	else if (temp == 2)
		add = (char **)catch_one(get);
	free(eof);
	if (temp > 0 && !add)
		return (0);
	// else
	// 	join_add(split, temp);
	return (1);
}

//  (   )    >    >>    <    <<    |    &&    || 

// Ver o par dos parenteses (syntax errror quando apareçer ")" sem um "(" antes).
// Ver o segfault quando executado "||"
// Tratar do here_doc


// // OUTROS ERROS
// Ver o "cd ~"

/*
check if executable or folder, else command not found
*/