/* ==========================================================================
 * Universidade Federal de São Carlos - Campus Sorocaba
 * Disciplina: Organização de Recuperação da Informação
 * Prof. Tiago A. Almeida
 *
 * Trabalho 03 - Tabelas Hash
 *
 * RA: 769298
 * Aluno: Caio Fernando Peres
 * ========================================================================== */

/* Bibliotecas */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

typedef enum {false, true} bool;

/* Tamanho dos campos dos registros */
/* Campos de tamanho fixo */
#define TAM_CPF 12
#define TAM_NASCIMENTO 11
#define TAM_CELULAR 12
#define TAM_SALDO 14
#define TAM_TIMESTAMP 15
#define QTD_MAX_CHAVES_PIX 4

/* Campos de tamanho variável (tamanho máximo) */
// Restaram 204 bytes (48B nome, 47B email, 11B chave CPF, 11B chave número de celular,
// 47B chave email, 37B chave aleatória, 3B demilitadores)
#define TAM_MAX_NOME 48
#define TAM_MAX_EMAIL 47
#define TAM_MAX_CHAVE_PIX 48

#define MAX_REGISTROS 15000
#define TAM_REGISTRO_CLIENTE 256
#define TAM_REGISTRO_TRANSACAO 49
#define TAM_ARQUIVO_CLIENTE (TAM_REGISTRO_CLIENTE * MAX_REGISTROS + 1)
#define TAM_ARQUIVO_TRANSACAO (TAM_REGISTRO_TRANSACAO * MAX_REGISTROS + 1)

#define TAM_RRN_REGISTRO 4
#define TAM_CHAVE_TRANSACOES_IDX (TAM_CPF + TAM_TIMESTAMP + TAM_RRN_REGISTRO - 2)
#define TAM_CHAVE_CHAVES_PIX_IDX (TAM_MAX_CHAVE_PIX + TAM_CPF - 2)
#define TAM_CHAVE_TIMESTAMP_CPF_ORIGEM_IDX (TAM_TIMESTAMP + TAM_CPF - 2)

#define TAM_ARQUIVO_TRANSACOES_IDX (1000 * MAX_REGISTROS + 1)
#define TAM_ARQUIVO_TIMESTAMP_CPF_ORIGEM_IDX (1000 * MAX_REGISTROS + 1)

/* Mensagens padrões */
#define SUCESSO                          "OK\n"
#define RRN_NOS                          "Nos percorridos:"
#define INDICE_PERCORRIDO                "Indices percorridos:"
#define AVISO_NENHUM_REGISTRO_ENCONTRADO "AVISO: Nenhum registro encontrado\n"
#define ERRO_OPCAO_INVALIDA              "ERRO: Opcao invalida\n"
#define ERRO_MEMORIA_INSUFICIENTE        "ERRO: Memoria insuficiente\n"
#define ERRO_PK_REPETIDA                 "ERRO: Ja existe um registro com a chave primaria %s\n"
#define ERRO_REGISTRO_NAO_ENCONTRADO     "ERRO: Registro nao encontrado\n"
#define ERRO_SALDO_NAO_SUFICIENTE        "ERRO: Saldo insuficiente\n"
#define ERRO_VALOR_INVALIDO              "ERRO: Valor invalido\n"
#define ERRO_CHAVE_PIX_REPETIDA          "ERRO: Ja existe uma chave PIX %s\n"
#define ERRO_CHAVE_PIX_DUPLICADA         "ERRO: Chave PIX tipo %c ja cadastrada para este usuario\n"
#define ERRO_CHAVE_PIX_INVALIDA          "ERRO: Chave PIX invalida\n"
#define ERRO_TIPO_PIX_INVALIDO           "ERRO: Tipo %c invalido para chaves PIX\n"
#define ERRO_ARQUIVO_VAZIO               "ERRO: Arquivo vazio\n"
#define ERRO_NAO_IMPLEMENTADO            "ERRO: Funcao %s nao implementada\n"

/* Registro de Cliente */
typedef struct {
    int this_rrn;
    char cpf[TAM_CPF];
    char nome[TAM_MAX_NOME];
    char nascimento[TAM_NASCIMENTO];
    char email[TAM_MAX_EMAIL];
    char celular[TAM_CELULAR];
    double saldo;
    char chaves_pix[QTD_MAX_CHAVES_PIX][TAM_MAX_CHAVE_PIX];
} Cliente;

/* Registro de transação */
typedef struct {
    int this_rrn;
    char cpf_origem[TAM_CPF];
    char cpf_destino[TAM_CPF];
    double valor;
    char timestamp[TAM_TIMESTAMP];
} Transacao;

/*----- Registros dos índices -----*/
/* Struct para índice primário de clientes */
typedef struct {
    char cpf[TAM_CPF];
    int rrn;
} clientes_idx_struct;

/* Struct para índice secundário de chaves PIX */
typedef struct {
    char chave_pix[TAM_MAX_CHAVE_PIX];
    char pk_cliente[TAM_CPF];
} chaves_pix_idx_struct;

// a posição livre é representada pelo nó NULL
typedef enum {used_node, deleted_node} hash_node_state_enum;

/* Struct para um elemento da tabela hash */
typedef struct hash_node_struct {
    void *data;
    union {
        struct hash_node_struct *next; // é utilizado apenas no encadeamento
        hash_node_state_enum state; // é utilizado apenas no endereçamento aberto
    };
} hash_node;

/* Struct para um nó de Árvore-B */
typedef struct {
    int this_rrn;
    int qtd_chaves;
    char **chaves; // ponteiro para o começo do campo de chaves no arquivo de índice respectivo
    bool folha;
    int *filhos; // vetor de int para o RRN dos nós filhos (DEVE SER DESALOCADO APÓS O USO!!!)
} btree_node;

/* Variáveis globais */
/* Arquivos de dados */
char ARQUIVO_CLIENTES[TAM_ARQUIVO_CLIENTE];
char ARQUIVO_TRANSACOES[TAM_ARQUIVO_TRANSACAO];

/* Ordem das Árvores-B */
int btree_order = 3; // valor padrão

/* Índices */
/* Struct para os parâmetros de uma Árvore-B */
typedef struct {
    // RRN da raíz
    int rrn_raiz;

    // Ponteiro para o arquivo de índice
    char *arquivo;

    // Quantidade de nós no arquivo de índice
    unsigned qtd_nos;

    // Tamanho de uma chave nesse índice
    unsigned tam_chave;

    // Função utilizada para comparar as chaves do índice.
    // Igual às funções de comparação do bsearch e qsort.
    int (*compar)(const void *key, const void *elem);
} btree;

// a posição livre é representada pelo nó NULL
typedef enum {open_addressing, separate_chaining} hash_type_enum;

/* Struct para os parâmetros de uma tabela hash */
typedef struct hash_struct {
    // Ponteiro para a tabela hash
    hash_node **tabela;

    // Tamanho (em bytes) do dado nesse índice
    unsigned tam_chave;

    // Quantidade de inserções no índice
    unsigned qtd_insercoes;

    // Função de hash
    unsigned (*hash_function)(const void *data, unsigned table_size);

    // Ordem da tabela hash
    unsigned table_size;

    // Método de resolução de colisão
    hash_type_enum type;

    // Função utilizada para comparar as chaves do índice.
    // Igual às funções de comparação do bsearch e qsort.
    int (*compar)(const void *key, const void *elem);

    void (*create_idx)();
} hash;

typedef struct {
    char chave_promovida[TAM_CHAVE_CHAVES_PIX_IDX + 1]; // TAM_CHAVE_CHAVES_PIX_IDX é a maior chave possível
    int filho_direito;
} promovido_aux;

/* Arquivos de índices */
char ARQUIVO_TRANSACOES_IDX[TAM_ARQUIVO_TRANSACOES_IDX];
char ARQUIVO_TIMESTAMP_CPF_ORIGEM_IDX[TAM_ARQUIVO_TIMESTAMP_CPF_ORIGEM_IDX];

/* Comparam a chave (key) com cada elemento do índice (elem).
 * Funções auxiliares para o buscar e inserir chaves em Árvores-B ou hash (dependendo do índice).
 * Note que, desta vez, as funções comparam chaves no formato de strings quando no índice Árvore-B e structs no índice hash.
 * key é a chave do tipo string que está sendo buscada ou inserida. elem é uma chave do tipo string da struct btree_node ou uma struct do índice hash.
 *
 * Dica: busque sobre as funções strncmp e strnlen, muito provavelmente vai querer utilizá-las no código.
 * */
int order_clientes_idx(const void *key, const void *elem);
int order_transacoes_idx(const void *key, const void *elem);
int order_chaves_pix_idx(const void *key, const void *elem);
int order_timestamp_cpf_origem_idx(const void *key, const void *elem);

/**
 * Função de hash utilizada pelo índice clientes_idx.
 * <p>
 * Recomenda-se utilizar a implementação pow_uint64 já fornecida para evitar
 * diferenças de implementação entre arquiteturas.
 *
 * @param data Dado a ser feito o hash. Espera-se que seja fornecida uma struct
 * clientes_idx_struct que representa o registro a ser inserido/buscado na tabela hash.
 * @param table_size Tamanho da tabela hash (ht->table_size).
 * @return Resultado da função hash aplicado do dado fornecido.
 */
unsigned hash_function_clientes_idx(const void *data, unsigned table_size);

/**
 * Função de hash utilizada pelo índice chaves_pix_idx.
 * <p>
 * Recomenda-se utilizar a implementação pow_uint64 já fornecida para evitar
 * diferenças de implementação entre arquiteturas.
 *
 * @param data Dado a ser feito o hash. Espera-se que seja fornecida uma struct
 * chaves_pix_idx_struct que representa o registro a ser inserido/buscado na tabela hash.
 * @param table_size Tamanho da tabela hash (ht->table_size).
 * @return Resultado da função hash aplicado do dado fornecido.
 */
unsigned hash_function_chaves_pix_idx(const void *data, unsigned table_size);

/* Cria o índice respectivo */
void criar_clientes_idx(); // movida para cima (para ser utilizado no índice hash)
void criar_chaves_pix_idx(); // movida para cima (para ser utilizado no índice hash)

hash clientes_idx = {
    .tabela = NULL,
    .tam_chave = sizeof(clientes_idx_struct),
    .qtd_insercoes = 0,
    .hash_function = hash_function_clientes_idx,
    .table_size = 503,
    .type = open_addressing,
    .compar = order_clientes_idx,
    .create_idx = criar_clientes_idx,
};

btree transacoes_idx = {
    .rrn_raiz = -1,
    .arquivo = ARQUIVO_TRANSACOES_IDX,
    .qtd_nos = 0,
    .tam_chave = TAM_CHAVE_TRANSACOES_IDX,
    .compar = order_transacoes_idx,
};

hash chaves_pix_idx = {
    .tabela = NULL,
    .tam_chave = sizeof(chaves_pix_idx_struct),
    .qtd_insercoes = 0,
    .hash_function = hash_function_chaves_pix_idx,
    .table_size = 1009,
    .type = separate_chaining,
    .compar = order_chaves_pix_idx,
    .create_idx = criar_chaves_pix_idx,
};

btree timestamp_cpf_origem_idx = {
    .rrn_raiz = -1,
    .arquivo = ARQUIVO_TIMESTAMP_CPF_ORIGEM_IDX,
    .qtd_nos = 0,
    .tam_chave = TAM_CHAVE_TIMESTAMP_CPF_ORIGEM_IDX,
    .compar = order_timestamp_cpf_origem_idx,
};

/* Contadores */
unsigned qtd_registros_clientes = 0;
unsigned qtd_registros_transacoes = 0;

/* Funções de geração determinística de números pseudo-aleatórios */
uint64_t prng_seed;

void prng_srand(uint64_t value) {
    prng_seed = value;
}

uint64_t prng_rand() {
    // https://en.wikipedia.org/wiki/Xorshift#xorshift*
    uint64_t x = prng_seed; // O estado deve ser iniciado com um valor diferente de 0
    x ^= x >> 12; // a
    x ^= x << 25; // b
    x ^= x >> 27; // c
    prng_seed = x;
    return x * UINT64_C(0x2545F4914F6CDD1D);
}

