#include "../../includes/philosophers.h"

static int	ft_isspace(int C)
{
	return (((C >= 9 && C <= 13) || C == 32));
}

static int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	n;

	if (!str)
		return (0);
	i = 0;
	sign = 1;
	n = 0;
	while (ft_isspace(str[i]) && str[i])
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while ((str[i] >= '0' && str[i] <= '9') && str[i])
	{
		n = n * 10 + (str[i] - '0');
		i++;
	}
	return (n * sign);
}


e_bool ft_parse_cmd_line(int argc, char *argv[], t_params *params)
{
    if (argc < 4 || argc > 5)
        return (FALSE);

    params->number_of_philosofers = (unsigned int) ft_atoi(argv[1]);
    params->time_to_die           = (unsigned int) ft_atoi(argv[2]);
    params->time_to_eat           = (unsigned int) ft_atoi(argv[3]);
    params->time_to_sleep         = (unsigned int) ft_atoi(argv[4]);
    if (argc > 4) 
        params->number_of_time_must_eat = ft_atoi(argv[5]);
    else
        params->number_of_time_must_eat = 0;
    return (TRUE);
}

