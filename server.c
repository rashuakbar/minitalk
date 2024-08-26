#include "minitalk.h"

int	main(void)
{
	struct sigaction	s_sig;
	

	int pid;	
	ft_putstr_fd("PID: ",1);
	ft_putnbr_fd(pid=getpid(),1);
	sigaction(SIGUSR1, &sa_sig,NULL)
	return (0);
}