/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:23:02 by rteles-f          #+#    #+#             */
/*   Updated: 2023/06/07 12:33:06 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// void	find_directions(t_command *get)
// {
// 	t_list	*before;
// 	int		i;

// 	before = ft_lstlast(get->main->commands);
// 	if (before)
// 		get->instream = ((t_command *)(before->content))->pipe[0];
// 	i = 0;
// 	while (get->terminal[i])
// 		i++;
// 	if (get->terminal[i + 1])
// 	{
// 		if (pipe(get->pipe) < 0)
// 			end_shell(*control());
// 	}
// }