/**
 * Gera um <a href="https://en.wikipedia.org/wiki/Universally_unique_identifier">UUID Version-4 Variant-1</a>
 * (<i>string</i> aleatória) de 36 caracteres utilizando o gerador de números pseudo-aleatórios
 * <a href="https://en.wikipedia.org/wiki/Xorshift#xorshift*">xorshift*</a>. O UUID é
 * escrito na <i>string</i> fornecida como parâmetro.
 * <p>
 * Exemplo de uso:
 * <p>char chave_aleatoria[37];
 * <p>new_uuid(chave_aleatoria);
 * <p>printf("chave aleatória: %s&#92;n", chave_aleatoria);
 *
 * @param buffer String de tamanho 37 no qual será escrito
 * o UUID. É terminado pelo caractere <code>\0</code>.
 */
void new_uuid(char buffer[37]) {
    uint64_t r1 = prng_rand();
    uint64_t r2 = prng_rand();

    sprintf(buffer, "%08x-%04x-%04lx-%04lx-%012lx", (uint32_t)(r1 >> 32), (uint16_t)(r1 >> 16), 0x4000 | (r1 & 0x0fff), 0x8000 | (r2 & 0x3fff), r2 >> 16);
}

/* Funções de manipulação de data (timestamp) */
int64_t epoch;

void set_time(int64_t value) {
    epoch = value;
}

void tick_time() {
    epoch += prng_rand() % 864000; // 10 dias
}

struct tm gmtime_(const int64_t lcltime) {
    // based on https://sourceware.org/git/?p=newlib-cygwin.git;a=blob;f=newlib/libc/time/gmtime_r.c;
    struct tm res;
    long days = lcltime / 86400 + 719468;
    long rem = lcltime % 86400;
    if (rem < 0) {
        rem += 86400;
        --days;
    }

    res.tm_hour = (int) (rem / 3600);
    rem %= 3600;
    res.tm_min = (int) (rem / 60);
    res.tm_sec = (int) (rem % 60);

    int weekday = (3 + days) % 7;
    if (weekday < 0) weekday += 7;
    res.tm_wday = weekday;

    int era = (days >= 0 ? days : days - 146096) / 146097;
    unsigned long eraday = days - era * 146097;
    unsigned erayear = (eraday - eraday / 1460 + eraday / 36524 - eraday / 146096) / 365;
    unsigned yearday = eraday - (365 * erayear + erayear / 4 - erayear / 100);
    unsigned month = (5 * yearday + 2) / 153;
    unsigned day = yearday - (153 * month + 2) / 5 + 1;
    month += month < 10 ? 2 : -10;

    int isleap = ((erayear % 4) == 0 && (erayear % 100) != 0) || (erayear % 400) == 0;
    res.tm_yday = yearday >= 306 ? yearday - 306 : yearday + 59 + isleap;
    res.tm_year = (erayear + era * 400 + (month <= 1)) - 1900;
    res.tm_mon = month;
    res.tm_mday = day;
    res.tm_isdst = 0;

    return res;
}

/**
 * Escreve a <i>timestamp</i> atual no formato <code>AAAAMMDDHHmmSS</code> em uma <i>string</i>
 * fornecida como parâmetro.
 * <p>
 * Exemplo de uso:
 * <p>char timestamp[TAM_TIMESTAMP];
 * <p>current_timestamp(timestamp);
 * <p>printf("timestamp atual: %s&#92;n", timestamp);
 *
 * @param buffer String de tamanho <code>TAM_TIMESTAMP</code> no qual será escrita
 * a <i>timestamp</i>. É terminado pelo caractere <code>\0</code>.
 */
void current_timestamp(char buffer[TAM_TIMESTAMP]) {
    // http://www.cplusplus.com/reference/ctime/strftime/
    // http://www.cplusplus.com/reference/ctime/gmtime/
    // AAAA MM DD HH mm SS
    // %Y   %m %d %H %M %S
    struct tm tm_ = gmtime_(epoch);
    strftime(buffer, TAM_TIMESTAMP, "%Y%m%d%H%M%S", &tm_);
}

/* Remove comentários (--) e caracteres whitespace do começo e fim de uma string */
void clear_input(char *str) {
    char *ptr = str;
    int len = 0;

    for (; ptr[len]; ++len) {
        if (strncmp(&ptr[len], "--", 2) == 0) {
            ptr[len] = '\0';
            break;
        }
    }

    while(len-1 > 0 && isspace(ptr[len-1]))
        ptr[--len] = '\0';

    while(*ptr && isspace(*ptr))
        ++ptr, --len;

    memmove(str, ptr, len + 1);
}

/* ==========================================================================
 * ========================= PROTÓTIPOS DAS FUNÇÕES =========================
 * ========================================================================== */

/* Cria o índice respectivo */
//void criar_clientes_idx(); // movida para cima (para ser utilizado no índice hash)
void criar_transacoes_idx();
//void criar_chaves_pix_idx(); // movida para cima (para ser utilizado no índice hash)
void criar_timestamp_cpf_origem_idx();

/* Exibe um registro com base no RRN */
bool exibir_cliente(int rrn);
bool exibir_transacao(int rrn);

/* Exibe um registro com base na chave de um btree_node */
bool exibir_btree_transacao(char *chave);
bool exibir_btree_timestamp_cpf_origem(char *chave);

/* Recupera do arquivo o registro com o RRN informado
 * e retorna os dados nas struct Cliente/Transacao */
Cliente recuperar_registro_cliente(int rrn);
Transacao recuperar_registro_transacao(int rrn);

/* Escreve no arquivo respectivo na posição informada (RRN)
 * os dados na struct Cliente/Transacao */
void escrever_registro_cliente(Cliente c);
void escrever_registro_transacao(Transacao t);

/* Funções principais */
void cadastrar_cliente_menu(char *cpf, char *nome, char *nascimento, char *email, char *celular);
void remover_cliente_menu(char *cpf);
void alterar_saldo_menu(char *cpf, double valor);
void cadastrar_chave_pix_menu(char *cpf, char tipo);
void remover_chave_pix_menu(char *cpf, char tipo);
void transferir_menu(char *chave_pix_origem, char *chave_pix_destino, double valor);

/* Busca */
void buscar_cliente_cpf_menu(char *cpf);
void buscar_cliente_chave_pix_menu(char *chave_pix);
void buscar_transacao_cpf_origem_timestamp_menu(char *cpf, char *timestamp);

/* Listagem */
void listar_transacoes_periodo_menu(char *data_inicio, char *data_fim);
void listar_transacoes_cpf_origem_periodo_menu(char *cpf, char *data_inicio, char *data_fim);

/* Liberar espaço */
void liberar_espaco_menu();

/* Imprimir arquivos de dados */
void imprimir_arquivo_clientes_menu();
void imprimir_arquivo_transacoes_menu();

/* Imprimir arquivos de índice */
void imprimir_clientes_idx_menu();
void imprimir_transacoes_idx_menu();
void imprimir_chaves_pix_idx_menu();
void imprimir_timestamp_cpf_origem_idx_menu();

/* Liberar memória e encerrar programa */
void liberar_memoria_menu();

/* Funções de manipulação de Árvores-B */

/**
 * Responsável por inserir uma chave (k) em uma Árvore-B (T). Atualiza os parâmetros da Árvore-B conforme necessário.
 * <p>
 * A chave a ser inserida deve estar no formato correto e com tamanho t->tam_chave.
 * <p>
 * O funcionamento deve ser genérico para qualquer Árvore-B, considerando que os únicos parâmetros que se alteram entre
 * as árvores é o t->tam_chave.
 * <p>
 * Comportamento de acordo com as especificações do PDF sobre Árvores-B e suas operações.
 * <p>
 * Exemplo de uso:
 * <p>char cliente_str[TAM_CHAVE_CLIENTES_IDX + 1];
 * <p>sprintf(cliente_str, "%s%04d", cpf, rrn_cliente);
 * <p>btree_insert(cliente_str, &clientes_idx);
 *
 * @param chave Chave a ser inserida na Árvore-B.
 * @param t Ponteiro para o índice do tipo Árvore-B no qual será inserida a chave.
 */
void btree_insert(char *chave, btree *t);

/**
 * Função auxiliar de inserção de uma chave (k) em uma Árvore-B (T). Atualiza os parâmetros da Árvore-B conforme necessário.
 * <p>
 * Esta é uma função recursiva. Ela recebe o RRN do nó a ser trabalhado sobre.
 * <p>
 * Comportamento de acordo com as especificações do PDF sobre Árvores-B e suas operações.
 *
 * @param chave Chave a ser inserida na Árvore-B.
 * @param rrn RRN do nó no qual deverá ser processado.
 * @param t Ponteiro para o índice do tipo Árvore-B no qual será inserida a chave.
 * @return Retorna uma struct do tipo promovido_aux que contém a chave promovida e o RRN do filho direito.
 */
promovido_aux btree_insert_aux(char *chave, int rrn, btree *t);

/**
 * Função auxiliar para dividir um nó de uma Árvore-B (T). Atualiza os parâmetros conforme necessário.
 * <p>
 * Comportamento de acordo com as especificações do PDF sobre Árvores-B e suas operações.
 *
 * @param chave Chave a ser inserida na Árvore-B.
 * @param filho_direito RRN do filho direito.
 * @param rrn RRN do nó no qual deverá ser processado.
 * @param t Ponteiro para o índice do tipo Árvore-B no qual será inserida a chave.
 * @return Retorna uma struct do tipo promovido_aux que contém a chave promovida e o RRN do filho direito.
 */
promovido_aux btree_divide(char *chave, int filho_direito, int rrn, btree *t);

/**
 * Responsável por buscar uma chave (k) em uma Árvore-B (T). O valor de retorno indica se a chave foi encontrada ou não.
 * <p>
 * O ponteiro para a string result pode ser fornecido opcionalmente, e conterá o resultado encontrado.
 * <p>
 * Esta é uma função recursiva. O parâmetro rrn recebe a raíz da Árvore-B na primeira chamada, e nas chamadas
 * subsequentes é o RRN do filho de acordo com o algoritmo fornecido.
 * <p>
 * Comportamento de acordo com as especificações do PDF sobre Árvores-B e suas operações.
 * <p>
 * Exemplos de uso:
 * <p>
 * // Exemplo 1. A chave encontrada deverá ser retornada e o caminho não deve ser informado.
 * <p>char result[TAM_CHAVE_CLIENTES_IDX + 1];
 * <p>bool found = btree_search(result, false, cpf, clientes_idx.rrn_raiz, &clientes_idx);
 * <p>
 * // Exemplo 2. Não há interesse na chave encontrada, apenas se ela existe, e o caminho não deve ser informado.
 * <p>bool found = btree_search(NULL, false, cpf, clientes_idx.rrn_raiz, &clientes_idx);
 * <p>
 * // Exemplo 3. Busca por uma chave de tamanho variável (específico para o caso de buscas por chaves PIX).
 * <p>char chave_pix_str[TAM_MAX_CHAVE_PIX];
 * <p>strcpy(chave_pix_str, c.chaves_pix[i] + 1);
 * <p>strpadright(chave_pix_str, '#', TAM_MAX_CHAVE_PIX - 1);
 * <p>bool found = btree_search(NULL, false, chave_pix_str, chaves_pix_idx.rrn_raiz, &chaves_pix_idx);
 * <p>
 * // Exemplo 4. Há interesse no caminho feito para encontrar a chave.
 * <p>char result[TAM_CHAVE_CLIENTES_IDX + 1];
 * <p>printf(RRN_NOS);
 * <p>bool found = btree_search(result, true, cpf, clientes_idx.rrn_raiz, &clientes_idx);
 * <p>printf("&#92;n");
 *
 * @param result Ponteiro para ser escrita a chave encontrada. É ignorado caso NULL.
 * @param exibir_caminho Indica se o caminho percorrido deve ser impresso.
 * @param chave Chave a ser buscada na Árvore-B.
 * @param rrn RRN do nó no qual deverá ser processado. É o RRN da raíz da Árvore-B caso seja a primeira chamada.
 * @param t Ponteiro para o índice do tipo Árvore-B no qual será buscada a chave.
 * @return Indica se a chave foi encontrada.
 */
bool btree_search(char *result, bool exibir_caminho, char *chave, int rrn, btree *t);

