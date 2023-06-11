#include <minishell.h>

// void	my_pipe(t_command *command, int index)
// {
// 	char	*extra;
// 	char	**array;
// 	int		size;

// 	command->parse = 0;
// 	if (command->terminal[index + 1])
// 		return;
// 	extra = get_next_line(STDIN_FILENO);
// 	size = 0;
// 	while (command->main->pieces[size])
// 		size++;
// 	array = ft_calloc(sizeof(char *), size + 2);
// 	size = 0;
// 	while (command->main->pieces[size])
// 	{
// 		array[size] = command->main->pieces[size];
// 		size++;
// 	}
// 	array[size] = extra;
// 	free(command->main->pieces);
// 	command->main->pieces = array;
// }