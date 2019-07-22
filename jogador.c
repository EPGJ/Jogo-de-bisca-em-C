#include"jogador.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>




void criaJogador(tJogador **jogador, int tipoJogador,int id){
    
    *jogador = malloc(sizeof(tJogador));
    (*jogador)->tipoJogador = tipoJogador;
    (*jogador)->id = id;
    
    switch(id){
        case 0:
            scanf("%*c"); // limpa o buffer
            printf("\n\nPor favor insira seu nome(maximo 13 caracteres): ");
            scanf("%13[^ \n]", (*jogador)->nome);
            break;
            
        case 1:
            strcpy((*jogador)->nome,"Player 1");
            break;
            
        case 2:
            strcpy((*jogador)->nome,"Player 2");
            break;
            
        case 3:
            strcpy((*jogador)->nome,"Player 3");
            break;  
        default:
            printf("\n\nERRO!! caso não computado\n\n");
    }
    
    (*jogador)->cartasGanhas = malloc(sizeof(tBaralho));
    (*jogador)->cartasNaMao = malloc(sizeof(tBaralho));
    
    fazBaralhoVazio((*jogador)->cartasGanhas);
    fazBaralhoVazio((*jogador)->cartasNaMao);
    
}
int calculaPontos(tBaralho *baralho){
    
    tCartaDoBaralho *p;
    int pontos=0;
    for(p=baralho->primeira; p!=NULL;p = p->proximaCarta){
        pontos +=p->carta.valor;
    }
    return pontos;
}
void compraCarta(tBaralho *baralhoJogo,tJogador *jogador){
    
    tCarta cartaComprada;
    
    if(vazio(baralhoJogo)){
        printf("Impossível concluir operação.  O baralho está vazio.");
        exit(1);
    }
    else{
        
        retiraCartaBaralho(&baralhoJogo,baralhoJogo->quantidadeCartas, &cartaComprada);
        insereNoBaralho(&jogador->cartasNaMao, &cartaComprada);
        
    } 
}
void jogaCarta(tJogador *jogador,tCarta *trunfo,int dificuldade,int modalidade,tCarta *carta,tCarta *cartaVencedoraDoMonte, int qtdCartasNoMonte){
    
    
    switch(dificuldade){
        
        case FACIL:
            
            jogaCartaModoFacil(jogador,trunfo,carta,modalidade);
            
            break;
            
        case DIFICIL:
            
            jogaCartaModoDificil(jogador,trunfo,carta,cartaVencedoraDoMonte, qtdCartasNoMonte, modalidade);
            break;
        
        default:
            printf("ERRO!! Dificuldade não reconhecida.");
            exit(1);     
    }
}

void jogaCartaModoFacil(tJogador * jogador, tCarta * trunfo,tCarta *carta,int modalidade){
    switch(jogador->tipoJogador){
        
        case HUMANO:
            
            jogaCartasJogadorHumano(jogador,carta);
            
            break;
        
        case MAQUINA:
            srand(time(NULL));
            int i;
            printf(GRN "\nVez do jogador %s" , jogador->nome);
            
            if(modalidade == EXPOSITIVO){
                imprimeBaralho(jogador->cartasNaMao);
            }
                       
            i = rand()%jogador->cartasNaMao->quantidadeCartas+1;
            retiraCartaBaralho(&jogador->cartasNaMao, i,carta);
            printf("\n");
            imprimeCarta(carta);    
            printf("\n" RESET);
            break;
        default:
            printf("\nERRO!!!  Tipo de jogador não reconhecido");
            exit(1);
    }
    
}

void jogaCartaModoDificil(tJogador * jogador, tCarta * trunfo,tCarta *carta,tCarta *cartaVencedoraDoMonte, int qtdCartasNoMonte,int modalidade){
    int i;
    switch(jogador->tipoJogador){
        
        case HUMANO:
            
            jogaCartasJogadorHumano(jogador,carta);
            
            break;
        
        case MAQUINA:
            
            printf(GRN "\nVez do jogador %s" , jogador->nome);

            
            if(qtdCartasNoMonte == 0){ //Se for o primeiro a jogar a carta de menor valor que ele tem na mão
                srand(time(NULL));
                
                i = buscaCartaComMenorValor(jogador->cartasNaMao,trunfo);

            }
            
            
            else{
                
                   i = buscaCartaDeMaiorPrioridade(jogador->cartasNaMao, cartaVencedoraDoMonte, trunfo);
                   
                   if(i == -1){ // caso não encontre requisitado, o indice i recebe o indice que possui a carta de menor valore prioridade
                      i = buscaCartaComMenorValor(jogador->cartasNaMao, trunfo); 
                   }            
            }
            
            if(modalidade == EXPOSITIVO){
                imprimeBaralho(jogador->cartasNaMao);
            }

            retiraCartaBaralho(&jogador->cartasNaMao, i,carta);
            printf("\n");
            imprimeCarta(carta);
            printf("\n" RESET);
            
            break;
        default:
            printf("\nERRO!!!  Tipo de jogador não reconhecido");
            exit(1);
    }
    
    
    
}


void jogaCartasJogadorHumano(tJogador * jogador,tCarta *carta){
     
    int indiceCarta;
    char i;
    printf("\nSua vez %s, escolha uma carta: ",jogador->nome);
            imprimeBaralho(jogador->cartasNaMao);
            
            voltaParaEscolherIndice:  //flag de retorno casa seja digitado algum indice não válido
            
            if(jogador->cartasNaMao->quantidadeCartas == 3)printf("(1) (2) (3), entre com o número da carta que você deseja jogar: ");
            if(jogador->cartasNaMao->quantidadeCartas == 2)printf("(1) (2), entre com o número da carta que você deseja jogar: ");
            if(jogador->cartasNaMao->quantidadeCartas == 1)printf("(1), entre com o número da carta que você deseja jogar: ");
            scanf("%c", &i);
            
            switch(i){
                case '1':
                    indiceCarta =1;
                    break;
                
                case '2':
                    indiceCarta =2;
                    break;
                
                case '3':
                    indiceCarta =3;
                    break;
                default:
                    printf(RED "\nERRO, carta não disponível.\n" RESET);
                    scanf("%*c");
                    goto voltaParaEscolherIndice;       
            }
            
            
            
            if(indiceCarta> jogador->cartasNaMao->quantidadeCartas || indiceCarta < 1 ){
                
                printf(RED "\nERRO, carta não disponível.\n" RESET);
                scanf("%*c");
                goto voltaParaEscolherIndice;
            }
            
            
            retiraCartaBaralho(&jogador->cartasNaMao, indiceCarta, carta);
            imprimeCarta(carta);
}



void destroiJogador(tJogador **jogador){
       
    destroiBaralho(&(*jogador)->cartasGanhas);
    destroiBaralho(&(*jogador)->cartasNaMao);
    free((*jogador));
    
    
}