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

    char *JsonSymbTab = " tfu{}[],:snn#";
    char *colonneTabAction = "{}[],:sntfu#";
    char *colonneTabGoto = "OMPAEV";
    char *rawData = "{\"titre_album\":\"Abbey Road\",\"groupe\":\"The Beatles\",\"annee\":1969,\"est_cool\":true,\"infos-en-vrac\":[1012,false,null,12.34],\"batteur\":{\"nom\":\"Ringo Starr\"}}";
    char *cleanData = removeBlanks(rawData);
    char *action = NULL;
    int fini = 0;

	int *reducsTab = NULL;
	int reducsTabSize = 0;

    lex_data = initLexData(cleanData);

	char lexeme = JsonSymbTab[lex(lex_data)];
    free(cleanData);

	printf("\n\n/************ Entrée ***********/\n\n");
	printf("%s", lex_data->data);

	
    while (!fini) {

        fflush(stdout);

		// Affichage pour débogage
		printf("\n\n------------ Action ------------\n\n");
		printf("Lexeme\t\t\t : '%c'\n", lexeme);   
		printf("[sommetInt, indexOfChar] : [%d, %d]\n", sommetInt(pile), indexOfChar(colonneTabAction, lexeme));
		printf("Action\t\t\t : %s", TableAction[sommetInt(pile)][indexOfChar(colonneTabAction, lexeme)]);

        action = strdup(TableAction[sommetInt(pile)][indexOfChar(colonneTabAction, lexeme)]);

        if (action == NULL) { // ERREUR
            printf("\n\n/********************************/\n/*******  String refusée  ********/\n/********************************/\n\n");
            return -1;
        }
        else if (strcmp(action, "acc") == 0) {
            printf("\n\n/********************************/\n/*******  String acceptée  ******/\n/********************************/\n\n");
            void *o = depilerVoid(pileJson);


			int i;
			printf("Réductions opérées : ");
			for (i = 0; i < reducsTabSize; i++) printf("%d ", reducsTab[i]);


            fini = 1;
            return 0;
        }
        else if (action[0] == 'd') {
            int i;
			int deplacement;
            char *buff = strdup(action);

            for (i = 0 ; i < strlen(action) ; i++)
                buff[i] = action[i+1];

            deplacement = atoi(buff);

            empilerInt(pile, deplacement);

			lexeme = JsonSymbTab[lex(lex_data)];

			// Affichage pour débogage
			printIntPile(pile);
        }
        else {
            int i;
			int nRegle;
            char *buff = strdup(action);

            for (i = 0 ; i < strlen(action) ; i++)
                buff[i] = action[i+1];

            nRegle = atoi(buff);

			// Affichage pour débogage
			printf("\n\n========== Réduction ===========\n\n");
            printf("Règle : %d\n", nRegle);
			printf("Contenu : %s → %s", TableRegle[nRegle][0], TableRegle[nRegle][1]);

            for (i = 0 ; i < strlen(TableRegle[nRegle][1]) ; i++)
                depilerInt(pile);

            empilerInt(pile, atoi(TableGoto[sommetInt(pile)][indexOfChar(colonneTabGoto, TableRegle[nRegle][0][0])]));

			// Affichage pour débogage
			printIntPile(pile);
			reducsTabSize++;
			reducsTab = realloc(reducsTab, reducsTabSize * sizeof(int));
			reducsTab[reducsTabSize - 1] = nRegle;
			printf("\nreducsTab[%d] = %d", reducsTabSize, reducsTab[reducsTabSize - 1]);
			
            /*switch(nRegle) {
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
                    void *P = depilerVoid(pileJson);
                    void *O = CreateJsonObject();
                    InsertJsonObject(O, P);
                    empilerVoid(pileJson, O);

                    break;
                }
                case 4: { // M → P, M
                    void *O = depilerVoid(pileJson);
                    void *P = depilerVoid(pileJson);
                    InsertJsonObject(O, P);
					empilerVoid(pileJson, O);

                    break;
                }
                case 5: { // P → s : V
                    void *P = CreateJsonPair();
                    void *V = depilerVoid(pileJson);

                    char *s = strdup(lex_data->tableSymboles[lex_data->nbSymboles - 1].val.chaine);
					free(s);

                    UpdateJsonPair(P, s, V);
                    empilerVoid(pileJson, P);

                    break;
                }
				case 6: {
                    break;
                }
				case 7: {
                    break;
                }
				case 8: {
                    break;
                }
				case 9: {
                    break;
                }
                case 10: { // V → s
					JsonValueContainer *V = CreateJsonValueContainer();
                    JsonValue value;
					ValueType type = string;

                    value.string = strdup(lex_data->tableSymboles[lex_data->nbSymboles - 1].val.chaine);
					
					UpdateJsonValueContainer(V, type, value);

					free(value.string);

					empilerVoid(pileJson, V);

					if (lex_data->nbSymboles > 0) {
						free(lex_data->tableSymboles[lex_data->nbSymboles - 1].val.chaine);
						lex_data->nbSymboles--;
		                lex_data->tableSymboles = realloc(lex_data->tableSymboles, sizeof(TSymbole) * lex_data->nbSymboles);
						if (lex_data->tableSymboles == NULL)
							return -1;
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
						lex_data->tableSymboles = realloc(lex_data->tableSymboles, sizeof(TSymbole) * lex_data->nbSymboles);
						if (lex_data->tableSymboles == NULL)
							return -1;
					}

                    break;
                }
				case 12: { // V → O
					JsonValueContainer *V = CreateJsonValueContainer();
                    JsonValue value;
					ValueType type = object;

					value.object = CreateJsonObject();

					UpdateJsonValueContainer(V, type, value);
					empilerVoid(pileJson, V);

					if (lex_data->nbSymboles > 0) {
						lex_data->nbSymboles--;
		                lex_data->tableSymboles = realloc(lex_data->tableSymboles, sizeof(TSymbole) * lex_data->nbSymboles);
						if (lex_data->tableSymboles == NULL)
							return -1;
					}

                    break;
                }
				case 13: {
                    break;
                }
				case 14: {
                    break;
                }
				case 15: {
                    break;
                }
				case 16: {
                    break;
                }
                default:
                    fini = 1;
                    break;
            }*/

			/*

			#define CSTE_JSON_NULL 2
			#define CSTE_JSON_TRUE 1
			#define CSTE_JSON_FALSE 0


			typedef struct _json_pair {
				char * string;
				struct _json_value_container * value;
			} JsonPair;

			typedef enum _value_type {
				string,
				integer,
				real,
				object,
				array,
				constant
			} ValueType;

			typedef union {
				char * string;
				int integer;
				float real;
				struct _json_object * object;
				struct _json_array * array;
				int constant;
			} JsonValue;

			typedef struct _json_value_container {
				ValueType type;
				JsonValue value;
			} JsonValueContainer;

			typedef struct _json_object {
				JsonPair ** members;
				int size;
			} JsonObject;

			typedef struct _json_array {
				JsonValueContainer ** elements;
				int size;
			} JsonArray;


			JsonArray * CreateJsonArray();
			int InsertJsonArray(JsonArray * _array, JsonValueContainer * _valueContainer, const unsigned int _position);
			int DeleteJsonArray(JsonArray ** _array);
			char * PrintJsonArray(const JsonArray * _array);
			char * PrintDotJsonArray(const JsonArray * _array);

			JsonObject * CreateJsonObject();
			int InsertJsonObject(JsonObject * _object, JsonPair * _pair);
			JsonValueContainer * GetJsonValueContainer(const JsonObject * _object, const char * _string);
			int DeleteJsonObject(JsonObject ** _object);
			char * PrintJsonObject(const JsonObject * _object);
			char * PrintDotJsonObject(const JsonObject * _object, int _id, int _idParent);

			JsonValueContainer * CreateJsonValueContainer();
			void UpdateJsonValueContainer(JsonValueContainer * _valueContainer, ValueType _type, JsonValue _value);
			int DeleteJsonValueContainer(JsonValueContainer ** _valueContainer);
			char * PrintJsonValueContainer(const JsonValueContainer * _valueContainer);

			JsonPair * CreateJsonPair();
			void UpdateJsonPair(JsonPair * _pair, char * _string, JsonValueContainer * _value);
			int DeleteJsonPair(JsonPair ** _pair);
			char * PrintJsonPair(const JsonPair *_pair);

			*/
        }
        free(action);
    }

    deleteIntPile(&pile);
    deleteVoidPile(&pileJson);
    deleteLexData(lex_data);

    return 0;
}

int main(int argc, const char argv[]) {

    printf("----------- Analyseur syntaxique -----------\n\n");
    analyseurLR();
    printf("\n");
    return 0;
}
