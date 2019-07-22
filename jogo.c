#include"jogo.h"
#include"rodada.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void criaJogo(tJogo** jogo){
    
    *jogo = malloc(sizeof(tJogo));
    
    definiQuantidadeJogadores(*jogo);
    criaBaralho(&(*jogo)->baralho);
    criaJogadores(jogo); 
    defineDificuldade(jogo);
    defineModalidade(jogo);
    defineTrunfo(jogo); 
}

void defineDificuldade(tJogo** jogo){
    
    char dificuldade;
    
    
    printf("\nMuito bem %s, vamos definir a dificuldade do jogo, digite D ou F:\n D -- Nível difícil.\n F -- Nível fácil.\nDigite sua resposta: ", nomeJogadorHumano(*jogo));
    
    verifica:    //flag de retorno caso a dificuldade selecionada não seja reconhecida.
    scanf("%*c");
    scanf("%c", &dificuldade);
    
    
    if(dificuldade == 'D' || dificuldade == 'd') (*jogo)->dificuldade = DIFICIL;
    else 
        if(dificuldade == 'F' || dificuldade == 'f')(*jogo)->dificuldade = FACIL;
        else{
            printf("\nPor favor, entre apenas com D ou F: ");
            goto verifica;
        }
    
}

void defineModalidade(tJogo **jogo){
    char modalidade;
    
    
    printf("\nQuase lá, agora só resta definir a modalidade do jogo, Digite P ou E:\n P -- Para jogar no modo padão.\n E -- Para jogar no modo expositivo.\nDigite sua resposta:  ");
    
    verificaModalidade: //flag de retorno caso a modalidade selecionada não seja reconhecida
    scanf("%*c");
    scanf("%c", &modalidade);
    
    if(modalidade == 'P' || modalidade == 'p')(*jogo)->modalidade = PADRAO;
    else
        if(modalidade == 'E' || modalidade == 'e')(*jogo)->modalidade = EXPOSITIVO;
        else{
            printf("\nPor favor, entre apenas com P ou E: ");
            goto verificaModalidade;
        }
    
    
}

void defineTrunfo(tJogo** jogo){
    
    srand(time(NULL));
    int i = rand()%(*jogo)->baralho->quantidadeCartas; // O índice i assumirá um número aleatório entre 0 e (quantidade de cartas -1).
    static tCarta trunfo;  // definida como estática pois é a mesma até o final do jogo
    
    embaralhar((*jogo)->baralho);// a função é utilizada aqui apenas para o maior desenpenho de retiradas de naipes aleatórios do baralho do jogo
    
    trunfo = buscaCarta((*jogo)->baralho,i );
    
    (*jogo)->trunfo = &trunfo;
    
    printf("\nTudo pronto !!!\nQuando estiver preparado para iniciar o jogo pressione enter.");
    
    scanf("%*c");
    scanf("%*c");
    
}
char * nomeJogadorHumano(tJogo * jogo){
    return jogo->jogadores->primeiro->jogador->nome; // O jogador Humano será sempre o primeiro da lista.
}
void definiQuantidadeJogadores(tJogo *jogo){
    
      char quantidade;
    
    printf("\e[H\e[2J"); //limpa a tela do terminal
    
    printf("Bem-vindo(a) ao Jogo de Bisca!!\n\nVocê pode escolher jogar contra 1 ou 3 jogadores, por favor nos informe a quantidade desejada: ");
    
    voltar:
    scanf(" %c", &quantidade);
    
    switch(quantidade){
        case '1':
            printf("\e[H\e[2J");
            printf("Você escolheu a opção de jogar contra um jogador.");
            jogo->quantidadeJogadores = 2; // número total de jogadores (um máquina e um humano).
            
            break;
        case '3':
            printf("\e[H\e[2J");
            printf("Você escolheu a opção de jogar contra três jogadores.");
            jogo->quantidadeJogadores = 4; // número total de jogadores.
            
            break;
        default:
            printf("\nPor favor, você pode apenas escolher jogar contra 1 ou 3 jogadores, entre com sua opção válida: \n");
            scanf("%*c");
            goto voltar;
    }
}
tBaralho ** baralhoJogo(tJogo* jogo){
    return &jogo->baralho;
}
void fazListaVazia(tJogo** jogo){
    
    (*jogo)->jogadores = malloc(sizeof(tListaJogadores));
    
    (*jogo)->jogadores->primeiro=NULL;
    (*jogo)->jogadores->ultimo=NULL;
    
}
void criaJogadores(tJogo** jogo){
    
    int i;
    fazListaVazia(jogo);    
    tJogadores *novoJogador;
    tListaJogadores * listaJogadores = (*jogo)->jogadores;
    
    for(i=0; i<(*jogo)->quantidadeJogadores;i++){
        
        novoJogador = malloc(sizeof(tJogadores));
        if(i == 0){  // se for o primeiro ciclo haverá a criação de um jogador humano.
          
            criaJogador(&novoJogador->jogador, HUMANO,i);
            
        }
        else{
            
            criaJogador(&novoJogador->jogador, MAQUINA,i);
            
        }
        
        if(listaJogadores->primeiro == NULL){
            
            listaJogadores->primeiro = novoJogador;
            listaJogadores->ultimo = novoJogador;
            
        }
        else{
            
            listaJogadores->ultimo->proximo = novoJogador;
            listaJogadores->ultimo = listaJogadores->ultimo->proximo;
            
        }
        
        listaJogadores->ultimo->proximo = listaJogadores->primeiro; // faz lista circular
          
    }
    
    
    (*jogo)->jogadores = listaJogadores; 
    
}


