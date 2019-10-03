# Integration Arduino/LabVIEW par le protocole de communicaiton Modbus

Ce projet présente des exemples d'utilisation du protocole de communication Modbus, plus précisement d'un maître en LabVIEW ainsi que d'un esclave en Arduino tant en Modbus RTU qu'en Modbus TCP.

Les exemples simulent un esclave Modbus réalisé par un Arduino qui mesure une température et qui active/désactive un relais. Un maître LabVIEW récupère cette mesure de température et commande le relais directement par la face avant. Notez que le capteur de température est simulé par un potentiomètre à l'entrée A0 et que le relais est simulé par la DEL de l'Arduino (pin 31).

Les registres (*holding registers*) sont disposés de la façon suivante:

| Adresse | Description | Simulation                   |
|---------|-------------|------------------------------|
| 0       | Température | Entrée analogique A0         |
| 1       | Relais      | Sortie discrète pin 13 (DEL) |

Trois vidéos YouTube supportent l'explication des exemples:

1. https:....

Notez que le document de support du premier vidéo est disponible dans ce projet sous le répertoire */doc*.