/**
 * Função para percorrer uma Árvore-B (T) em ordem.
 * <p>
 * Os parâmetros chave_inicio e chave_fim podem ser fornecidos opcionalmente, e contém o intervalo do percurso.
 * <p>
 * Caso chave_inicio e chave_fim sejam NULL, o índice inteiro é percorrido.
 * <p>
 * Esta é uma função recursiva. O parâmetro rrn recebe a raíz da Árvore-B na primeira chamada, e nas chamadas
 * subsequentes é o RRN do filho de acordo com o algoritmo de percursão em ordem.
 * <p>
 * Exemplo de uso:
 * <p>
 * // Exemplo 1. Intervalo não especificado.
 * <p>bool imprimiu = btree_print_in_order(NULL, NULL, exibir_btree_cliente, clientes_idx.rrn_raiz, &clientes_idx);
 * <p>
 * // Exemplo 2. Imprime as transações contidas no intervalo especificado.
 * <p>bool imprimiu = btree_print_in_order(data_inicio, data_fim, exibir_btree_timestamp_cpf_origem, timestamp_cpf_origem_idx.rrn_raiz, &timestamp_cpf_origem_idx);
 *
 * @param chave_inicio Começo do intervalo. É ignorado caso NULL.
 * @param chave_fim Fim do intervalo. É ignorado caso NULL.
 * @param exibir Função utilizada para imprimir uma chave no índice. É informada a chave para a função.
 * @param rrn RRN do nó no qual deverá ser processado.
 * @param t Ponteiro para o índice do tipo Árvore-B no qual será inserida a chave.
 * @return Indica se alguma chave foi impressa.
 */
bool btree_print_in_order(char *chave_inicio, char *chave_fim, bool (*exibir)(char *chave), int rrn, btree *t);

/**
 * Função interna para ler um nó em uma Árvore-B (T).
 *
 * @param rrn RRN do nó a ser lido da Árvore-B.
 * @param t Árvore-B na qual será feita a leitura do nó.
 * @return Nó lido do RRN fornecido. Note que é necessário desalocá-lo após o uso por meio do btree_node_free.
 */
btree_node btree_read(int rrn, btree *t);

/**
 * Função interna para escrever um nó em uma Árvore-B (T).
 *
 * @param no No a ser escrito na Árvore-B.
 * @param t Árvore-B na qual será feita a escrita do nó.
 */
void btree_write(btree_node no, btree *t);

/**
 * Função interna para alocar o espaço necessário dos campos chaves (vetor de strings) e filhos (vetor de inteiros) da struct btree_node.
 *
 * @param t Árvore-B base para o qual será alocado um struct btree_node.
 * @return Nó com os campos devidamente alocados.
 */
btree_node btree_node_malloc(btree *t);

/**
 * Função interna para liberar o espaço alocado dos campos chaves (vetor de strings) e filhos (vetor de inteiros) da struct btree_node.
 *
 * @param t Árvore-B base para o qual será liberado o espaço alocado para um struct btree_node.
 */
void btree_node_free(btree_node no);

/**
 * Preenche uma string str com o caractere pad para completar o tamanho size.
 *
 * @param str Ponteiro para a string a ser manipulada.
 * @param pad Caractere utilizado para fazer o preenchimento à direita.
 * @param size Tamanho desejado para a string.
 * @return Retorna o próprio parâmetro str. Útil para encadeamento de funções.
 */
char* strpadright(char *str, char pad, unsigned size);

/**
 * Responsável por inserir uma chave em uma tabela hash (ht).
 * <p>
 * Exemplo de uso:
 * <p>clientes_idx_struct cliente;
 * <p>strcpy(cliente.cpf, cpf);
 * <p>cliente.rrn = rrn_cliente;
 * <p>hash_insert(&cliente_str, &clientes_idx);
 *
 * @param chave Chave a ser inserida na tabela hash.
 * @param t Ponteiro para o índice do tipo tabela hash no qual será inserida a chave.
 * @return Indica se houve redimensionamento. Útil para parar a função de criar índice.
 */
bool hash_insert(void *chave, hash *ht);

/**
 * Responsável por buscar uma chave em uma tabela hash (ht).
 * <p>
 * Funciona de forma similar ao btree_search.
 * <p>
 * Exemplo de uso:
 * <p>clientes_idx_struct cliente_search;
 * <p>clientes_idx_struct cliente_result;
 * <p>strcpy(cliente_search.cpf, cpf);
 * <p>hash_search(&cliente_result, false, &cliente_search, &clientes_idx);
 *
 * @param result Ponteiro para ser escrita a chave encontrada. É ignorado caso NULL.
 * @param exibir_caminho Indica se o caminho percorrido deve ser impresso.
 * @param chave Chave a ser encontrada na tabela hash.
 * @param ht Ponteiro para a tabela hash na qual a busca será feita.
 * @return Indica se a chave foi encontrada.
 */
bool hash_search(void *result, bool exibir_caminho, void *chave, hash *ht);

/**
 * Responsável por remover uma chave de uma tabela hash (ht).
 * <p>
 * Exemplo de uso:
 * <p>clientes_idx_struct cliente_remove;
 * <p>strcpy(cliente_remove.cpf, cpf);
 * <p>hash_remove(&cliente_remove, &clientes_idx);
 *
 * @param chave Chave a ser removida da tabela hash.
 * @param ht Ponteiro para a tabela hash na qual a remoção será feita.
 * @return Indica se a chave foi encontrada e removida.
 */
bool hash_delete(void *chave, hash *ht);

/**
 * Responsável por redimensionar uma tabela hash (ht).
 * <p>
 * A tabela hash deve ser realocada (hash_free) e reconstruída (vide ht->create_idx) utilizando
 * o próximo primo (vide next_prime), que deve ser maior que o dobro do tamanho atual da tabela.
 *
 * @param ht Ponteiro para a tabela hash na qual o redimensionamento será feito.
 */
void hash_resize(hash *ht);

/**
 * Responsável por liberar a memória de uma tabela hash (ht).
 *
 * @param ht Ponteiro para a tabela hash a qual será liberada a memória.
 */
void hash_free(hash *ht);

/* Procura o próximo primo depois ou igual a p */
unsigned next_prime(unsigned p) {
    if (p % 2 == 0)
        p++;

    for (int i = 3; i <= sqrt(p); i += 2) {
        if (p % i == 0) {
            p += 2;
            i = 1;
        }
    }

    return p;
}

/**
 * Calcula A elevado a B em complexidade de tempo O(log n).
 * <p>
 * A função pow em math.h possui resultados ligeiramente diferentes
 * entre arquiteturas além de não trabalhar com inteiros.
 * <p>
 * Baseado em https://www.geeksforgeeks.org/write-a-c-program-to-calculate-powxn/
 *
 * @param a, b Parâmetros da potenciação.
 * @return Resultado de a^b.
 */
uint64_t pow_uint64(uint64_t a, uint64_t b) {
    if (b == 0) return 1;

    uint64_t temp = pow_uint64(a, b / 2);

    if ((b % 2) == 0) return temp * temp;
    else return a * temp * temp;
}

/* <<< COLOQUE AQUI OS DEMAIS PROTÓTIPOS DE FUNÇÕES, SE NECESSÁRIO >>> */
bool alterar_saldoSemOK(char *cpf, double valor);
int proxCampoArquivo(int indiceAtual, char delimiter, int quant);
/* ==========================================================================
 * ============================ FUNÇÃO PRINCIPAL ============================
 * =============================== NÃO ALTERAR ============================== */

int main() {
    // variáveis utilizadas pelo interpretador de comandos
    char input[500];
    bool debug_mode = true;
    uint64_t seed = 2;
    uint64_t time = 1616077800; // UTC 18/03/2021 14:30:00
    char cpf[TAM_CPF];
    char nome[TAM_MAX_NOME];
    char nascimento[TAM_NASCIMENTO];
    char email[TAM_MAX_EMAIL];
    char celular[TAM_CELULAR];
    double valor;
    char tipo_chave_pix;
    char chave_pix_origem[TAM_MAX_CHAVE_PIX];
    char chave_pix_destino[TAM_MAX_CHAVE_PIX];
    char chave_pix[TAM_MAX_CHAVE_PIX];
    char timestamp[TAM_TIMESTAMP];
    char data_inicio[TAM_TIMESTAMP];
    char data_fim[TAM_TIMESTAMP];

    scanf("SET HASH_CLIENTES_IDX_ORDER %d;\n", &clientes_idx.table_size);
    scanf("SET HASH_CHAVES_PIX_IDX_ORDER %d;\n", &chaves_pix_idx.table_size);
    scanf("SET BTREE_ORDER %d;\n", &btree_order);

    scanf("SET ARQUIVO_CLIENTES '%[^\n]\n", ARQUIVO_CLIENTES);
    int temp_len = strlen(ARQUIVO_CLIENTES);
    if (temp_len < 2) temp_len = 2; // corrige o tamanho caso a entrada seja omitida
    qtd_registros_clientes = (temp_len - 2) / TAM_REGISTRO_CLIENTE;
    ARQUIVO_CLIENTES[temp_len - 2] = '\0';

    scanf("SET ARQUIVO_TRANSACOES '%[^\n]\n", ARQUIVO_TRANSACOES);
    temp_len = strlen(ARQUIVO_TRANSACOES);
    if (temp_len < 2) temp_len = 2; // corrige o tamanho caso a entrada seja omitida
    qtd_registros_transacoes = (temp_len - 2) / TAM_REGISTRO_TRANSACAO;
    ARQUIVO_TRANSACOES[temp_len - 2] = '\0';

    // inicialização do gerador de números aleatórios e função de datas
    prng_srand(seed);
    set_time(time);

    criar_clientes_idx();
    criar_transacoes_idx();
    criar_chaves_pix_idx();
    criar_timestamp_cpf_origem_idx();

    while (1) {
        fgets(input, 500, stdin);
        if (debug_mode)
            printf("%s", input);

        clear_input(input);

        if (strcmp("", input) == 0)
            continue; // não avança o tempo nem imprime o comando este seja em branco

        /* Funções principais */
        if (sscanf(input, "INSERT INTO clientes VALUES ('%[^']', '%[^']', '%[^']', '%[^']', '%[^']');", cpf, nome, nascimento, email, celular) == 5)
            cadastrar_cliente_menu(cpf, nome, nascimento, email, celular);
        else if (sscanf(input, "DELETE FROM clientes WHERE cpf = '%[^']';", cpf) == 1)
            remover_cliente_menu(cpf);
        else if (sscanf(input, "UPDATE clientes SET saldo = saldo + %lf WHERE cpf = '%[^']';", &valor, cpf) == 2)
            alterar_saldo_menu(cpf, valor);
        else if (sscanf(input, "UPDATE clientes SET chaves_pix = array_append(chaves_pix, '%c') WHERE cpf = '%[^']';", &tipo_chave_pix, cpf) == 2)
            cadastrar_chave_pix_menu(cpf, tipo_chave_pix);
        else if (sscanf(input, "UPDATE clientes SET chaves_pix = array_remove('%c', chaves_pix) WHERE cpf = '%[^']';", &tipo_chave_pix, cpf) == 2)
            remover_chave_pix_menu(cpf, tipo_chave_pix);
        else if (sscanf(input, "INSERT INTO transacoes VALUES ('%[^']', '%[^']', %lf);", chave_pix_origem, chave_pix_destino, &valor) == 3)
            transferir_menu(chave_pix_origem, chave_pix_destino, valor);

        /* Busca */
        else if (sscanf(input, "SELECT * FROM clientes WHERE cpf = '%[^']';", cpf) == 1)
            buscar_cliente_cpf_menu(cpf);
        else if (sscanf(input, "SELECT * FROM clientes WHERE '%[^']' = ANY (chaves_pix);", chave_pix) == 1)
            buscar_cliente_chave_pix_menu(chave_pix);
        else if (sscanf(input, "SELECT * FROM transacoes WHERE cpf_origem = '%[^']' AND timestamp = '%[^']';", cpf, timestamp) == 2)
            buscar_transacao_cpf_origem_timestamp_menu(cpf, timestamp);

        /* Listagem */
        else if (sscanf(input, "SELECT * FROM transacoes WHERE timestamp BETWEEN '%[^']' AND '%[^']' ORDER BY timestamp ASC;", data_inicio, data_fim) == 2)
            listar_transacoes_periodo_menu(data_inicio, data_fim);
        else if (sscanf(input, "SELECT * FROM transacoes WHERE cpf_origem = '%[^']' AND timestamp BETWEEN '%[^']' AND '%[^']' ORDER BY timestamp ASC;", cpf, data_inicio, data_fim) == 3)
            listar_transacoes_cpf_origem_periodo_menu(cpf, data_inicio, data_fim);

        /* Imprimir arquivos de dados */
        else if (strcmp("\\echo file ARQUIVO_CLIENTES", input) == 0)
            imprimir_arquivo_clientes_menu();
        else if (strcmp("\\echo file ARQUIVO_TRANSACOES", input) == 0)
            imprimir_arquivo_transacoes_menu();

        /* Liberar espaço */
        else if (strcmp("VACUUM clientes;", input) == 0)
            liberar_espaco_menu();

        /* Imprimir arquivos de índice */
        else if (strcmp("\\echo index clientes_idx", input) == 0)
            imprimir_clientes_idx_menu();
        else if (strcmp("\\echo index transacoes_idx", input) == 0)
            imprimir_transacoes_idx_menu();
        else if (strcmp("\\echo index chaves_pix_idx", input) == 0)
            imprimir_chaves_pix_idx_menu();
        else if (strcmp("\\echo index timestamp_cpf_origem_idx", input) == 0)
            imprimir_timestamp_cpf_origem_idx_menu();

        /* Liberar memória e encerrar programa */
        else if (strcmp("\\q", input) == 0)
            { liberar_memoria_menu(); return 0; }
        else if (sscanf(input, "SET SRAND %lu;", &seed) == 1)
            { prng_srand(seed); printf(SUCESSO); continue; }
        else if (sscanf(input, "SET TIME %lu;", &time) == 1)
            { set_time(time); printf(SUCESSO); continue; }
        else if (sscanf(input, "SET DEBUG_MODE %d;", &debug_mode) == 1)
            { printf(SUCESSO); continue; }
        else
            printf(ERRO_OPCAO_INVALIDA);

        tick_time();
    }
}

