#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "EstruturasVetores.h"

#define VALOR_NULO INT_MIN
#define TAM 10
#define SEPARATOR 59

typedef struct Ponteiros{
    int * ponteiros[TAM];
    int tam[TAM];
}Ponteiros;

Ponteiros vetorPrincipal;
/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'

Rertono (int)
    SUCESSO - criado com sucesso
    JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
    TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
*/
int criarEstruturaAuxiliar(int posicao, int tamanho){
    posicao -= 1;
    if(posicao >= 0 && posicao < TAM){
        if(vetorPrincipal.ponteiros[posicao] == NULL){
            if(tamanho > 0){
                vetorPrincipal.ponteiros[posicao] = (int *) malloc(tamanho * sizeof(int));
                vetorPrincipal.tam[posicao] = tamanho;
                for(int icont = 0; icont < tamanho; icont++)
                    vetorPrincipal.ponteiros[posicao][icont] = VALOR_NULO;
                return SUCESSO;
            }
            else
                return TAMANHO_INVALIDO;
        }
        else
            return JA_TEM_ESTRUTURA_AUXILIAR;
    }
    else
        return POSICAO_INVALIDA;
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
CONSTANTES
*/
int inserirNumeroEmEstrutura(int posicao, int valor)
{
    int retorno = 0;
    int existeEstruturaAuxiliar = 0;
    int temEspaco = 0;
    int posicao_invalida = 0;
    int icont;
    posicao -= 1;
    if (posicao < 0 || posicao > 9)
        retorno = POSICAO_INVALIDA;
    else
    {
        // testar se existe a estrutura auxiliar
        if (vetorPrincipal.ponteiros[posicao] != NULL)
        {
            for(icont = 0; vetorPrincipal.ponteiros[posicao][icont] != VALOR_NULO && icont < vetorPrincipal.tam[posicao]; icont++);
            
            if (icont < vetorPrincipal.tam[posicao])
            {
                vetorPrincipal.ponteiros[posicao][icont] = valor;
                retorno = SUCESSO;
            }
            else
            {
                retorno = SEM_ESPACO;
            }
        }
        else
        {
            retorno = SEM_ESTRUTURA_AUXILIAR;
        }
    }

    return retorno;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar da seguinte forma [3, 8, 7,  ,  ,  ].
Obs. Esta é uma exclusão lógica

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao)
{
    int retorno, icont;
    posicao -= 1;
    
    if(posicao >= 0 && posicao < TAM){
        
        if(vetorPrincipal.ponteiros[posicao] != NULL){
            
            if(vetorPrincipal.ponteiros[posicao][icont] != VALOR_NULO){
                
                for(icont = 0; vetorPrincipal.ponteiros[posicao][icont] != VALOR_NULO && icont < vetorPrincipal.tam[posicao]; icont++);
                
                vetorPrincipal.ponteiros[posicao][icont - 1] = VALOR_NULO;
                
                retorno = SUCESSO;
            }
            else
                retorno = ESTRUTURA_AUXILIAR_VAZIA;
        }
        else
            retorno = SEM_ESTRUTURA_AUXILIAR;
    }
    else
        retorno = POSICAO_INVALIDA;
        
    return retorno;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ]
Obs. Esta é uma exclusão lógica
Rertono (int)
    SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar

*/
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor)
{
    int retorno, icont;
    posicao -= 1;
    
    if(posicao >= 0 && posicao < TAM){
        
        if(vetorPrincipal.ponteiros[posicao] != NULL){
            
            for(icont = 0; vetorPrincipal.ponteiros[posicao][icont] != valor && vetorPrincipal.ponteiros[posicao][icont] != VALOR_NULO && icont < vetorPrincipal.tam[posicao]; icont++);
            
            if(vetorPrincipal.ponteiros[posicao][icont] == valor && icont < vetorPrincipal.tam[posicao]){
                
                for(; icont + 1 < vetorPrincipal.tam[posicao]; icont++)
                    vetorPrincipal.ponteiros[posicao][icont] = vetorPrincipal.ponteiros[posicao][icont + 1];
                
                vetorPrincipal.ponteiros[posicao][icont] = VALOR_NULO;
                
                retorno = SUCESSO;
            }
            else
                retorno = NUMERO_INEXISTENTE;
        }
        else
            retorno = SEM_ESTRUTURA_AUXILIAR;
    }
    else
        retorno = POSICAO_INVALIDA;
    
    return retorno;
}

