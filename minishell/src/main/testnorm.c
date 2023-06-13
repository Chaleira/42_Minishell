#include <minishell.h>

int	count_cases(char **string)
{
	int	count;
	int	i;

	(void)find;
	count = 0;
	i = 0;
	if (!string)
		return (0);
	while (string[i])
	{
		if (*string[index] == '|' || *string[index] == '&' || *string[index] == ';')
			count++;
		i++;
	}
	return (count);
}

void	fix_quotes(char *string)
{
	int	i;
	int	close;
	int	stop;

	i = 0;
	while (string[i])
	{
		close = ignore_quotes(&string[i]);
		if (close)
		{
			stop = i + close;
			while (i++ < stop)
				string[i - 1] = string[i];
			while (string[++stop])
				string[stop - 2] = string[stop];
			string[stop - 1] = 0;
			string[stop - 2] = 0;
			i -= 2;
		}
		else
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
		new[i] = split[i];
	return (new);
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
	get->pipes = count_cases(split);
	get->pieces = ft_calloc(sizeof(char **), get->pipes + 2);
	i = 0;
	j = 0;
	start = 0;
	while (split[index])
	{
		if (*split[index] == '|' || *split[index] == '&' || *split[index] == ';')
		{
			get->pieces[j++] = copy_split_size(&split[start], index - start);
			start = index;
		}
		index++;
	}
	free(split);
}