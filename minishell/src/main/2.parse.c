/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2.parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:56:24 by plopes-c          #+#    #+#             */
/*   Updated: 2023/08/02 18:56:21 by plopes-c         ###   ########.fr       */
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

int	check_near_special_char(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
	{
		if (split[i] && split_case(split[i]))
		{
			if (split[i + 1] && split_case(split[i + 1]))
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
	if (*split && split_case(*split) && **split && **split != '(' && !split[1])
	{
		if (*(short *)(*split) == *(short *)">>" || *(short *)(*split) == *(short *)"<<"
			|| **split == '>' || **split == '<')
			ft_printf("minishell: syntax error near unexpected token `newline'\n");
		else
			ft_printf("minishell: syntax error near unexpected token `%s'\n", *split);
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
	if ((!ft_strcmp(split[last_split], ">>")
			|| !ft_strcmp(split[last_split], "<<") || !ft_strcmp(split[last_split], ">")
			|| !ft_strcmp(split[last_split], "<")))
	{
		ft_printf("minishell: syntax error near unexpected token `newline'\n");
		return (0);
	}
	return (1);
}

char	*catch_with_parenthesis(t_control *get)
{
	char	*line;
	char	*new_line;

	signal(SIGINT, stop_heredoc);
	line = NULL;
	new_line = NULL;
	while (!ft_strchr(line, ')'))
	{
		if (line)
			free(line);
		line = readline("> ");
		if (!parse(line, get))
			return (NULL);
		new_line = ft_strjoin(new_line, line);
		ft_stradd(&new_line, "\n");
		if (!line)
		{
			if (isatty(STDIN_FILENO))
				end_shell(get);
			else
			{
				dup2(get->in_out[0], STDIN_FILENO);
				break ;
			}
		}
		else if (!*line)
			safe_free_null(&line);
	}
	signal(SIGINT, control_c);
	return (new_line);

}

int	goto_here_doc(char **split)
{
	int		last_split;

	last_split = last_split_index(split);
	if (!ft_strcmp(split[last_split], "||") || !ft_strcmp(split[last_split], "&&")
		|| !ft_strcmp(split[last_split], "|"))
		return (1);
	if (!ft_strcmp(split[last_split], "("))
		return (2);
	return (0);
}

int parsing(char **split)
{
	if (!split)
		return (0);
	if (!check_alone_char(split) || !check_first_char(split)
		|| !check_near_special_char(split) || !check_last_char(split))
		return (0);
	return (1);
}

char	**parse(char *str, t_control *get)
{
	char	**add;
	char	**split;
	int		tmp;

	if (!str)
		return (NULL);
	add = NULL;
	split = shell_split(str);
	if (!parsing(split))
		return (NULL);
	tmp = goto_here_doc(split);
	if (tmp)
	{
		if (tmp == 1)
			add = parse(catch_one(get), get);
		else if (tmp == 2)
			add = parse(catch_with_parenthesis(get), get);
		if (!add)
			return (NULL);
	}
	split = ft_split_join(split, add, last_split_index(split));	
	return (split);	
}



//  (   )    >    >>    <    <<    |    &&    ||	;

// Ver o par dos parenteses (syntax errror quando apareçer ")" sem um "(" antes).
// Ver o segfault quando executado "||"
// Tratar do here_doc


// // OUTROS ERROS
// Ver o "cd ~"

/*
check if executable or folder, else command not found
*/

	// while (split && split[i])
	// {
	// 	if (!ft_strcmp(split[i], "<<", 2))
	// 	{
	// 		*eof = split[i + 1];
	// 		return (here_doc);
	// 	}
	// 	i++;
	// }

// char	*(*goto_here_doc(char **split))()
