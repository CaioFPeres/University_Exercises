#include "fila_prioridade.c"

#ifndef FILA_PRIORIDADE_H
#define FILA_PRIORIDADE_H

/*! \brief Fila de prioridade com tamanho máximo.
 *         O tipo do elemento é especificado neste arquivo.
 *
 *  Esta implementação de fila de prioridade utiliza alocação dinâmica e sequencial
 * 
 *  Autor: Fulado de tal
 *  Data: XX de xxxxxxxx de 2020
 */


/*!
 * Tipo do elemento armazenado na fila
 */
typedef char fp_item;

// Tipo do elemento da fila de prioridade
// Altere este typedef para mudar o tipo de elemento
typedef struct {
    int prioridade;
    fp_item item;
} fp_item_prioridade;

// Estrutura fila de prioridade.
typedef struct {
	unsigned quantidade; // Número de elementos na fila no momento atual
  unsigned maximo; // Número de elementos máximo
	fp_item_prioridade* heap; // Estrutura Heap
} fp;

/*! Função para inicializar uma fila de prioridade do usuário. É obrigatório chamar esta função antes do início da utilização da fila.
    \param f endereço da fila alocada pelo usuário
    \param maximo número máximo de elementos na fila
    \return Sucesso ou falha na inicialização da fila de prioridade
*/
int inicializa(fp* f, unsigned maximo);

/*! Função para desalocar uma fila do usuário. É obrigatório chamar esta função depois da utilização da fila.
  \param f endereço da fila
*/
void destroi(fp* f);

/*! Função para verificar se uma fila está vazia.
  \param f endereço da fila do usuário
  \return Verdadeiro se a fila estiver vazia, falso caso contrário
*/
int vazia(fp* f);

/*! Função para verificar se uma fila está cheia.
  \param f endereço da fila do usuário
  \return Verdadeiro se a fila estiver cheia, falso caso contrário
*/
int cheia(fp* f);


/*! Função para obter o número de elementos armazenados em uma fila.
  \param f endereço da fila do usuário
  \return número de elementos armazenados na fila
*/
unsigned tamanho(fp* f);

/*! Função para inserir um elemento em uma fila de prioridade do usuário.
  \param f endereço da fila do usuário
  \param item elemento a ser inserido na fila
  \param prioridade prioridade do elemento a ser inserido
  \return Sucesso ou não da inserção. A fila pode estar cheia.
*/
int insere(fp* f, fp_item item, int prioridade);

/*! Função para remover um elemento de uma fila do usuário. Esta função não retorna o elemento removido.
  \param f endereço da fila do usuário
  \return Sucesso ou não da remoção. A fila pode estar vazia
*/
int removeMaiorPrioridade(fp* f);

/*! Função para obter o elemento de maior prioridade da fila. Esta função não remove o elemento.
  \param f endereço da fila do usuário
  \param item endereço onde será copiado o elemento de maior prioridade
  \param prioridade endereço onde será copiada a prioridade do elemento
  \return Sucesso ou não na obtenção do elemento. A fila pode estar vazia.
*/
int maiorPrioridade(fp* f, fp_item* item, int* prioridade);

#endif