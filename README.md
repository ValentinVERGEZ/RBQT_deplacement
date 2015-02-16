RBQT_deplacement
================

Stack ROS de gestion du déplacement robotino pour l'équipe RBQT dans le cadre de la Robocup

rbqt_pathfinder
---------------

### Présentation

Package de recherche de chemin, fourni deux nodes :
* *server* : 
Recherche et publie un chemin via l'algorithme AStar. 
La map est codée en dur actuellement.
* *server_static* : 
Un générateur de chemin statique. Les chemins sont écrits en dur, il n'y a pas de recherche effectuée.

### Visualiser les résultats

Pour visualiser une Map ainsi qu'un Path, on peut utiliser l'outils rviz.
Dans RVIZ, ajouter un Path et lire le topic "path", ajouter une Map et lire le topic "grid".
Pour publier une Map fictive, éxecuter le script fakeGrid.sh
Pour générer un chemin, lancer le pathfinder (rosruns rbqt_pathfinder server) et effectuer une requête avec le script pathReq.sh.
Le chemin devrait s'afficher en vert sur la map.

execute_path
------------

Package de suivi de chemin
