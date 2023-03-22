/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malleman <malleman@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:01:42 by malleman          #+#    #+#             */
/*   Updated: 2023/03/22 13:15:12 by malleman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
	Fonction permettant d'envoyer dans le shell la confirmation que le message
	a ete recu si le signal est bien egal a SIGUSR2.
*/
void	confirmed_message(int signal)
{
	if (signal == SIGUSR2)
		ft_printf("Message reçu\n");
}

/*
	Fonction permettant d'envoyer le message au serveur. On initialise bit a 8
	afin d'avoir l'entier de l'octect et on boucle tant que l'on est pas a 0.
	tant qu'on peux decaler a droite sur le prochain bit on envoie le SIGUSR1.
	Si ce n'est plus le cal on envoie SIGUSR2 car on sera a la fin du message.
	Le usleep permet a la fonction de patienter entre deux envoie de signal.
*/
void	message_sender(int pid, char c)
{
	int	bit;

	bit = 8;
	while (bit--)
	{
		if ((c >> bit) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(500);
	}
}

/*
	Fonction main qui prend en parametre le num. PID donner par le serveur et
	la string que l'on souhaite transmettre. 
	Si le nombre d'argument est juste on transforme le PID recu de av[1] en int
	pour le stocker dans la variable pid. La fonction signal est defenie avec
	SIGUSR2 et la fonction confirmed_message. 
	Elle boucle tant que la string n'est pas terminee et envoi chaque char a la
	fonction message_sender. Une fois terminee on envoie a la fonction 
	message_sender avec le pid et le /0 pour l'informer que le message est fini.
	Si le nombre  d'argument est faux on print un message d'erreur. 
*/
int	main(int ac, char **av)
{
	int	pid;
	int	i;

	i = 0;
	if (ac == 3)
	{
		pid = ft_atoi(av[1]);
		signal(SIGUSR2, confirmed_message);
		while (av[2][i] != '\0')
		{
			message_sender(pid, av[2][i]);
			i++;
		}
		message_sender(pid, '\0');
	}
	else
	{
		ft_printf("Nombre d'arguments incorrects\n");
		return (1);
	}
	return (0);
}
