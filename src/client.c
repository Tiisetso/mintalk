/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:58:13 by timurray          #+#    #+#             */
/*   Updated: 2025/09/05 17:53:20 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static volatile sig_atomic_t g_msg_receipt = 0;

static void receipt_handler(int sig)
{
	(void)sig;
	g_msg_receipt = 1;
}

static void receipt_wait(void)
{
	while(!g_msg_receipt)
		pause();
	g_msg_receipt = 1;
}

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
		if(kill(pid, sig) == -1)
			return (1);
		usleep(100);
	}
	receipt_wait();
	// ft_printf("message receipt.\n"); // TODO remove
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

// int send_length(pid_t pid, size_t length)
// {
// 	int i;
// 	unsigned char byte_32;

// 	i = 3;
// 	while(i >= 0)
// 	{
// 		byte_32 = (unsigned char)(length >> (i * 8)) & (unsigned int)0b11111111;
// 		if(!(send_char(pid, byte_32) == 0))
// 			return (1);
// 		i--;
// 	}
// 	return (0);
// }

static void    init_sigact(void)
{
    struct sigaction    sigact;

    sigact.sa_flags = 0;
    sigact.sa_handler = receipt_handler;
    sigemptyset(&sigact.sa_mask);
    // sigaddset(&sigact.sa_mask, SIGUSR1);
    // sigaddset(&sigact.sa_mask, SIGUSR2);
    if (sigaction(SIGUSR1, &sigact, 0) == -1)
        ft_putendl_fd("fail",2);
    // if (sigaction(SIGUSR2, &sigact, 0) == -1)
    //     ft_putendl_fd("fail",2);
}

int main(int ac, char **av)
{
	int pid;
	// size_t length;

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
		init_sigact();
		
		// length = ft_strlen(av[2]);
		// send_length(pid, length);


		
		

		send_string(pid, av[2]);
	}
	return(0);
}

// Arg size
// Send length, 


// -1 exception? Edge cases?
// Acknowledge server receipt?
// Error cascading handling
//does client kill return -1?