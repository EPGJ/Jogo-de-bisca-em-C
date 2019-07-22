#include"rodada.h"
#include<stdio.h>
#include<stdlib.h>

tCarta * cartaDoMonte(tMonteRodada* monte, int vezDoJogador){

    return &monte->cartaJogada[vezDoJogador].carta;

}
void insereIdJogadorNaCartaDoMonte(tMonteRodada* monte, int vezDoJogador,tJogador* jogador){

    monte->cartaJogada[vezDoJogador].idJogador = jogador->id;

}

int defineVencedorRodada(tMonteRodada* monte, tCarta * trunfo,int quantidadeJogadores){

    int i;
    int idVencedor = monte->cartaJogada[0].idJogador; 
    tCarta cartaVencedora = monte->cartaJogada[0].carta;
    tCarta cartaAtual;
    for( i = 0; i<quantidadeJogadores;i++){

        cartaAtual = monte->cartaJogada[i].carta;

        idVencedor = verificaCartaGanhadora(&cartaVencedora, &cartaAtual,monte->cartaJogada[i].idJogador,idVencedor, trunfo);
    }

    return idVencedor;
}

int verificaCartaGanhadora(tCarta *cartaVencedora, tCarta * cartaAtual,int idAtual ,int idVencedor,tCarta * trunfo){

    if(cartaAtual->naipe == trunfo->naipe){
        if(cartaVencedora->naipe == trunfo->naipe){

            if(cartaAtual->valor > cartaVencedora->valor){
                *cartaVencedora = *cartaAtual;
                return idAtual;
            }
            if(cartaAtual->valor == cartaVencedora->valor){
                
                if(cartaAtual->natureza > cartaVencedora->natureza){
                    *cartaVencedora = *cartaAtual;
                    return idAtual;
                }
                else{
                    return idVencedor;
                }
                
            }  
            else{
                return idVencedor;
            }

        }  
        else{
            *cartaVencedora = *cartaAtual;
            return idAtual;
        }    
    }
    
    else{
        if(cartaVencedora->naipe != trunfo->naipe){

            if(cartaAtual->naipe == cartaVencedora->naipe){

                if(cartaAtual->valor > cartaVencedora->valor){
                    *cartaVencedora = *cartaAtual;
                    return idAtual;
                }
                
                if(cartaAtual->valor == cartaVencedora->valor){
                    
                    if(cartaAtual->natureza > cartaVencedora->natureza){
                        *cartaVencedora = *cartaAtual;
                         return idAtual;
                    }
                    else{
                        return idVencedor;
                    }    
                }
                else{
                    return idVencedor;
                }

            }
            else{
                return idVencedor;
            }

        }
        else{
            return idVencedor;
        }
    }
    printf("Caso não computado, erro ao estabelecer carta ganhadora.");
    exit(1);

}

tCarta cartaVencedoraDoMonte(tMonteRodada *monte, int qtdCartasNoMonte,tCarta *trunfo){
    
    int aux=0;
    tCarta cartaAtual,cartaVencedora = monte->cartaJogada[0].carta;
    
    for(int i=0; i<=qtdCartasNoMonte;i++){
        cartaAtual = monte->cartaJogada[i].carta;
         aux =verificaCartaGanhadora(&cartaVencedora, &cartaAtual, monte->cartaJogada[i].idJogador, aux, trunfo);
        
    }

    return cartaVencedora;
    
}

void recebeCartasRodada(tJogador **jogador, tMonteRodada *monte, int qtdCartasNoMonte){
    
    for(int i =0; i< qtdCartasNoMonte; i++){
        insereNoBaralho(&(*jogador)->cartasGanhas, &monte->cartaJogada[i].carta);
    }
    
}
    
void imprimeMonteRodada(tMonteRodada *monte, int qtdCartasNoMonte){
    printf("\n");
    for(int i=0; i<qtdCartasNoMonte;i++){
        
        imprimeCarta(&monte->cartaJogada[i].carta);
        if(i%10 == 0 && i!=0)printf("\n");
        
        
    }
    printf("\n\n" RESET);
    printf("===================================== (pressione enter)");
}
