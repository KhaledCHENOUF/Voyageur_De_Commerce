                          /* population.c : la population d'anticorps */
#include <stdio.h>
#include <stdlib.h>       /* Pour qsort */
#include <unistd.h>       /* Pour sleep */

#include "params.h"
#include "anticorps.h"
#include "population.h"

/**********************************************************************/
/********* Une Population *********************************************/
/**********************************************************************/
/*
typedef struct { Ac* *individus;     // Tableau alloue dynamiquement d'Ac*
                 Ac* *clones;        // Pointeur vers la zone des clones
                 int nbIndividus;
                 int nbClones;
               }                             Population;
*/

/* Generation d'une Population */
void generePopulation(Population *population,
                      int nbIndividus,int nbClones)
{
 int i=0;
 int nbIndividus_Plus_nbClones; /* Par la suite, aura pour valeur:
                                   population->nbIndividus
                                             +
                                   population->nbClones
                                */
 if (nbIndividus<=0)
 {
  printf("**** Warning ! **** : nbIndividus <= 0 (generePopulation)\n");
  nbIndividus=0;
  exit(EXIT_FAILURE); /* Travailler avec une population vide ...? bof ! */
 }

 if (nbClones<=0)
 {
  printf("**** Warning ! **** : nbClones <= 0 (generePopulation)\n");
  nbClones=0;
 }

 if (nbClones>nbIndividus)
 {
  printf("**** Warning ! **** : nbClones > nbIndividus (generePopulation)\n");
  nbClones=nbIndividus;
 }

 population->nbIndividus=nbIndividus;
 population->nbClones=nbClones;

 nbIndividus_Plus_nbClones=population->nbIndividus+population->nbClones;

 if (nbIndividus_Plus_nbClones==0)
 {
   population->individus=NULL;
   population->clones=NULL;
 }
 else
 {
  /* Allocation pour les individus et pour les clones d'un seul coup */
  population->individus=(Ac**)malloc(nbIndividus_Plus_nbClones*sizeof(Ac*));
  if (population->individus==NULL) { printf("Erreur::generePopulation, "
                                            "probleme sur malloc Ac*\n");
                                     exit(EXIT_FAILURE);
  }
  /* Et on positionne le pointeur population->clones ou il faut */
  population->clones=population->individus+population->nbIndividus;
 }

 for(i=0;i<population->nbIndividus;i++)
 {
  Ac *ac = (Ac*)malloc(sizeof(Ac));
  if (ac==NULL) { printf("Erreur::generePopulation,"
                         "probleme sur malloc Ac-1\n");
                  exit(EXIT_FAILURE);
  }
  population->individus[i]=ac;
 }

 for(i=0;i<population->nbIndividus;i++)
 {
  genereAc(population->individus[i]);
 }

 for(i=0;i<population->nbClones;i++)
 {
  Ac *ac = (Ac*)malloc(sizeof(Ac));
  if (ac==NULL) { printf("Erreur::generePopulation,"
                         "probleme sur malloc Ac-2\n");
                  exit(EXIT_FAILURE);
  }
  population->clones[i]=ac;
 }

 /* Pas utile... sauf si la suite est mal utilisee */
 for(i=0;i<population->nbClones;i++)
 {
  genereAc(population->clones[i]);
 }
}

/* Destruction d'une population */
void supprimePopulation(Population *population)
{
 int i=0;

 if (population->individus) 
 {
  for(i=0;i<population->nbIndividus;i++)
  {
   free(population->individus[i]);
  }
 }

 if (population->clones) 
 {
  for(i=0;i<population->nbClones;i++)
  {
   free(population->clones[i]);
  }
 }

 if (population->individus) free(population->individus);
}

/*-------------*/
/* Pour qsort,                                                */
/* comparaison du cout de deux Anti-Corps (via les pointeurs) */
/* Avec qsort, tri avec un cout CROISSANT                     */
static int compareAcPtr(const void *ac1,const void *ac2)
{
 Ac **ac1P=(Ac**)ac1;
 Ac **ac2P=(Ac**)ac2;

 return compareAc(*ac1P,*ac2P);
}
/*---*/
/* Pour qsort,                                                */
/* comparaison du cout de deux Anti-Corps (via les pointeurs) */
/* Avec qsort, tri avec un cout DECROISSANT                   */
static int compareInvAcPtr(const void *ac1,const void *ac2)
{
 return - compareAcPtr(ac1,ac2);
}

/*-------------*/
/* Tri d'une Population et calcul du meilleur avec            */
/* un COUT DECROISSANT =>                                     */
/* les moins bons sont a gauche, les meilleurs a droite       */
static void triSousPopulation(Population *population,
                              int indice, int nbIndividusSousPopulation)
{
 if (nbIndividusSousPopulation>0)
 {
  qsort(population->individus+indice,nbIndividusSousPopulation,sizeof(Ac*),
        compareInvAcPtr);
 }
}
/*---*/
void triPopulation(Population *population)
{
 triSousPopulation(population,0,population->nbIndividus);
}

