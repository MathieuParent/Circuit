#define _CRT_SECURE_NO_WARNINGS
#include "t_porte.h"

t_porte* t_porte_init(int id, e_types_portes type)
{
	/* On déclare un pointeur menant vers un type t_porte. */
	t_porte* nouv_porte;

	/* On alloue de l'espace mémoire pour une_porte. */
	nouv_porte = (t_porte*)malloc(sizeof(t_porte));

	/* Si le retour de la fonction malloc est égale à NULL. */
	if (nouv_porte == NULL)
	{
		/* On affiche un message d'erreur. */
		printf("ERREUR ALLOCATION MEMOIRE T_PORTE_INIT");
		
		/* On met le système en pause. */
		system("pause");
		
		/* On quitte le programme. */
		exit(EXIT_FAILURE);
	}
	
	/* On alloue de l'espace mémoire pour le nom de nouv_porte. */
	nouv_porte->nom = (char*)malloc(sizeof(NOM_PORTE_TAILLE_MAX + 1));
	
	/* On assigne l'identificateur à la porte. */
	nouv_porte->id = id;
	
	/* On crée le nom de la porte. */
	sprintf(nouv_porte->nom, "P%d", id);
	
	/* On inscrit le type de la porte. */
	nouv_porte->type = type;
	
	/* S'il ne s'agit pas d'une porte NOT. */
	if(type==PORTE_NOT)
	{
		/* On assigne la valeur 1 au nombre d'entrées de la porte. */
		nouv_porte->nb_entrees = 1;
		
		/* On initialise la pin d'entree 0. */
		nouv_porte->entrees[0] = t_pin_entree_init();
	}

	/* Sinon */
	else
	{
		/* On assigne la valeur 2 au nombre d'entrées de la porte. */
		nouv_porte->nb_entrees = 2;
		
		for (int i = 0; i < nouv_porte->nb_entrees; i++)
		{
			/* On initialise la pin d'entree. */
			nouv_porte->entrees[i] = t_pin_entree_init();
		}
	}
	
	/* On initialise la pin sorite. */
	nouv_porte->sortie = t_pin_sortie_init();

	/* On retourne nouv_porte. */
	return nouv_porte;
}

void t_porte_destroy(t_porte* porte)
{
	/* On libère l'espace mémoire allouée à la pin 0. */
	t_pin_entree_destroy(porte->entrees[0]);

	/* S'il ne s'agit pas d'une porte NOT. */
	if (porte->type != 2)
	{
		/* On libère l'espace mémoire allouée à la pin 1. */
		t_pin_entree_destroy(porte->entrees[1]);
	}

	/* On libère l'espace mémoire occupé par la pin sortie de la porte. */
	t_pin_sortie_destroy(porte->d);

	/* On libère l'espace mémoire occupé par le nom de la porte. */
	free(porte->nom);
	
	/* On libère l'espace mémoire occupé par la porte. */
	free(porte);
}

void t_porte_calculer_sorties(t_porte* porte)
{
	/* Soit porte->type */
	switch (porte->type) 
	{
			
	/* S'il s'agit d'un porte ET. */
	case PORTE_ET:
		
		/* On attribue les valeurs des pins entree 0 ET 1 à la pin sortie. */
		t_pin_sortie_set_valeur(porte->sortie,(porte->entrees[0]->valeur) & (porte->entrees[1]->valeur));
		break;
			
	/* S'il s'agit d'un porte OU. */		
	case PORTE_OU:
			
		/* On attribue les valeurs des pins entree 0 OU 1 à la pin sortie. */
		t_pin_sortie_set_valeur(porte->sortie,(porte->entrees[0]->valeur) | (porte->entrees[1]->valeur));
		break;
	
	/* S'il s'agit d'un porte NOT. */
	case PORTE_NOT:
		
		/* Si la valeur de la pin entree 0 est égale à 0. */
		if (porte->entrees[0]->valeur == 0) 
		{
			/* On attribue la valeur 1 à la pin sortie. */
			t_pin_sortie_set_valeur(porte->sortie, 1);
		}
			
		/* Sinon */
		else 
		{
			/* On attribue la valeur 1 à la pin sortie. */
			t_pin_sortie_set_valeur(porte->sortie, 0);
		}
		break;
			
	/* S'il s'agit d'un porte XOR. */
	case PORTE_XOR:
		
		t_pin_sortie_set_valeur(porte->sortie,(porte->entrees[0]->valeur) ^ (porte->entrees[1]->valeur));
		break;
	}
}

int t_porte_relier(t_porte* dest, int num_entree, const t_pin_sortie* source)
{
	
	/* Si l'indice de la pin a reliee est superieur au nombre d'entrees possedees par la
	porte. */
	if (num_entree <= dest->nb_entrees)
	{
		
		/* On relie les pins en utilisant la fonction t_pin_entree_relier. */
		t_pin_entree_relier(dest->entrees[num_entree-1], source);
		
		/* On retourne la valeur 1. */
		
		return 1;
	}

	/* Sinon */
	else
	{
		
		/* On retourne la valeur 0. */
		return 0;
	}
}

int t_porte_est_reliee(t_porte* porte)
{
	int test = 1;		/* Entier servant a memoriser le resultat du test. */
	int entree = 0;		/* Compteur servant a memoriser l'indice de l'entree testee. */

	/* Fait */
	do
	{
		/* Si l'entre testee n'est pas reliee. */
		if (t_pin_entree_est_reliee(porte->entrees[entree]) == 0)
		{
			/* On attribue la valeur 0 a la variable test. */
			test = 0;
		}
		/* On incremente le compteur entree. */
		entree++;
		/* Tant que la variable test est egale a 1 et que la valeur du compteur entree est
		inferieure au nombre d'entrees possedees par la porte. */
	} while (test == 1 && entree < porte->nb_entrees);

	/* Si la sortie de la porte n'est pas reliee. */
	if (t_pin_sortie_est_reliee(porte->sortie) == 0)
	{
		/* On attribue la valeur 0 a la variable test. */
		test = 0;
	}
	/* On retourne la valeur de la variable test. */
	return test;
}

void t_porte_reset(t_porte* porte)
{
	for (int i = 0; i < porte->nb_entrees; i++)
	{
		/* On reinitialise la valeur de la pin entree. */
		t_pin_entree_reset(porte->entrees[i]);
	}
	/* On reinitialise la valeur de la pin sorie. */
	t_pin_sortie_reset(porte->sortie);
}

int t_porte_propager_signal(t_porte* porte)
{
	
	/* Si l'ensemble des pins de la portes sont reliées. */
	if (t_porte_est_reliee(porte))
	{
		
		/* On calcule la valeur de la pin sortie de la porte. */
		t_porte_calculer_sorties(porte);

		/* On propage le signal de la sortie vers toutes les entrees auquelles elle est
		reliee. */
		t_pin_sortie_propager_signal(porte->sortie);
		
		/* On retourne la valeur 1. */
		return 1;
	}
	
	/* Sinon */
	else 
	{
		/* On prévient l'utilisateur que la porte n'est pas reliée. */
		printf("La porte %s n'est pas complétement relié\n", porte->nom);
		
		/* On retourne la valeur 0. */
		return 0;
	}
}

t_pin_sortie* t_porte_get_pin_sortie(t_porte* porte)
{
	/* On retourne le pointeur vers la pin sortie de la porte. */
	return porte->sortie;
}
