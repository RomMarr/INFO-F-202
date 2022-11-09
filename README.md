# INFO-F-202
Jeu Sokoban

- [ ] 5 tâches de base
- [ ] 10/12 tâches additionnelles
- [ ] Makefile
- [ ] Rapport


Les tâches de bases :
- [ ] Déplacement personnage
- [ ] Murs infranchissables
- [ ] Eléments (boites) à pousser
- [ ] Cases cibles
- [ ] Moyen de reset le niveau

Les tâches additionnelles :
- [ ] Animation des éléments en cours de déplacement
- [ ] Cases de téléportation
- [ ] Boites de couleur
- [ ] Boîtes légères
- [ ] Compteur de pas
- [ ] Meilleur score de pas
- [ ] Écran d’accueil
- [ ] Niveaux et sélection de niveau
- [ ] Limite de pas
- [ ] Déplacement automatique à la souris
- [ ] Éditeur de niveau
- [ ] Détection d’échec


Idées :
Crée une matrice pour tout ce qui est déplacement puis d’un autre côté faire le graphisme basé sur la matrice 
- Class objet (abstraite):
        - class mur
        - class boite (différents poids) 
        - class cible 
        - class sol
        - class sol vide (dehors)
        - class teleportation
- main :
       -> bouton (ou autre) pour reset le niveau 
- Changement de terrain :
       -> on clique sur un bloc ça passe au type suivant en boucle
       -> limité aux classes descendantes de objet
