/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rodada.h
 * Author: elias
 *
 * Created on 26 de Abril de 2019, 21:05
 */

#ifndef RODADA_H
#define RODADA_H
#include"jogador.h"
#define QTD_MAX_CARTAS_NO_MONTE 4

typedef struct {
    tCarta carta;
    int idJogador;
}tCartaJogada;

typedef struct {
    tCartaJogada cartaJogada[QTD_MAX_CARTAS_NO_MONTE];
}tMonteRodada;


/* Retorna ponteiro de uma carta que foi adicionado ao monte na vez passada como prâmetro
 * inputs: monte e a vez 
 * output: ponteiro para carta desejada
 * pre-condicao: monte e vez válidos
 * pos-condicao: monte inalterado
 */
tCarta * cartaDoMonte(tMonteRodada* monte, int vez);

/* Insere a indentidade do jogador na carta jogada no monte
 * inputs: o monte, a vez do jogador e o jogador
 * output: nenhum
 * pre-condicao: monte e jogador válidos
 * pos-condicao: monte alterado e jogador inalterado
 */
void insereIdJogadorNaCartaDoMonte(tMonteRodada* monte, int vezDoJogador,tJogador* jogador);

/* Define um vencedor para a rodada 
 * inputs: monte, trunfo e quantidade de jogadores
 * output: id do jogador ganhador
 * pre-condicao: monte e trunfo válidos 
 * pos-condicao: monte e trunfo inalterados
 */
int defineVencedorRodada(tMonteRodada* monte, tCarta * trunfo,int quantidadeJogadores);

/* Decide qual carta é a vencedora se é a carta atual ou a carta anterior
 * inputs: carta vencedora anterior, carta atual, id vencedor atual, id vencedor anterior e carta trunfo
 * output: valor inteior do id do jogador cuja carta foi a vencedora
 * pre-condicao: canta vencedora, carta atual e trunfo válidos. Além disso que o idAtual e idVencedor sejam id's de jogadores existentes
 * pos-condicao: carta vencedora atualizada, carta atual inalterada e trunfo inalterado 
 */
int verificaCartaGanhadora(tCarta *cartaVencedora, tCarta * cartaAtual,int idAtual ,int idVencedor,tCarta * trunfo);

/* Insere cartas do monte no baralho do jogador
 * inputs: ponteiro para jogador, monte e quantidade de cartas no monte
 * output: nenhum
 * pre-condicao: ponteiro para jogador e monte válidos
 * pos-condicao: baralho na mão do jogador atualizado com  as cartas do monte
 */
void recebeCartasRodada(tJogador **jogador, tMonteRodada *monte, int qtdCartasNoMonte);

/* Imprime as cartas do monte
 * inputs: monte e quantidade de cartas no monte
 * output: nenhum
 * pre-condicao: monte válido
 * pos-condicao: monte inalterado
 */
void imprimeMonteRodada(tMonteRodada *monte, int qtdCartasNoMonte);

/* Retorna a carta vencedora do monte
 * inputs: monte, quantidade de cartas no monte e a carta trunfo
 * output: carta vencedora
 * pre-condicao: monte e trunfo válidos
 * pos-condicao: monte e trunfo inalterados
 */
tCarta cartaVencedoraDoMonte(tMonteRodada *monte, int qtdCartasNoMonte,tCarta *trunfo);



#endif /* RODADA_H */