void comecaJogo(tJogo** jogo){
    printf("\e[H\e[2J"); // limpa a tela do terminal
    int numeroRodada=1;
    int idVencedorRodadaAnterior=0;
    char embaralha;
    int i =0;
    
    if((*jogo)->modalidade == EXPOSITIVO){
        embaralharNovamente:
        
        imprimeBaralho((*jogo)->baralho);
        digitouErrado:
        if(i == 0)printf("(Pressione Enter)");
        scanf("%*c");
        i++;
        printf("Você deseja embaralhar o baralho do jogo S/N? " );
        scanf("%c", &embaralha);
        
        if(embaralha == 'S'|| embaralha == 's'){
            embaralhar((*jogo)->baralho);
            goto embaralharNovamente;
        }
        else{
            if(embaralha == 'N'|| embaralha == 'n'){
                printf("\nVocê não poderá mais embaralhar o baralho.\n");
                scanf("%*c");
            }
            else{
                goto digitouErrado;
            }
        }
    }
    
    do{
        
        idVencedorRodadaAnterior = jogaRodada(jogo, numeroRodada, idVencedorRodadaAnterior);
        numeroRodada++;
        
        if((*jogo)->modalidade == EXPOSITIVO){
            printf("\e[H\e[2J");
            printf("Baralho do jogo: ");
            imprimeBaralho((*jogo)->baralho);
        }
        
    
    }while(!vazio((*jogo)->baralho)); 
    
    
    // Após o baralho estiver vazio, acontece mais duas rodadas para terminar as cartas dos jogadores;
    for(int i = 0; i< 2; i++){ 
        
        idVencedorRodadaAnterior = jogaRodada(jogo, numeroRodada,idVencedorRodadaAnterior);
        numeroRodada++;
        
        if((*jogo)->modalidade == EXPOSITIVO){
            printf("\e[H\e[2J");
            printf("Baralho do jogo: ");
            imprimeBaralho((*jogo)->baralho);
        }
        
        
    }
    
    imprimeGanhadorJogo(*jogo);
    
        
}


void imprimeGanhadorJogo(tJogo *jogo){
    
    printf("\e[H\e[2J"); //limpa tela
    int maiorQuantidadePontos=0;
    tJogadores * jogador = jogo->jogadores->primeiro;
    tJogadores * ganhador = jogo->jogadores->primeiro;
    int pontos, numeroEmpates=0, valorEmpate=0,valorEmpateAnterior;
    
    
    printf("DADOS DO JOGO: \n\n\n");
    
    do{
        
        pontos =calculaPontos(jogador->jogador->cartasGanhas);
        if(pontos == maiorQuantidadePontos){
            
            valorEmpate = pontos;
            
            if(numeroEmpates == 0){
                valorEmpateAnterior = valorEmpate;
            }
            else{
                
                if(valorEmpate != valorEmpateAnterior){
                    numeroEmpates =0;
                }
                
                
            }
            numeroEmpates++;
        }
        
        if( pontos > maiorQuantidadePontos){
            maiorQuantidadePontos = pontos;
            ganhador = jogador;
        }
       
        
        printf("%s fez %d pontos", jogador->jogador->nome, pontos);
        if(!vazio(jogador->jogador->cartasGanhas)){
            printf(" e ganhou as cartas a seguir:\n");
            imprimeBaralho(jogador->jogador->cartasGanhas);
            
        }
        else{
            printf(". O jogador não ganhou nenhuma rodada.\n");
        }
        
        printf("\n");
        jogador = jogador->proximo;
    }while(jogador != jogo->jogadores->primeiro);
    
    if(valorEmpate == maiorQuantidadePontos){
        
        printf("\n\n Houve %d empates, a partida não adimitiu um  ganhador.", numeroEmpates);
        
    }
    else{
        
        if(ganhador->jogador->id == 0) printf("\n\nPARABÉNS!!!! Você venceu o jogo com %d pontos!!.\n\n", maiorQuantidadePontos);
        else printf("\n\nO jogador %s venceu o jogo com %d pontos!.\n\n" , ganhador->jogador->nome,maiorQuantidadePontos);
    
    }
    
    
    
}



