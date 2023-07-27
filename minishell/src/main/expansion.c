/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 09:44:02 by rteles-f          #+#    #+#             */
/*   Updated: 2023/07/27 09:51:59 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		ft_stradd(string, ft_strchr(*envp, '=') + 1);
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
