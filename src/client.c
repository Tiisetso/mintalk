/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:58:13 by timurray          #+#    #+#             */
/*   Updated: 2025/09/07 12:27:27 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static volatile sig_atomic_t	g_msg_receipt = 0;

static void	receipt_handler(int sig)
{
	(void)sig;
	g_msg_receipt = 1;
}

static int	send_char(pid_t pid, unsigned char c)
{
	int	i;
	int	bit;
	int	sig;

	i = 8;
	while (i > 0)
	{
		i--;
		bit = (c >> i) & 1u;
		if (bit == 0)
			sig = SIGUSR1;
		else
			sig = SIGUSR2;
		g_msg_receipt = 0;
		if (kill(pid, sig) == -1)
			return (1);
		while (g_msg_receipt == 0)
			pause();
	}
	return (0);
}

static int	send_string(pid_t pid, const char *msg)
{
	size_t	i;

	i = 0;
	if (!msg)
		return (1);
	while (msg[i])
	{
		if (send_char(pid, (unsigned char)msg[i]))
			return (1);
		i++;
	}
	if (send_char(pid, '\0'))
		return (1);
	return (0);
}

static void	init_sigact(void)
{
	t_sigaction	sigact;

	sigact.sa_flags = 0;
	sigact.sa_handler = receipt_handler;
	sigemptyset(&sigact.sa_mask);
	sigaddset(&sigact.sa_mask, SIGUSR1);
	if (sigaction(SIGUSR1, &sigact, NULL) == -1)
	{
		ft_putendl_fd("Client SIGUSR1 failure.", 2);
		exit(1);
	}
}

int	main(int ac, char **av)
{
	pid_t	pid;

	if (ac != 3)
	{
		ft_putendl_fd("Invalid use.\nUsage: ./client <valid PID> <msg>", 2);
		return (1);
	}
	else
	{
		pid = get_pid(av[1]);
		if (!pid)
			return (1);
		init_sigact();
		if (send_string(pid, av[2]))
		{
			ft_putendl_fd("Send msg failure.", 2);
			return (1);
		}
	}
	return (0);
}
