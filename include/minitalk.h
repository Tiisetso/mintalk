/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 19:05:21 by timurray          #+#    #+#             */
/*   Updated: 2025/09/06 15:41:50 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "../libft/libft.h"
# include <signal.h>

# ifndef MSG_BUFFER_SIZE
#  define MSG_BUFFER_SIZE 4096
# endif

int			get_pid(const char *pid);

#endif
