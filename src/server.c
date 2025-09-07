/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:58:15 by timurray          #+#    #+#             */
/*   Updated: 2025/09/07 10:29:27 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static char	*resize_msg(char *msg, int length, int *size)
{
	char	*temp;

	if (!msg)
	{
		msg = (char *)malloc(*size * sizeof(char) + 1);
		if (!msg)
			exit(1);
	}
	if (length + 1 >= *size)
	{
		*size *= 2;
		temp = (char *)malloc(*size * sizeof(char) + 1);
		if (!temp)
			exit(1);
		temp = ft_memcpy(temp, msg, length);
		free(msg);
		msg = temp;
	}
	return (msg);
}

static void	finish_msg(char **msg, int *size, int *length)
{
	(*msg)[*length] = '\0';
	ft_putendl_fd(*msg, 1);
	free(*msg);
	*msg = NULL;
	*size = MSG_BUFFER_SIZE;
	*length = 0;
}

static void	signal_detect(int sig, siginfo_t *info, void *context)
{
	static unsigned char	c = 0;
	static int				bit = 7;
	static int				length = 0;
	static int				size = MSG_BUFFER_SIZE;
	static char				*msg;

	(void)context;
	msg = resize_msg(msg, length, &size);
	if (sig == SIGUSR2)
		c = c | ((unsigned int)1 << bit);
	if (--bit < 0)
	{
		if (c == '\0')
			finish_msg(&msg, &size, &length);
		else
			msg[length++] = c;
		c = 0;
		bit = 7;
	}
	if (info)
		kill(info->si_pid, SIGUSR1);
}

static void	init_sigact(void)
{
	struct sigaction	sigact;

	sigact.sa_flags = SA_SIGINFO;
	sigact.sa_sigaction = signal_detect;
	sigemptyset(&sigact.sa_mask);
	sigaddset(&sigact.sa_mask, SIGUSR1);
	sigaddset(&sigact.sa_mask, SIGUSR2);
	if (sigaction(SIGUSR1, &sigact, 0) == -1)
	{
		ft_putendl_fd("Server SIGUSR1 failure.", 2);
		exit(1);
	}
	if (sigaction(SIGUSR2, &sigact, 0) == -1)
	{
		ft_putendl_fd("Server SIGUSR2 failure.", 2);
		exit(1);
	}
}

int	main(void)
{
	pid_t	pid;

	init_sigact();
	pid = getpid();
	ft_printf("Server PID: %d\n", pid);
	while (1)
		pause();
	return (0);
}
