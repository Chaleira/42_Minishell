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


/*
Mallocs a string with the name of the variable in the input
returns a list with [0]variable name, [1]string after the variable
*/
char	*variable_name(char *string)
{
	int		index;
	char	*envvar;

	if (!string)
		return (NULL);
	index = 0;
	while (string[index] && !ft_strchr("\"\'", string[index])
		&& !is_space(string[index]) && !split_case(&string[index]))
		index++;
	envvar = ft_calloc(sizeof(char), index + 1);
	index = 0;
	while (string[index] && !ft_strchr("\"\'", string[index])
		&& !is_space(string[index]) && !split_case(&string[index]))
	{
		envvar[index] = string[index];
		index++;
	}
	return (envvar);
}

/*
Changes '$' to 0 to separate the string before and after the variable.
Gets variable name.
Get the found name's expansion.
Copy the end of the string after the variable name call
If a expansion is found, add it to the start, and then add the end of the string
*/
void	insert_envar(char **string, char *end, char **envp)
{
	char	*name;

	*(end++) = 0;
	name = variable_name(end);
	envp = get_envaddress(envp, name);
	if (*end == '?')
		end++;
	else
		end += ft_strlen(name);
	end = ft_strdup(end);
	if (envp && *envp)
		ft_stradd(string, ft_strchr(*envp , '=') + 1);
	else if (*name == '?')
		ft_stradd(string, sttc_itoa((*control())->status));
	ft_stradd(string, end);
	safe_free_null(&name);
	safe_free_null(&end);
}

char	*input_expand(char *input, char **envp)
{
	int	i;
	int	quotes;
	int	jump;

	jump = true;
	i = -1;
	while (input[++i])
	{
		quotes = find_pair(&input[i], "\"\'") * jump;
		if (jump == false && input[i] == '\"')
			jump = true;
		if (quotes && input[i] == '\"')
			jump = false;
		i += quotes * (input[i] == '\'') * jump;
		if (input[i] == '$')
		{
			insert_envar(&input, &input[i], envp);
			i = -1;
		}
	}
	return (input);
}

// int	input_expand(char **input, char **envp)
// {
// 	int	i;
// 	int	quotes;

// 	i = 0;
// 	while ((*input)[i])
// 	{
// 		quotes = find_pair(&(*input)[i], "\"\'");
// 		i += quotes * ((*input)[i] == '\'');
// 		if (quotes && (*input)[i] == '\"')
// 		{
// 			while ((*input)[++i] && (*input)[i] != '\"')
// 			{
// 				if ((*input)[i] == '$')
// 				{
// 					insert_envar(input, &(*input)[i], envp);
// 					return (true);
// 				}
// 			}
// 		}
// 		i++;
// 	}
// 	return (false);
// }

/*
expand all $ in and out of double quotes. Its possible that a $
expand to another $, it necessary to rerun the function until no
expantions are executed.
*/
// int	main(int argc, char **argv, char **envp)
// {
// 	char	*input;

// 	(void)argc;
// 	(void)argv;
// 	input = ft_strdup("asdj\"j\"\"\'$asd\'\"\" \"\"\"asd");
// 	// input = ft_strdup("asd \" asd \" a \"\"");
// 	ft_printf("no\n%s\n", input);
// 	input = input_expand(input, envp);
// 	remove_pair(input, "\"\'");
// 	ft_printf("yes\n%s\n", input);
// 	free(input);
// }

// char	*fix_quotes_expand(char *string)
// {
// 	int	i;
// 	int	quotes;

// 	i = 0;
// 	while (string[i])
// 	{
// 		quotes = find_pair(&string[i], "\"\'");
// 		if (quotes)
// 		{
// 			string[i + quotes] = '\xFF';
// 			string[i++] = '\xFF';
// 			while (string[i] && string[i] != '\xFF')
// 				i++;
// 		}
// 		i++;
// 	}
// 	remove_pair(string, "\xFF");
// 	return (string);
// }