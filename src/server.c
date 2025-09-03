/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:58:15 by timurray          #+#    #+#             */
/*   Updated: 2025/09/03 15:02:40 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void signal_detect(int sig, siginfo_t *info, void *context)
{
	(void)context;
	if (sig == SIGUSR1)
		ft_printf("SIGUSR1: %d from %d\n", sig, info->si_pid); //TODO change to write
	if (sig == SIGUSR2)
		ft_printf("SIGUSR2: %d\n", sig);
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

// Rebuild string!
//process signal? Unicode?
//show the result unicode?
//send signal back. Read receipt?
