/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimendes <vimendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:21:52 by vimendes          #+#    #+#             */
/*   Updated: 2024/08/28 13:00:54 by vimendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sinal;
	int	result;

	sinal = 1;
	result = 0;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sinal = -sinal;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - 48);
		i++;
	}
	return (result * sinal);
}

size_t	time_sleep(size_t size)
{
	if (size < 4000)
		return (50);
	else if (size < 10000)
		return (150);
	else if (size < 20000)
		return (200);
	else if (size < 60000)
		return (300);
	else if (size < 100000)
		return (500);
	else
		return (10000);
}
void	handler_mens(int signum)
{
	if (signum == SIGUSR2)
		ft_putendl_fd("Message delivery", 1);
	if (signum == SIGUSR1)
		ft_putendl_fd("ainda a enviar ", 1);
}

void	send_bit(int pid, char c, size_t len)
{
	int	bit;
	int	signal;

	(void)len;
	bit = 0;
	while (bit < 8)
	{
		if (c & (1 << bit))
			signal = SIGUSR1;
		else
			signal = SIGUSR2;
		if (kill(pid, signal) == -1)
		{
			ft_putstr_fd("ERRO SENDING BITS", 1);
			exit(1);
		}
		usleep (4000);
		//usleep(time_sleep(len));
		bit++;
	}
}

int	main(int argc, char **argv)
{
	int		pid;
	size_t	i;

	signal(SIGUSR2, handler_mens);
	signal(SIGUSR1, handler_mens);
	if (argc != 3)
	{
		ft_putstr_fd("ERROR\nwrong input format! PID \"text\" \n", 1);
		exit(1);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	{
		ft_putstr_fd("PID invalid", 1);
	}
	i = 0;
	while (argv[2][i] != '\0')
	{
		send_bit(pid, argv[2][i], ft_strlen(argv[2]));
		i++;
	}
	send_bit(pid, '\0', 1);
	return (0);
	while(1)
		pause();
}