/* (Re)cria o índice primário clientes_idx */
void criar_clientes_idx() {
    if (!clientes_idx.tabela)
        clientes_idx.tabela = malloc(clientes_idx.table_size * sizeof(hash_node*));

    if (!clientes_idx.tabela) {
        printf(ERRO_MEMORIA_INSUFICIENTE);
        exit(1);
    }

    for (unsigned i = 0; i < clientes_idx.table_size; ++i)
        clientes_idx.tabela[i] = NULL;

    for (unsigned i = 0; i < qtd_registros_clientes; ++i) {
        Cliente c = recuperar_registro_cliente(i);

        if(c.this_rrn != -1){


            clientes_idx_struct* cliente = malloc(sizeof(clientes_idx_struct));

            strcpy(cliente->cpf, c.cpf);

            cliente->rrn = c.this_rrn;

            if(hash_insert(cliente, &clientes_idx)){
                break;
            }


        }

    }

}

/* Cria o índice primário transacoes_idx */
void criar_transacoes_idx() {
    char transacao_str[TAM_CHAVE_TRANSACOES_IDX + 1];
    for (unsigned i = 0; i < qtd_registros_transacoes; ++i) {
        Transacao t = recuperar_registro_transacao(i);

        sprintf(transacao_str, "%s%s%04d", t.cpf_origem, t.timestamp, i);
        btree_insert(transacao_str, &transacoes_idx);
    }
}

/* Cria o índice secundário chaves_pix_idx */
void criar_chaves_pix_idx() {

    char chavePixCPF[TAM_CHAVE_CHAVES_PIX_IDX + 1];
    int k = 0;

    if (!chaves_pix_idx.tabela)
        chaves_pix_idx.tabela = malloc(chaves_pix_idx.table_size * sizeof(hash_node*));

    if (!chaves_pix_idx.tabela) {
        printf(ERRO_MEMORIA_INSUFICIENTE);
        exit(1);
    }

    for (unsigned i = 0; i < chaves_pix_idx.table_size; ++i)
        chaves_pix_idx.tabela[i] = NULL;


    for (unsigned i = 0; i < qtd_registros_clientes; ++i) {

        Cliente c = recuperar_registro_cliente(i);
        

        for(int j = 0; j < 4; j++){
            if(c.chaves_pix[j][0] != '\0'){

                chaves_pix_idx_struct* chavePixCPF = malloc(sizeof(chaves_pix_idx_struct));

                strcpy(chavePixCPF->chave_pix, &c.chaves_pix[j][1]);
                strcpy(chavePixCPF->pk_cliente, c.cpf);


                if(hash_insert(chavePixCPF, &chaves_pix_idx)){
                    return;
                }
                
            }
        }

    }

}

/* Cria o índice secundário timestamp_cpf_origem_idx */
void criar_timestamp_cpf_origem_idx() {
    char timestamp_str[TAM_CHAVE_TRANSACOES_IDX + 1];
    for (unsigned i = 0; i < qtd_registros_transacoes; ++i) {
        Transacao t = recuperar_registro_transacao(i);

        sprintf(timestamp_str, "%s%s", t.timestamp, t.cpf_origem);
        btree_insert(timestamp_str, &timestamp_cpf_origem_idx);
    }
}

/* Exibe um cliente dado seu RRN */
bool exibir_cliente(int rrn) {
    if (rrn < 0)
        return 0;

    Cliente c = recuperar_registro_cliente(rrn);

    printf("%s, %s, %s, %s, %s, %.2lf, {", c.cpf, c.nome, c.nascimento, c.email, c.celular, c.saldo);

    int imprimiu = 0;
    for (int i = 0; i < QTD_MAX_CHAVES_PIX; ++i) {
        if (c.chaves_pix[i][0] != '\0') {
            if (imprimiu)
                printf(", ");
            printf("%s", c.chaves_pix[i]);
            imprimiu = 1;
        }
    }
    printf("}\n");

    return 1;
}

/* Exibe uma transação dada seu RRN */
bool exibir_transacao(int rrn) {
    if (rrn < 0)
        return 0;

    Transacao t = recuperar_registro_transacao(rrn);

    printf("%s, %s, %.2lf, %s\n", t.cpf_origem, t.cpf_destino, t.valor, t.timestamp);

    return 1;
}

bool exibir_btree_transacao(char *chave) {
    int rrn = atoi(chave + TAM_CHAVE_TRANSACOES_IDX - 4);
    return exibir_transacao(rrn);
}

bool exibir_btree_timestamp_cpf_origem(char *chave) {
    
    char CPFTimestamp[TAM_CHAVE_TIMESTAMP_CPF_ORIGEM_IDX + 1], result[TAM_CHAVE_TRANSACOES_IDX + 1];

    strncpy(CPFTimestamp, &chave[TAM_TIMESTAMP-1], TAM_CPF-1);

    strncpy(&CPFTimestamp[TAM_CPF-1], chave, TAM_TIMESTAMP-1);
    CPFTimestamp[TAM_CHAVE_TIMESTAMP_CPF_ORIGEM_IDX] = '\0';


    if(!btree_search(result, false, CPFTimestamp, transacoes_idx.rrn_raiz, &transacoes_idx)){
        return false;
    }

    int rrn = atoi(&result[TAM_CHAVE_TRANSACOES_IDX - 4]);
    return exibir_transacao(rrn);

}

/* Recupera do arquivo de clientes o registro com o RRN
 * informado e retorna os dados na struct Cliente */
Cliente recuperar_registro_cliente(int rrn) {
    Cliente c;
    c.this_rrn = rrn;

    char temp[TAM_REGISTRO_CLIENTE + 1], *p;
    strncpy(temp, ARQUIVO_CLIENTES + (rrn * TAM_REGISTRO_CLIENTE), TAM_REGISTRO_CLIENTE);
    temp[TAM_REGISTRO_CLIENTE] = '\0';

    if (strncmp(temp, "*|", 2) == 0)
        return (Cliente){ .this_rrn = -1 };

    p = strtok(temp, ";");
    strcpy(c.cpf, p);
    p = strtok(NULL, ";");
    strcpy(c.nome, p);
    p = strtok(NULL, ";");
    strcpy(c.nascimento, p);
    p = strtok(NULL, ";");
    strcpy(c.email, p);
    p = strtok(NULL, ";");
    strcpy(c.celular, p);
    p = strtok(NULL, ";");
    c.saldo = atof(p);
    p = strtok(NULL, ";");

    for(int i = 0; i < QTD_MAX_CHAVES_PIX; ++i)
        c.chaves_pix[i][0] = '\0';

    if(p[0] != '#') {
        p = strtok(p, "&");

        for(int pos = 0; p; p = strtok(NULL, "&"), ++pos)
            strcpy(c.chaves_pix[pos], p);
    }

    return c;
}

/* Recupera do arquivo de transações o registro com o RRN
 * informado e retorna os dados na struct Transacao */
Transacao recuperar_registro_transacao(int rrn) {

    Transacao t;
    char temp[TAM_REGISTRO_TRANSACAO + 1];
    strncpy(temp, ARQUIVO_TRANSACOES + (rrn * TAM_REGISTRO_TRANSACAO), TAM_REGISTRO_TRANSACAO);
    temp[TAM_REGISTRO_TRANSACAO] = '\0';
    
    char valorChar[TAM_SALDO + 1];

    strncpy(t.cpf_origem, temp, TAM_CPF-1);
    t.cpf_origem[TAM_CPF-1] = '\0';

    strncpy(t.cpf_destino, temp+TAM_CPF-1, TAM_CPF-1);
    t.cpf_destino[TAM_CPF-1] = '\0';

    strncpy(valorChar, temp + 2*(TAM_CPF -1), TAM_SALDO);
    t.valor = atof(valorChar);

    strncpy(t.timestamp, temp+2*(TAM_CPF -1)+TAM_SALDO-1, TAM_TIMESTAMP-1);
    t.timestamp[TAM_TIMESTAMP-1] = '\0';

    return t;

}

/* Escreve no arquivo de clientes na posição informada (RRN)
 * os dados na struct Cliente */
void escrever_registro_cliente(Cliente c) {

    int tamNome, tamEmail, tamSobrando, k = 0;
    int rrn = c.this_rrn;

    char saldoChar[TAM_SALDO], chavesPix[TAM_MAX_CHAVE_PIX*4];
    chavesPix[0] = '\0';

    sprintf(saldoChar, "%013.2lf", c.saldo);


    // da pra substituir por proxCampoArquivo()
    //pega tamanho
    for(tamNome = 0; tamNome < TAM_MAX_NOME; tamNome++){
        if(c.nome[tamNome] == '\0')
            break;
    }

    for(tamEmail = 0; tamEmail < TAM_MAX_EMAIL; tamEmail++){
        if(c.email[tamEmail] == '\0')
            break;
    }



    //arquivo

    strncpy(&ARQUIVO_CLIENTES[rrn*TAM_REGISTRO_CLIENTE], c.cpf, TAM_CPF-1);
    strncpy(&ARQUIVO_CLIENTES[rrn*TAM_REGISTRO_CLIENTE + TAM_CPF - 1], ";", 1);

    strncpy(&ARQUIVO_CLIENTES[rrn*TAM_REGISTRO_CLIENTE + TAM_CPF], c.nome, tamNome + 1);
    strncpy(&ARQUIVO_CLIENTES[rrn*TAM_REGISTRO_CLIENTE + TAM_CPF + tamNome], ";", 1);

    strncpy(&ARQUIVO_CLIENTES[rrn*TAM_REGISTRO_CLIENTE + TAM_CPF + tamNome + 1], c.nascimento, TAM_NASCIMENTO - 1);
    strncpy(&ARQUIVO_CLIENTES[rrn*TAM_REGISTRO_CLIENTE + TAM_CPF + tamNome + 1 + TAM_NASCIMENTO - 1], ";", 1);

    strncpy(&ARQUIVO_CLIENTES[rrn*TAM_REGISTRO_CLIENTE + TAM_CPF + tamNome + 1 + TAM_NASCIMENTO], c.email, tamEmail);
    strncpy(&ARQUIVO_CLIENTES[rrn*TAM_REGISTRO_CLIENTE + TAM_CPF + tamNome + 1 + TAM_NASCIMENTO + tamEmail], ";", 1);
    
    strncpy(&ARQUIVO_CLIENTES[rrn*TAM_REGISTRO_CLIENTE + TAM_CPF + tamNome + 1 + TAM_NASCIMENTO + tamEmail + 1], c.celular, TAM_CELULAR);
    strncpy(&ARQUIVO_CLIENTES[rrn*TAM_REGISTRO_CLIENTE + TAM_CPF + tamNome + 1 + TAM_NASCIMENTO + tamEmail + 1 + TAM_CELULAR - 1], ";", 1);
    
    strncpy(&ARQUIVO_CLIENTES[rrn*TAM_REGISTRO_CLIENTE + TAM_CPF + tamNome + 1 + TAM_NASCIMENTO + tamEmail + 1 + TAM_CELULAR], saldoChar, TAM_SALDO);
    strncpy(&ARQUIVO_CLIENTES[rrn*TAM_REGISTRO_CLIENTE + TAM_CPF + tamNome + 1 + TAM_NASCIMENTO + tamEmail + 1 + TAM_CELULAR + TAM_SALDO - 1], ";", 1);

    
    
    //pega chaves pix da struct e conta tamanho
    for(int i = 0; i < 4; i++){
        if(c.chaves_pix[i][0] != '\0'){
            if(i > 0)
                ARQUIVO_CLIENTES[rrn*TAM_REGISTRO_CLIENTE + TAM_CPF + tamNome + 1 + TAM_NASCIMENTO + tamEmail + 1 + TAM_CELULAR + TAM_SALDO + k++] = '&';

            for(int j = 0; j < TAM_MAX_CHAVE_PIX; j++){
                if(c.chaves_pix[i][j] == '\0')
                    break;

                ARQUIVO_CLIENTES[rrn*TAM_REGISTRO_CLIENTE + TAM_CPF + tamNome + 1 + TAM_NASCIMENTO + tamEmail + 1 + TAM_CELULAR + TAM_SALDO + k++] = c.chaves_pix[i][j];
            }
        }
    }

    ARQUIVO_CLIENTES[rrn*TAM_REGISTRO_CLIENTE + TAM_CPF + tamNome + 1 + TAM_NASCIMENTO + tamEmail + 1 + TAM_CELULAR + TAM_SALDO + k] = ';';


    tamSobrando = TAM_REGISTRO_CLIENTE - (TAM_CPF + tamNome + 1 + TAM_NASCIMENTO + tamEmail + 1 + TAM_CELULAR + 1 + TAM_SALDO + 1 + k) + 1;


    // aqui estava usando strcat antes, dentro do mesmo for. Isso causava uma demora enorme para processar o input 10, pois o strcat procura pelo '\0' toda vez, e não precisa sendo que
    // eu já sei onde está o '\0'
    for(int i = 0; i < tamSobrando; i++){
        ARQUIVO_CLIENTES[rrn*TAM_REGISTRO_CLIENTE + TAM_CPF + tamNome + 1 + TAM_NASCIMENTO + tamEmail + 1 + TAM_CELULAR + TAM_SALDO + k + 1 + i] = '#';
    }


    ARQUIVO_CLIENTES[(rrn+1)*TAM_REGISTRO_CLIENTE] = '\0';
}

