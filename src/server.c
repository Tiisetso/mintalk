/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:58:15 by timurray          #+#    #+#             */
/*   Updated: 2025/09/03 18:59:04 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void signal_detect(int sig, siginfo_t *info, void *context)
{
	static unsigned char c = 0;
	static int bit = 7;
	static int i = 0;
	static char buf[1024];
	
	(void)context;
	(void)info;
	if(sig == SIGUSR2)
		c = c | (1 << bit);
	bit--;
	if (bit < 0)
	{
		if (c == '\0')
		{
			buf[i] = '\0';
			ft_putendl_fd(buf,1);
			i = 0;
		}
		else
			buf[i++] = c;
		c = 0;
		bit = 7;
	}
}

static void    init_sigact(void)
{
    struct sigaction    sigact;

    sigact.sa_flags = SA_SIGINFO;
    sigact.sa_sigaction = signal_detect;
    sigemptyset(&sigact.sa_mask);
    sigaddset(&sigact.sa_mask, SIGUSR1);
    sigaddset(&sigact.sa_mask, SIGUSR2);
    if (sigaction(SIGUSR1, &sigact, 0) == -1)
        ft_putendl_fd("fail",2);
    if (sigaction(SIGUSR2, &sigact, 0) == -1)
        ft_putendl_fd("fail",2);
}

int main(void)
{
	pid_t pid;

	init_sigact();

	pid = getpid();
	ft_printf("Server PID: %d\n", pid);
	
	while (1)
        pause();
	return(0);
}

// Check for buf limits
//send signal back. 
//Read receipt for final message.
//Error cascading handling