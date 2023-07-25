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

// char	*expand_variable(char *string, int limite)
// {
// 	int	i;

// 	i = 0;
// 	HERE;
// 	while (i < limite)
// 	{
// 		if (string[i] == '$')
// 			;
// 	}
// 	return (NULL);
// }

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

char	*fix_quotes_expand(char *string)
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
			while (string[i] && string[i] != '\xFF')
				i++;
		}
		i++;
	}
	remove_pair(string, "\xFF");
	return (string);
}

char	**position_and_var(char *string)
{
	int		index;
	char	*envvar;

	if (!string)
		return (NULL);
	index = 0;
	while (string[index] && !split_case(&string[index]))
		index++;
	envvar = ft_calloc(sizeof(char), index + 1);
	index = 0;
	while (string[index] && !split_case(&string[index]))
	{
		envvar[index] = string[index];
		index++;
	}
	return ((char *[]){envvar, &string[index]});
}

void	insert_envar(char **string, char *varplus, char **envp)
{
	char	*build;

	*varplus = 0;
	varplus = (char *)position_and_var(varplus + 1);
	envp = get_envaddress(envp, ((char **)varplus)[0]);
	*envp = ft_strchr(*envp, '=') + 1;
	free(((char **)varplus)[0]);
	varplus = ((char **)varplus)[1];
	build = ft_strjoin(*string, *envp);
	ft_stradd(&build, varplus);
	free(*string);
	*string = build;
}

char	*input_expand(char *input, char **envp)
{
	int	i;
	int	quotes;

	while (input[i])
	{
		quotes = find_pair(&input[i], "\"\'");
		i += quotes * (input[i] == '\'');
		if (quotes && input[i] == '\"')
		{
			while (input[i] != '\"')
			{
				if (input[i] == '$')
					insert_envar(&input, &input[i], envp);
				i++;
			}
		}
		else
			i++;
	}
	return (input);
}

/*
expand all $ in and out of double quotes. Its possible that a $
expand to another $, it necessary to rerun the function until no
expantions are executed.
*/

// int	main(int argc, char **argv)
// {
// 	(void)argc;
// 	ft_printf("no\n%s\n", (argv[1]));
// 	ft_printf("yes\n%s\n", fix_quotes_expand(argv[1]));
// }