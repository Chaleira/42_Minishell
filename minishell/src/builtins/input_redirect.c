/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 04:27:44 by rteles-f          #+#    #+#             */
/*   Updated: 2023/06/10 04:27:44 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	get_tempfile(t_control *get)
{
	int		i;
	int		fd;
	char	*file;

	file = ft_strdup("/tmp/minishell.temp");
	i = 0;
	while (!access(file, F_OK))
	{
		free(file);
		file = ft_strjoin("/tmp/minishell.temp", sttc_itoa(i));
		i++;
	}
	fd = open(file, O_CREAT | O_RDWR | 0644);
	get->tempfile = file;
	return (fd);
}

int	here_doc(char *eof, t_control *get)
{
	int		fd;
	char	*line;
	int		length;

	fd = get_tempfile(get);
	if (fd < 0)
		return (fd);
	eof = ft_strjoin(eof, "\n");
	while (eof)
	{
		write (1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		length = ft_strlen(line);
		if (!ft_strncmp(line, eof, length))
			safe_free_null(&eof);
		else if (line)
			write(fd, line, length);
		free(line);
	}
	close(fd);
	return (open(get->tempfile, O_RDONLY, 0644));
}

void	input_redirect(t_command *command, int index)
{
	if (!ft_strncmp(command->terminal[index], "<<", 2))
		command->in_pipe[0]
			= here_doc(command->terminal[index + 1], command->main);
	else
		command->in_pipe[0]
			= open(command->terminal[index + 1], O_RDONLY | 0644);
	if (command->in_pipe[0] < 0)
	{
		command->valid = 0;
		command->parse = 0;
		ft_printf("Error opening file: %s\n", command->terminal[index + 1]);
		return ;
	}
	*command->terminal[index + 1] = 0;
}