/* Escreve no arquivo de transações na posição informada (RRN)
 * os dados na struct Transacao */
void escrever_registro_transacao(Transacao t) {

    char valorChar[TAM_SALDO];
    
    sprintf(valorChar, "%013.2lf", t.valor);
    
    strncpy(&ARQUIVO_CLIENTES[t.this_rrn*TAM_REGISTRO_CLIENTE], t.cpf_origem, TAM_CPF - 1);

    strncpy(&ARQUIVO_CLIENTES[t.this_rrn*TAM_REGISTRO_CLIENTE + TAM_CPF - 1], t.cpf_destino, TAM_CPF - 1);

    strncpy(&ARQUIVO_CLIENTES[t.this_rrn*TAM_REGISTRO_CLIENTE + TAM_CPF - 1 + TAM_CPF - 1], valorChar, TAM_SALDO - 1);

    strncpy(&ARQUIVO_CLIENTES[t.this_rrn*TAM_REGISTRO_CLIENTE + TAM_CPF - 1 + TAM_CPF - 1 + TAM_SALDO - 1], t.timestamp, TAM_TIMESTAMP - 1);

}

/* Funções principais */
void cadastrar_cliente_menu(char *cpf, char *nome, char *nascimento, char *email, char *celular) {

    if(clientes_idx.qtd_insercoes > 0 && hash_search(NULL, false, cpf, &clientes_idx)){
        printf(ERRO_PK_REPETIDA, cpf);
        return;
    }

    Cliente c;
    strcpy(c.cpf, cpf);
    strcpy(c.nome, nome);
    strcpy(c.nascimento, nascimento);
    strcpy(c.email, email);
    strcpy(c.celular, celular);
    c.saldo = 0;
    c.this_rrn = qtd_registros_clientes;

    //chave pix
    for(int i = 0; i < 4; i++){
        c.chaves_pix[i][0] = '\0';
    }

    //arquivo
    escrever_registro_cliente(c);
    qtd_registros_clientes++;


    //indice hash
    if (!clientes_idx.tabela)
        criar_clientes_idx();


    clientes_idx_struct* cliente = malloc(sizeof(clientes_idx_struct));


    strcpy(cliente->cpf, cpf);
    cliente->rrn = c.this_rrn;


    hash_insert(cliente, &clientes_idx);


    printf(SUCESSO);

}

void remover_cliente_menu(char *cpf) {

    unsigned index = clientes_idx.hash_function(cpf, clientes_idx.table_size);

    int i = index;

    bool encontrado = false;

    while( clientes_idx.tabela[i] != NULL ){


        if( clientes_idx.tabela[i]->data != NULL && clientes_idx.compar( clientes_idx.tabela[i]->data, cpf) == 0){
            //achou
            encontrado = true;
            break;
        }

        
        if(i == clientes_idx.table_size - 1){
            i = 0;
        }
        else{
            i++;
        }

        if( i == index){
            break;
        }

    }


    if(encontrado == false){
        printf(ERRO_REGISTRO_NAO_ENCONTRADO);
        return;
    }


    int rrn = ((clientes_idx_struct*)clientes_idx.tabela[i]->data)->rrn;


    //recupera o registro antes de deletar
    Cliente c = recuperar_registro_cliente(rrn);


    // *| no cpf
    strncpy(&ARQUIVO_CLIENTES[rrn * TAM_REGISTRO_CLIENTE], "*|", 2);


    //deleta o cliente da tabela hash
    clientes_idx.tabela[i]->state = deleted_node;
    free(clientes_idx.tabela[i]->data);
    clientes_idx.tabela[i]->data = NULL;

    

    //deleta chaves pix

    for(int j = 0; j < 4; j++){

        index = chaves_pix_idx.hash_function(c.chaves_pix[j], chaves_pix_idx.table_size);

        encontrado = false;

        hash_node* aux = chaves_pix_idx.tabela[index];

        while(aux != NULL && aux->data != NULL && encontrado == false){

            if(chaves_pix_idx.compar( aux->data, c.chaves_pix[j]) == 0){

                //achou, deletar
                free(aux->data);
                aux->data = NULL;

                while(aux->next != NULL){
                    *aux = *aux->next;
                    aux = aux->next;
                }

                encontrado = true;
                
            }

            aux = aux->next;

        }

    }
    
    
    printf(SUCESSO);
}

void alterar_saldo_menu(char *cpf, double valor) {

    if(alterar_saldoSemOK(cpf, valor)){
        printf(SUCESSO);
    }

}

void cadastrar_chave_pix_menu(char *cpf, char tipo) {

    char chavepix[TAM_MAX_CHAVE_PIX];
    char aleatorio[37];
    clientes_idx_struct CPF;

    int insereEm, length = 0, remover = 0;
    int i = 0, rrn = 0;

    chavepix[0] = '\0';
    aleatorio[0] = '\0';



    //hash search
    if(!hash_search(&CPF, false, cpf, &clientes_idx)){
        printf(ERRO_REGISTRO_NAO_ENCONTRADO);
        return;
    }


    //pega rrn
    rrn = CPF.rrn;

    Cliente C = recuperar_registro_cliente(rrn);


    for(i = 0; i < 4; i++){
        if(C.chaves_pix[i][0] == tipo){
            printf(ERRO_CHAVE_PIX_DUPLICADA, tipo);
            return;
        }
    }

    
    ///////////////////////////////////////////////////////////////// arquivo

    if(C.chaves_pix[0][0] != '\0'){
        strcat(chavepix, "&");
        length = 1;
        remover = 1;
    }

    if(tipo == 'C'){
        strcat(chavepix, "C");
        strcat(chavepix, cpf);
        length = length + TAM_CPF;
        remover = remover + 1;
    }
    else if(tipo == 'N'){
        strcat(chavepix, "N");
        strcat(chavepix, C.celular);
        length = length + TAM_CELULAR;
        remover = remover + 1;
    }
    else if(tipo == 'E'){
        strcat(chavepix, "E");
        strcat(chavepix, C.email);

        for(i = 0; i < TAM_MAX_EMAIL; i++){
            if(chavepix[i] == '\0'){
                break;
            }
        }

        length = i;
        remover = remover + 1;
    }
    else if(tipo == 'A'){
        strcat(chavepix, "A");
        new_uuid(aleatorio);
        strcat(chavepix, aleatorio);
        length = length + 37;
        remover = remover + 1;
    }
    else{
        printf(ERRO_TIPO_PIX_INVALIDO, tipo);
        return;
    }

    
    if(hash_search(NULL, false, &chavepix[remover], &chaves_pix_idx)){
        printf(ERRO_CHAVE_PIX_REPETIDA, &chavepix[remover]);
        return;
    }



    insereEm = (rrn * TAM_REGISTRO_CLIENTE) + TAM_CPF;

    //pula nome variavel
    insereEm = proxCampoArquivo(insereEm, ';', TAM_MAX_NOME);

    insereEm = insereEm + TAM_NASCIMENTO;

    //pula email variavel
    insereEm = proxCampoArquivo(insereEm, ';', TAM_MAX_EMAIL);

    insereEm = insereEm + TAM_CELULAR;

    insereEm = proxCampoArquivo(insereEm, ';', TAM_SALDO);

    //pula chave pix
    insereEm = proxCampoArquivo(insereEm, ';', TAM_MAX_CHAVE_PIX*4) - 1;

    strncpy(&ARQUIVO_CLIENTES[insereEm], chavepix, length);
    strncpy(&ARQUIVO_CLIENTES[insereEm+length], ";", 1);


    /////////////////////////////////////////////////////////// indice

    if (!chaves_pix_idx.tabela)
        criar_chaves_pix_idx();

    chaves_pix_idx_struct* chavePixCPF = malloc(sizeof(chaves_pix_idx_struct));


    strcpy(chavePixCPF->chave_pix, &chavepix[remover]);
    strcpy(chavePixCPF->pk_cliente, C.cpf);


    hash_insert(chavePixCPF, &chaves_pix_idx);


    printf(SUCESSO);
}

void remover_chave_pix_menu(char *cpf, char tipo) {
    
    clientes_idx_struct CPF;
    bool achou = false;
    int i = 0;
    int insereEm = 0;
    int tamChave = 0;
    int copyLength = 0;
    int source = 0;
    int remover = 1;


    if(!hash_search(&CPF, false, cpf, &clientes_idx)){
        printf(ERRO_REGISTRO_NAO_ENCONTRADO);
        return;
    }


    Cliente cliente = recuperar_registro_cliente(CPF.rrn);

    //procura chave pix a ser removida
    for(i = 0; i < 4; i++){
        if(cliente.chaves_pix[i][0] == tipo){
            achou = true;
            break;
        }
    }


    if(!achou){
        printf(ERRO_REGISTRO_NAO_ENCONTRADO);
        return;
    }


    //remover do arquivo


    //pega o tamanho da chavepix
    for(tamChave = 0; tamChave < TAM_MAX_CHAVE_PIX; tamChave++){
        if(cliente.chaves_pix[i][tamChave] == '\0'){
            break;
        }
    }
    
    
    insereEm = (CPF.rrn * TAM_REGISTRO_CLIENTE) + TAM_CPF;

    //pula nome variavel
    insereEm = proxCampoArquivo(insereEm, ';', TAM_MAX_NOME);

    insereEm = insereEm + TAM_NASCIMENTO;

    //pula email variavel
    insereEm = proxCampoArquivo(insereEm, ';', TAM_MAX_EMAIL);

    insereEm = insereEm + TAM_CELULAR;

    insereEm = insereEm + TAM_SALDO;


    while(ARQUIVO_CLIENTES[insereEm] != tipo){
        insereEm = proxCampoArquivo(insereEm, '&', TAM_MAX_CHAVE_PIX);
    }


    if(!proxCampoArquivo(insereEm, '&', TAM_MAX_CHAVE_PIX)){
        source = proxCampoArquivo(insereEm, ';', TAM_MAX_CHAVE_PIX);
        remover = 0;
    }
    else{
        source = proxCampoArquivo(insereEm, '&', TAM_MAX_CHAVE_PIX);
    }


    copyLength = proxCampoArquivo(insereEm, ';', TAM_MAX_CHAVE_PIX*3) - insereEm - tamChave - remover;


    // copia as chaves pix de volta
    strncpy(&ARQUIVO_CLIENTES[insereEm], &ARQUIVO_CLIENTES[source], copyLength);

    // coloca os #
    for(int j = 0; j < tamChave + remover; j++){
        ARQUIVO_CLIENTES[insereEm + copyLength + j] = '#';
    }


    //remover do hash

    if(!hash_delete(&cliente.chaves_pix[i][1], &chaves_pix_idx)){
        printf(ERRO_REGISTRO_NAO_ENCONTRADO);
        return;
    }


    printf(SUCESSO);

}

