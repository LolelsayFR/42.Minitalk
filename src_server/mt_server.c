/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mt_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:40:04 by emaillet          #+#    #+#             */
/*   Updated: 2024/11/21 01:21:54 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mt_server.h"

int	g_sig1;

int	main(void)
{
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	ft_printf(GRN"Server PID : %i\n"RES, getpid());
	while (1)
	{
		pause();
	}
	ft_printf(RED"Stop"RES);
	return (0);
}

void	signal_handler(int sig)
{
	if (sig == 10)
		g_sig1 += 1;
	else
	{
		if (g_sig1 != 0)
			ft_putchar_fd((char)g_sig1, 1);
		g_sig1 = 0;
	}
}
