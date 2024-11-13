/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mianni <mianni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:05:56 by mianni            #+#    #+#             */
/*   Updated: 2024/11/13 15:13:14 by mianni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigquit(t_data *data)
{
	if (data->is_child == 1)
	{
		ft_putstr_fd("Quit: 3\n", 1);
		data->status = 131;
		g_status = 131;
	}
}

int	readline_function(void)
{
	return (0);
}

void	set_parent_signals(void)
{
	rl_event_hook = readline_function;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	set_child_signals(void)
{
	rl_event_hook = readline_function;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	signal_handler(int signum)
{
	t_data	*data;

	data = get_data(NULL);
	g_status = 128 + signum;
	rl_done = 1;
	data->signaled = 1;
}