// se posição é um valor válido {entre 1 e 10}
int ehPosicaoValida(int posicao)
{
    int retorno = 0;
    if (posicao < 1 || posicao > 10)
    {
        retorno = POSICAO_INVALIDA;
    }
    else
        retorno = SUCESSO;

    return retorno;
}
/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    int retorno, icont;
    int jcont = 0;
    posicao -= 1; 
    
    if(posicao >= 0 && posicao < TAM){
        
        if(vetorPrincipal.ponteiros[posicao] != NULL){
            
            if(*(vetorPrincipal.ponteiros[posicao] + 0) != VALOR_NULO){
                
                for(icont = 0; *(vetorPrincipal.ponteiros[posicao] + icont) != VALOR_NULO && icont < vetorPrincipal.tam[posicao]; icont++)
                    vetorAux[jcont++] = *(vetorPrincipal.ponteiros[posicao] + icont);
                
                retorno = SUCESSO;
            }
            else
                retorno = ESTRUTURA_AUXILIAR_VAZIA;
        }
        else
            retorno = SEM_ESTRUTURA_AUXILIAR;
    }
    else
        retorno = POSICAO_INVALIDA;
    
    return retorno;
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao (1..10)'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    int retorno, icont;
    int jcont = 0;
    posicao -= 1;
    
    if(posicao >= 0 && posicao < TAM){
        
        if(vetorPrincipal.ponteiros[posicao] != NULL){
            
            if(*(vetorPrincipal.ponteiros[posicao] + 0) != VALOR_NULO){
                
                for(icont = 0; *(vetorPrincipal.ponteiros[posicao] + icont) != VALOR_NULO && icont < vetorPrincipal.tam[posicao]; icont++)
                    vetorAux[jcont++] = *(vetorPrincipal.ponteiros[posicao] + icont);
                
                for(int i = 1; i < icont; i++){
                    int chave = vetorAux[i]; 
                    int j = i - 1;

                    
                    while (j >= 0 && vetorAux[j] > chave) {
                        vetorAux[j + 1] = vetorAux[j];
                        j--;
                    }

                    vetorAux[j + 1] = chave; 
                }
                
                retorno = SUCESSO;
            }
            else
                retorno = ESTRUTURA_AUXILIAR_VAZIA;
        }
        else
            retorno = SEM_ESTRUTURA_AUXILIAR;
    }
    else
        retorno = POSICAO_INVALIDA;
    
    return retorno;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int list = 0, jcont = 0;
    int icont, posicao, retorno;
    
    for(icont = 0, posicao = 0; posicao < TAM; icont++){
        
        if(vetorPrincipal.ponteiros[posicao] != NULL && *(vetorPrincipal.ponteiros[posicao] + 0) != VALOR_NULO){
            
            if(icont < vetorPrincipal.tam[posicao]){
                
                if(*(vetorPrincipal.ponteiros[posicao] + icont) != VALOR_NULO){
                    vetorAux[jcont++] = *(vetorPrincipal.ponteiros[posicao] + icont);
                } else{
                    icont = -1;
                    posicao++;
                }
            } else{
                icont = -1;
                posicao++;
            }
        } else{
            list++;
            icont = -1;
            posicao++;
        }
    }
    if(list == 10)
        retorno = TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    else
        retorno = SUCESSO;
    
    return retorno;
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int list = 0, jcont = 0, kcont = 0;
    int icont, posicao, retorno;
    
    for(icont = 0, posicao = 0; posicao < TAM; icont++){
        
        if(vetorPrincipal.ponteiros[posicao] != NULL && *(vetorPrincipal.ponteiros[posicao] + 0) != VALOR_NULO){
            
            if(icont < vetorPrincipal.tam[posicao]){
                
                if(*(vetorPrincipal.ponteiros[posicao] + icont) != VALOR_NULO){
                    vetorAux[jcont++] = *(vetorPrincipal.ponteiros[posicao] + icont);
                    kcont++;
                } else{
                    icont = -1;
                    posicao++;
                }
            } else{
                icont = -1;
                posicao++;
            }
        } else{
            list++;
            icont = -1;
            posicao++;
        }
    }
    for (int i = 1; i < kcont; i++) {
        int chave = vetorAux[i]; 
        int j = i - 1;

        
        while (j >= 0 && vetorAux[j] > chave) {
            vetorAux[j + 1] = vetorAux[j];
            j--;
        }

        vetorAux[j + 1] = chave; 
    }
    
    if(list == 10){
        retorno = TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
        return retorno;
    }
    else{
        retorno = SUCESSO;
        return retorno;
    }
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o novo tamanho 'novoTamanho' + tamanho atual
Suponha o tamanho inicial = x, e novo tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser sempre >= 1

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho)
{
    int retorno;
    posicao -= 1;
    if(posicao >= 0 && posicao < TAM){
        if(vetorPrincipal.ponteiros[posicao] != NULL){
            novoTamanho += vetorPrincipal.tam[posicao];
            if(novoTamanho > 0){
                vetorPrincipal.ponteiros[posicao] = realloc(vetorPrincipal.ponteiros[posicao], novoTamanho * sizeof(int));
                if(vetorPrincipal.ponteiros[posicao] != NULL){
                    for(int icont = vetorPrincipal.tam[posicao]; icont < novoTamanho; icont++)
                        *(vetorPrincipal.ponteiros[posicao] + icont) = VALOR_NULO;
                    vetorPrincipal.tam[posicao] = novoTamanho;
                    
                    retorno = SUCESSO;
                } else
                    retorno = SEM_ESPACO_DE_MEMORIA;
            } else
                retorno = NOVO_TAMANHO_INVALIDO;
        } else
            retorno = SEM_ESTRUTURA_AUXILIAR;
    } else
        retorno = POSICAO_INVALIDA;
    
    return retorno;
}

