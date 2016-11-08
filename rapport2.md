Rapport TP2 Nachos : Multithreading
===================================

Clément Renazeau & Thomas Loubiou

Bilan
-----

Dans cette deuxième partie de l’implémentation nachos, il nous est demandé d’ajouter la possibilité d’avoir plusieurs `threads` au niveau des programmes utilisateurs. Pour se faire :

-   Nous avons créé de nouveaux appels système necessaire à l'utilisation d'un `thread`,
-   Nous nous sommes ensuite portés vers la gestion de plusieurs `threads` en même temps :
    -	Utilisation de sémaphore pour mettre le code sensible en section critique,
    -   Nous avons implémenté l’allocation de la pile pour les nouveaux `threads` de manière simpliste,
    -   Pour finalement aboutir à une gestion permettant la création et la destructions successive de plusieurs `thread`.
-   Mise en pause du `thread` principal lorsqu’il termine avant les autres `threads`,
-   La terminaison automatique d’un `thread` sans appel explicite à `ThreadExit`.

Dans un premier temps, nous avons débuté l'implémentation permettant de gérer un seul `thread`, en créant les appels systèmes comme demandé dans la feuille de TP. La première étape a consisté à mettre en place l'interface des nouveaux appels systèmes, comme nous l'avions fait dans la première partie du projet. Nous avons ensuite implémenté ces fonctions dans un fichier `userthread`. Pour la fonction `StartUserThread` nous avons décidé de créer une structure pour pouvoir contenir les différents paramètres nécessaire à l'appel de `Start`.

Pour la gestion de plusieurs `threads`, nous avons dû mettre en place des sémaphores, dans le but de protéger le code critique de `SynchPutChar` et `SynchGetChar`, qui ne sont pas nécessaire pour la version chaîne de caractère (car ces fonctions utilisent déjà le code de `SynchPutChar` et `SynchGetChar`).

Pour permettre une utilisation de plusieurs `threads` nous avons mis un système simple de comptage en place dans `addrspace`.
 

Points délicats
---------------

Limitations
-----------

Tests
-----
