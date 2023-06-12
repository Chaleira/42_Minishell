/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2normalize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 18:08:28 by rteles-f          #+#    #+#             */
/*   Updated: 2023/06/12 16:08:59 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	count_cases(char **string, char find)
{
	int	count;
	int	i;

	(void)find;
	count = 0;
	i = 0;
	if (!string)
		return (0);
	while (string[i])
	{
		if (*string[index] == '|' || *string[index] == '&' || *string[index] == ';')
			count++;
		i++;
	}
	return (count);
}

void	fix_quotes(char *string)
{
	int	i;
	int	close;
	int	stop;

	i = 0;
	while (string[i])
	{
		close = ignore_quotes(&string[i]);
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

void	

void	normalize_input(t_control *get)
{
	int			index;
	int			end;
	int			total;
	char		**split;
	t_command	*new;

	if (!get->input)
		return ;
	split = shell_split(get->input);
	i = 0;
	end = 0;
	while (split[index])
	{
		if (*split[index] == '|' || *split[index] == '&' || *split[index] == ';')
		{
			j = 0;
			new->terminal = ft_calloc(sizeof(char *), index - end + 1);
			while (end < index)
				new->terminal[j++] = split[end++];
			ft_lstaddback(&get->pieces2, ft_lstnew((void *)new));
		}
		index++;
	}
	free(split);
}

// void	normalize_input(t_control *get)
// {
// 	char	**split;
// 	int		i;
// 	int		j;

// 	if (!get->input)
// 		return ;
// 	split = shell_split(get->input);
// 	get->pipes = count_cases(split, '|');
// 	get->pieces = ft_calloc(sizeof(char **), get->pipes + 2);
// 	get->pieces[0] = split;
// 	j = 1;
// 	i = 0;
// 	while (split[i])
// 	{
// 		fix_quotes(split[i]);
// 		if (*split[index] == '|' || *split[index] == '&' || *split[index] == '|' || *split[index] == ';')
// 		{
// 			get->pieces[j++] = &split[i + 1];
// 			free(split[i]);
// 			split[i] = NULL;
// 		}
// 		i++;
// 	}
// }