/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao'.

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos preenchidos da estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao)
{
    int retorno, qtd = 0;
    posicao -= 1;
    if(posicao >= 0 && posicao < TAM){
        if(vetorPrincipal.ponteiros[posicao] != NULL){
            if(*(vetorPrincipal.ponteiros[posicao] + 0) != VALOR_NULO){
                for(int icont = 0; icont < vetorPrincipal.tam[posicao] && *(vetorPrincipal.ponteiros[posicao] + icont) != VALOR_NULO; icont++)
                    qtd++;
                return qtd;
            } else
                retorno = ESTRUTURA_AUXILIAR_VAZIA;
        } else
            retorno = SEM_ESTRUTURA_AUXILIAR;
    } else
        retorno = POSICAO_INVALIDA;

    return retorno;
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote(){
    No * inicio;
    inicio = (No *) malloc(sizeof(No));
    inicio->next = NULL;
    No * atual;
    atual = (No *) malloc(sizeof(No));

    int jcont = 0;
    int icont, posicao;
    
    for(icont = 0, posicao = 0; posicao < TAM; icont++){
        
        if(vetorPrincipal.ponteiros[posicao] != NULL && *(vetorPrincipal.ponteiros[posicao] + 0) != VALOR_NULO){
            
            if(icont < vetorPrincipal.tam[posicao]){
                
                if(*(vetorPrincipal.ponteiros[posicao] + icont) != VALOR_NULO){
                    No * novo;
                    novo = (No *) malloc(sizeof(No));
                    novo->key = *(vetorPrincipal.ponteiros[posicao] + icont);
                    novo->next = NULL;
                    if(inicio->next == NULL){
                        inicio->next = novo;
                        atual = novo;
                    } else{
                        atual->next = novo;
                        atual = novo;
                    }
                } else{
                    icont = -1;
                    posicao++;
                }
            } else{
                icont = -1;
                posicao++;
            }
        } else{
            icont = -1;
            posicao++;
        }
    }
    atual = NULL;
    free(atual);
    return inicio;
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[]){
    No * temp = (No *) malloc(sizeof(No));
    temp = inicio->next;
    int icont = 0;

    while(temp != NULL){
        vetorAux[icont++] = temp->key;
        temp = temp->next;
    }
    free(temp);
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno 
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio){
    
    No * atual = (No *) malloc(sizeof(No));
    atual = (*inicio)->next;
    *inicio = NULL;

    while(atual != NULL){
        No * liberar = (No *) malloc(sizeof(No));
        liberar = atual;
        atual = atual->next;
        free(liberar);
    }
}

/*
Objetivo: inicializa o programa. deve ser chamado ao inicio do programa 

*/

void inicializar(){
    for(int i = 0; i < TAM; i++)
        vetorPrincipal.ponteiros[i] = NULL;
    
    load();
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa 
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/

void finalizar()
{
    store();

    for(int icont = 0; icont < TAM; icont++){
        free(vetorPrincipal.ponteiros[icont]);
    }

}

void store(){
    FILE * file;

    file = fopen("EstruturasVetoresFiles.txt","w");

    if(file == NULL){
        printf("Erro em reescrever arquivo!");
        return;
    }

    for(int i = 0; i < TAM; i++){
        if(vetorPrincipal.ponteiros[i] != NULL){
            fprintf(file, "%d;%d;", i, vetorPrincipal.tam[i]);
            for(int j = 0; vetorPrincipal.ponteiros[i][j] != VALOR_NULO && j < vetorPrincipal.tam[i]; j++)
                fprintf(file, "%d;", vetorPrincipal.ponteiros[i][j]);
            fprintf(file, "\n");
        }
    }
    fclose(file);
}
void load(){
    FILE * file;

    file = fopen("EstruturasVetoresFiles.txt","r+");

    if(file == NULL) file = fopen("EstruturasVetoresFiles.txt","w");

    if(file == NULL){
        printf("Erro em criar arquivo!");
        return;
    }
    char buffer[100];

    while(fgets(buffer, sizeof(buffer), file) != NULL){
        
        char * copy = strdup(buffer);
        if(!copy){
            printf("Alocação de memória falhou");
            return;
        }

        char separator[2] = {SEPARATOR, '\0'};

        char * token = strtok(copy, separator);
        int pos = atoi(token);
        
        vetorPrincipal.tam[pos] = atoi(strtok(NULL, separator));
        vetorPrincipal.ponteiros[pos] = (int *) malloc(vetorPrincipal.tam[pos] * sizeof(int));
        
        for(int icont = 0; icont < vetorPrincipal.tam[pos]; icont++)
                vetorPrincipal.ponteiros[pos][icont] = VALOR_NULO;

        int i = 0;
        token = strtok(NULL, separator);
        while(token != NULL){
            vetorPrincipal.ponteiros[pos][i] = atoi(token);
            token = strtok(NULL, separator);
            i++;
        }
        free(copy);
    }
    fclose(file);
}