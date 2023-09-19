    while(*Ganhador == False){
        if(*Ganhador == True){
            break;
        }
        else if(primeiraJogada1 == True){
            int iDescarte=0;
            Desempilha(pBaralho, cartaDesempilha);
            Empilha(pJogadorUm, cartaDesempilha, nBaralho);
            printf("JOGADOR 1\nSUAS CARTAS:\n");
            imprimeCartas(pJogadorUm, mao+1);
            printf("\n");
            printf("QUAL SERA DESCARTADA? ");
            scanf("%d",&iDescarte);
            descarteCarta(pJogadorUm, mao, iDescarte, pDescarte, nBaralho);
            imprimeCartas(pJogadorUm, mao);
            printf("\n"); //ESPAÇO ENTRE UM JOGADOR E OUTRO
            primeiraJogada1 = False;
        }
        else if(primeiraJogada2 == True){
            int iDescarte=0;
            Desempilha(pBaralho, cartaDesempilha);
            Empilha(pJogadorDois, cartaDesempilha, nBaralho);
            printf("JOGADOR 2\nSUAS CARTAS:\n");
            imprimeCartas(pJogadorDois, mao+1);
            printf("\n");
            printf("QUAL SERA DESCARTADA? ");
            scanf("%d",&iDescarte);
            descarteCarta(pJogadorDois, mao, iDescarte, pDescarte, nBaralho);
            imprimeCartas(pJogadorDois, mao);
            printf("\n"); //ESPAÇO ENTRE UM JOGADOR E OUTRO
            primeiraJogada2 = False;
        }
        else if(primeiraJogada1 == False && primeiraJogada2 == False){
            break;
        }
    }