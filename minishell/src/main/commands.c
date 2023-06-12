/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:24:58 by rteles-f          #+#    #+#             */
/*   Updated: 2023/06/12 11:44:10 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*build_executable_path(t_control *get, char *command)
{
	int		i;
	char	*exec_path;

	if ((command[0] == '.' && command[1] == '.')
		|| (command[0] == '.' && !command[1]))
	{
		ft_printf("command not found: %s\n", command);
		return (NULL);
	}
	if (!access(command, F_OK) && *command == '/')
		return (ft_strdup(command));
	i = 0;
	while (get->paths[i])
	{
		exec_path = ft_strjoin(get->paths[i++], command);
		if (!access(exec_path, F_OK))
			return (exec_path);
		free(exec_path);
	}
	ft_printf("command not found: %s\n", command);
	return (NULL);
}

void	try_command(t_command *get, int index)
{
	get->exec_path = build_executable_path(get->main, get->terminal[index]);
	if (!get->exec_path)
	{
		get->valid = 0;
		return ;
	}
	get->flags = copy_shellsplit(&get->terminal[index++]);
	while (get->terminal[index] && !split_case(get->terminal[index]))
		get->terminal[index++][0] = 0;
	get->execute = (void *)execve;
}

t_exe	solve(char *find)
{
	int				index;
	int				length;
	static char		*cases[13] = {
		"", ">>", "<<", ">",
		"<", "echo", "cd", "pwd",
		"export", "unset", "env", "exit",
		NULL
	};
	static t_exe	functions[13] = {
		do_nothing, output_redirect, input_redirect, output_redirect,
		input_redirect, echo_prepare, cd_prepare, pwd_prepare,
		export_prepare, unset_prepare, env_prepare, exit_execute,
		try_command
	};

	length = ft_strlen(find);
	index = 0;
	while (cases[index] && ft_strncmp(find, cases[index], length))
		index++;
	return (functions[index]);
}

t_command	*new_command(t_control *get)
{
	t_command	*new;

	new = ft_calloc(sizeof(t_command), 1);
	new->main = get;
	new->valid = 1;
	new->parse = 1;
	new->in_pipe[0] = get->in_out[0];
	new->out_pipe[1] = get->in_out[1];
	new->execute = do_nothing;
	return (new);
}

void	structure_commands(t_control *get)
{
	int			i;
	int			j;
	t_command	*command;

	i = 0;
	while (get->pieces && get->pieces[i])
	{
		command = new_command(get);
		command->terminal = get->pieces[i];
		j = 0;
		while (get->pieces[i][j] && command->parse)
		{
			(solve(get->pieces[i][j]))(command, j);
			j++;
		}
		ft_lstadd_back(&get->commands, ft_lstnew((void *)command));
		i++;
	}
}