void transferir_menu(char *chave_pix_origem, char *chave_pix_destino, double valor) {
    
    int i = 0, j = 0, k = 0, tamPixOrigem = 0, tamPixDestino = 0, rrnOrigem, rrnDestino;
    
    chaves_pix_idx_struct searchPixOrigem, searchPixDestino;
    clientes_idx_struct searchClienteOrigem, searchClienteDestino;
    

    //pega tamanho
    for(tamPixOrigem = 0; tamPixOrigem < TAM_MAX_CHAVE_PIX-1; tamPixOrigem++){
        if(chave_pix_origem[tamPixOrigem] == '\0')
            break;
    }
    

    //pega tamanho
    for(tamPixDestino = 0; tamPixDestino < TAM_MAX_CHAVE_PIX-1; tamPixDestino++){
        if(chave_pix_destino[tamPixDestino] == '\0')
            break;
    }


    // pesquisa na arvore de pix
    if(!hash_search(&searchPixOrigem, false, chave_pix_origem, &chaves_pix_idx) || !hash_search(&searchPixDestino, false, chave_pix_destino, &chaves_pix_idx)){
        printf(ERRO_CHAVE_PIX_INVALIDA);
        return;
    }


    // comparação para ver se as chaves pix pertencem ao mesmo cpf
    if(strcmp(searchPixOrigem.pk_cliente, searchPixDestino.pk_cliente) == 0){
        printf(ERRO_CHAVE_PIX_INVALIDA);
        return;
    }

    // pesquisa na arvore de cliente
    if(!hash_search(&searchClienteOrigem, false, searchPixOrigem.pk_cliente, &clientes_idx) || 
    !hash_search(&searchClienteDestino, false, searchPixDestino.pk_cliente, &clientes_idx) ){
        printf(ERRO_CHAVE_PIX_INVALIDA);
        return;
    }


    //pega o rrn do arquivo de cliente
    rrnOrigem = searchClienteOrigem.rrn;
    rrnDestino = searchClienteDestino.rrn;
  

    if(rrnOrigem == -1 || rrnDestino == -1){
        printf(ERRO_CHAVE_PIX_INVALIDA);
        return;
    }


    Cliente c1 = recuperar_registro_cliente(rrnOrigem);
    Cliente c2 = recuperar_registro_cliente(rrnDestino);


    if(valor > c1.saldo){
        printf(ERRO_SALDO_NAO_SUFICIENTE);
        return;
    }

    if(valor <= 0){
        printf(ERRO_VALOR_INVALIDO);
        return;
    }


    alterar_saldoSemOK( c1.cpf, -valor);
    alterar_saldoSemOK( c2.cpf, +valor);


    // cadastrar transacao no arquivo

    Transacao t;

    char timestamp[TAM_TIMESTAMP];
    char valorChar[TAM_SALDO + 1];
    int tam = sprintf(valorChar, "%013.2lf", valor);



    strcpy(t.cpf_origem, c1.cpf);
    strcpy(t.cpf_destino, c2.cpf);
    current_timestamp(timestamp);
    strcpy(t.timestamp, timestamp);


    
    strcat(ARQUIVO_TRANSACOES, t.cpf_origem);
    strcat(ARQUIVO_TRANSACOES, t.cpf_destino);
    strcat(ARQUIVO_TRANSACOES, valorChar);
    strcat(ARQUIVO_TRANSACOES, t.timestamp);


    // cadastrar transacao no indice de transacoes

    char transacao_str[TAM_CHAVE_TRANSACOES_IDX + 1];

    sprintf(transacao_str, "%s%s%04d", t.cpf_origem, t.timestamp, qtd_registros_transacoes);

    transacao_str[TAM_CHAVE_TRANSACOES_IDX] = '\0';

    btree_insert(transacao_str, &transacoes_idx);


    // cadastrar transacao no indice de timestamp
    
    char timestamp_str[TAM_CHAVE_TIMESTAMP_CPF_ORIGEM_IDX + 1];

    sprintf(timestamp_str, "%s%s", t.timestamp, t.cpf_origem);

    
    timestamp_str[TAM_CHAVE_TIMESTAMP_CPF_ORIGEM_IDX] = '\0';
    

    btree_insert(timestamp_str, &timestamp_cpf_origem_idx);


    qtd_registros_transacoes++;


    printf(SUCESSO);

}

/* Busca */
void buscar_cliente_cpf_menu(char *cpf) {
    
    clientes_idx_struct cliente;

    if(!hash_search(&cliente, true, cpf, &clientes_idx)){
        printf(ERRO_REGISTRO_NAO_ENCONTRADO);
        return;
    }

    exibir_cliente(cliente.rrn);

}

void buscar_cliente_chave_pix_menu(char *chave_pix) {
    
    chaves_pix_idx_struct cliente;

    if(!hash_search(&cliente, true, chave_pix, &chaves_pix_idx)){    
        printf(ERRO_REGISTRO_NAO_ENCONTRADO);
        return;
    }


    buscar_cliente_cpf_menu(cliente.pk_cliente);

}

void buscar_transacao_cpf_origem_timestamp_menu(char *cpf, char *timestamp) {

    //pesquisar nas transacoes
    char CPFTimestamp[TAM_CHAVE_TIMESTAMP_CPF_ORIGEM_IDX + 1], resultado[TAM_CHAVE_TRANSACOES_IDX + 1];

    strcpy(CPFTimestamp, cpf);
    CPFTimestamp[TAM_CPF-1] = '\0';
    
    strcat(CPFTimestamp, timestamp);
    CPFTimestamp[TAM_CHAVE_TIMESTAMP_CPF_ORIGEM_IDX] = '\0';


    if(!btree_search(resultado, true, CPFTimestamp, transacoes_idx.rrn_raiz, &transacoes_idx)){
        printf(ERRO_REGISTRO_NAO_ENCONTRADO);
        return;
    }


    int rrn = atoi(&resultado[TAM_CHAVE_TRANSACOES_IDX - 4]);
    return exibir_transacao(rrn);

}

/* Listagem */
void listar_transacoes_periodo_menu(char *data_inicio, char *data_fim) {
    
    if(strcmp(data_inicio, data_fim) > 0){
        printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
        return;
    }

    char chave_inicio[TAM_CHAVE_TIMESTAMP_CPF_ORIGEM_IDX + 1];
    char chave_fim[TAM_CHAVE_TIMESTAMP_CPF_ORIGEM_IDX + 1];


    strcpy(chave_inicio, data_inicio);
    
    for(int i = TAM_TIMESTAMP - 1; i < TAM_CHAVE_TIMESTAMP_CPF_ORIGEM_IDX; i++){
        chave_inicio[i] = '0';
    }

    chave_inicio[TAM_CHAVE_TIMESTAMP_CPF_ORIGEM_IDX] = '\0';



    strcpy(chave_fim, data_fim);
    
    for(int i = TAM_TIMESTAMP - 1; i < TAM_CHAVE_TIMESTAMP_CPF_ORIGEM_IDX; i++){
        chave_fim[i] = '9';
    }

    chave_fim[TAM_CHAVE_TIMESTAMP_CPF_ORIGEM_IDX] = '\0';

    if(!btree_print_in_order(data_inicio, data_fim, exibir_btree_timestamp_cpf_origem, timestamp_cpf_origem_idx.rrn_raiz, &timestamp_cpf_origem_idx)){
        printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
    }

}

void listar_transacoes_cpf_origem_periodo_menu(char *cpf, char *data_inicio, char *data_fim) {
    
    if(strcmp(data_inicio, data_fim) > 0){
        printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
        return;
    }


    char chave_inicio[TAM_CHAVE_TIMESTAMP_CPF_ORIGEM_IDX + 1];
    char chave_fim[TAM_CHAVE_TIMESTAMP_CPF_ORIGEM_IDX + 1];
    

    strcpy(chave_inicio, cpf);
    strcat(chave_inicio, data_inicio);

    strcpy(chave_fim, cpf);
    strcat(chave_fim, data_fim);


    if(!btree_print_in_order(chave_inicio, chave_fim, exibir_btree_transacao, transacoes_idx.rrn_raiz, &transacoes_idx)){
        printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
    }

}

/* Liberar espaço */
void liberar_espaco_menu() {

    for (unsigned i = 0; i < qtd_registros_clientes; ++i) {

        Cliente c1 = recuperar_registro_cliente(i);

        if (c1.this_rrn == -1){

            // arquivo
            if(ARQUIVO_CLIENTES[(i+1)*TAM_REGISTRO_CLIENTE] != '\0'){
                strncpy(ARQUIVO_CLIENTES + ((i) * TAM_REGISTRO_CLIENTE), ARQUIVO_CLIENTES + ((i+1) * TAM_REGISTRO_CLIENTE), (qtd_registros_clientes - i+1) * TAM_REGISTRO_CLIENTE);
                ARQUIVO_CLIENTES[((qtd_registros_clientes - 1) * TAM_REGISTRO_CLIENTE)] = '\0';
                qtd_registros_clientes--;
            }
            else{
                ARQUIVO_CLIENTES[((qtd_registros_clientes - 1) * TAM_REGISTRO_CLIENTE)] = '\0';
                qtd_registros_clientes--;
            }

            if(strncmp(&ARQUIVO_CLIENTES[(i)*TAM_REGISTRO_CLIENTE], "*|", 2) == 0){
                i--;
            }

        }

    }

    // indice
    hash_free(&clientes_idx);
    criar_clientes_idx();

    printf(SUCESSO);
    
}

/* Imprimir arquivos de dados */
void imprimir_arquivo_clientes_menu() {
    if (qtd_registros_clientes == 0)
        printf(ERRO_ARQUIVO_VAZIO);
    else
        printf("%s\n", ARQUIVO_CLIENTES);
}

void imprimir_arquivo_transacoes_menu() {
    if (qtd_registros_transacoes == 0)
        printf(ERRO_ARQUIVO_VAZIO);
    else
        printf("%s\n", ARQUIVO_TRANSACOES);
}

/* Imprimir índices */
void imprimir_clientes_idx_menu() {
    hash_node **tabela = clientes_idx.tabela;
    for (unsigned i = 0; i < clientes_idx.table_size; ++i) {
        printf("[%d]", i);
        if (tabela[i]) {
            if (tabela[i]->state == deleted_node)
                printf(" {DELETED}");
            else {
                clientes_idx_struct *data = tabela[i]->data;
                printf(" {%s, %04d}", data->cpf, data->rrn);
            }
        }
        printf("\n");
    }
}

void imprimir_transacoes_idx_menu() {
    if (transacoes_idx.qtd_nos == 0)
        printf(ERRO_ARQUIVO_VAZIO);
    else
        printf("%s\n", ARQUIVO_TRANSACOES_IDX);
}

void imprimir_chaves_pix_idx_menu() {
    hash_node **tabela = chaves_pix_idx.tabela;
    for (unsigned i = 0; i < chaves_pix_idx.table_size; ++i) {
        printf("[%d]", i);
        hash_node *node = tabela[i];
        while(node) {
            chaves_pix_idx_struct *data = node->data;
            printf(" {%s, %s}", data->chave_pix, data->pk_cliente);
            node = node->next;
        }
        printf("\n");
    }
}

void imprimir_timestamp_cpf_origem_idx_menu() {
    if (timestamp_cpf_origem_idx.qtd_nos == 0)
        printf(ERRO_ARQUIVO_VAZIO);
    else
        printf("%s\n", ARQUIVO_TIMESTAMP_CPF_ORIGEM_IDX);
}

