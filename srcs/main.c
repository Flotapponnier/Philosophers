#include "../includes/philosopher.h"

int main(int argc, char **argv)
{
	t_table *table;

    if(is_valid_input(argc, argv))
	{
		table = initialising_table(argc, argv);
	}
	ft_printf("valid argument");
    return (0);
}
