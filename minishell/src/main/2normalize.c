#include <minishell.h>

int	count_cases(char **string)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (!string)
		return (0);
	while (string[i])
	{
		if (string[i][0] == '|' || string[i][0] == '&' || string[i][0] == ';')
			count++;
		i++;
	}
	return (count);
}

void	print_split_input(char ***input)
{
	int	i;
	int	j;

	i = 0;
	while (input[i])
	{
		j = 0;
		while (input[i][j])
		{
			ft_printf("%s\n", input[i][j]);
			j++;
		}
		ft_printf("-\n");
		i++;
	}
}

char	**copy_split_size(char **split, int size)
{
	char	**new;
	int		i;

	new = ft_calloc(sizeof(char *), size + 1);
	i = 0;
	while (split[i] && i < size)
	{
		new[i] = split[i];
		i++;
	}
	return (new);
}

int	is_end_of_command(char c)
{
	if (c == '|' || c == '&' || c == ';')
		return (1);
	return (0);
}

void	normalize_input(t_control *get)
{
	int			index;
	int			start;
	int			j;
	char		**split;

	if (!get->input)
		return ;
	split = shell_split(get->input);
	get->tokens = ft_calloc(sizeof(char **), count_cases(split) + 2);
	index = 0;
	j = 0;
	start = 0;
	while (split[index])
	{
		if (is_end_of_command(split[index][0]))
		{
			get->tokens[j++] = copy_split_size(&split[start], index - start);
			start = index;
		}
		index++;
	}
	get->tokens[j++] = copy_split_size(&split[start], index - start);
	free(split);
}