/* Liberar memória e encerrar programa */
void liberar_memoria_menu() {
    
}

/* Função de comparação entre clientes_idx_struct do índice clientes_idx */
int order_clientes_idx(const void *key, const void *elem) {
    return strncmp(key, elem, TAM_CPF - 1);
}

/* Função de comparação entre chaves do índice transacoes_idx */
int order_transacoes_idx(const void *key, const void *elem) {
    if(strncmp(key, elem, TAM_CPF-1) == 0){
        return strncmp( &((char*) key)[TAM_CPF - 1], &((char*) elem)[TAM_CPF - 1], TAM_TIMESTAMP - 1);
    }

    return strncmp(key, elem, TAM_CPF - 1);
}

/* Função de comparação entre chaves_pix_idx_struct do índice chaves_pix_idx */
int order_chaves_pix_idx(const void *key, const void *elem) {
    return strncmp(key, elem, TAM_MAX_CHAVE_PIX - 1);
}

/* Função de comparação entre chaves do índice timestamp_cpf_origem_idx */
int order_timestamp_cpf_origem_idx(const void *key, const void *elem) {
    return strncmp(key, elem, strnlen(key, TAM_TIMESTAMP + TAM_CPF - 2));
}

void btree_insert(char *chave, btree *t) {

    btree_node no;

    if(t->rrn_raiz == -1){
        no = btree_node_malloc(t);
        no.folha = true;
        no.qtd_chaves = 1;
        no.this_rrn = 0;
        strncpy(no.chaves[0], chave, t->tam_chave);
        no.chaves[0][t->tam_chave] = '\0';
        
        btree_write(no, t);

        btree_node_free(no);

        t->qtd_nos = 1;
        t->rrn_raiz = 0;

    }
    else{

        promovido_aux noPromovido = btree_insert_aux(chave, t->rrn_raiz, t);

        if(noPromovido.chave_promovida[0] != '\0'){
            
            no = btree_node_malloc(t);
            no.folha = false;
            no.qtd_chaves = 1;
            strncpy(no.chaves[0], noPromovido.chave_promovida, t->tam_chave);
            no.chaves[0][t->tam_chave] = '\0';

            no.filhos[0] = t->rrn_raiz;
            
            t->rrn_raiz = t->qtd_nos;
            no.this_rrn = t->qtd_nos;

            no.filhos[1] = noPromovido.filho_direito;

            btree_write(no, t);

            btree_node_free(no);

            t->qtd_nos++;
            
        }

    }

}

promovido_aux btree_insert_aux(char *chave, int rrn, btree *t) {
    
    btree_node no = btree_read(rrn, t);

    promovido_aux noPromovido;
    noPromovido.chave_promovida[0] = '\0';
    noPromovido.filho_direito = -1;

    int i = 0;

    if(no.folha){
        if(no.qtd_chaves < (btree_order-1)){

            i = no.qtd_chaves-1;

            while(i >= 0 && t->compar(chave, no.chaves[i]) < 0 ){
                strcpy(no.chaves[i+1], no.chaves[i]);
                i--;
            }

            strcpy(no.chaves[i+1], chave);

            no.qtd_chaves++;

            btree_write(no, t);

            btree_node_free(no);

            noPromovido.chave_promovida[0] = '\0';
            noPromovido.filho_direito = -1;

            return noPromovido;
        
        }
        else{
            btree_node_free(no);
            return btree_divide(chave, -1, rrn, t);
        }
    }
    else{

        i = no.qtd_chaves-1;
        
        while(i >= 0 && t->compar(chave, no.chaves[i]) < 0)
            i--;

        i++;

        noPromovido = btree_insert_aux(chave, no.filhos[i], t);

        if(noPromovido.chave_promovida[0] != '\0'){
            strcpy(chave, noPromovido.chave_promovida);

            if(no.qtd_chaves < (btree_order-1)){
                i = no.qtd_chaves-1;

                while(i >= 0 && t->compar(chave, no.chaves[i]) < 0){
                    strcpy(no.chaves[i+1], no.chaves[i]);
                    no.filhos[i+2] = no.filhos[i+1];
                    i--;
                }


                strcpy(no.chaves[i+1], chave);
                no.filhos[i+2] = noPromovido.filho_direito;

                no.qtd_chaves++;

                btree_write(no, t);

                btree_node_free(no);

                noPromovido.chave_promovida[0] = '\0';
                noPromovido.filho_direito = -1;
                
                return noPromovido;

            }
            else{
                btree_node_free(no);
                return btree_divide(chave, noPromovido.filho_direito, rrn, t);
            }

        }
        else{

            btree_node_free(no);

            noPromovido.chave_promovida[0] = '\0';
            noPromovido.filho_direito = -1;
            
            return noPromovido;

        }

    }

}

promovido_aux btree_divide(char *chave, int filho_direito, int rrn, btree *t) {
    
    //no x:
    btree_node no = btree_read(rrn, t);

    int i = no.qtd_chaves-1;

    bool chaveAlocada = false;

    //no aux:
    btree_node aux =  btree_node_malloc(t);

    promovido_aux noPromovido;
    noPromovido.chave_promovida[0] = '\0';
    noPromovido.filho_direito = -1;

    aux.folha = no.folha;

    aux.qtd_chaves = (btree_order-1)/2;


    for(int j = aux.qtd_chaves - 1; j >= 0; j--){

        if(!chaveAlocada && t->compar(chave, no.chaves[i]) > 0){
            strcpy(aux.chaves[j], chave);
            aux.filhos[j+1] = filho_direito;
            chaveAlocada = true;
        }
        else{
            strcpy(aux.chaves[j], no.chaves[i]);
            aux.filhos[j+1] = no.filhos[i+1];
            i--;
        }

    }

    if(!chaveAlocada){
        while(i >= 0 && t->compar(chave, no.chaves[i]) < 0){
            strcpy(no.chaves[i+1], no.chaves[i]);
            no.filhos[i+2] = no.filhos[i+1];
            i--;
        }

        strcpy(no.chaves[i+1], chave);
        no.filhos[i+2] = filho_direito;
    }


    // codigo pdf
    strcpy(noPromovido.chave_promovida, no.chaves[(btree_order/2)]);
    aux.filhos[0] = no.filhos[(btree_order/2)+1];


    no.qtd_chaves = btree_order/2;

    aux.this_rrn = t->qtd_nos;
    noPromovido.filho_direito = aux.this_rrn;


    //escreve no
    btree_write(no, t);
    btree_write(aux, t);

    btree_node_free(no);
    btree_node_free(aux);

    t->qtd_nos++;

    return noPromovido;

}

bool btree_search(char *result, bool exibir_caminho, char *chave, int rrn, btree *t) {
    
    if(rrn == -1){
        printf("Nos percorridos:\n");
        return false;
    }


    btree_node no = btree_read(rrn, t);


    if(exibir_caminho == true){
        if(rrn == t->rrn_raiz){
            printf("Nos percorridos: %i", no.this_rrn);
        }
        else{
            printf(" %i", no.this_rrn);
        }
    }

    int i = 0;

    while(i < no.qtd_chaves && t->compar(chave, no.chaves[i]) > 0){
        i++;
    }

    if(i < no.qtd_chaves && t->compar(chave, no.chaves[i]) == 0){
        if(result != NULL){
            strcpy(result, no.chaves[i]);
        }

        if(exibir_caminho == true)
            printf("\n");


        btree_node_free(no);
        return true;
    }

    if(no.folha){
        
        if(exibir_caminho == true){
            printf("\n");
        }
        
        btree_node_free(no);
        return false;
    }
    else{

        //para conseguir desalocar o no

        bool var;
        
        if(btree_search(result, exibir_caminho, chave, no.filhos[i], t))
            var = true;
        else
            var = false;

        if(no.this_rrn == t->rrn_raiz)
            btree_node_free(no);

        
        return var;

    }

}

bool btree_print_in_order(char *chave_inicio, char *chave_fim, bool (*exibir)(char *chave), int rrn, btree *t) {
    
    bool imprimiu = 0;

    // se for nulo, atribui uma chave de comparacao zerada e uma chave "infinita"
    if(chave_inicio == NULL && chave_fim == NULL){

        chave_inicio = (char*) malloc(sizeof(char) * (t->tam_chave + 1));
        chave_fim = (char*) malloc(sizeof(char) * (t->tam_chave + 1));


        for(int i = 0; i < t->tam_chave; i++){
            chave_inicio[i] = '0';
        }
        chave_inicio[t->tam_chave] = '\0';


        for(int i = 0; i < t->tam_chave; i++){
            chave_fim[i] = '9';
        }
        chave_fim[t->tam_chave] = '\0';

    }




    btree_node no = btree_read(rrn, t);

    int i = 0;


    while(i < no.qtd_chaves && t->compar(no.chaves[i], chave_inicio) < 0){
        i++;
    }

    if(i < no.qtd_chaves && t->compar(no.chaves[i], chave_inicio) == 0){
        imprimiu = true;
        exibir(no.chaves[i++]);
    }


    if(no.folha){
        for(int j = i; j < no.qtd_chaves; j++){
            if(t->compar(no.chaves[j], chave_inicio) >= 0 && t->compar(chave_fim, no.chaves[j]) >= 0){
                imprimiu = true;
                exibir(no.chaves[j]);
            }
        }
        
    }
    else{

        if(btree_print_in_order(chave_inicio, chave_fim, exibir, no.filhos[i], t) && imprimiu == false){
            imprimiu = true;
        }

        if(i < no.qtd_chaves && t->compar(no.chaves[i], chave_inicio) >= 0 && t->compar(chave_fim, no.chaves[i]) >= 0 ){
            imprimiu = true;
            exibir(no.chaves[i]);
        }
    
        while(i < no.qtd_chaves && t->compar(no.chaves[i], chave_inicio) >= 0 && t->compar(chave_fim, no.chaves[i]) >= 0){
            
            i++;

            if(btree_print_in_order(chave_inicio, chave_fim, exibir, no.filhos[i], t) && imprimiu == false){
                imprimiu = true;
            }

            
            if(i < no.qtd_chaves && t->compar(no.chaves[i], chave_inicio) >= 0 && t->compar(chave_fim, no.chaves[i]) >= 0){
                imprimiu = true;
                exibir(no.chaves[i]);
            }
        }

    }


    // cria uma variavel para conseguir comparar de acordo com o tamanho da arvore
    int k = 0;

    for(k = 0; k < t->tam_chave; k++){
        if(chave_inicio[k] != '0')
            break;
    }

    if(no.this_rrn == t->rrn_raiz && k == t->tam_chave){
        free(chave_inicio);
        free(chave_fim);
    }

    btree_node_free(no);

    return imprimiu;

}

btree_node btree_read(int rrn, btree *t) {

    btree_node no = btree_node_malloc(t);

    //tamanho de cada registro de indice: 3 + ((m-1)*t->tam_chave) + 1 + (m * 3)
    int tamRegistro = 3 + ((btree_order-1)*t->tam_chave) + 1 + (btree_order * 3);
    char contadorChaves[4], contadorFilhos[4];


    // pegar o registro em si
    //t->arquivo[rrn * tamRegistro];

    strncpy(contadorChaves, &t->arquivo[rrn * tamRegistro], 3);
    contadorChaves[3] = '\0';
    no.qtd_chaves = atoi(contadorChaves);

    for(int i = 0; i < no.qtd_chaves; i++){
        strncpy(no.chaves[i], &t->arquivo[((rrn * tamRegistro) + 3) + (i*t->tam_chave)], t->tam_chave);
        no.chaves[i][t->tam_chave] = '\0';
    }

    if(t->arquivo[((rrn * tamRegistro) + 3) + ((btree_order-1)*t->tam_chave)] == 'T')
        no.folha = true;
    else
        no.folha = false;



    for(int i = 0; i < no.qtd_chaves + 1; i++){
        if(t->arquivo[((rrn * tamRegistro) + 3) + ((btree_order-1)*t->tam_chave) + 1 + 3*i] != '*'){

            strncpy(contadorFilhos, &t->arquivo[((rrn * tamRegistro) + 3) + ((btree_order-1)*t->tam_chave) + 1 + 3*i], 3);
            contadorFilhos[3] = '\0';
            no.filhos[i] = atoi(contadorFilhos);
        
        }
        else{
            no.filhos[i] = -1;
        }
    }

    no.this_rrn = rrn;

    return no;
}

