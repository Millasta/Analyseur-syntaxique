#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pile.h" // Gestion des piles
#include "tp2_a.h" // Analyseur syntaxique
#include "json_tree.h"

#include <unistd.h>

static char * TableAction[26][12] = {};
static char * TableGoto[26][6] = {};
static char * TableRegle[17][2] = {};

void freeTables() {
    int i,j,k;
    for(i = 0 ; i < 26 ; i++) {
        for(j = 0 ; j < 12 ; j++) {
            if(TableAction[i][j] != NULL)
                free(TableAction[i][j]);
        }

        for(k = 0 ; k < 6 ; k++) {
            if(TableGoto[i][k] != NULL)
                free(TableGoto[i][k]);
        }
    }

    for(i = 0 ; i < 17 ; i++) {
        free(TableRegle[i][0]);
        free(TableRegle[i][1]);
    }
}

void initTableAction(char * table[26][12]) {
    table[0][0] = strdup("d2");
        table[9][0] = strdup("d2");
        table[14][0] = strdup("d2");
        table[24][0] = strdup("d2");

        table[2][1] = strdup("d5");
        table[3][1] = strdup("d7");
        table[4][1] = strdup("r3");
        table[5][1] = strdup("r1");
        table[7][1] = strdup("r2");
        table[10][1] = strdup("r4");
        table[11][1] = strdup("r12");
        table[12][1] = strdup("r13");
        table[13][1] = strdup("r5");
        table[15][1] = strdup("r10");
        table[16][1] = strdup("r11");
        table[17][1] = strdup("r14");
        table[18][1] = strdup("r15");
        table[19][1] = strdup("r16");
        table[22][1] = strdup("r6");
        table[23][1] = strdup("r7");

        table[9][2] = strdup("d4");
        table[14][2] = strdup("d4");
        table[24][2] = strdup("d4");

        table[5][3] = strdup("r1");
        table[7][3] = strdup("r2");
        table[11][3] = strdup("r12");
        table[12][3] = strdup("r13");
        table[14][3] = strdup("d22");
        table[15][3] = strdup("r10");
        table[16][3] = strdup("r11");
        table[17][3] = strdup("r14");
        table[18][3] = strdup("r15");
        table[19][3] = strdup("r16");
        table[20][3] = strdup("d23");
        table[21][3] = strdup("r8");
        table[22][3] = strdup("r5");
        table[23][3] = strdup("r7");
        table[25][3] = strdup("r9");

        table[4][4] = strdup("d8");
        table[5][4] = strdup("r1");
        table[7][4] = strdup("r2");
        table[11][4] = strdup("r12");
        table[12][4] = strdup("r13");
        table[13][4] = strdup("r5");
        table[15][4] = strdup("r10");
        table[16][4] = strdup("r11");
        table[17][4] = strdup("r14");
        table[18][4] = strdup("r15");
        table[19][4] = strdup("r16");
        table[21][4] = strdup("d24");
        table[22][4] = strdup("r6");
        table[23][4] = strdup("r7");

        table[6][5] = strdup("d9");

        table[2][6] = strdup("d6");
        table[8][6] = strdup("d6");
        table[9][6] = strdup("d15");
        table[14][6] = strdup("d15");
        table[24][6] = strdup("d15");

        table[9][7] = strdup("d16");
        table[14][7] = strdup("d16");
        table[24][7] = strdup("d16");

        table[9][8] = strdup("d17");
        table[14][8] = strdup("d17");
        table[24][8] = strdup("d17");

        table[9][9] = strdup("d18");
        table[14][9] = strdup("d18");
        table[24][9] = strdup("d18");

        table[9][10] = strdup("d19");
        table[14][10] = strdup("d19");
        table[24][10] = strdup("d19");

        table[1][11] = strdup("acc");
        table[5][11] = strdup("r1");
        table[7][11] = strdup("r2");
}

void initTableGoto(char * table[26][6]) {
    table[0][0] = strdup("1");
    table[9][0] = strdup("11");
    table[14][0] = strdup("11");
    table[24][0] = strdup("11");

    table[2][1] = strdup("3");
    table[8][1] = strdup("10");

    table[2][2] = strdup("4");
    table[8][2] = strdup("4");

    table[9][3] = strdup("12");
    table[14][3] = strdup("12");
    table[24][3] = strdup("12");

    table[14][4] = strdup("20");
    table[24][4] = strdup("25");

    table[9][5] = strdup("13");
    table[14][5] = strdup("21");
    table[24][5] = strdup("21");

}

