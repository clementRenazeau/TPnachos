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



Points délicats
---------------

L'implémentation de l'appel système `ForkExec` nous a demandé un peu plus de réflexion que le reste: 

-   Après avoir créé l'espace d'adressage du processus à créer (`do_ForkExec` dans le fichier `userthread.cc`), il est nécessaire de démarrer son thread principal grâce à la fonction `StartForkExec`.
-   La fonction `StartForkExec` est chargée d'initialiser les registres du processus (notamment les registres PCReg et NextPCReg), et de lancer le processus.

Limitations
-----------

Les bonus n'ont pas été traités.

Il faut modifier à la main, avant la compilation, le nombre de page physiques (`NumPhysPages` dans `machine.h`) et l'espace réservé aux piles de chaque processus (`UserStacksAreaSize` dans `addrspace.h`)

Tests
-----
