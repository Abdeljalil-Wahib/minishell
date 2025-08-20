#include "../minishell.h"

void	handle_sig(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_all_data->status = 130;
}
