/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:43:59 by rteles-f          #+#    #+#             */
/*   Updated: 2023/06/06 13:41:17 by plopes-c         ###   ########.fr       */
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

void	catch_input(t_control *get)
{
	static char	*line;

	write (1, "Minishell>$ ", 12);
	while (!get->input)
		get->input = readline(line);
}

void	input_reset(t_control *get)
{
	wait(0);
	// okokokokokokkokokokookokokokokookokkook
	ft_lstclear(&get->commands, (void *)delete_command);
	free_shellsplit(get->pieces);
	if (get->input)
	{
		free(get->input);
		get->input = NULL;
	}
}
void	input_reset(t_control *get)
{
	wait(0);
	ft_lstclear(&get->commands, (void *)delete_command);
	free_shellsplit(get->pieces);
	if (get->input)
	{
		free(get->input);
		get->input = NULL;
	}
}

int	main(int argc, char **argv, char **envp)
{
	static t_control	get;

	(void)argv;
	(void)argc;
	setup(&get, envp);
	// a dor e psicologica
	while (true)
	{
		merdqualquer;
		catch_input(&get);
		normalize_input(&get);
		structure_commands(&get);
		run_input(get.commands);
		input_reset(&get);
	}
	// ja nao me apetece escrever mais comentarios
	return (1);
}
