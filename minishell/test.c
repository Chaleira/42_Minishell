#include <stdio.h>


struct s_stupido {
	int	a[5];
};

t_stupido fill_array(void)
{
	return ((t_stupido){10, 9, 8, 7, 6});
}

int main(void)
{
	t_stupido *array;

	array = &fill_array();
	for (int i = 0; i < 5; i++)
		printf("%i ", ((int *)&array)[i]);
}