#include "../minishell.h"

int	check_num(char *str)
{
	int	i;

	i = 0;
	if (str && (!str[0] || ((str[0] == '-' || str[0] == '+') && !str[1])))
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str && str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(t_commands *commands)
{
	ft_dprintf(1, "exit\n");
	if (commands->options && commands->options[1]
		&& check_num(commands->options[1]) == 1
		&& ft_strlen_double(commands->options) > 2)
	{
		ft_dprintf(2, "exit: too many arguments\n");
		g_all_data->status = 1;
	}
	else
	{
		if (commands->options && commands->options[1])
		{
			if (check_num(commands->options[1]) == 0)
			{
				ft_dprintf(2, "%s: numeric argument required\n",
					commands->options[1]);
				exit(2);
			}
			exit(ft_atoi(commands->options[1]));
		}
		else
			exit(0);
	}
}
