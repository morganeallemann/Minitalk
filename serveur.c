#include "minitalk.h"

void    receipt_message(int signal, siginfo_t *info, void *context)
{
    static int  bit;
    static int  i;

    (void) *context;
    if (signal == SIGUSR1)
        i |= (0x01 << bit);
    bit++;
    if (bit == 8)
    {
        if (i == 0)
            kill(info->si_pid, SIGUSR2);
        ft_printf("%c", i);
        bit = 0;
        i = 0;
    }
}

int main()
{
    int                 pid;
    struct sigaction    act;

    pid = getpid();
    ft_printf("PID: %d\n", pid);
    act.sa_sigaction = receipt_message;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    while (1)
    {
        sigaction(SIGUSR1, &act, NULL);
        sigaction(SIGUSR2, &act, NULL);
        pause ();
    }
    return (0);
}