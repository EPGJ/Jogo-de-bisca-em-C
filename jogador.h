/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   jogador.h
 * Author: elias
 *
 * Created on 10 de Abril de 2019, 23:12
 */

#ifndef JOGADOR_H
#define JOGADOR_H
#define MAX_TAMANHO_NOME 13
#define HUMANO 1
#define MAQUINA 2
#define FACIL 1
#define DIFICIL 2
#define PADRAO  1
#define EXPOSITIVO 2
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"
#include"baralho.h"
 

typedef struct{
    int tipoJogador, id; // o tipo poderá ser humano ou máquina.
    char nome[MAX_TAMANHO_NOME];
    tBaralho *cartasNaMao;
    tBaralho *cartasGanhas;
}tJogador;


/* Cria novo jogador
 * inputs: ponteiro para jogador, tipo do jogador e id do jogador
 * output: nenhum
 * pre-condicao: tipo do jogador válido e ponteiro válido
 * pos-condicao: jogador criado
 */
void criaJogador(tJogador **jogador,int tipoJogador,int id); 

/* Calcula pontos do jogador
 * inputs: baralho
 * output: valor inteiro dos pontos feitos pelo jogador
 * pre-condicao: baralho válido
 * pos-condicao: baralho inalterado
 */
int calculaPontos(tBaralho *baralho);

/* Retira carta do baralho passado  e insere no baralho da mão do jogador
 * inputs: baralho e jogador
 * output: nenhum
 * pre-condicao: baralho e jogador válidos
 * pos-condicao: baralho do jogo com uma carta a menos e baralho da mão do jogador com uma carta a mais
 */
void compraCarta(tBaralho *baralhoJogo, tJogador *jogador);

/* Joga uma carta da mão do jogador
 * inputs: jogador, carta trunfo, dififuldade do jogo, modalidade do jogo, carta, carta vencedora do monte e quantidade de cartas no monte
 * output: nenhum
 * pre-condicao: jogador, trunfo, carta, carta vencedora válidos
 * pos-condicao: trunfo inalterado, baralho da mão do jogador com uma carta a menos e carta igual a uma carta da mão do jogador
 */
void jogaCarta(tJogador *jogador,tCarta * trunfo,int dificuldade,int modalidade,tCarta *carta,tCarta *cartaVencedoraDoMonte, int qtdCartasNoMonte);

/* Libera espaço reservado para o jogador
 * inputs: ponteiro para jogador
 * output: nenhum
 * pre-condicao: jogador precisa existir
 * pos-condicao: jogador destruido
 */
void destroiJogador(tJogador **jogador);

/* Joga uma carta no modo fácil
 * inputs: jogador, a carta trunfo, carta a ser jogada e a modadalidade do jogo
 * output: nenhum
 * pre-condicao: monte e trunfo válidos
 * pos-condicao: monte e trunfo inalterados
 */
void jogaCartaModoFacil(tJogador * jogador, tCarta * trunfo,tCarta *carta,int modalidade);

/* Joga carta quando o jogador é humano
 * inputs: jogador, carta trunfo, carta a se jogada e modalidade do jogo
 * output: nenhum
 * pre-condicao: jogador válido
 * pos-condicao: baralho da mão do jogador com uma carta a menos
 */
void jogaCartasJogadorHumano(tJogador * jogador,tCarta *carta);

/* Joga cartas no modo dificil
 * inputs: jogador, carta trunfo, carta a ser retirada, carta vencedora do monte, quantidade de cartas no monte e modalidade do jogo
 * output: nenhum
 * pre-condicao: jogado, trunfo e carta vencedora do monte válidos
 * pos-condicao: monte e trunfo inalterados
 */
void jogaCartaModoDificil(tJogador * jogador, tCarta * trunfo,tCarta *carta,tCarta *cartaVencedoraDoMonte, int qtdCartasNoMonte,int modalidade);


#endif /* JOGADOR_H */