int jogaRodada(tJogo **jogo, int numeroRodada, int idVencedorRodadaAnterior){
    
    int idVencedorRodada;
    
    if((*jogo)->modalidade == PADRAO){
        printf("\e[H\e[2J"); //limpa tela do terminal
    }
    
    printf("Rodada %d\n", numeroRodada);
    imprimeCabecalhoPartida(*jogo);
    
    distribuiCartas(jogo, numeroRodada, idVencedorRodadaAnterior);
   
    
    idVencedorRodada = jogaCartas(jogo, idVencedorRodadaAnterior);
    
    return idVencedorRodada;
}
void imprimeCabecalhoPartida(tJogo *jogo){
   
    printf("\nO trunfo é: ");
    imprimeNaipe(jogo->trunfo);
    printf("\n");  

}

tJogadores * jogadorVencedorRodada(tJogo *jogo,int idVencedorRodadaAnterior){
    
    tJogadores  *jogadorVencedor =jogo->jogadores->primeiro ;
    
    do{
        
        jogadorVencedor = jogadorVencedor->proximo;
        
    }while(jogadorVencedor != jogo->jogadores->primeiro && jogadorVencedor->jogador->id !=idVencedorRodadaAnterior);
    
    
    return jogadorVencedor;
}

void distribuiCartas(tJogo **jogo, int numeroRodada,int idVencedorRodadaAnterior){
    
    tJogadores * jogador, *jogadorVencedor;
    
    jogadorVencedor = jogadorVencedorRodada(*jogo, idVencedorRodadaAnterior);
    
    
    if(numeroRodada==1){
        int numeroMaximoCartas=0;
        
        for(jogador= jogadorVencedor; numeroMaximoCartas != (*jogo)->quantidadeJogadores *MAX_QTD_CARTAS_RODADA; jogador = jogador->proximo){
            
            numeroMaximoCartas+=jogador->jogador->cartasNaMao->quantidadeCartas;
            compraCarta((*jogo)->baralho, jogador->jogador);
            
        }
        
    }
    else{
        
        if(!vazio((*jogo)->baralho)){
            
            int p=0;
            for(jogador= (*jogo)->jogadores->primeiro; p != (*jogo)->quantidadeJogadores; jogador = jogador->proximo){
            
                compraCarta((*jogo)->baralho, jogador->jogador);
                p++;
            
            }     
        }
        
    }
    
    
    
    
    
    
}
int jogaCartas(tJogo **jogo,int idVencedorRodadaAnterior){
    tJogadores * jogador = (*jogo)->jogadores->primeiro, *jogadorVencedorAnterior, *jogadorVencedorAtual;
    tMonteRodada monteRodada;
    int vezDoJogador=0;
    int idVencedor=0;
    tCarta  cartaVencedoraAtual; // pega carta vencedora momentaneamente durante a execução de uma rodada.
    
    jogador = jogadorVencedorRodada(*jogo, idVencedorRodadaAnterior);   
    
    jogadorVencedorAnterior = jogador;

    do{
        
        jogaCarta(jogador->jogador, (*jogo)->trunfo, (*jogo)->dificuldade,(*jogo)->modalidade, cartaDoMonte(&monteRodada, vezDoJogador),&cartaVencedoraAtual, vezDoJogador);
        insereIdJogadorNaCartaDoMonte(&monteRodada, vezDoJogador, jogador->jogador);
        cartaVencedoraAtual = cartaVencedoraDoMonte(&monteRodada, vezDoJogador,(*jogo)->trunfo);
        
        
        vezDoJogador++;
        jogador = jogador->proximo;  
        
    }while(jogador!= jogadorVencedorAnterior);

   idVencedor = defineVencedorRodada(&monteRodada, (*jogo)->trunfo, (*jogo)->quantidadeJogadores);
   jogadorVencedorAtual = jogadorVencedorRodada(*jogo, idVencedor);
   printf(CYN "\nO jogador %s venceu a partida: " ,jogadorVencedorAtual->jogador->nome);
    
   recebeCartasRodada(&jogadorVencedorAtual->jogador, &monteRodada,vezDoJogador);
   
   imprimeMonteRodada(&monteRodada, vezDoJogador);

   scanf("%*c");
   scanf("%*c");
   
   return idVencedor;
}
void destroiJogo(tJogo** jogo){
    
    destroiBaralho(&(*jogo)->baralho);
    
    tJogadores *t,*p=(*jogo)->jogadores->primeiro ;
    
    for(int i=0; i< (*jogo)->quantidadeJogadores; i++){
        t= p->proximo;
        destroiJogador(&p->jogador);
        free(p);
        p=t;
    }
    
    free((*jogo)->jogadores);
    free(*jogo);
    
    
}