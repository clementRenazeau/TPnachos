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

Nous n'avons pas eu le temps de passer les sémaphores dans l'espace utilisateur, néanmoins nous avons eu le temps de réfléchir à une implémentation de cette fonctionnalité:

- L'utilisateur aurait accès 3 appels systèmes pour les sémaphores:
    - 1 pour la création qui retourne une sémaphore de type `sem_t`,
    - 1 pour V, qui prend en paramètre 1 `sem_t` et effectue un V dessus,
    - 1 pour P, similaire au V.
- L'appel système dédié à la création allouerai une nouvelle sémaphore dans l'espace noyau (se pose la question de la sécurité, doit on limiter le nombre de sémaphores allouables par processus ?)
et retournerai son adresse à l'utilisateur, masqué derrière le type `sem_t`.
* Les appels V et P peuvent alors utiliser l'adresse passée en paramètre.
* Question sécurité, cette implémentation n'est pas du tout sécurisée étant donné que l'on passe directement une adresse au noyau.
Si l'utilisateur passe une adresse erronée, le noyau peut tenter des accès mémoires non prévus, et le comportement est indéterminé.
Pour une version plus sécurisée, il vaut mieux utiliser un mécanisme de descripteur (un entier que l'on peut associer à une adresse dans le noyau).

Tests
-----