/*** Il faut un tri avant ***/
/* Recuperation du meilleur individu */
Ac  meilleurIndividu(Population *population)
{
 return *(population->individus[population->nbIndividus-1]);
}

/*** Il faut un tri avant (les meilleurs doivent etre a droite).     ***/
void clonageMeilleurs(Population *population)
{
 int i = 0;
 int nbClones=population->nbClones;

 for(i=0;i<nbClones;i++)
 {
  int indiceAc;
  int indiceClone;

  indiceAc=population->nbIndividus-nbClones+i;      /*  meilleur  */
  indiceClone=i;                                    /*   clone    */

  cloneAc(population->individus[indiceAc],
          population->clones[indiceClone]);
 }
}

/*** Il faut un clonage avant ....                                   ***/
void mutationClones(Population *population)
{
 /* Plus un clone est a droite, meilleur il est.                   */
 /* On peut ainsi faire varier le nombre de mutations a effectuer. */
 /* Dans un premier temps, le nombre de mutations peut etre fixe.  */

 (void)population;

 /* A completer ... */
    for(int i=0;i<population->nbClones;i++) {
        muteAc(population->clones[i],1);
    }
}

/*** Les meilleurs et les clones sont comparares                     ***/
/*** Chaque couple (meilleur,clone) est evalue...                    ***/
/*** Et on garde le meilleur des deux                                ***/
void selectionMeilleursEtClonesMutes(Population *population)
{
 
 /* Les declarations de variables a mettre ici ! */
 int nbSP,indiceSP;
 Ac *temp;

 (void)population;
    
    nbSP=population->nbClones*2;
    indiceSP=population->nbIndividus-population->nbClones;
    //Tri sous-population
    triSousPopulation(population,indiceSP,nbSP);//les meilleures solutions seront plus à droite
    //mettre les meilleures solution dans indivudus
     int j=0;
    for (int i=indiceSP;i<population->nbIndividus;i++){
    if ( population->individus[i]->cout >  population->clones[j]->cout){
    temp = population->individus[i];        
    population->individus[i] = population->clones[j];
    population->clones[j] = temp;
    j++;
    }  
  }
}

/*** Les moins bons doivent etre a gauche (apres un tri par exemple) ***/
void remplacementMoinsBons(Population *population, int nbNouveaux)
{
 
 /* Les declarations de variables a mettre ici ! */

 (void)population; (void)nbNouveaux;

 /* A completer ... */
    for (int i=0;i<nbNouveaux;i++) {
    genereAc(population->individus[i]);
    }
}

/*** Les moins bons doivent etre a gauche (apres un tri par exemple) ***/
void mutationMoinsBons(Population *population)
{
 /* Plus un mauvais est a droite, meilleur il est!                 */
 /* On peut ainsi faire varier le nombre de mutations a effectuer. */
 /* Dans un premier temps, le nombre de mutations peut etre fixe.  */

 /* Les declarations de variables a mettre ici ! */
 int nbRestants;   
 (void)population;
   
 /* A completer ... */
nbRestants=population->nbIndividus-population->nbClones;   
 for (int i=0;i<nbRestants;i++) {
    muteAc(population->individus[i],1);    
    }
}

/* Affichage des meilleurs individus de la Population  */
/* Pour afficher toute la population =>  nbIndividus=0 */
void printIndividusPopulation(Population *population, int nbIndividus)
{
 int i=0, borne=0;

 if (nbIndividus==0) borne=0;
 else borne=population->nbIndividus-nbIndividus;
 borne = (borne<0) ? 0: borne;

 if (borne==0) printf("Affichage de la population entiere\n");
 else printf("Affichage des %d meilleurs individus de la population\n",
              population->nbIndividus-borne);

 for(i=borne;i<population->nbIndividus;i++)
 {
  printAc(population->individus[i]);
 }
}

/* Dessin des meilleurs individus de la Population     */
/* Pour dessiner toute la population =>  nbIndividus=0 */
void dessineIndividusPopulation(FILE* flot,
                                Population *population, int nbIndividus)
{
 int i=0, borne=0;

 if (nbIndividus==0) borne=0;
 else borne=population->nbIndividus-nbIndividus;
 borne = (borne<0) ? 0: borne;

 if (borne==0) printf("Dessin de la population entiere\n");
 else printf("Dessin des %d meilleurs individus de la population\n",
              population->nbIndividus-borne);

 for(i=borne;i<population->nbIndividus;i++)
 {
  dessineAc(flot,population->individus[i]);
  sleep(1);
 }
}
