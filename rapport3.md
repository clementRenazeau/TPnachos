Rapport TP3 Nachos : Pagination
===============================


Thomas Loubiou, Clément Renazeau, Ruslan Pichuzhkin


Bilan
-----
La dernière partie du projet Nachos consiste en la mise en place d'un système de pagination pour ensuite introduire des processus pouvant accueillir un nombre arbitraire de threads. Pour atteindre ces objectifs nous avons :
-   travaillé sur la copie d'une page octet par octet,
-   ajouté une classe `PageProvider` qui va se charger de gérer la mémoire et l'allocation des pages,
-   mis en place un nouvel appel système pour pouvoir garder plusieurs programme en mémoire,
-   des tests 

Points délicats
---------------

Limitations
-----------

Tests
-----
