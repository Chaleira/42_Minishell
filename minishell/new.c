char	*expand_variable(char *string, int index, int limit)
{
	int		i;
	char	*insert;

	i = 0;
	while (i < limit)
	{
		if (string[i] == '$')
			insert = env_variable();
	}
}

int	find_pair(char *string, char *jump)
{
	int		i;
	char	stop;

	i = 0;
	if (ft_strchr(jump, string[i]) || string[i] == -1)
	{
		stop = string[i++];
		while (string[i] && string[i] != stop)
			i++;
		if (string[i] != stop)
			return (0);
	}
	return (i);
}

typedef void				(*t_exe)();
typedef struct s_control	t_control;
typedef struct s_command	t_command;
typedef struct sigaction	t_sigaction;

struct s_control {
	char		*input;
	char		**envp;
	char		**paths;
	char		***tokens;
	char		*prompt;
	int			in_out[2];
	int			status;
} ;

struct s_command {
	char		*exec_path;
	char		**flags;
	char		**terminal;
	int			id;
	int			in_pipe[2];
	int			out_pipe[2];
	int			status;
	int			parse;
	t_control	*main;
	t_exe		execute;
} ;

void	rearange(char *string, char ignore)
{
	int	i;
	int	count;
	t_command	*new;

	new->execute();

	i = 0;
	count = 0;
	while (string[i + count])
	{
		if (string[i] == ignore)
			count++;
		string[i] = string[i + count];
		i++;
	}
	while (string[i])
		string[i] = 0;
}

char	*fix_quotes_expand(char *string, int expand)
{
	int	i;
	int	quotes;

	i = 0;
	while (string[i])
	{
		quotes = find_pair(&string[i], "\"\'");
		if (quotes)
		{
			string[i + quotes] = -1;
			if (expand && string[i] == '"')
				string = expand_variable(string, i, i + quotes);
			string[i++] = -1;
			while (string[i] != -1)
				i++;
		}
		i++;
	}
	rearange(string, '\xFF');
	return (string);
}

// void	remove_pair(char *string, int find)
// {
// 	int	i;
// 	int	close;
// 	int	stop;

// 	i = 0;
// 	while (string[i])
// 	{
// 		close = find_pair(&string[i], (char *)(&find));
// 		if (close)
// 		{
// 			stop = i + close;
// 			while (i++ < stop)
// 				string[i - 1] = string[i];
// 			while (string[++stop])
// 				string[stop - 2] = string[stop];
// 			string[stop - 1] = 0;
// 			string[stop - 2] = 0;
// 			i -= 2;
// 		}
// 		else
// 			i++;
// 	}
// }


struct s_control {

} ;

struct s_command {

	t_control	*main;
} ;