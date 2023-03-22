/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malleman <malleman@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:15:36 by malleman          #+#    #+#             */
/*   Updated: 2023/03/22 13:35:53 by malleman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
	Fonction permettant de recevoir le message envoier via client. On void le 
	context afin de le mute. Ensuite on va ajouter dans i la valeur de signal
	si il est bien SIGUSR1. On incremente notre variable bit. Si notre bit est 
	a 8 et que i est egal a 0 alors ont aura fini notre string, on print un 
	retour a la ligne et on envoie le signal SIGUSR2. Si i n'est pas egal 0 on
	print notre char et on remet bit et i a 0 pour attendre le prochain char. 
	Si bit n'est pas a 8 alors on decale de 1 vers la droite pour recuperer le 
	bit suivant dans i. 
*/
void	receipt_message(int signal, siginfo_t *info, void *context)
{
	static int			bit;
	static unsigned int	i;

	(void) *context;
	i |= (signal == SIGUSR1);
	bit++;
	if (bit == 8)
	{
		if (i == 0)
		{
			ft_printf("\n");
			kill(info->si_pid, SIGUSR2);
		}
		ft_printf("%c", i);
		bit = 0;
		i = 0;
	}
	i = i << 1;
}

/*
	Fonction main qui ne prend rien en parametre. On va chercher le pid avec la 
	fonction getpid ensuite on le print dans le terminal.
	On defini sigaction avec la fonction receipt_message, la fonction sigempty
	permet de mute le mask et on met les flags a 0 pour les mute egalement.  
	Ensuite on met une boucle infie en definissant sigaction avec SIGUSR1 et 
	SIGUSR2 et un pause pour pouvoir attendr les prochains signaux envoyer par 
	le client. 
*/
int	main(void)
{
	int					pid;
	struct sigaction	act;

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
