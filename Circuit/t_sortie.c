#define _CRT_SECURE_NO_WARNINGS
#include "t_sortie.h"

t_sortie* t_sortie_init(int num)
{
	/* On déclare un pointeur menant vers un type t_sortie et on alloue de l'espace mémoire pour ce dernier. */
	t_sortie* nouv_sortie = (t_sortie*)malloc(sizeof(t_sortie));

	/* Si le retour de la fonction malloc est égale à NULL. */
	if (nouv_sortie == NULL)
	{
		/* On quitte le programme. */
		EXIT_FAILURE;
	}

	/* On alloue de l'espace mémoire pour le nom de nouvelle_sortie. */
	nouv_sortie->nom = (char*)malloc(sizeof(NOM_SORTIE_TAILLE_MAX + 1));

	/* Si le retour de la fonction malloc est égale à NULL. */
	if (nouv_sortie == NULL)
	{
		/* On libère l'espace mémoire allouée à nouvelle_entree. */
		free(nouv_sortie);

		/* On quitte le programme. */
		EXIT_FAILURE;
	}
	
	/* On assigne l'identificateur à la sortie. */
	nouv_sortie->id = num;
	
	/* On crée le nom de la porte. */
	sprintf(nouv_sortie->nom, "S%d", num);
	
	/* On initialise la pin entree de la sortie. */
	nouv_sortie->pin = t_pin_entree_init();

	/* On retourne nouv_sortie. */
	return nouv_sortie;
}

void t_sortie_destroy(t_sortie* sortie)
{
	/* On libère l'espace mémoire occupé la pin entrée de la sortie. */
	t_pin_entree_destroy(sortie->pin);

	/* On libère l'espace mémoire occupé par le nom de la sortie. */
	free(sortie->nom);

	/* On libère l'espace mémoire occupé par la sortie. */
	free(sortie);
}

t_pin_entree* t_sortie_get_pin(t_sortie* sortie)
{
	/* On retourne le pointeur vers la pin entrée de la sortie. */
	return sortie->pin;
}

int t_sortie_relier(t_sortie* dest, const t_pin_sortie* source)
{
	/* Si la pin de destination est reliée. */
	if (t_pin_entree_est_reliee(dest->pin))
	{
		/* On réinitialise la pin de destination. */
		t_pin_entree_reset(dest->pin);
	}
	
	/* On relie la pin source à la pin destination. */
	t_pin_entree_relier(dest->pin, source);
	
	/* Si la pin destination est reliée. */
	if (t_pin_entree_est_reliee(dest->pin)
	{
		/* On retourne 1. */
		return 1;
	}
	    
	/* Sinon */
	else
	{
		/* On retourne 0. */
		return 0;
	}
}

int t_sortie_est_reliee(t_sortie* sortie)
{
	/* On retourne la valeur de la fonction t_pin_entree_est_reliee avec la 
	pin sortie en paramètre*/
	return t_pin_entree_est_reliee(sortie->pin);
}

void t_sortie_reset(t_sortie* sortie)
{
	/* On réinitialise la pin sortie. */
	t_pin_entree_reset(sortie->pin);
}

int t_sortie_get_valeur(t_sortie* sortie)
{
	/* On retourne la valeur de la pin sortie. */
	return sortie->pin->valeur;
}