void initTableRegle(char* TableRegle[17][2]) {
    TableRegle[0][0] = strdup("S");
    TableRegle[0][1] = strdup("O");

    TableRegle[1][0] = strdup("O");
    TableRegle[1][1] = strdup("{}");

    TableRegle[2][0] = strdup("O");
    TableRegle[2][1] = strdup("{M}");

    TableRegle[3][0] = strdup("M");
    TableRegle[3][1] = strdup("P");

    TableRegle[4][0] = strdup("M");
    TableRegle[4][1] = strdup("P,M");

    TableRegle[5][0] = strdup("P");
    TableRegle[5][1] = strdup("s:V");

    TableRegle[6][0] = strdup("A");
    TableRegle[6][1] = strdup("[]");

    TableRegle[7][0] = strdup("A");
    TableRegle[7][1] = strdup("[E]");

    TableRegle[8][0] = strdup("E");
    TableRegle[8][1] = strdup("V");

    TableRegle[9][0] = strdup("E");
    TableRegle[9][1] = strdup("V,E");

    TableRegle[10][0] = strdup("V");
    TableRegle[10][1] = strdup("s");

    TableRegle[11][0] = strdup("V");
    TableRegle[11][1] = strdup("n");

    TableRegle[12][0] = strdup("V");
    TableRegle[12][1] = strdup("O");

    TableRegle[13][0] = strdup("V");
    TableRegle[13][1] = strdup("A");

    TableRegle[14][0] = strdup("V");
    TableRegle[14][1] = strdup("t");

    TableRegle[15][0] = strdup("V");
    TableRegle[15][1] = strdup("f");

    TableRegle[16][0] = strdup("V");
    TableRegle[16][1] = strdup("u");
}

int indexOfChar(const char *str, char c) {
    size_t i;
    for(i = 0 ; i < strlen(str) ; i++) {
        if(str[i] == c) {
            return i;
        }
    }
    return -1;
}

