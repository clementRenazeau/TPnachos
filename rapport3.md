Rapport TP3 Nachos : Pagination
===============================


Thomas Loubiou, Clément Renazeau, Ruslan Pichuzhkin


Bilan
-----

La dernière partie du projet Nachos consiste en la mise en place d'un système de pagination pour ensuite introduire des processus pouvant accueillir un nombre arbitraire de threads. Pour atteindre ces objectifs nous avons :
-   travaillé sur la copie d'une page octet par octet,
-   ajouté une classe `PageProvider` qui va se charger de gérer la mémoire et l'allocation des pages,
-   mis en place un nouvel appel système pour pouvoir garder plusieurs programme en mémoire,
-   fait quelques tests pour générer un grand nombre de processus et de threads en même temps.

En premier lieu nous avons défini la nouvelle fonction `ReadAtVirtual` qui a pour but de copier octet par octet le contenue d'une page dans une nouvelle page de mémoire. Puis nous avons modifié la création de la table des pages pour qu'elle corresponde aux demandes de la feuille de TP, tout en s'assurant que les tests effectués auparavant restent valables.



Points délicats
---------------

Limitations
-----------
Les bonus n'ont pas été traités. Il faut modifier à la main le nombre de page maximum (A PRECISER LE NOM ET LA LOCALISATION) et la taille maximale attribuée à chaque processus (A PRECISER LE NOM ET LA LOCALISATION)
Tests
-----
