# Voyageur_De_Commerce
2
Introduction

Certains problèmes de rangement ou de prévision de trajet sont trop complexes pour être résolus de manière exhaustive. On peut se contenter alors de solutions quasi-optimales. Pour rechercher de telles solutions, on fait appel à des algorithmes méta-heuristiques inspirés de la Nature. En effet il arrive que la somme d’"intelligences" individuelles sous forme d’une "intelligence" collective soit plus performante que le plus puissant des super-ordinateurs.

Problématique

Problème du voyageur de commerce c’est un exemple connu de problème difficile. Son nom vient de la situation fictive d’un représentant de commerce qui devrait faire une tournée en passant par un certain nombre de villes. Cependant à l’échelle d’un pays, le coût en argent et en temps d’un tel voyage peut devenir prohibitif si l’on ne prévoit pas un trajet optimal à l’avance.
En langage plus mathématique, le problème consiste à trouver un chemin ou un cycle hamiltonien de poids minimum étant donné un graphe où les sommets sont les villes et les arêtes les routes les joignant. Ce problème fait partie d’une famille de problèmes trop complexes pour qu’une solution soit recherchée de façon systématique parmi toutes les solutions possibles.

Algorithmes génétiques

Les algorithmes génétiques s’inspirent de la théorie de l’évolution des espèces. Comme dans la vie, les espèces peuvent se reproduire pour créer de nouveaux individus, et leur ADN peut subir des mutations au cours de leur vie. De plus, à l’instar de ce qu’on observe dans la nature, plus un individu est “fort”, plus il a de chance de se reproduire.
Un algorithme génétique est constitué de 5 grandes étapes que nous détaillerons par la suite lorsque nous résolverons notre problème du voyageur de commerce : • Création d'une population initiale • Evaluation de la "fitness" (qualité) des individus • Création de nouveaux individus • Ajout des nouveaux individus dans la population • Retour à la seconde étape Le but de l’algorithme génétique est de faire évoluer notre population initiale vers une population contenant de meilleurs individus.
