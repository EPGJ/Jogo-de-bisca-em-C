/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   jogo.h
 * Author: elias
 *
 * Created on 10 de Abril de 2019, 22:57
 */

#ifndef JOGO_H
#define JOGO_H
#define FACIL 1
#define DIFICIL 2
#define PADRAO  1
#define EXPOSITIVO 2
#define MAX_QTD_CARTAS_RODADA 3 // máxima quantidade de cartas que um jogador pode ter em uma rodada
#include"jogador.h"

typedef struct jogadores{
    tJogador * jogador;
    struct jogadores * proximo;
}tJogadores;

typedef struct{
    tJogadores *primeiro;
    tJogadores *ultimo;
}tListaJogadores;



typedef struct{
    tListaJogadores * jogadores;
    tBaralho * baralho;
    tCarta * trunfo;
    int quantidadeJogadores;
    int dificuldade; //pode ser difícil ou fácil
    int modalidade; // pode ser padão ou expositiva
}tJogo;






/* Cria novo jogo
 * inputs: ponteiro para jogo
 * output: nenhum
 * pre-condicao: ponteiro para jogo válido
 * pos-condicao: jogo criado
 */
void criaJogo(tJogo** jogo);

/* Inicia jogo
 * inputs: ponteiro para jogo
 * output: nenhum
 * pre-condicao: jogo construido
 * pos-condicao: jogo terminado
 */
void comecaJogo(tJogo** jogo);

/* Libera espaço reservado para o jogo
 * inputs: ponteiro para jogo
 * output: nenhum
 * pre-condicao: jogo construido
 * pos-condicao: jogo destruido
 */
void destroiJogo(tJogo** jogo);

/* Define a quantidade de jogadores 
 * inputs: jogo
 * output: nenhum
 * pre-condicao: jogo válido
 * pos-condicao: jogo com quantidade de jogadores definida
 */
void definiQuantidadeJogadores(tJogo *jogo);

/* Cria dos jogadores do jogo 
 * inputs: ponteiro para jogo
 * output: nenhum
 * pre-condicao: jogo válido
 * pos-condicao: jogo com jogadores criados
 */
void criaJogadores(tJogo** jogo);

/* Faz a lista vazia
 * inputs: ponteiro para jogo
 * output: nenhum
 * pre-condicao: jogo válido
 * pos-condicao: lista vazia
 */
void fazListaVazia(tJogo** jogo);

/* Define a modalidade do jogo
 * inputs: ponteiro para jogo
 * output: nenhum
 * pre-condicao: jogo válido
 * pos-condicao: jogo com modalidade definida
 */
void defineModalidade(tJogo** jogo);

/* Define a dificuldade do jogo
 * inputs: ponteiro para jogo
 * output: nenhum
 * pre-condicao: jogo válido
 * pos-condicao: jogo com dificuldade definida
 */
void defineDificuldade(tJogo** jogo);

/* Define trunfo do jogo
 * inputs: ponteiro para jogo
 * output: nenhum
 * pre-condicao: jogo válido
 * pos-condicao: jogo com trunfo definido
 */
void defineTrunfo(tJogo** jogo);

/* Retorna o nome do jogador humano
 * inputs: jogo
 * output: nome do jogador humano
 * pre-condicao: jogo criado
 * pos-condicao: jogo inalterado
 */
char * nomeJogadorHumano(tJogo * jogo);

/* Joga rodada
 * inputs: ponteiro para jogo, numero da rodada, id vencedor da rodada anterior
 * output: valor inteiro do vencedor da rodada
 * pre-condicao: jogo criado
 * pos-condicao: jogo alterado de acordo com as necessidades da execução do jogo
 */
int jogaRodada(tJogo **jogo, int numeroRodada,int idVencedorRodadaAnterior);

/* Imprime o cabeçalho da partida 
 * inputs: jogo
 * output: nenhum
 * pre-condicao: jogo criado
 * pos-condicao: jogo inalterado
 */
void imprimeCabecalhoPartida(tJogo *jogo);

/* Distribui as cartas aos jogadores
 * inputs: ponteiro para jogo, numero da rodada e id do vencedor da rodada anterior
 * output: nenhum
 * pre-condicao: jogo criado com numero de rodada e id vencedor válidos
 * pos-condicao: Cartas distribuidas para os jogadores de acordo com as regras do jogo
 */
void distribuiCartas(tJogo **jogo, int numeroRodada,int idVencedorRodadaAnterior);

/* Jogadores jogam as cartas
 * inputs: ponteiro para jogo e id do vencedor da rodada anterior
 * output: id vencedor da rodada
 * pre-condicao: ponteiro de jogo válido
 * pos-condicao: cada jogador joga sua carta
 */
int jogaCartas(tJogo **jogo,int idVencedorRodadaAnterior);

/* Retorna célula do jogador vencedor da rodada
 * inputs: jogo, id vencedor da rodada anterior
 * output: ponteiro para célula do jogador vencedor
 * pre-condicao: jogo criado
 * pos-condicao: jogo inalterado
 */
tJogadores * jogadorVencedorRodada(tJogo *jogo,int idVencedorRodadaAnterior);

/* Imprime o ganhador do jogo
 * inputs: jogo
 * output: nenhum
 * pre-condicao: jogo criado
 * pos-condicao: jogo inalterado
 */
void imprimeGanhadorJogo(tJogo *jogo);

#endif /* JOGO_H */

