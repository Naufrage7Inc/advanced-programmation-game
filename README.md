# Projet programmation avancée

## Présentation du jeu
Vous incarnez un personnage célèbre personnage du nom de Sacha. Grâce à de la magie rudimentaire car extrêmement ancienne, vous pouvez capturer des petits Pokémons !
  
  
## Organisation du projet
  
### Avancement
Ce qui est possible :
 - Création de la carte et affichage ( basique )
 - Création du personnage, affichage et déplacement ( basique )
 - Création d'une map en fonction d'un fichier 

Ce qui sera bientôt possible :
 - Gestion des animations du personnage ( effet de marche )
 - Création, affichage et gestion des Pokémons
 - Création du menu principal
  
  
### Module Engine
Le module Engine apporte plusieurs fonctions facilitant la gestion d'erreurs, l'utilisation de la SDL, ... Un ensemble de fonctions bien pratique !
  
  
### Module Character
Le module Character permet la manipulation directe d'un personnage : création, déplacement, ... 

  -> enum Direction { UP , DOWN , LEFT , RIGHT }  
    Permet de définir un ensemble de direction: Haut, Bas, Gauche et Droite.
  
  -> struct Character { SDL_Surface* , SDL_Rect , Coord , Direction }  
    Permet de définir une structure Character qui contient une surface (image du personnage), un rectangle (rectangle qui découpe une partie de l'image du personnage), une coordonnée (coordonnée qui détermine la position du personnage sur la carte) et une direction (direction du personnage).

  - Character* CharacterCreate( const char* imagePath, const Coord position )  
    Retourne un personnage en utilisant l'image imagePath à la position position.
        
  - void CharacterDraw( const Character* character, SDL_Surface* surface )  
    Permet de dessiner le personnage character sur une surface surface.
        
  - void CharacterMove( Character* character, Direction direction )  
    Permet de déplacer un personnage character vers la direction direction.
    
  - void CharacterFree( Character* character )  
    Permet de libérer la mémoire utilisée par le personnage character.
  
### Module Map
Le module Map permet la manipulation directe d'une carte : création, affichage, ...
  
  
### Module Tile
Le module Tile permet la manipulation directe d'un bloc composant la carte : création et identification du bloc ( traversable ou non )
  
  
### Les petites structures
Pour mener à bien ce projet, nous avons intégré quelques structures de base comme Coord et Size par exemple.
