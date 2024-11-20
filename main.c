#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Element Element;
struct Element{
  short int valeur;
  Element *e_droit;
  Element *e_gauche;
};


Element *initialize(int valeur){
  Element *element = malloc(sizeof(Element));
  element->valeur = valeur;
  element->e_droit = NULL;
  element->e_gauche = NULL;

  return element;
}


Element *insert(Element *root, int valeur){ // complexity : o(log n)
  if(root == NULL){
    root = initialize(valeur);
  }else if(valeur <= root->valeur){
    root->e_gauche = insert(root->e_gauche, valeur);
  }else{
    root->e_droit = insert(root->e_droit, valeur);
  }
  return root;
}


bool find(Element *root, int valeur){ //time complexity o(log n)
  if(root == NULL) return false;
  if(root->valeur == valeur) return true;
  else if(valeur <= root->valeur) return find(root->e_gauche, valeur);
  else return find(root->e_droit, valeur);
}


void pre_ordre(Element *root){

    if(root != NULL){
        printf("%d  ", root->valeur);
        pre_ordre(root->e_gauche);
        pre_ordre(root->e_droit);
    }
}

void post_ordre(Element *root){

    if(root != NULL){
        post_ordre(root->e_gauche);
        post_ordre(root->e_droit);
        printf("%d  ", root->valeur);
    }
}

void symetrique(Element *root){

    if(root != NULL){
        symetrique(root->e_gauche);
        printf("%d  ", root->valeur);
        symetrique(root->e_droit);
    }

}

Element *minimum(Element *root){
    if(root == NULL){
        return NULL;
    }
    else if(root->e_gauche != NULL){
        return minimum(root->e_gauche);
    }
    return root;
}

Element *supprimer(Element *root, int valeur){

    if(root == NULL) return NULL; // si l'arbre est vide retourne NULL

    if (valeur > root->valeur){ //si la valeur a supprimer est plus grande que la valeur de la racine

        root->e_droit = supprimer(root->e_droit, valeur);// on recherche le noeud a supprimer dans le sous arbre droit
    }

    else if(valeur < root->valeur){//si la valeur a supprimer est plus petite que la valeur de la racine

        root->e_gauche = supprimer(root->e_gauche, valeur);//on recherche le noeud dans le sous arbre gauche
    }

    else{//sinon, on a trouvé le noeud a supprimer

        if(root->e_droit == NULL && root->e_gauche == NULL){//Le noeud est une feuille (n'a pas de fils)
            free(root);// supprimer
            return NULL;//retourne null

        }else if(root->e_droit == NULL || root->e_gauche == NULL){//le noeud a un seul fils (soit gauche soit droit)
            Element *temp;
            if(root->e_gauche == NULL){//si le fils gauche est null
                temp = root->e_droit;//on utilise le fils droit
            }
            else{
                temp = root->e_gauche;//sinon on utilise le fils gauche
            }
            free(root);//supprimer le noeud
            return temp;//retourne le fils non null pour le rattacher au parent ( --- root = temp --- )
        }
        else{// le noeud a deux fils
            Element *temp = minimum(root->e_droit);//on trouve le successeur -le plus petit element du sous arbre droit
            root->valeur = temp->valeur;//on remplace la valeur du noeud par la valeur du successeur
            root->e_droit = supprimer(root->e_droit, temp->valeur);//on supprimer le successeur dans le sous arbre droit
        }
    }
    return root;
}

int hauteur(Element *root) {
    if (root == NULL) {
        return -1; // pour compter les arrets, return 0 pour compter les noeuds
    }

    int hauteur_gauche = hauteur(root->e_gauche); //calculer la hauteur du sous arbre gauche
    int hauteur_droite = hauteur(root->e_droit); //calculer la hauteur du sous arbre droit

    // Retourne la hauteur maximale entre les deux sous-arbres + 1 pour le noeud actuel
    return (hauteur_gauche > hauteur_droite ? hauteur_gauche : hauteur_droite) +1;
}

int nombre_noeuds(Element *root){

    if(root == NULL) return 0;

   return 1+nombre_noeuds(root->e_gauche) + nombre_noeuds(root->e_droit);
}

void detruit(Element *root){

    if(root == NULL) return ;

    detruit(root->e_gauche);
    detruit(root->e_droit);

    free(root);
}

int main() {
    Element *root = NULL;
    root = insert(root, 15);
    insert(root, 10);
    insert(root, 25);
    insert(root, 18);
    insert(root, 30);
    insert(root, 27);
    insert(root, 40);
    insert(root, 8);
    insert(root, 12);
    insert(root, 13);



    int nb;
    printf("Entrer un nombre :\n");
    scanf("%d", &nb);
    if (find(root, nb) == true) {
        printf("Trouve !!!\n");
    } else {
        printf("Non trouve !!!\n");
    }

    printf("\nI- Affichage en pre-ordre :\n\t");
    pre_ordre(root);

    printf("\n\nII- Affichage en Post_ordre :\n\t");
    post_ordre(root);

    printf("\n\nIII- Affichage Parcours symetrique :\n\t");
    symetrique(root);

    printf("\n\nIV- Suppression de 11 (n'a pas de fils = feuille):\n");
    supprimer(root, 11);
    printf("\t- Affichage en pre-ordre apres suppression de 11 : \n\t\t");
    pre_ordre(root);


    printf("\n\nV- Suppression de 17 (qui a un seul fils):\n");
    supprimer(root,17);
    printf("\t- Affichage en pre-ordre apres suppression de 17 : \n\t\t");
    pre_ordre(root);

    printf("\n\nVI- Suppression de 20 (qui a deux fils) : \n");
    supprimer(root, 20); // Mettez à jour root après la suppression.
    printf("\t- Affichage en pre-ordre apres suppression de 20 : \n\t\t");
    pre_ordre(root);


    printf("\n\nVII- La hauteur de l'arbre est : %d", hauteur(root));
    printf("\n\t-Si on supprime 13, la hauteur devient : 2");
    printf("\n\t\t- Suppression de 13 :");
    supprimer(root,13);
    printf("\n\t\tAffichage en pre-ordre de l'arbre :\n\t\t\t");
    pre_ordre(root);
    printf("\n\t\tLa hauteur de l'arbre est :%d", hauteur(root));

    printf("\n\nVIII- Le nombre de noeuds dans l'abre est : %d\n\n", nombre_noeuds(root));



    return 0;
}

