/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:38:19 by timurray          #+#    #+#             */
/*   Updated: 2025/09/04 12:47:23 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

int get_pid(const char *pid)
{
	int i;
	long num;

	i = 0;
	while(pid[i])
	{
		if (ft_isdigit(pid[i]) == 0)
		{
			ft_putendl_fd("Integer PID values only.", 2);
			return (0);
		}
		i++;
	}
	num = ft_atol(pid);
	if(!(num > 0 && num <= 4194304))
	{
		ft_putendl_fd("Valid PID range 1 - 4194304.", 2);
		return (0);
	}
	return (int)(num);
}
