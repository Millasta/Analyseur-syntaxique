#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pile.h" // Gestion des piles
#include "tp2_a.h" // Analyseur syntaxique
#include "json_tree.h"

#include <sys/wait.h> // Exec
#include <errno.h>

#include <unistd.h>

#define FILE_LENGTH_LIMIT 100000

static char * TableAction[26][12] = {0};
static char * TableGoto[26][6] = {0};
static char * TableRegle[17][2] = {0};

void freeTables() {
    int i,j,k;
    for (i = 0 ; i < 26 ; i++) {
        for (j = 0 ; j < 12 ; j++) {
            if (TableAction[i][j] != NULL)
                free(TableAction[i][j]);
        }

        for (k = 0 ; k < 6 ; k++) {
            if (TableGoto[i][k] != NULL)
                free(TableGoto[i][k]);
        }
    }

    for (i = 0 ; i < 17 ; i++) {
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

    table[9][2] = strdup("d14");
    table[14][2] = strdup("d14");
    table[24][2] = strdup("d14");

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

void initTableRegle(char * table[17][2]) {
    table[0][0] = strdup("S");
    table[0][1] = strdup("O");

    table[1][0] = strdup("O");
    table[1][1] = strdup("{}");

    table[2][0] = strdup("O");
    table[2][1] = strdup("{M}");

    table[3][0] = strdup("M");
    table[3][1] = strdup("P");

    table[4][0] = strdup("M");
    table[4][1] = strdup("P,M");

    table[5][0] = strdup("P");
    table[5][1] = strdup("s:V");

    table[6][0] = strdup("A");
    table[6][1] = strdup("[]");

    table[7][0] = strdup("A");
    table[7][1] = strdup("[E]");

    table[8][0] = strdup("E");
    table[8][1] = strdup("V");

    table[9][0] = strdup("E");
    table[9][1] = strdup("V,E");

    table[10][0] = strdup("V");
    table[10][1] = strdup("s");

    table[11][0] = strdup("V");
    table[11][1] = strdup("n");

    table[12][0] = strdup("V");
    table[12][1] = strdup("O");

    table[13][0] = strdup("V");
    table[13][1] = strdup("A");

    table[14][0] = strdup("V");
    table[14][1] = strdup("t");

    table[15][0] = strdup("V");
    table[15][1] = strdup("f");

    table[16][0] = strdup("V");
    table[16][1] = strdup("u");
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

JsonObject * analyseurLR(TLex * lex_data) {

    TIntPile *pile = NULL;
    TVoidPile *pileJson = NULL;
	JsonObject *O = NULL;

    pile = initIntPile();
    pileJson = initVoidPile();
    empilerInt(pile, 0);

    initTableAction(TableAction);
    initTableGoto(TableGoto);
    initTableRegle(TableRegle);

    char *JsonSymbTab = " tfu{}[],:snn#";
    char *colonneTabAction = "{}[],:sntfu#";
    char *colonneTabGoto = "OMPAEV";
    char *action = NULL;
	char *messageErreur = NULL;
	char lexeme = JsonSymbTab[lex(lex_data)];
	unsigned int i = 0;
	int exit = 0;
	int valid = 0; 
	int lexCode;

    while (!exit) {
        fflush(stdout);
        
		if (TableAction[sommetInt(pile)][indexOfChar(colonneTabAction, lexeme)] != NULL) {
			action = strdup(TableAction[sommetInt(pile)][indexOfChar(colonneTabAction, lexeme)]);
		}
		else {
			action = NULL;
        }

		if (action == NULL) {
			messageErreur = strdup("Action invalide");
			exit = 1;
		}
		else if (strcmp(action, "acc") == 0) {
            O = (JsonObject*)depilerVoid(pileJson);

			valid = 1;
            exit = 1;
        }
        else if (action[0] == 'd') {
			int deplacement;
            char *buff = strdup(action);

            for (i = 0 ; i < strlen(action) ; i++)
                buff[i] = action[i+1];

            deplacement = atoi(buff);

            empilerInt(pile, deplacement);

			lexCode = lex(lex_data);

			if (lexCode != JSON_LEX_ERROR) {
				lexeme = JsonSymbTab[lexCode];
			}
			else {
				messageErreur = strdup("Erreur lexicale");
				exit = 1;
			}
        }
        else {
			int nRegle;
            char *buff = strdup(action);

            for (i = 0 ; i < strlen(action) ; i++)
                buff[i] = action[i+1];

            nRegle = atoi(buff);

            for (i = 0 ; i < strlen(TableRegle[nRegle][1]) ; i++)
                depilerInt(pile);


            empilerInt(pile, atoi(TableGoto[sommetInt(pile)][indexOfChar(colonneTabGoto, TableRegle[nRegle][0][0])]));
			
            switch(nRegle) {
                case 1: { // S → O
                    void *O = CreateJsonObject();

                    empilerVoid(pileJson, O);
                    break;
                }
                case 2: { // O → {M}
                    // Il n’y a rien à faire car l’objet M est déjà sur la pile
                    break;
				}
                case 3: { // M → P
                    void *O = CreateJsonObject();
                    void *P = depilerVoid(pileJson);

					if (P == NULL) {
						messageErreur = strdup("Erreur syntaxique : pile Json vide");
						exit = 1;
						break;			
					}

                    InsertJsonObject(O, P);
                    empilerVoid(pileJson, O);

                    break;
                }
                case 4: { // M → P, M
                    void *O = depilerVoid(pileJson);
                    void *P = depilerVoid(pileJson);

					if (O == NULL || P == NULL) {
						messageErreur = strdup("Erreur syntaxique : pile Json vide");
						exit = 1;
						break;					
					}

                    InsertJsonObject(O, P);
					empilerVoid(pileJson, O);

                    break;
                }
                case 5: { // P → s : V
                    void *P = CreateJsonPair();
                    void *V = depilerVoid(pileJson);

					if (V == NULL) {
						messageErreur = strdup("Erreur syntaxique : pile Json vide");
						exit = 1;
						break;			
					}

                    char *s = strdup(lex_data->tableSymboles[lex_data->nbSymboles - 1].val.chaine);

                    UpdateJsonPair(P, s, V);
                    empilerVoid(pileJson, P);

					if (lex_data->nbSymboles > 0) {
						free(lex_data->tableSymboles[lex_data->nbSymboles - 1].val.chaine);
						lex_data->nbSymboles--;
					}

                    break;
                }
				case 6: { // A → []
                    void *A = CreateJsonArray();

                    empilerVoid(pileJson, A);

                    break;
                }
				case 7: { // A → [E]
					// Il n’y a rien à faire car l’objet E est déjà sur la pile
                    break;
                }
				case 8: { // E → V
 					void *E = CreateJsonArray();
	                void *V = depilerVoid(pileJson);

					if (V == NULL) {
						messageErreur = strdup("Erreur syntaxique : pile Json vide");
						exit = 1;
						break;			
					}

	                InsertJsonObject(E, V);
					empilerVoid(pileJson, E);

                    break;
                }
				case 9: { // E → V, E
					JsonArray *E = depilerVoid(pileJson);
                    void *V = depilerVoid(pileJson);

					if (E == NULL || V == NULL) {
						messageErreur = strdup("Erreur syntaxique : pile Json vide");
						exit = 1;
						break;			
					}

                    InsertJsonArray(E, V, E->size - 1);
					empilerVoid(pileJson, E);

                    break;
                }
                case 10: { // V → s
					JsonValueContainer *V = CreateJsonValueContainer();
                    JsonValue value;
					ValueType type = string;

                    value.string = strdup(lex_data->tableSymboles[lex_data->nbSymboles - 1].val.chaine);

					UpdateJsonValueContainer(V, type, value);

					empilerVoid(pileJson, V);

					if (lex_data->nbSymboles > 0) {
						free(lex_data->tableSymboles[lex_data->nbSymboles - 1].val.chaine);
						lex_data->nbSymboles--;
					}

                    break;
                }
                case 11: { // V → n
					JsonValueContainer *V = CreateJsonValueContainer();
                    JsonValue value;
					ValueType type;

					if (lex_data->tableSymboles[lex_data->nbSymboles - 1].type == JSON_INT_NUMBER) {
						type = integer;
						value.integer = lex_data->tableSymboles[lex_data->nbSymboles - 1].val.entier;
					}
					else {
						type = real;
						value.real = lex_data->tableSymboles[lex_data->nbSymboles - 1].val.reel;
					}
					
					UpdateJsonValueContainer(V, type, value);
					empilerVoid(pileJson, V);

					if (lex_data->nbSymboles > 0) {
						lex_data->nbSymboles--;
					}

                    break;
                }
				case 12: { // V → O
					JsonValueContainer *V = CreateJsonValueContainer();
                    JsonValue value;
					ValueType type = object;

					value.object = depilerVoid(pileJson);

					if (value.object == NULL) {
						messageErreur = strdup("Erreur syntaxique : pile Json vide");
						exit = 1;
						break;			
					}

					UpdateJsonValueContainer(V, type, value);
					empilerVoid(pileJson, V);

                    break;
                }
				case 13: { // V → A
					JsonValueContainer *V = CreateJsonValueContainer();
                    JsonValue value;
					ValueType type = array;

					value.array = depilerVoid(pileJson);

					if (value.array == NULL) {
						messageErreur = strdup("Erreur syntaxique : pile Json vide");
						exit = 1;
						break;			
					}

					UpdateJsonValueContainer(V, type, value);
					empilerVoid(pileJson, V);

                    break;
                }
				case 14: { // V → t
					JsonValueContainer *V = CreateJsonValueContainer();
                    JsonValue value;
					ValueType type = constant;

					value.constant = CSTE_JSON_TRUE;

					UpdateJsonValueContainer(V, type, value);
					empilerVoid(pileJson, V);

                    break;
                }
				case 15: { // V → f
					JsonValueContainer *V = CreateJsonValueContainer();
                    JsonValue value;
					ValueType type = constant;

					value.constant = CSTE_JSON_FALSE;

					UpdateJsonValueContainer(V, type, value);
					empilerVoid(pileJson, V);

                    break;
                }
				case 16: { // V → u
					JsonValueContainer *V = CreateJsonValueContainer();
                    JsonValue value;
					ValueType type = constant;

					value.constant = CSTE_JSON_NULL;

					UpdateJsonValueContainer(V, type, value);
					empilerVoid(pileJson, V);

                    break;
                }
                default:
                    exit = 1;
                    break;
            }
        }
        if (action != NULL) {
			free(action);
		}
    }

    deleteIntPile(&pile);
    deleteVoidPile(&pileJson);
    deleteLexData(lex_data);

	if (valid) {
		printf("\nFichier Json valide\n");
		return O;
	}
	else {
		printf("\nFichier Json invalide : %s\n", messageErreur);
		free(messageErreur);
		return NULL;
	}
}

int genererGraphe(JsonObject *O) {
	pid_t pid;
	FILE * fd = fopen("json_graph.dot", "w");
	char * content = PrintDotJsonObject(O, -1, -1);
	char * args[6] = {"dot", "-Tps", "json_graph.dot", "-o", "json_graph.pdf", NULL};
	int resu = -1;

	printf("\nCréation d'un graphe Json en cours..\n");

	if (fputs("digraph G {\n", fd) != EOF && fputs(content, fd) != EOF && fputs("\n}", fd) != EOF) {

		fclose(fd);

		if ((pid = fork()) < 0) {
			perror("fork");
			exit(errno);
		}

		if (pid == 0) {
		    if (execvp(args[0], args) == -1) {
		        perror("execvp");
		        exit(errno);
		    }
		}
		else {
			wait(NULL);
			printf("\nFichier \"json_graph.pdf\" correctement créé\n");
			resu = 1;
		}

	}
	else {
		fclose(fd);
		printf("\nUne erreur s'est produite lors de l'écriture du fichier\n");
	}

	free(content);
	remove("json_graph.dot");
	return resu;
}

int main(int argc, char * argv[]) {
	JsonObject *O;
	TLex *lex_data = NULL;
	FILE *file = NULL;
	char *cleanData;

	if (argc > 1) {
		printf("\nFichier à analyser : \"%s\"\n", argv[1]);

		int idx;
		char currChar;
		char rawData[FILE_LENGTH_LIMIT] = {0};

		file = fopen(argv[1], "r");
		currChar = fgetc(file);

		for (idx = 0 ; currChar != EOF && idx < FILE_LENGTH_LIMIT ; idx++) {
			rawData[idx] = currChar;
			currChar = fgetc(file);
		}

		if (idx == FILE_LENGTH_LIMIT) {
			printf("Fichier trop volumineux");
			return -1;
		}

		fclose(file);

		cleanData = removeBlanks(rawData);
	}
	else {
		printf("Veuillez préciser le fichier à traiter");
		return -1;
	}
    
	lex_data = initLexData(cleanData);
	free(cleanData);

    printf("\nAnalyse lancée..\n");

	if ((O = analyseurLR(lex_data)) != NULL) {
		return genererGraphe(O);
	}
	else {
		return -1;	
	}
}
