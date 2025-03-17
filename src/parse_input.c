#include "libft.h"
#include "libft_extra.h"
#include "philosophers.h"



t_settings	*init_settings(int argc, char *argv[])
{
	t_settings *settings;
	int	*array[];
    if (argc != 5 && argc != 6)
        return NULL;
	settings = safe_malloc(sizeof(t_settings));

	array =




	settings.n = n;
	settings.time_to_die = die;
	settings.time_to_eat = eat;
	settings.time_to_sleep = sleep;
	settings.meals_needed = win; // make -1 for ignored
}


int main(int argc, char *argv[])
{
	int	i;

	i = 1;
	if (argc != 5 || argc != 6)
		return 1;

	while (i < argc)
	{
		ft_atoi(argv[i]);
	}



    return 0;
}
