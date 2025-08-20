#include "../minishell.h"

void	close_fds(t_fds_controle *fds)
{
	if (fds->read_from > 0)
		close(fds->read_from);
	if (fds->write_on > 1)
		close(fds->write_on);
}

int	ft_handel_infile(t_files *files, t_fds_controle **fds)
{
	if ((*fds)->read_from > 0)
		close((*fds)->read_from);
	if ((ft_strchr(files->name, ' ') && files->s_type == t_nquoted)
		|| files->name[0] == '\0')
	{
		ft_dprintf(2, "%s: ambiguous redirect\n", files->name);
		(*fds)->read_from = -1;
		close_fds(*fds);
		return (-1);
	}
	if (access(files->name, F_OK) == 0 && access(files->name, R_OK) == -1)
	{
		ft_dprintf(2, "%s: Permission denied\n", files->name);
		(*fds)->read_from = -1;
		close_fds(*fds);
		return (-1);
	}
	(*fds)->read_from = open(files->name, O_RDONLY, 0664);
	if ((*fds)->read_from == -1)
	{
		ft_dprintf(2, "%s: No such file or directory\n", files->name);
		close_fds(*fds);
		return (-1);
	}
	return (0);
}

int	ft_hendel_outfile(t_files *files, t_fds_controle **fds)
{
	if ((*fds)->write_on > 1)
		close((*fds)->write_on);
	if ((ft_strchr(files->name, ' ') && files->s_type == t_nquoted)
		|| files->name[0] == '\0')
	{
		ft_dprintf(2, "%s: ambiguous redirect\n", files->name);
		(*fds)->write_on = -1;
		close_fds(*fds);
		return (-1);
	}
	if (access(files->name, F_OK) == 0 && access(files->name, W_OK) == -1)
	{
		ft_dprintf(2, "%s: Permission denied\n", files->name);
		(*fds)->write_on = -1;
		close_fds(*fds);
		return (-1);
	}
	if (files->type == t_outred)
		(*fds)->write_on = open(files->name, O_CREAT | O_WRONLY | O_TRUNC,
				0664);
	else
		(*fds)->write_on = open(files->name, O_CREAT | O_WRONLY | O_APPEND,
				0664);
	return (0);
}

t_fds_controle	*ft_handel_fds(t_files *files)
{
	t_fds_controle	*fds;

	fds = malloc(sizeof(t_fds_controle));
	if (!fds)
		return (NULL);
	fds->read_from = 0;
	fds->write_on = 1;
	while (files)
	{
		if (files->type == t_inred || files->type == t_heredoc)
		{
			if (ft_handel_infile(files, &fds) == -1)
			{
				return (fds);
			}
		}
		else if (files->type == t_outred || files->type == t_append)
		{
			if (ft_hendel_outfile(files, &fds) == -1)
				return (fds);
		}
		files = files->next;
	}
	return (fds);
}

int	ft_check_builtin(char *cmd)
{
	char	*builtins[8];
	int		i;

	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
	builtins[7] = NULL;
	i = 0;
	while (i < 7)
	{
		if (ft_strcmp(cmd, builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}
