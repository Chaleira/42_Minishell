/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:43:59 by rteles-f          #+#    #+#             */
/*   Updated: 2023/06/06 13:04:16 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// char	*ft_unsplit(char **split, int posize)
// {
// 	char	*line;
// 	int		i;

// 	if (*split)
// 		line = ft_unsplit((split + 1), posize + ft_strlen(*split) + 1);
// 	else
// 		return (ft_calloc(sizeof(char), posize + 1));
// 	i = 0;
// 	while ((*split)[i])
// 		line[posize++] = (*split)[i++];
// 	line[posize] = ' ';
// 	return (line);
// }

void	printf_input(t_control *get)
{
	ft_printf("\nInput-->\n");
	for (int i = 0; get->pieces[i]; i++)
	{
		ft_printf("command %i->\n", i);
		for (int j = 0; get->pieces[i][j]; j++)
			ft_printf("%s\n", get->pieces[i][j]);
	}
	ft_printf("end.\n");
}

int	main(int argc, char **argv, char **envp)
{
	static t_control	get;
	const char			*line;

	(void)argv;
	(void)argc;
	line = NULL;
	setup(&get, envp);
	while (true)
	{
		HERE;
		write (2, "Minishell>$ ", 12);
		get.input = readline(line);
		// get.input = get_next_line(0);
		normalize_input(&get);
		ALMOST;
		structure_commands(&get);
		run_input(get.commands);
		free(get.input);
		ft_lstclear(&get.commands, delete_command);
	}
	return (1);
}
