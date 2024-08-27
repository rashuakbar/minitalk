/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimendes <vimendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:21:52 by vimendes          #+#    #+#             */
/*   Updated: 2024/08/27 22:02:13 by vimendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

size_t	get_sleep(size_t size)
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

void	send_bit(int pid, char c, size_t len)
{
	int	bit;
	int		signal;
	
	bit = 0;
	while (bit < 8)
	{
		if (c & (1 << bit))
			signal = SIGUSR1;
		else 
			signal = SIGUSR2;
		if (kill(pid,signal) == -1)
		{
			ft_putstr_fd("ERRO SENDING BITS", 1);
			exit(1);
		}
		usleep(get_sleep(len));
		bit++;
	}
}

int main(int argc, char **argv)
{
	int	pid;
	size_t i;
	
	if(argc != 3)
	{
		ft_putstr_fd("ERROR \n Please  send your message in this format: PID \"text\"",1);
		exit(1);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	{
		ft_putstr_fd("PID invalid",1);
	}
	i = 0;
	while(argv[2][i] != '\0')
	{
		send_bit(pid, argv[2][i], ft_strlen(argv[2]));
		i++;
	}
	send_bit(pid,'\0',1);
	return (0);
}
