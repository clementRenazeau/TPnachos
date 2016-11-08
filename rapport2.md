Rapport TP2 Nachos : Multithreading
===================================

Clément Renazeau & Thomas Loubiou

Bilan
-----

Dans cette deuxième partie de l'implémentation nachos, il nous est demandé d’ajouter la possibilité d’avoir plusieurs `threads` au niveau des programmes utilisateurs. Pour se faire :

-   Nous avons créé de nouveaux appels système nécessaire à l'utilisation d'un `thread`,
-   Nous nous sommes ensuite portés vers la gestion de plusieurs `threads` en même temps:
    -	Utilisation de sémaphore pour mettre le code sensible en section critique,
    -   Nous avons implémenté l'allocation de la pile pour les nouveaux `threads` de manière simpliste,
    -   Pour finalement aboutir à une gestion permettant la création et la destructions successive de plusieurs `thread`.
-   Mise en pause du `thread` principal lorsqu'il termine avant les autres `threads`,
-   La terminaison automatique d’un `thread` sans appel explicite à `ThreadExit`.

Dans un premier temps, nous avons débuté l'implémentation permettant de gérer un seul `thread`, en créant les appels systèmes comme demandé dans la feuille de TP.
La première étape a consisté à mettre en place l'interface des nouveaux appels systèmes, comme nous l'avions fait dans la première partie du projet.
Nous avons ensuite implémenté ces fonctions dans un fichier `userthread`.
Pour la fonction `StartUserThread` nous avons décidé de créer une structure pour pouvoir contenir les différents paramètres nécessaire à l'appel de `Start`.

Pour la gestion de plusieurs `threads`, nous avons dû mettre en place des sémaphores, dans le but de protéger le code critique de `SynchPutChar` et `SynchGetChar`, qui ne sont pas nécessaire pour la version chaîne de caractère (car ces fonctions utilisent déjà le code de `SynchPutChar` et `SynchGetChar`).

Pour permettre une utilisation de plusieurs `threads` nous avons mis un système simple de comptage en place dans `addrspace`.


Points délicats
---------------

Plusieurs points on été délicats au cours de ce TP:

1.  Attendre tous les 'threads' à la fin du main.
Cela est réalisé avec l'aide d'une sémaphore: le dernier thread qui quitte met 1 jeton dans une sémaphore initialisée à 0.
Si, quand le main quitte, il reste des threads en cours d'exécution, alors il fait un P sur cette sémaphore.
Nous avons pris soin à l'implémentation, afin que les appels concurrents ne posent pas de soucis.
Par exemple si un thread quitte entre le moment ou le thread principal vérifie s'il reste des threads et le moment où il attend les autres threads, cela ne pose pas de problème.
Les fonctions nécessaire à ce mécanisme ont été écrites dans les fichiers `addrspace.*`.
2.  L'allocation/désallocation de la pile grâce à un bitmap.
Cela a été en grande partie écrit dans les fichiers `addrspace.*`.
Dans le détail, les fonctions introduites retournent une adresse, il a donc été nécessaire de trouver une formule pour convertir ces adresses en indice de `BitMap` et vice-versa.
3.  Le `ThreadExit` automatique, qui passe l'adresse de l'appel système `ThreadExit` à la fonction `ThreadCreate` grâce à une macro dans le fichier `syscall.h`.
Cette adresse est ensuite mise dans le registre 31 lors de l'initialisation de la pile du thread, afin qu'elle soit appelée automatiquement à la fin de la fonction.

Limitations
-----------

Nous n'avons pas eu le temps de passer les sémaphores dans l'espace utilisateur, néanmoins nous avons eu le temps de réfléchir à une implémentation de cette fonctionnalité:

-   L'utilisateur aurait accès 3 appels systèmes pour les sémaphores:
    -   1 pour la création qui retourne une sémaphore de type `sem_t`,
    -   1 pour V, qui prend en paramètre 1 `sem_t` et effectue un V dessus,
    -   1 pour P, similaire au V.
-   L'appel système dédié à la création allouerai une nouvelle sémaphore dans l'espace noyau (se pose la question de la sécurité, doit on limiter le nombre de sémaphores allouables par processus ?) et retournerai son adresse à l'utilisateur, masqué derrière le type `sem_t`.
-   Les appels V et P peuvent alors utiliser l'adresse passée en paramètre.
-   Question sécurité, cette implémentation n'est pas du tout sécurisée étant donné que l'on passe directement une adresse au noyau.
Si l'utilisateur passe une adresse erronée, le noyau peut tenter des accès mémoires non prévus, et le comportement est indéterminé.
Pour une version plus sécurisée, il vaut mieux utiliser un mécanisme de descripteur (un entier que l'on peut associer à une adresse dans le noyau).

Il faut également noter que l'utilisateur est limité dans le nombre de threads qu'il peut créer.
En effet l'espace réservé pour les piles d'exécution est défini dans `userprog/addrspace.h` par la constante `UserStacksAreaSize`, et doit donc être modifié à la compilation.

Tests
-----
