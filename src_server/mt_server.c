/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mt_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 22:55:34 by emaillet          #+#    #+#             */
/*   Updated: 2025/02/17 23:13:42 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mt_server.h"
#include <signal.h>

/* ************************************************************************** */
/* Handle strlen int bit per bit (Size of int = 32 bit)                       */
/* ************************************************************************** */
void	ft_sv_strlen(int *curr_bit, char **str, int *len_received, int signal)
{
	static int	len_val = 0;

	if (signal == SIGUSR2)
		len_val += (1 << *curr_bit);
	if (*curr_bit == 31)
	{
		*len_received = 1;
		*str = ft_calloc((len_val + 1), sizeof(char));
		if (!*str)
			exit(EXIT_FAILURE);
		*curr_bit = 0;
		len_val = 0;
	}
	else
		(*curr_bit)++;
}

/* ************************************************************************** */
/* Make minitalk server great again ! (Its just a free and re-init var's)     */
/* ************************************************************************** */
void	mt_sv_restart(int *len_received, char **str, int *i)
{
	*len_received = 0;
	if (*str)
	{
		ft_printf("%s\n", *str);
		free(*str);
		*str = NULL;
	}
	*i = 0;
}

/* ************************************************************************** */
/* Handle sig's and convert them in some char bit per bit (char = 8 bit)      */
/* ************************************************************************** */
void	sv_sig_handler(int signal, siginfo_t *info, void *context)
{
	static int	char_value = 0;
	static int	current_bit = 0;
	static int	len = 0;
	static int	i = 0;
	static char	*final_str = NULL;

	(void)context;
	if (!len)
		ft_sv_strlen(&current_bit, &final_str, &len, signal);
	else
	{
		if (signal == SIGUSR2)
			char_value += (1 << current_bit);
		if (current_bit == 7)
		{
			final_str[i++] = char_value;
			if (char_value == '\0')
				mt_sv_restart(&len, &final_str, &i);
			char_value = 0;
			current_bit = 0;
		}
		else
			current_bit++;
	}
	kill(info->si_pid, SIGUSR1);
}

/* ************************************************************************** */
/* Just the main function, define sig action.                                 */
/* ************************************************************************** */
int	main(void)
{
	struct sigaction	sa;

	ft_printf(GRN"Server PID: %d\n"RES, getpid());
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sv_sig_handler;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/* End of file...                                                             */
/* ************************************************************************** */
