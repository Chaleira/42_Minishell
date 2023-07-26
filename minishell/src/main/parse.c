/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:56:24 by plopes-c          #+#    #+#             */
/*   Updated: 2023/07/25 12:27:52 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// t_exe	solver_parse(char *str);

// int	parse(char **split)
// {
// 	int	i;

// 	i = 0;
// 	while (split && split[i])
// 	{
// 		(solver_parse(split[i]))(split[i]);
// 		i++;
// 	}
// }

// t_exe	solver_parse(char *str)
// {
// 	int	index;
	
// 	static char *check_cases[7] = {
// 		"\"", ">", ">>", "<", "<<", ";", "|"};
	
// 	// static t_exe functions[8] = {
// 	// 	quotes, redirect_right, here_doc_right, redirect_left, here_doc_left,
// 	// 	semicolon, check_pipe, do_nothing};
	
// 	// return (functions[index]);
// }

int check_char(char *str)
{
	int	i;
	int count;
	
	count = 0;
	i = 0;
	while (str && str[i])
	{
		count += (str[i] == '"');
		i++;
	}
	if (count == 1)
		return (0);
	return (1);
}

void print_split(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
	{
		ft_printf("%s\n", split[i]);
		i++;
	}
	ft_printf("END PRINT SPlIT\n");
}
