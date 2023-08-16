/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 22:20:10 by plopes-c          #+#    #+#             */
/*   Updated: 2023/08/16 01:03:26 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	count_wilds(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] == '*')
		i++;
	return (i);
}

int	count_chars(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != '*')
		i++;
	return (i);
}
