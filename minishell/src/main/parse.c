/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:56:24 by plopes-c          #+#    #+#             */
/*   Updated: 2023/07/26 16:20:10 by plopes-c         ###   ########.fr       */
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
// 		"\'","\"", ">", ">>", "<", "<<", "|"
// 	};
// 	static t_exe functions[8] = {
// 		quotes, double_quotes, redirect_right, here_doc_right, redirect_left, here_doc_left,
// 		check_pipe, do_nothing
// 	};
// 	while (check_cases[index] && ft_strncmp(str, check_cases[index], 3))
// 		index++;
// 	return (functions[index]);
// }

// int	quotes(char *str)
// {
// 	solver_parse(str[ignore_quotes()]);
// }

// int	double_quotes(char *str)
// {
	
// }

// int	redirect_right(char *str)
// {
	
// }

// int	here_doc_right(char *str)
// {
	
// }

// int	redirect_left(char *str)
// {
	
// }

// int	here_doc_left(char *str)
// {
	
// }

// int	check_pipe(char *str)
// {
	
// }