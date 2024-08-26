#include "minitalk.h"

int main(int argc, char **argv)
{
	if(argc != 3)
	{
		ft_putstr_fd("ERROR \n Please  send your message in this format: PID \"text\"");
		exit(1);
	}
	signal(SIGUSR1, &handler_sig);
	signal(SIGUSR2, &handler_sig);
}