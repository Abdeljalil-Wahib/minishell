#include "../minishell.h"

void	ft_change_sp(char **str)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = *str;
	while (new_str && new_str[i])
	{
		if ((new_str[i] >= 9 && new_str[i] <= 13) || new_str[i] == '\n')
			new_str[i] = ' ';
		i++;
	}
}

void	split_newvals(char **args, char *new_val, int *tabsize,
		char ***new_vals)
{
	int	size;

	ft_change_sp(&new_val);
	*new_vals = ft_split(new_val, ' ');
	size = ft_strlen_double(*new_vals);
	*tabsize = ft_strlen_double(args) + size + 1;
}

void	copy_newvals(char **new_args, char **new_vals, int *index)
{
	int	j;

	j = 0;
	while (new_vals && new_vals[j])
	{
		new_args[*index] = ft_strdup(new_vals[j]);
		(*index)++;
		j++;
	}
	ft_free(new_vals);
}

char	**args_inserter(char **args, char *new_val, int is_unquoted)
{
	int		tab_size;
	int		index;
	char	**newvals;
	char	**new_args;

	index = 0;
	if ((is_unquoted == 1 && !args) || (args && args[0] && ft_strcmp(args[0],
				"export") != 0 && is_unquoted))
		split_newvals(args, new_val, &tab_size, &newvals);
	else
		tab_size = ft_strlen_double(args) + 2;
	new_args = malloc(sizeof(char *) * tab_size);
	while (index < ft_strlen_double(args))
	{
		new_args[index] = args[index];
		index++;
	}
	if ((is_unquoted == 1 && !args) || (args && args[0] && ft_strcmp(args[0],
				"export") != 0 && is_unquoted))
		copy_newvals(new_args, newvals, &index);
	else
		new_args[index] = ft_strdup(new_val);
	new_args[tab_size - 1] = NULL;
	free(args);
	return (new_args);
}
