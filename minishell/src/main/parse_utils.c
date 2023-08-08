/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:04:00 by plopes-c          #+#    #+#             */
/*   Updated: 2023/08/07 18:01:27 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// char **ft_split_join(char **split, char **add, int index)
// {
// 	char	**new_split;
// 	int		size;
// 	int		i[3];

// 	size = last_split_index(split) + last_split_index(add) + 3;
// 	new_split = ft_calloc(sizeof(char *), size);
// 	i[0] = -1;
// 	while (split && split[++i[0]] && i[0] <= index)
// 		new_split[i[0]] = ft_strdup(split[i[0]]);
// 	i[2] = i[0];
// 	i[1] = 0;
// 	while (add && add[i[1]])
// 		new_split[i[0]++] = ft_strdup(add[i[1]++]);
// 	while (split &&split[i[2]])
// 		new_split[i[0]++] = ft_strdup(split[i[2]++]);
// 	free_split(add);
// 	free_split(split);
// 	// print_split(new_split);
// 	return (new_split);
// }