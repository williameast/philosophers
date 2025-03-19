#include "philosophers.h"

void print_settings(const t_settings *settings)
{
    if (settings == NULL)
    {
        printf("Error: Settings is NULL\n");
        return;
    }
    printf("Settings at time: %zu :\n", get_time());
    printf("Number of philosophers: %d\n", settings->n);
    printf("Time to die: %d\n", settings->time_to_die);
    printf("Time to eat: %d\n", settings->time_to_eat);
    printf("Time to sleep: %d\n", settings->time_to_sleep);
    printf("Number of meals needed: %d\n", settings->meals_needed);
}

void	print_thread_message(char *str, t_phil *phil)
{
	size_t time;

	// lock thread

}