int analyseurLR() {

    TIntPile *pile = NULL;
    TVoidPile *pileJson = NULL;
    TLex * lex_data = NULL;

    pile = initIntPile();
    pileJson = initVoidPile();
    empilerInt(pile, 0);

    initTableAction(TableAction);
    initTableGoto(TableGoto);
    initTableRegle(TableRegle);

    char *JsonSymbTab = " tfu{}[],:snn";
    char *colonneTabAction = "{}[],:sntfu#";
    char *colonneTabGoto = "OMPAEV";
    char *rawData = "{ \" titre_album\":\"Abacab\",\"groupe\":\"Genesis\",\"annee\":1981,\"genre\":\"Rock \" }";
    char *cleanData = removeBlanks(rawData);
    lex_data = initLexData(cleanData);
    free(cleanData);
    printf("Entrée : %s\n", lex_data->data);

    char* action = NULL;
    int fini = 0;
    char lexeme = JsonSymbTab[lex(lex_data)];
    while(!fini) {
        printf("\nPile : %d Lexeme : %c Index: %d", sommetInt(pile), lexeme, indexOfChar(colonneTabAction, lexeme));
        fflush(stdout);
        action = strdup(TableAction[sommetInt(pile)][indexOfChar(colonneTabAction, lexeme)]);
        printf(" Action : %s\n", action);
        if(action == NULL) { //ERREUR
            printf("Erreur\n");
            return -1;
        }
        else if(strcmp(action, "acc") == 0) {
            void *o = depilerVoid(pileJson);
            fini = 1;
            return 0;
        }
        else if(action[0] == 'd') {
            //printf("TableGoto[%d][%d] = ", sommetInt(pile), indexOfChar(colonneTabAction, lexeme));
            //int t = atoi(TableGoto[sommetInt(pile)][indexOfChar(colonneTabAction, lexeme)]);
            int i;
            char *buff = strdup(action);
            for(i = 0 ; i < strlen(action) ; i++)
                buff[i] = action[i+1];
            int deplacement = atoi(buff);

            printf("Deplacement : %d\n", deplacement);
            empilerInt(pile, deplacement);
            lexeme = JsonSymbTab[lex(lex_data)];
        }
        else {
            int i;
            char *buff = strdup(action);
            for(i = 0 ; i < strlen(action) ; i++)
                buff[i] = action[i+1];
            int nRegle = atoi(buff);
            printf("Regle (%d) : %s -> %s\n", nRegle, TableRegle[nRegle][0], TableRegle[nRegle][1]);

            for(i = 0 ; i < strlen(TableRegle[nRegle][1]) ; i++)
                depilerInt(pile);

            empilerInt(pile, atoi(TableGoto[sommetInt(pile)][indexOfChar(colonneTabGoto, TableRegle[nRegle][0][0])]));

            switch(nRegle) {
                case 1: {
                    void *P = CreateJsonObject();
                    empilerVoid(pileJson, P);
                    break;
                }
                case 2:
                    // il n’y a rien à faire car l’objet M est déjà sur la pile
                    break;
                case 3: {
                    void *P = depilerVoid(pileJson);
                    void *object = CreateJsonObject();
                    InsertJsonObject(object, P);
                    empilerVoid(pileJson, object);
                    break;
                }
                case 4: {
                    void *O = depilerVoid(pileJson);
                    void *P = depilerVoid(pileJson);
                    InsertJsonObject(O, P);
                    break;
                }
                case 5: {
                    void *P = CreateJsonPair();
                    void *C = depilerVoid(pileJson);
                    char *s = strdup(lex_data->tableSymboles[lex_data->nbSymboles-1].val.chaine);
                    UpdateJsonPair(P, s, NULL);
                    free(s);
                    empilerVoid(pileJson, P);

                    // Delete s from tableSymboles
                    lex_data->nbSymboles--;
                    free(lex_data->tableSymboles[lex_data->nbSymboles].val.chaine);
                    lex_data->tableSymboles = realloc(lex_data->tableSymboles, sizeof(TSymbole) * lex_data->nbSymboles);
                    if(lex_data->tableSymboles == NULL)
                        printf("Err: realloc\n");
                    break;
                }
                case 10: {
                    JsonPair *P = depilerVoid(pileJson);
                    char *value = strdup(lex_data->tableSymboles[lex_data->nbSymboles-1].val.chaine);
                    char *pairName = strdup(P->string);
                    void *C = CreateJsonValueContainer();
                    enum ValueType type;
                    type = string;
                    UpdateJsonValueContainer(C, type, value);
                    UpdateJsonPair(P, pairName, C);
                    free(value);
                    free(pairName);
                    empilerVoid(P, pileJson);
                }
                default:
                    fini = 1;
                    break;
            }
        }
        free(action);
        //fini = 1;
    }

    deleteIntPile(&pile);
    deleteVoidPile(&pileJson);
    deleteLexData(lex_data);

    /* initialisation
    Pile : Pile d’Entiers
    PileJSon : Pile de void
    Empiler l’état 0 sur la Pile
    /* on recupère un symbole en appelant l’analyseur lexicale
    lexeme = Lex()
    /* boucle générale
    Fini = faux
    TantQue non Fini Faire
        action = TableAction[sommet(Pile)][lexeme]
        Si action==Acceptation Alors
            O = Depiler un objet JSon de la PileJSon /* l’arbre JSON est sur la pile
            Fini = vrai
            Retourner (O)
        Sinon Si action==Déplacement Alors
            Empiler TableGoto[sommet(Pile)][lexeme] sur la Pile
            lexeme = Lex() /* on lit le symbole suivant
        Sinon Si action==ERREUR Alors
            Afficher l’erreur et Sortir
        Sinon /* c’est une réduction, la table donne le numéro de la règle : n
            /* on depile autant d’états que d’éléments
            * en partie droite de la règle
            i = 0,
            Tantque i<taillePartieDroiteRegle[n]
            Depiler un état de la Pile
            i=i+1
            /* on empile le nouvel état qui résume la nouvelle situation
            * X est l’auxiliaire en partie gauche de la règle n
            Empiler TableGoto[sommet(Pile)][X] sur la Pile
            /* la suite de l’algorithme est consacré à la construction
            * de l’arbre JSon en mémoire (si on vérifie la validité de la
            * séquence, on pouvait s’arreter ici */
            /* en fonction de la règle, il faut créer et assembler les structures JSON
            Si n==1 Alors /* règle O -> { }
                Créer un objet JSon vide et l’empiler sur PileJSon
            Sinon Si n==2 Alors /* règle O -> { M }
                /* il n’y a rien à faire car l’objet M est déjà sur la pile
            Sinon Si n==3 Alors /* règle M -> P
                P = dépiler de la PileJSon
                Créer un objet Json, y insérer la paire P, et l’empiler sur PileJSon
            Sinon Si n==4 Alors /* M -> P , M
                O = dépiler de la PileJSon
                P = dépiler de la PileJSon
                Insérer la paire P dans l’objet O et empiler O sur PileJSon
            Sinon Si n==5 Alors /* règle P -> s : V
                Créer une paire P
                C = dépiler le conteneur de Valeur de la PileJSon
                s = dernier symbole lu par l’analyseur lexical (chaîne dans la table des symboles)
                insérer s dans P
                empiler P sur PileJSon
                effacer s de la table des symboles
            /*
            * continuer ainsi pour toutes les règles 6...16
    */

    return 0;
}

int main(int argc, const char argv[]) {

    printf("----------- Analyseur syntaxique -----------\n\n");
    analyseurLR();
    printf("\n");
    return 0;
}
