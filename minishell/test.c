#include <unistd.h>
#include <stdio.h>

typedef struct s_int {
	int t_int[5];
} t_int;

// int *pass_compound(void)
// {
// 	return ((int [5j]){5, 3, 7, 2, 1});
// }

t_int pass_compound(void)
{
	return ((t_int){5, 3, 7, 2, 1});
}

int	main(void)
{
	t_int	array;
	int		*new_array;

	array = pass_compound();
	new_array = ((int *)&array);
	for (int i = 0; i < 5; i++)
		printf("%i, ", new_array[i]);
	printf("\n");
	for (int i = 0; i < 5; i++)
		printf("%i, ", ((int *)&array)[i]);
	printf("\n");
}
