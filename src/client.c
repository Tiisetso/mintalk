/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:58:13 by timurray          #+#    #+#             */
/*   Updated: 2025/09/04 12:33:11 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

int send_char(pid_t pid, unsigned char c)
{
	int i;
	int bit;
	int sig;

	i = 8;
	while(i > 0)
	{
		i--;
		bit  = (c >> i) & 1;
		if (bit == 0)
			sig = SIGUSR1;
		else
			sig = SIGUSR2;
		kill(pid, sig);
		usleep(200);
	}
	return (0);
}

int send_string(pid_t pid, char *msg)
{
	int i;

	i = 0;
	while(msg[i])
	{
		send_char(pid, msg[i]);
		i++;
	}
	send_char(pid, '\0');
	return (0);
}

// int send_length(pid_t pid, char *msg)
// {
	
// }

int main(int ac, char **av)
{
	int pid;

	if (ac != 3)
	{
		ft_putendl_fd("Enter PID and message string.", 2);
		return (1);
	}
	else
	{
		pid = get_pid(av[1]);
		if (!pid)
			return (1);
		send_string(pid, av[2]);
		// pid = ft_atoi(av[1]);
		// ft_printf("pid: %d\n", pid);
		// ft_printf("msg: %s\n", av[2]);
	}
	return(0);
}

//is digit first.

// Arg size
// Send length, wait, send message.
//Error check
// Is pid a number, size limits on range
// How much text can we send?
// -1 exception? Edge cases?
// Acknowledge server receipt?
// Error cascading handling
//does client kill return -1?