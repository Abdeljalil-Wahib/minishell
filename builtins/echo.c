#include "../minishell.h"

int	ft_parse_n(char *str)
{
	int	i;

	i = 0;
	if (str && str[i] == '-' && str[i + 1] == 'n')
	{
		i++;
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

void	ft_print_echo(t_commands *commands, int i, int fd)
{
	int	k;

	k = i;
	while (commands->options && commands->options[i])
	{
		ft_dprintf(fd, "%s", commands->options[i]);
		i++;
		if (commands->options[i])
			ft_dprintf(fd, " ");
	}
	if (k < 2)
		ft_dprintf(fd, "\n");
}

void	ft_echo(t_commands *commands, int fd)
{
	int	flag;
	int	i;

	i = 1;
	flag = 1;
	while (flag == 1)
	{
		flag = ft_parse_n(commands->options[i]);
		if (flag == 0)
			break ;
		i++;
	}
	ft_print_echo(commands, i, fd);
}
