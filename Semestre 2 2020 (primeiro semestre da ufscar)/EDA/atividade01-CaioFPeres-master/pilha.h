#ifndef PILHA_H
#define PILHA_H

/*! \brief Pilha de elementos com tamanho máximo.
 *         O tipo do elemento é especificado neste arquivo.
 *
 *  Esta implementação de pilha utiliza alocação dinâmica e encadeamento
 * 
 *  Autor: Fulado de tal
 *  Data: 26 de agosto de 2020
 */

// Tipo do elemento da pilha
// Altere este typedef para mudar o tipo de elemento
typedef char pilha_item;

// Tipo do nó com um elemento da pilha
struct pilha_no_struct { 
  pilha_item item;
  struct pilha_no_struct* prox;
};
typedef struct pilha_no_struct* pilha_no;

// Estrutura pilha.
struct pilha_struct {
	unsigned quantidade; // Número de elementos na pilha no momento atual
	pilha_no topo; // Índice do elemento que está no topo da pilha
};

// Tipo do elemento da pilha.
// Estrutura pilha definida para o usuário
typedef struct pilha_struct* pilha;

/*! Função para inicializar uma pilha do usuário. É obrigatório chamar esta função antes do início da utilização da pilha.
    \return pilha inicializada a ser atribuida
*/
pilha inicializa();

/*! Função para liberar uma pilha do usuário. É obrigatório chamar esta função depois da utilização da pilha.
  \param p pilha do usuário
*/
void destroi(pilha p);

/*! Função para verificar se uma pilha está vazia.
  \param p pilha do usuário
  \return Verdadeiro se a pilha estiver vazia, falso caso contrário
*/
int vazia(pilha p);

/*! Função para obter o número de elementos armazenados em uma pilha.
  \param p pilha do usuário
  \return número de elementos armazenados na pilha
*/
unsigned tamanho(pilha p);

/*! Função para inserir um elemento em uma pilha do usuário.
  \param p pilha do usuário
  \param item elemento a ser inserido na pilha (no topo)
  \return Sucesso ou não da inserção.
*/
int empilha(pilha p, pilha_item item);

/*
! Função para remover um elemento de uma pilha do usuário. Esta função retorna o elemento removido.
  \param p pilha do usuário
  \param item endereço onde será copiado o elemento que foi removido
  \return Sucesso ou não da remoção. A pilha pode estar vazia
*/
int desempilha_retorna(pilha p, pilha_item* item);

/*! Função para remover um elemento de uma pilha do usuário. Esta função não retorna o elemento removido.
  \param p pilha do usuário
  \return Sucesso ou não da remoção. A pilha pode estar vazia
*/
int desempilha(pilha p);

//! Função para obter o elemento do topo de uma pilha
    /*! Esta função não remove o elemento do topo
      \param p pilha do usuário
      \param item endereço onde será copiado o elemento do topo
      \return Sucesso ou não na obtenção do topo. A pilha pode estar vazia.
    */
int topo(pilha p, pilha_item* item);

#endif
