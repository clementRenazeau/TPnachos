Rapport TP2 Nachos : Multithreading
===================================

Clément Renazeau & Thomas Loubiou

Bilan
-----

Dans cette deuxième partie de l’implémentation nachos, il nous est demandé d’ajouter la possibilité d’avoir plusieurs « threads » au niveau des programmes utilisateurs. Pour se faire :

-   Nous avons créé de nouveaux appels système,
-   Nous avons implémenté l’allocation de la pile pour le nouveau 'thread',
-   Nous nous sommes ensuite portés vers la gestion de plusieurs 'threads' en même temps :
    -   Dans un premier temps une utilisation simpliste de la mémoire,
    -   Pour finalement aboutir à une gestion permettant la création et la destructions successive de plusieurs « thread ».
-   Mise en pause du 'thread' principal lorsqu’il termine avant les autres « threads »
-   La terminaison automatique d’un 'thread' sans appel explicite à `ThreadExit`.

Points délicats
---------------

Limitations
-----------

Tests
-----
