#include "minitalk.h"

void    confirmed_message(int signal)
{
    if (signal == SIGUSR2)
        ft_printf("Message reçu\n");
}

void    message_sender(int pid, char c)
{
    int bit;

    bit = 0;
    while (bit < 8)
    {
        if (c & (0x01 << bit))
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        usleep(500);
        bit++;
    }
}

int main(int ac, char **av)
{
    int pid;
    int i;

    i = 0;
    if (ac == 3)
    {
        pid = ft_atoi(av[1]);
        while (av[2][i])
        {
            message_sender(pid, i);
            i++;
        }
        signal(SIGUSR2, confirmed_message);
        message_sender(pid, '\0');
    }
    else
    {
        ft_printf("Nombre d'arguments incorrects\n");
        return (1);
    }
    return (0);
}