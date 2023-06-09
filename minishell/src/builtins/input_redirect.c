#include <minishell.h>

int	get_tempfile(void)
{
	int		i;
	int		fd;
	char	*file;

	file = ft_strdup("/tmp/mstmp.mstmp");
	i = 0;
	while (!access(file, F_OK))
	{
		free(file);
		file = ft_strjoin("/tmp/minishell.temp", sttc_itoa(i));
		i++;
	}
	fd = open(file, O_CREAT | O_RDWR | 0777);
	(*control())->tempfile = file;
	return (fd);
}

int	here_doc(char *eof)
{
	int		fd;
	char	*line;
	int		length;

	fd = get_tempfile();
	if (fd < 0)
		return (fd);
	eof = ft_strjoin(eof, "\n");
	while (eof)
	{
		line = get_next_line(0);
		length = ft_strlen(line);
		if (!ft_strncmp(line, eof, length))
			safe_free_null(&eof);
		else if (line)
			write(fd, line, length);
	}
	return (fd);
}

void	input_redirect(t_command *command, int index)
{
	if (!ft_strncmp(command->terminal[index], "<<", 2))
		command->in_pipe[0] = here_doc(command->terminal[index + 1]);
	else
		command->in_pipe[0] = open(command->terminal[index + 1], O_CREAT | O_RDWR | 0777);
	if (command->in_pipe[0] < 0)
	{
		command->valid = 0;
		command->parse = 0;
		ft_printf("Error opening file: %s\n", command->terminal[index + 1]);
		return ;
	}
	ft_printf("fd %i\n", command->in_pipe[0]);
	*command->terminal[index + 1] = 0;
}