void btree_write(btree_node no, btree *t) {

    //tamanho de cada registro de indice: 3 + ((m-1)*t->tam_chave) + 1 + (m * 3)
    int tamRegistro = 3 + ((btree_order-1)*t->tam_chave) + 1 + (btree_order * 3);
    char filhoChar[4];
    int qtd_filhos = 0;
    
    // gravar no registro em si
    //t->arquivo[no.this_rrn * tamRegistro];

    //adiciona a quantidade de chaves
    sprintf(&t->arquivo[no.this_rrn * tamRegistro], "%03i", no.qtd_chaves);
    t->arquivo[(no.this_rrn * tamRegistro) + 3] = '\0';


    //adiciona as chaves
    for(int i = 0; i < no.qtd_chaves; i++){
        strcpy(&t->arquivo[((no.this_rrn * tamRegistro) + 3) + (i*t->tam_chave)], no.chaves[i]);
    }
    

    //adiciona os #
    if(no.qtd_chaves < (btree_order-1)){
        for(int i = 0; i < (btree_order-1) - no.qtd_chaves; i++){
            for(int j = 0; j < t->tam_chave; j++){
                t->arquivo[( (no.this_rrn * tamRegistro) + 3) + (no.qtd_chaves*t->tam_chave) + (i*t->tam_chave) + j ] = '#';
            }
        }
    }



    if(no.folha == true)
        t->arquivo[((no.this_rrn * tamRegistro) + 3) + ((btree_order-1)*t->tam_chave)] = 'T';
    else
        t->arquivo[((no.this_rrn * tamRegistro) + 3) + ((btree_order-1)*t->tam_chave)] = 'F';



    for(int i = 0; i < no.qtd_chaves+1; i++){
        if(no.filhos[i] != -1){
            sprintf(filhoChar, "%03i", no.filhos[i]);
            strncpy(&t->arquivo[((no.this_rrn * tamRegistro) + 3) + ((btree_order-1)*t->tam_chave) + 1 + 3*i], filhoChar, 3);

            qtd_filhos++;
        }
    }


    for(int i = qtd_filhos; i < btree_order; i++){
        for(int j = 0; j < 3; j++){
            t->arquivo[( (no.this_rrn * tamRegistro) + 3) + ((btree_order-1)*t->tam_chave) + 1 + 3*(i) + j] = '*';
        }
    }


    t->arquivo[((t->qtd_nos+1) * tamRegistro)] = '\0';

    // btree_node_free(no);  já to dando free em outros momentos
}

btree_node btree_node_malloc(btree *t) {
    btree_node no;

    no.chaves = malloc((btree_order-1) * sizeof(char*));
    for (int i = 0; i < btree_order-1; ++i) {
        no.chaves[i] = malloc(t->tam_chave + 1);
        no.chaves[i][0] = '\0';
    }

    no.filhos = malloc(btree_order * sizeof(int));
    for (int i = 0; i < btree_order; ++i)
        no.filhos[i] = -1;

    return no;
}

void btree_node_free(btree_node no) {
    for (int i = 0; i < btree_order-1; ++i)
        free(no.chaves[i]);

    free(no.chaves);
    free(no.filhos);
}

char* strpadright(char *str, char pad, unsigned size) {
    for (unsigned i = strlen(str); i < size; ++i)
        str[i] = pad;
    str[size] = '\0';

    return str;
}

unsigned hash_function_clientes_idx(const void *data, unsigned table_size) {

    uint64_t soma = 0;


    for( int i = 1; i <= 9; i++){
        soma = soma + pow_uint64( ((clientes_idx_struct*)data)->cpf[i-1] - '0', i);
        soma = soma % table_size;
    }

    return soma;

}

unsigned hash_function_chaves_pix_idx(const void *data, unsigned table_size) {
    
    uint64_t soma = 0;


    for( int i = 1; i <= 9; i++){
        soma = soma + pow_uint64( ((chaves_pix_idx_struct*)data)->chave_pix[i-1], i);
        soma = soma % table_size;
    }


    return soma;

}

bool hash_insert(void *chave, hash *ht) {

    ht->qtd_insercoes++;

    float a = (float) ht->qtd_insercoes/ht->table_size;
    float Cn;
    
    int i = 0;

    hash_node* node = malloc(sizeof(hash_node));
    node->data = chave;


    if(ht->type == open_addressing){
        Cn = (float)( (2-a)/(2-(2*a)) );

        // a tabela nunca fica mais cheia do que 80% da capacidade max
        if(Cn > 3){
            hash_resize(ht);
            return true;
        }

        node->state = used_node;
    }
    else{
        Cn = (float) ( 1 + a/2 );

        // a tabela nunca fica mais cheia do que % da capacidade max
        if(Cn > 2){
            hash_resize(ht);
            return true;
        }

        node->next = NULL;
    }


    unsigned index = ht->hash_function(chave, ht->table_size);
    i = index;
    

    if( ht->tabela[index] != NULL && ht->tabela[index]->data != NULL){
        
        if(ht->type == open_addressing){

            while( ht->tabela[i] != NULL && ht->tabela[i]->data != NULL){
                
                if(i == ht->table_size - 1){
                    i = 0;
                }
                else{
                    i++;
                }
                
            }
            
            ht->tabela[i] = node;
            
        }
        else{

            hash_node** aux = &ht->tabela[index];

            while( *aux != NULL && ht->compar((*aux)->data, chave) < 0 ){
                aux = &(*aux)->next;
            }

            node->next = *aux;
            *aux = node;

        }
        
    }
    else{
        ht->tabela[index] = node;
    }

    
    return false;

}

bool hash_search(void *result, bool exibir_caminho, void *chave, hash *ht) {
    
    unsigned index = ht->hash_function(chave, ht->table_size);

    int i = index;

    bool encontrado = false;
    

    if(exibir_caminho == true){
        printf("Indices percorridos: %i", index);
    }


    if( ht->tabela[index] != NULL && ht->tabela[index]->data != NULL){

        if(ht->compar( ht->tabela[index]->data, chave) != 0){

            if(ht->type == open_addressing){

                while( ht->tabela[i] != NULL ){

                    if( ht->tabela[i]->data != NULL && ht->compar( ht->tabela[i]->data, chave) == 0){

                        if(result != NULL)
                            memcpy(result, ht->tabela[i]->data, ht->tam_chave);

                        encontrado = true;
                        break;
                    }

                    
                    if(i == ht->table_size - 1){
                        i = 0;
                    }
                    else{
                        i++;
                    }

                    if( i == index){
                        break;
                    }

                    if(exibir_caminho == true){
                        printf(" %i", i);
                    }

                }

            }
            else{

                hash_node* aux = ht->tabela[index];

                i = 0;

                while( aux->next != NULL && aux->next->data != NULL && ht->compar( aux->data, chave) < 0){

                    aux = aux->next;
                    

                    if(exibir_caminho == true){
                        printf(" %i", i++);
                    }

                    
                    if(ht->compar( aux->data, chave) == 0){

                        if(result != NULL){
                            memcpy(result, aux->data, ht->tam_chave);
                        }

                        encontrado = true;

                        break;
                    }
                
                }


                if(exibir_caminho == true && aux != NULL && aux->data != NULL ){
                    printf(" %i", i);
                }

            }

        }
        else{

            if(result != NULL)
                memcpy(result, ht->tabela[index]->data, ht->tam_chave);


            encontrado = true;


            if(exibir_caminho == true){

                if(ht->type == separate_chaining){
                    printf(" %i", 0);
                }

            }

        }
    
    
    }


    if(exibir_caminho == true)
        printf("\n");


    return encontrado;

}

bool hash_delete(void *chave, hash *ht) {

    unsigned index = ht->hash_function(chave, ht->table_size);

    int i = index;

    bool encontrado = false;

    if( ht->tabela[index] != NULL && ht->tabela[index]->data != NULL){

        if(ht->compar( ht->tabela[index]->data, chave) != 0){

            if(ht->type == open_addressing){

                while( ht->tabela[i] != NULL){

                    if(ht->tabela[i]->data != NULL && ht->compar( ht->tabela[i]->data, chave) == 0){

                        ht->tabela[i]->state = deleted_node;
                        free(ht->tabela[i]->data);
                        ht->tabela[i]->data = NULL;

                        encontrado = true;
                        break;
                    }

                    
                    if(i > ht->table_size - 1){
                        i = 0;
                    }
                    else{
                        i++;
                    }

                    if( i == index){
                        break;
                    }
                
                }


            }
            else{

                hash_node* aux = ht->tabela[index];
                hash_node* anterior = aux;


                while( aux != NULL && ht->compar(aux->data, chave) != 0 ){
                    anterior = aux;
                    aux = aux->next;
                }

                if(ht->compar( aux->data, chave) == 0){
                    
                    free(aux->data);

                    anterior->next = aux->next;

                    free(aux);

                    encontrado = true;
                }

            }

        }
        else{

            if(ht->type == open_addressing){
            
                ht->tabela[index]->state = deleted_node;
                free(ht->tabela[index]->data);
                ht->tabela[index]->data = NULL;

            }
            else{

                hash_node* aux = ht->tabela[index]->next;

                free(ht->tabela[index]->data);

                free(ht->tabela[index]);

                ht->tabela[index] = aux;


            }

            encontrado = true;

        }
    
    }


    return encontrado;

}

void hash_resize(hash *ht) {

    hash_free(ht);
    
    ht->table_size = next_prime(ht->table_size * 2);

    ht->create_idx();

}

void hash_free(hash *ht) {
    
    if(ht->type == open_addressing){
        
        for(int i = 0; i < ht->table_size; i++){
            if(ht->tabela[i] != NULL){

                if(ht->tabela[i]->data != NULL){
                    free(ht->tabela[i]->data);
                    ht->tabela[i]->data = NULL;
                }

                free(ht->tabela[i]);
                ht->tabela[i] = NULL;

            }

        }

        free(ht->tabela);
        ht->tabela = NULL;

    }
    else{

        hash_node** atual;
        hash_node* prox;

        for(int i = 0; i < ht->table_size; i++){

            if(ht->tabela[i]){

                atual = &ht->tabela[i];
                prox = ht->tabela[i]->next;

                while(prox){

                    free(*atual);
                    *atual = NULL;
                    
                    atual = prox;
                    prox = prox->next;
                    
                }

                free(*atual);
                *atual = NULL;
            
            }

            
        }

        free(ht->tabela);
        ht->tabela = NULL;

    }

    ht->qtd_insercoes = 0;

}

//recebe o indice atual, delimitador, quantidade max verificacoes e pula pro proximo campo
int proxCampoArquivo(int indiceAtual, char delimiter, int quant){

    int i = 0;
    int bool = 0;

    for(i = indiceAtual; i < indiceAtual + quant; i++){
        
        if(ARQUIVO_CLIENTES[i] == delimiter){
            i++;
            bool++;
            break;
        }

    }

    if(bool == 0){
        return 0;
    }

    return i;

}

bool alterar_saldoSemOK(char *cpf, double valor){

    if(valor == 0){
        printf(ERRO_VALOR_INVALIDO);
        return false;
    }

    clientes_idx_struct cpfRrn;

    char valorChar[TAM_SALDO];
    int rrn = 0, i = 0, insereEm = 0;
    double saldo;

    //hash search
    if(!hash_search(&cpfRrn, false, cpf, &clientes_idx)){
        printf(ERRO_REGISTRO_NAO_ENCONTRADO);
        return false;
    }



    //pega rrn
    rrn = cpfRrn.rrn;


    //pega as informacoes atuais do cliente
    Cliente c = recuperar_registro_cliente(rrn);

    saldo = c.saldo + valor;

    if(saldo < 0){
        printf(ERRO_SALDO_NAO_SUFICIENTE);
        return false;
    }


    sprintf(valorChar, "%013.2lf", saldo);
    valorChar[TAM_SALDO-1] = ';';


    insereEm = (rrn * TAM_REGISTRO_CLIENTE) + TAM_CPF;

    //pula nome variavel
    insereEm = proxCampoArquivo(insereEm, ';', TAM_MAX_NOME);

    insereEm = insereEm + TAM_NASCIMENTO;

    //pula email variavel
    insereEm = proxCampoArquivo(insereEm, ';', TAM_MAX_EMAIL);

    insereEm = insereEm + TAM_CELULAR;

    // insere novo valor de saldo
    strncpy(&ARQUIVO_CLIENTES[insereEm], valorChar, TAM_SALDO);

    insereEm = insereEm + TAM_SALDO;


    return true;

}
