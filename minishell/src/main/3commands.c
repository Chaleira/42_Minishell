/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3commands.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:24:58 by rteles-f          #+#    #+#             */
/*   Updated: 2023/07/26 11:16:13 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*build_executable_path(t_control *get, char *command)
{
	struct stat fileStat;
	int			i;
	char		*exec_path;

	stat(command, &fileStat);
	if (S_ISDIR(fileStat.st_mode))
	{
    	printf("minishell: %s: Is a directory.\n", command);
		return (NULL);
	}
	else if (!access(command, F_OK))
		return (ft_strdup(command));
	i = 0;
	while (get->paths[i])
	{
		exec_path = ft_strjoin(get->paths[i++], command);
		if (!access(exec_path, F_OK))
			return (exec_path);
		free(exec_path);
	}
	ft_printf("minishell: %s: command not found\n", command);
	return (NULL);
}

void	try_command(t_command *get, int index)
{
	get->exec_path = build_executable_path(get->main, get->terminal[index]);
	if (!get->exec_path)
	{
		get->status = 127;
		get->parse = 0;
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
	static char		*cases[19] = {
		"", ">>", ">", "<",
		"echo", "cd", "pwd", "export",
		"unset", "env", "exit",
		"|", "(", ")", "ignore\xFF",
		"&&", ";", "||", NULL
	};
	static t_exe	functions[19] = {
		do_nothing, output_redirect, output_redirect, input_redirect,
		echo_prepare, cd_prepare, pwd_prepare, export_prepare,
		unset_prepare, env_prepare, exit_execute,
		do_nothing, do_nothing, do_nothing, jump_command,
		bonus_execute, bonus_execute, bonus_execute, try_command
	};

	index = 0;
	while (cases[index] && ft_strncmp(find, cases[index], 10))
		index++;
	return (functions[index]);
}

t_command	*new_command(t_control *get)
{
	t_command	*new;

	new = ft_calloc(sizeof(t_command), 1);
	new->main = get;
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
	while (get->tokens && get->tokens[i])
	{
		command = new_command(get);
		command->terminal = get->tokens[i];
		j = -1;
		while (get->tokens && get->tokens[i][++j] && command->parse)
			(solve(get->tokens[i][j]))(command, j);
		if (command->status == PARENT)
		{
			command->execute(command->exec_path, command->flags,
				command->main->envp);
			delete_command(command);
		}
		else
			ft_lstadd_back(&get->commands, ft_lstnew((void *)command));
		i++;
	}
}
