#!/bin/bash

## Script permettant d'appeler un service generatePath, générant un chemin sur la map de la Robocup LLSF 2014
# ATTENTION - l'id doit changer entre deux requêtes, une rêqûete de même id que la précédente sera ignorée

rosservice call /generatePath "id: 0
Arrivee:
  position:
    x: 2.0
    y: 3.0
    z: 0.0
  orientation:
    x: 0.0
    y: 0.0
    z: 0.0
    w: 0.0
Depart:
  position:
    x: 0.0
    y: 0.0
    z: 0.0
  orientation:
    x: 0.0
    y: 0.0
    z: 0.0
    w: 0.0
utilisePositionOdometry: false"