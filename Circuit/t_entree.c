#define _CRT_SECURE_NO_WARNINGS
#include "t_entree.h"

t_entree* t_entree_init(int num)
{
	/* On déclare un pointeur menant vers un type t_entree et on alloue de l'espace mémoire pour nouvelle_entree. */. */
	t_entree* nouv_entree = (t_entree*)malloc(sizeof(t_entree));
	
	/* Si le retour de la fonction malloc est égale à NULL. */
	if (nouv_entree == NULL)
	{
		/* On quitte le programme. */
		EXIT_FAILURE;
	}
	
	/* On alloue de l'espace mémoire pour le nom de nouvelle_entree. */
	nouv_entree->nom = (char*)malloc(sizeof(NOM_ENTREE_TAILLE_MAX + 1));

	/* Si le retour de la fonction malloc est égale à NULL. */
	if (nouv_entree->nom == NULL)
	{
		/* On libère l'espace mémoire allouée à nouvelle_entree. */
		free(nouv_entree);
		
		/* On quitte le programme. */
		EXIT_FAILURE;
	}
	
	/* On assigne l'identificateur à l'entrée. */
	nouv_entree->id = num;
	
	/* On crée le nom de la l'entrée. */
	sprintf(nouv_entree->nom, "E%d", num);
	
	/* On initialise la pin sortie de l'entree. */
	nouv_entree->pin = t_pin_sortie_init();

	/* On retourne nouv_entree. */
	return nouv_entree;
}

void t_entree_destroy(t_entree* entree)
{
	/* On libère l'espace mémoire occupé la pin sortie de l'entree. */
	t_pin_sortie_destroy(entree->pin);
	
	/* On libère l'espace mémoire occupé par le nom de l'entree. */
	free(entree->nom);

	/* On libère l'espace mémoire occupé par l'entree. */
	free(entree);
}

t_pin_sortie* t_entree_get_pin(t_entree* entree)
{
	/* On retourne le pointeur vers la pin sortie de l'entree. */
	return entree->pin;
}

int t_entree_est_reliee(t_entree* entree)
{
	/* Ou retourne la valeur de la fonction t_pin_sortie_est_reliee . */
	return t_pin_sortie_est_reliee(entree->pin);
}

void t_entree_reset(t_entree* entree)
{
	/* On reintitialise la pin sortie de l'entree. */
	t_pin_sortie_reset(entree->pin);
}

int t_entree_propager_signal(t_entree* entree)
{
	/* Si la valeur de la pin sortie de l'entrer n'est pas égale à -1. */
	if (entree->pin->valeur != -1)
	{
		/* On propage le signal de la sortie vers toutes les entrees auquelles elle est 
		reliee. Si le retour de la foction est égale à 1. */
		if (t_pin_sortie_propager_signal(entree->pin) == 1)
		{
			/* On retourne la valeur 1. */
			return 1;
		}
	}

	/* Sinon */
	else
	{
		/* On retourne la valeur 0. */
		return 0;
	}
}

int t_entree_get_valeur(t_entree* entree)
{
	/* On retourne la valeur de la pin sortie de l'entree. */
	return entree->pin->valeur;
}
