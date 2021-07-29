#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

int i, j, f;

void menu(){
    int o,s,e;
    system(" ");
    do{
    printf("\nSelecione o tamanho do tabuleiro:\n1=pequeno\n2=medio\n3=grande\n4=ajuda\n5=fechar menu.\n");
    scanf("%d",&o);
    switch(o){
        case 1:
            system(" ");
            printf("Selecione a dificuldade:\n1=facil\n2=medio\n3=dificil\n4=voltar ao menu principal.\n");
            scanf("%d",&s);
            switch(s){
                    case 1:
                        o=TPF();
                        break;
                    case 2:
                        TPM();
                        break;
                    case 3:
                        TPD();
                        break;
                    case 4:
                        menu();
                        break;
                    //default:
            }break;
        case 2:
            system(" ");
            printf("Selecione a dificuldade:\n1=facil\n2=medio\n3=dificil\n4=voltar ao menu principal.\n");
            scanf("%d",&s);
            switch(s){
                    case 1:
                        TMF();
                        break;
                    case 2:
                        TMM();
                        break;
                    case 3:
                        TMD();
                        break;
                    case 4:
                        menu();
                        break;
                    //default:
            }break;
        case 3:
            system(" ");
            printf("Selecione a dificuldade:\n1=facil\n2=medio\n3=dificil\n4=voltar ao menu principal.\n");
            scanf("%d",&s);
            switch(s){
                    case 1:
                        TGF();
                        break;
                    case 2:
                        TGM();
                        break;
                    case 3:
                        TGD();
                        break;
                    case 4:
                        menu();
                        break;
                    //default:
            }break;
        case 4:
            system(" ");
            do{
            printf("\nSobre o que voce deseja saber?\n1=regras do jogo\n2=como jogar\n3=Duvidas frequentes\n4=Funcionamento\n5=voltar ao menu principal.\n");
            scanf("%d",&s);
            switch(s){
                case 1:
                    printf("\nO jogo se baseia em destruir todos os navios presentes no tabuleiro com o numero minimo de erros(acertos na agua).\n");
                    printf("\nPara voltar ao menu pressione 1.\nPara sair do aplicativo digite 2.\n");
                    scanf("%i", &e);
                    if(e == 1){
                        menu();
                    }
                    else{
                        escolha();
                    }
                    break;
                case 2:
                    printf("\nDigite a coordenada 'x' que deseja, aperte enter e logo em seguida digite a coordenada 'y' que deseja.\nAperte enter de novo para atualizar o tabuleiro.\n");
                    printf("\nPara voltar ao menu pressione 1.\nPara sair do aplicativo digite 2.\n");
                    scanf("%i", &e);
                    if(e == 1){
                        menu();
                    }
                    else{
                        escolha();
                    }
                    break;
                case 3:
                    printf("\n1-Preciso apertar enter para cada coordenada?\nR: Sim\n\n2-Quais os tamanhos dos tabuleiros?\nR: Pequeno = 6x6;\n   Medio = 8x8;\n   Grande = 10x10.\n\n3-O que acontece se eu digitar linhas e colunas erradas?(linha = 11 por exemplo).\nR: Simplesmente perde uma rodada pois atirou fora do tabuleiro.\n");
                    printf("\nPara voltar ao menu pressione 1.\nPara sair do aplicativo digite 2.\n");
                    scanf("%i", &e);
                    if(e == 1){
                        menu();
                    }
                    else{
                        escolha();
                    }
                    break;
                case 4:
                    printf("\nO jogo analisa as coordenadas enviadas pelo jogador e em seguida a compara com a coordenada correspondente dentro da matriz.\nSe acertar um dos barcos imprime uma mensagem indicando qual barco acertou e se o destruiu.\n");
                    printf("\nPara voltar ao menu pressione 1.\nPara sair do aplicativo digite 2: \n");
                    scanf("%i", &e);
                    if(e == 1){
                        menu();
                    }
                    else{
                        escolha();
                    }
                    break;
                case 5:
                    menu();
                    break;
                default:
                    printf("\nOpcao invalida\n");
                    break;
                }break;
                case 6:
                    MT();
                    break;
            }while(s!=5);
        /*default:
            printf("opcao invalida\n");
            break;*/

    }
    }while(o!=5);
}

int TPF(){
    int hcontador=0, tcontador=0, ccontador=0, econtador=0, pcontador=0,contador=0, fim=1,op,op2;
    system(" ");
    char inimigo[7][7] = {

                           {0, 0, 0, 0, 0, 0, 0,},
                           {0, 1, 0, 3, 3, 3, 3,},
                           {0, 0, 0, 0, 0, 0, 0,},
                           {0, 0, 2, 2, 2, 0, 0,},
                           {0, 0, 0, 0, 0, 0, 0,},
                           {0, 2, 2, 2, 0, 1, 0,},
                           {0, 0, 0, 1, 0, 0, 0,}};
    char tabuleiro[7][7];
    for(i=1; i<7; i++){
             for(j=1; j<7; j++){
                      tabuleiro[i][j] =  '.';
                      printf("[ % c ]", tabuleiro[i][j]);
             }
             printf("\n");
    }
    printf("digite:\n1=Começar o jogo;\n2=voltar uma rodada;\nQualquer outro numero = sair do jogo:\n");
    scanf("%d",&op);
    switch(op){
		case 1:
    		printf("Informe as coordenadas do tiro (linha): ");
    		scanf("%d", &i);
    		printf("Informe as coordenadas do tiro (Coluna): ");
   			scanf("%d", &j);
    		printf("\n");
    		while(fim !=0){
            	if(inimigo[i][j] == 1){
                	tabuleiro[i][j] = 'H';
                	Beep(1000,200);
                	printf("Voce destruiu um Hidroavião!");
                	hcontador++;
                	printf("\n");
                }
                else{
                    if(inimigo[i][j] == 2){
                        tabuleiro[i][j] = 'P';
                        Beep(1000,200);
                        printf("Voce acertou um Porta-Avioes!");
                        pcontador++;
                        if(tabuleiro[3][2] == 'P' && tabuleiro[3][3] == 'P' && tabuleiro[3][4] == 'P' || tabuleiro[5][1] == 'P' && tabuleiro[5][2] == 'P' && tabuleiro[5][3] == 'P'){
                            printf("\n");
                            printf("Voce destruiu um Porta-Avioes!");
                            printf("\n");
                        }printf("\n");
                }
                else{
                    if(inimigo[i][j] == 3){
                        tabuleiro[i][j] = 'E';
                        Beep(1000,200);
                        printf("Voce acertou um Encouraçado!");
                        econtador++;
                        if(tabuleiro[1][3] == 'E' && tabuleiro[1][4] == 'E' && tabuleiro[1][5] == 'E' && tabuleiro[1][6] == 'E'){
                            printf("\n");
                            printf("Voce destruiu um Encouraçado!");
                            printf("\n");
                        }printf("\n");
                }else{
                    tabuleiro[i][j] = '0';
                    Beep(750,300);
                    printf("Acertou na agua!");
                    printf("\n");
                }
            }
        }
        for(i=1; i<7; i++){
             for(j=1; j<7; j++){
                      printf("[ % c ]", tabuleiro[i][j]);
             }
             printf("\n");
        }
        contador++;
        if(hcontador>=3 && econtador>=4 && pcontador>=6 || contador == 27){
                fim=0;
        }
                else {
                	do{
						printf("Deseja continuar?:\n1=sim\n2=não\n3=reiniciar o jogo\n");
                		scanf("%d",&op2);
                		switch(op2){
                			case 1:
                				system(" ");
    							for(i=1; i<7; i++){
             						for(j=1; j<7; j++){
                     					printf("[ % c ]", tabuleiro[i][j]);
            						}
             						printf("\n");
        						}
                    			printf("Informe as coordenadas do tiro (linha): ");
                    			scanf("%d", &i);
                    			printf("Informe as coordenadas do tiro (Coluna): ");
                    			scanf("%d", &j);
                    			printf("\n");
                    			break;
                    		case 2:
                    			return 5;
                    			break;
                    		case 3:
                    			return TPF();
                    			break;
                    		default:
                    			printf("Opçao invalida\n");
                    			break;
						}
					}while(op2<1 || op2>3);
               }
    }
    printf("\nFim de jogo\n");
    printf("Numero de Jogadas : %i", contador);
    if(contador == 27){
        contEXPLODE();
    }
    else{
        contWIN();
   		 }
   		fflush(stdin);
   	 	getchar();
    	break;
    	/*
    	case 2:
    		TPF();
    		break;
    	*/
    	default:
    		return 5;
    		break;

	}
	}

int TPM(){
    int hcontador=0, tcontador=0, ccontador=0, econtador=0, pcontador=0,contador=0, fim=1;
    system(" ");
    char inimigo[7][7] = {

                           {0, 0, 0, 0, 0, 0, 0,},
                           {0, 1, 0, 3, 3, 3, 3,},
                           {0, 0, 0, 0, 0, 0, 0,},
                           {0, 0, 2, 2, 2, 0, 0,},
                           {0, 0, 0, 0, 0, 0, 0,},
                           {0, 2, 2, 2, 0, 1, 0,},
                           {0, 0, 0, 1, 0, 0, 0,}};
    char tabuleiro[7][7];
    for(i=1; i<7; i++){
             for(j=1; j<7; j++){
                      tabuleiro[i][j] =  '.';
                      printf("[ % c ]", tabuleiro[i][j]);
             }
             printf("\n");
    }
    printf("Informe as coordenadas do tiro (linha): ");
    scanf("%d", &i);
    printf("Informe as coordenadas do tiro (Coluna): ");
    scanf("%d", &j);
    printf("\n");
    while(fim !=0){
            if(inimigo[i][j] == 1){
                tabuleiro[i][j] = 'H';
                Beep(1000,200);
                printf("Voce destruiu um Hidroavião!");
                hcontador++;
                printf("\n");
                }
                else{
                    if(inimigo[i][j] == 2){
                    tabuleiro[i][j] = 'P';
                    Beep(1000,200);
                    printf("Voce acertou um Porta-Avioes!");
                    pcontador++;
                    if(tabuleiro[3][2] == 'P' && tabuleiro[3][3] == 'P' && tabuleiro[3][4] == 'P' || tabuleiro[5][1] == 'P' && tabuleiro[5][2] == 'P' && tabuleiro[5][3] == 'P'){
                        printf("\n");
                        printf("Voce destruiu um Porta-Avioes!");
                        printf("\n");
                    }printf("\n");
                }
                else{
                    if(inimigo[i][j] == 3){
                    tabuleiro[i][j] = 'E';
                    Beep(1000,200);
                    printf("Voce acertou um Encouraçado!");
                    econtador++;
                    if(tabuleiro[1][3] == 'E' && tabuleiro[1][4] == 'E' && tabuleiro[1][5] == 'E' && tabuleiro[1][6] == 'E'){
                        printf("\n");
                        printf("Voce destruiu um Encouraçado!");
                        printf("\n");
                    }printf("\n");
                }else{
                    tabuleiro[i][j] = '0';
                    Beep(750,250);
                    printf("Acertou na agua!");
                    printf("\n");
                }
            }
        }
        for(i=1; i<7; i++){
             for(j=1; j<7; j++){
                      printf("[ % c ]", tabuleiro[i][j]);
             }
             printf("\n");
        }
        contador++;
        system(" ");
        if(hcontador>=3 && econtador>=4 && pcontador>=6 || contador == 18)
               { fim=0;}
               else {
                printf("Informe as coordenadas do tiro (linha): \n");
                scanf("%d", &i);
                printf("Informe as coordenadas do tiro (Coluna): \n");
                scanf("%d", &j);
                printf("\n");
               }
    }
    printf("\nFim de jogo\n");
    if(contador >= 18){
        contEXPLODE();
    }
    else{
        contWIN();
    }
    fflush(stdin);
    getchar();
}

int TPD(){
    int hcontador=0, tcontador=0, ccontador=0, econtador=0, pcontador=0,contador=0, fim=1;
    system(" ");
    char inimigo[7][7] = {

                        {0, 0, 0, 0, 0, 0, 0,},
                        {0, 1, 0, 3, 3, 3, 3,},
                        {0, 0, 0, 0, 0, 0, 0,},
                        {0, 0, 2, 2, 2, 0, 0,},
                        {0, 0, 0, 0, 0, 0, 0,},
                        {0, 2, 2, 2, 0, 1, 0,},
                        {0, 0, 0, 1, 0, 0, 0,}};
    char tabuleiro[7][7];
    for(i=1; i<7; i++){
             for(j=1; j<7; j++){
                      tabuleiro[i][j] =  '.';
                      printf("[ % c ]", tabuleiro[i][j]);
             }
             printf("\n");
    }
    printf("Informe as coordenadas do tiro (linha): ");
    scanf("%d", &i);
    printf("Informe as coordenadas do tiro (Coluna): ");
    scanf("%d", &j);
    printf("\n");
    while(fim !=0){
            if(inimigo[i][j] == 1){
                tabuleiro[i][j] = 'H';
                Beep(1000,200);
                printf("Voce destruiu um Hidroavião!");
                hcontador++;
                printf("\n");
                }
                else{
                    if(inimigo[i][j] == 2){
                    tabuleiro[i][j] = 'P';
                    Beep(1000,200);
                    printf("Voce acertou um Porta-Avioes!");
                    pcontador++;
                    if(tabuleiro[3][2] == 'P' && tabuleiro[3][3] == 'P' && tabuleiro[3][4] == 'P' || tabuleiro[5][1] == 'P' && tabuleiro[5][2] == 'P' && tabuleiro[5][3] == 'P'){
                        printf("\n");
                        printf("Voce destruiu um Porta-Avioes!");
                        printf("\n");
                    }printf("\n");
                }
                else{
                    if(inimigo[i][j] == 3){
                    tabuleiro[i][j] = 'E';
                    Beep(1000,200);
                    printf("Voce acertou um Encouraçado!");
                    econtador++;
                    if(tabuleiro[1][3] == 'E' && tabuleiro[1][4] == 'E' && tabuleiro[1][5] == 'E' && tabuleiro[1][6] == 'E'){
                        printf("\n");
                        printf("Voce destruiu um Encouraçado!");
                        printf("\n");
                    }printf("\n");
                }else{
                    tabuleiro[i][j] = '0';
                    Beep(750,250);
                    printf("Acertou na agua!");
                    printf("\n");
                }
            }
        }
        for(i=1; i<7; i++){
             for(j=1; j<7; j++){
                      printf("[ % c ]", tabuleiro[i][j]);
             }
             printf("\n");
        }
        contador++;
        system(" ");
        if(hcontador>=3 && econtador>=4 && pcontador>=6 || contador == 13)
               { fim=0;}
               else {
                printf("Informe as coordenadas do tiro (linha): \n");
                scanf("%d", &i);
                printf("Informe as coordenadas do tiro (Coluna): \n");
                scanf("%d", &j);
                printf("\n");
               }
    }
    printf("\nFim de jogo\n");
    if(contador >= 13){
            contEXPLODE();
        }
        else{
            contWIN();
        }
    fflush(stdin);
    getchar();
}

int TMF(){
    int hcontador=0, tcontador=0, ccontador=0, econtador=0, pcontador=0,contador=0, fim=1;
    system(" ");
    char inimigo[9][9] = {
                           {0, 0, 0, 0, 0, 0, 0, 0, 0,},
                           {0, 2, 0, 2, 2, 2, 0, 0, 0,},
                           {0, 2, 0, 0, 0, 0, 0, 0, 0,},
                           {0, 2, 0, 4, 4, 4, 4, 4, 0,},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0,},
                           {0, 3, 3, 3, 3, 0, 0, 1, 0,},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0,},
                           {0, 1, 0, 0, 0, 3, 3, 3, 3,},
                           {0, 0, 0, 0, 1, 0, 0, 1, 0,}};
    char tabuleiro[9][9];

    for(i=1; i<9; i++){
        for(j=1; j<9; j++){
            tabuleiro[i][j] =  '.';
                printf("[ % c ]", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("Informe as coordenadas do tiro (linha): ");
    scanf("%d", &i);
    printf("Informe as coordenadas do tiro (Coluna): ");
    scanf("%d", &j);
    printf("\n");
    while(fim !=0){
        if(inimigo[i][j] == 1){
            tabuleiro[i][j] = 'H';
            Beep(1000,200);
            printf("Voce destruiu um Hidroavião!");
            hcontador++;
            printf("\n");
            }
            else{
                if(inimigo[i][j] == 2){
                tabuleiro[i][j] = 'P';
                Beep(1000,200);
                printf("Voce acertou um Porta-Avioes!");
                pcontador++;
                if(tabuleiro[1][1] == 'P' && tabuleiro[2][1] == 'P' && tabuleiro[3][1] == 'P' || tabuleiro[1][3] == 'P' && tabuleiro[1][4] == 'P' && tabuleiro[1][5] == 'P'){
                    printf("\n");
                    printf("Voce destruiu um Porta-Avioes!");
                    printf("\n");
                }printf("\n");
            }
            else{
                if(inimigo[i][j] == 3){
                    tabuleiro[i][j] = 'E';
                    Beep(1000,200);
                    printf("Voce acertou um Encouraçado!");
                    econtador++;
                    if(tabuleiro[5][1] == 'E' && tabuleiro[5][2] == 'E' && tabuleiro[5][3] == 'E' && tabuleiro[5][4] == 'E' || tabuleiro[7][5] == 'E' && tabuleiro[7][6] == 'E' && tabuleiro[7][7] == 'E' && tabuleiro[7][8] == 'E'){
                        printf("\n");
                        printf("Voce destruiu um Encouraçado!");
                        printf("\n");
                    }printf("\n");
                }
                else{
                    if(inimigo[i][j] == 4){
                        tabuleiro[i][j] = 'C';
                        Beep(1000,200);
                        printf("Você acertou um Cruzador!");
                        ccontador++;
                        if(tabuleiro[3][3] == 'C' && tabuleiro[3][4] == 'C' && tabuleiro[3][5] == 'C' && tabuleiro[3][6] == 'C' && tabuleiro[3][7] == 'C'){
                            printf("\n");
                            printf("Você destruiu um Cruzador!");
                            ccontador++;
                        }printf("\n");
                    }
                    else{
                        tabuleiro[i][j] = '0';
                        Beep(750,250);
                        printf("Acertou na agua!");
                        printf("\n");
                    }
                }
            }
        }
    for(i=1; i<9; i++){
        for(j=1; j<9; j++){
                printf("[ % c ]", tabuleiro[i][j]);
        }
        printf("\n");
    }
    contador++;
    system(" ");
    if(hcontador>=4 && econtador>=8 && pcontador>=6 && ccontador>=5 || contador == 42){
        fim=0;
    }
    else{
        printf("Informe as coordenadas do tiro (linha): \n");
        scanf("%d", &i);
        printf("Informe as coordenadas do tiro (Coluna): \n");
        scanf("%d", &j);
        printf("\n");
        }
    }
    printf("\nFim de jogo\n");
    if(contador >= 42){
        contEXPLODE();
    }
    else{
        contWIN();
    }
    fflush(stdin);
    getchar();
}

int TMM(){
    int hcontador=0, tcontador=0, ccontador=0, econtador=0, pcontador=0,contador=0, fim=1;
    system(" ");
    char inimigo[9][9] = {
                           {0, 0, 0, 0, 0, 0, 0, 0, 0,},
                           {0, 2, 0, 2, 2, 2, 0, 0, 0,},
                           {0, 2, 0, 0, 0, 0, 0, 0, 0,},
                           {0, 2, 0, 4, 4, 4, 4, 4, 0,},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0,},
                           {0, 3, 3, 3, 3, 0, 0, 1, 0,},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0,},
                           {0, 1, 0, 0, 0, 3, 3, 3, 3,},
                           {0, 0, 0, 0, 1, 0, 0, 1, 0,}};
    char tabuleiro[9][9];

    for(i=1; i<9; i++){
        for(j=1; j<9; j++){
            tabuleiro[i][j] =  '.';
                printf("[ % c ]", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("Informe as coordenadas do tiro (linha): ");
    scanf("%d", &i);
    printf("Informe as coordenadas do tiro (Coluna): ");
    scanf("%d", &j);
    printf("\n");
    while(fim !=0){
        if(inimigo[i][j] == 1){
            tabuleiro[i][j] = 'H';
            Beep(1000,200);
            printf("Voce destruiu um Hidroavião!");
            hcontador++;
            printf("\n");
            }
            else{
                if(inimigo[i][j] == 2){
                tabuleiro[i][j] = 'P';
                Beep(1000,200);
                printf("Voce acertou um Porta-Avioes!");
                pcontador++;
                if(tabuleiro[1][1] == 'P' && tabuleiro[2][1] == 'P' && tabuleiro[3][1] == 'P' || tabuleiro[1][3] == 'P' && tabuleiro[1][4] == 'P' && tabuleiro[1][5] == 'P'){
                    printf("\n");
                    printf("Voce destruiu um Porta-Avioes!");
                    printf("\n");
                }printf("\n");
            }
            else{
                if(inimigo[i][j] == 3){
                    tabuleiro[i][j] = 'E';
                    Beep(1000,200);
                    printf("Voce acertou um Encouraçado!");
                    econtador++;
                    if(tabuleiro[5][1] == 'E' && tabuleiro[5][2] == 'E' && tabuleiro[5][3] == 'E' && tabuleiro[5][4] == 'E' || tabuleiro[7][5] == 'E' && tabuleiro[7][6] == 'E' && tabuleiro[7][7] == 'E' && tabuleiro[7][8] == 'E'){
                        printf("\n");
                        printf("Voce destruiu um Encouraçado!");
                        printf("\n");
                    }printf("\n");
                }
                else{
                    if(inimigo[i][j] == 4){
                        tabuleiro[i][j] = 'C';
                        Beep(1000,200);
                        printf("Você acertou um Cruzador!");
                        ccontador++;
                        if(tabuleiro[3][3] == 'C' && tabuleiro[3][4] == 'C' && tabuleiro[3][5] == 'C' && tabuleiro[3][6] == 'C' && tabuleiro[3][7] == 'C'){
                            printf("\n");
                            printf("Você destruiu um Cruzador!");
                            ccontador++;
                        }printf("\n");
                    }
                    else{
                        tabuleiro[i][j] = '0';
                        Beep(750,250);
                        printf("Acertou na agua!");
                        printf("\n");
                    }
                }
            }
        }
    for(i=1; i<9; i++){
        for(j=1; j<9; j++){
                printf("[ % c ]", tabuleiro[i][j]);
        }
        printf("\n");
    }
    contador++;
    system(" ");
    if(hcontador>=4 && econtador>=8 && pcontador>=6 && ccontador>=5 || contador == 32){
        fim=0;
    }
    else{
        printf("Informe as coordenadas do tiro (linha): \n");
        scanf("%d", &i);
        printf("Informe as coordenadas do tiro (Coluna): \n");
        scanf("%d", &j);
        printf("\n");
        }
    }
    printf("\nFim de jogo\n");
    if(contador >= 32){
        contEXPLODE();
    }
    else{
        contWIN();
    }
    fflush(stdin);
    getchar();
}

int TMD(){
    int hcontador=0, tcontador=0, ccontador=0, econtador=0, pcontador=0,contador=0, fim=1;
    system(" ");
    char inimigo[9][9] = {
                           {0, 0, 0, 0, 0, 0, 0, 0, 0,},
                           {0, 2, 0, 2, 2, 2, 0, 0, 0,},
                           {0, 2, 0, 0, 0, 0, 0, 0, 0,},
                           {0, 2, 0, 4, 4, 4, 4, 4, 0,},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0,},
                           {0, 3, 3, 3, 3, 0, 0, 1, 0,},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0,},
                           {0, 1, 0, 0, 0, 3, 3, 3, 3,},
                           {0, 0, 0, 0, 1, 0, 0, 1, 0,}};
    char tabuleiro[9][9];

    for(i=1; i<9; i++){
        for(j=1; j<9; j++){
            tabuleiro[i][j] =  '.';
                printf("[ % c ]", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("Informe as coordenadas do tiro (linha): ");
    scanf("%d", &i);
    printf("Informe as coordenadas do tiro (Coluna): ");
    scanf("%d", &j);
    printf("\n");
    while(fim !=0){
        if(inimigo[i][j] == 1){
            tabuleiro[i][j] = 'H';
            Beep(1000,200);
            printf("Voce destruiu um Hidroavião!");
            hcontador++;
            printf("\n");
            }
            else{
                if(inimigo[i][j] == 2){
                tabuleiro[i][j] = 'P';
                Beep(1000,200);
                printf("Voce acertou um Porta-Avioes!");
                pcontador++;
                if(tabuleiro[1][1] == 'P' && tabuleiro[2][1] == 'P' && tabuleiro[3][1] == 'P' || tabuleiro[1][3] == 'P' && tabuleiro[1][4] == 'P' && tabuleiro[1][5] == 'P'){
                    printf("\n");
                    printf("Voce destruiu um Porta-Avioes!");
                    printf("\n");
                }printf("\n");
            }
            else{
                if(inimigo[i][j] == 3){
                    tabuleiro[i][j] = 'E';
                    Beep(1000,200);
                    printf("Voce acertou um Encouraçado!");
                    econtador++;
                    if(tabuleiro[5][1] == 'E' && tabuleiro[5][2] == 'E' && tabuleiro[5][3] == 'E' && tabuleiro[5][4] == 'E' || tabuleiro[7][5] == 'E' && tabuleiro[7][6] == 'E' && tabuleiro[7][7] == 'E' && tabuleiro[7][8] == 'E'){
                        printf("\n");
                        printf("Voce destruiu um Encouraçado!");
                        printf("\n");
                    }printf("\n");
                }
                else{
                    if(inimigo[i][j] == 4){
                        tabuleiro[i][j] = 'C';
                        Beep(1000,200);
                        printf("Você acertou um Cruzador!");
                        ccontador++;
                        if(tabuleiro[3][3] == 'C' && tabuleiro[3][4] == 'C' && tabuleiro[3][5] == 'C' && tabuleiro[3][6] == 'C' && tabuleiro[3][7] == 'C'){
                            printf("\n");
                            printf("Você destruiu um Cruzador!");
                            ccontador++;
                        }printf("\n");
                    }
                    else{
                        tabuleiro[i][j] = '0';
                        Beep(750,250);
                        printf("Acertou na agua!");
                        printf("\n");
                    }
                }
            }
        }
    for(i=1; i<9; i++){
        for(j=1; j<9; j++){
                printf("[ % c ]", tabuleiro[i][j]);
        }
        printf("\n");
    }
    contador++;
    system(" ");
    if(hcontador>=4 && econtador>=8 && pcontador>=6 && ccontador>=5 || contador == 23){
        fim=0;
    }
    else{
        printf("Informe as coordenadas do tiro (linha): \n");
        scanf("%d", &i);
        printf("Informe as coordenadas do tiro (Coluna): \n");
        scanf("%d", &j);
        printf("\n");
        }
    }
    printf("\nFim de jogo\n");
    if(contador >= 23){
        contEXPLODE();
    }
    else{
        contWIN();
    }
    fflush(stdin);
    getchar();
}

int TGF(){
    int hcontador=0, tcontador=0, ccontador=0, econtador=0, pcontador=0,contador=0, fim=1;
    system(" ");
    char inimigo[11][11] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //0
                            {0, 2, 2, 2, 0, 4, 4, 4, 4, 4, 0}, //1
                            {0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0}, //2
                            {0, 1, 0, 2, 0, 0, 0, 0, 1, 0, 0}, //3
                            {0, 0, 1, 2, 0, 0, 5, 0, 0, 0, 0}, //4
                            {0, 0, 0, 2, 0, 0, 5, 0, 1, 0, 1}, //5
                            {0, 1, 0, 0, 1, 0, 5, 0, 0, 0, 0}, //6
                            {0, 0, 0, 0, 0, 0, 5, 0, 1, 0, 0}, //7
                            {0, 3, 3, 3, 3, 0, 0, 1, 0, 0, 1}, //8
                            {0, 0, 0, 0, 0, 1, 0, 2, 2, 2, 0}, //9
                            {0, 0, 0, 1, 0, 0, 1, 3, 3, 3, 3}};//10
                           //0  1  2  3  4  5  6  7  8  9  10
    char tabuleiro[11][11];
    for(i=1; i<11; i++){
             for(j=1; j<11; j++){
                      tabuleiro[i][j] =  '.';
                      printf("[ % c ]", tabuleiro[i][j]);
             }
             printf("\n");
    }
    printf("Informe as coordenadas do tiro (linha): ");
    scanf("%d", &i);
    printf("Informe as coordenadas do tiro (Coluna): ");
    scanf("%d", &j);
    printf("\n");
    while(fim !=0){
        if(inimigo[i][j] == 1){
            tabuleiro[i][j] = 'H';
            Beep(1000,200);
            printf("Você destruiu um Hidroaviao!");
            hcontador++;
            printf("\n");
            }
            else{
                if(inimigo[i][j] == 2){
                    tabuleiro[i][j] = 'P';
                    Beep(1000,200);
                    printf("voce acertou um Porta-Aviões!");
                    pcontador++;
                    if(tabuleiro[1][1] == 'P' && tabuleiro[1][2] == 'P' && tabuleiro[1][3] == 'P' || tabuleiro[3][3] == 'P' && tabuleiro[4][3] == 'P' && tabuleiro[5][3] == 'P' || tabuleiro[9][7] == 'P' && tabuleiro[9][8] == 'P' && tabuleiro[9][9] == 'P'){
                        printf("\n");
                        printf("Você destruiu um Porta-Aviões!");
                        printf("\n");
                    }
                    printf("\n");
                }
                else{
                if(inimigo[i][j] == 3){
                    tabuleiro[i][j] = 'E';
                    printf("voce acertou um Encouraçado!");
                    econtador += 1;
                        if(tabuleiro[8][1] == 'E' && tabuleiro[8][2] == 'E' && tabuleiro[8][3] == 'E' && tabuleiro[8][4] == 'E' || tabuleiro[10][7] == 'E' && tabuleiro[10][8] == 'E' && tabuleiro[10][9] == 'E' && tabuleiro[10][10] == 'E'){
                            printf("\n");
                            printf(" Você destruiu um Encouraçado!");
                            printf("\n");
                        }
                    printf("\n");
                    }
                    else
                     {
                        if(inimigo[i][j] == 4){
                            tabuleiro[i][j] = 'C';
                            printf("voce acertou um Cruzador!");
                            ccontador++;
                            if(tabuleiro[1][5] == 'C' && tabuleiro[1][6] == 'C' && tabuleiro[1][7] == 'C' && tabuleiro[1][8] == 'C' && tabuleiro[1][9] == 'C'){
                                printf("\n");
                                printf(" Você destruiu um Cruzador!");
                                printf("\n");
                            }
                            printf("\n");
                        }
                        else{
                            if(inimigo[i][j] == 5){
                                tabuleiro[i][j] = 'T';
                                printf("Você acertou um Transportador!");
                                tcontador++;
                                if(tabuleiro[4][6] == 'T' && tabuleiro[5][6] == 'T' && tabuleiro[6][6] == 'T' && tabuleiro[7][6] == 'T'){
                                    printf("\n");
                                    printf("Você destruiu u Transportador!");
                                    printf("\n");
                                }
                                printf("\n");
                            }
                            else {
                                tabuleiro[i][j] = '0';
                                printf("\n");
                                printf("Acertou Na Agua");
                                printf("\n");
                            }
                        }
                    }
                }
            }
            for(i=1; i<11; i++){
                for(j=1; j<11; j++){
                    printf("[ %c ]", tabuleiro[i][j]);
                }
                printf("\n");
            }
            contador++;
            system(" ");
            if(hcontador >= 16 && tcontador >= 4 && ccontador >= 5 && econtador >= 8 && pcontador >= 9|| contador == 85){
                fim=0;
            }
            else{
                printf("Informe as coordenadas do tiro (linha): \n");
                scanf("%d", &i);
                printf("Informe as coordenadas do tiro (Coluna): \n");
                scanf("%d", &j);
                printf("\n");
            }
        }
        printf("\nFim de jogo\n");
        if(contador >= 75){
            contEXPLODE();
        }
        else{
            contWIN();
        }
    fflush(stdin);
    getchar();
}

int TGM(){
    int hcontador=0, tcontador=0, ccontador=0, econtador=0, pcontador=0,contador=0, fim=1;
    system(" ");
    char inimigo[11][11] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //0
                            {0, 2, 2, 2, 0, 4, 4, 4, 4, 4, 0}, //1
                            {0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0}, //2
                            {0, 1, 0, 2, 0, 0, 0, 0, 1, 0, 0}, //3
                            {0, 0, 1, 2, 0, 0, 5, 0, 0, 0, 0}, //4
                            {0, 0, 0, 2, 0, 0, 5, 0, 1, 0, 1}, //5
                            {0, 1, 0, 0, 1, 0, 5, 0, 0, 0, 0}, //6
                            {0, 0, 0, 0, 0, 0, 5, 0, 1, 0, 0}, //7
                            {0, 3, 3, 3, 3, 0, 0, 1, 0, 0, 1}, //8
                            {0, 0, 0, 0, 0, 1, 0, 2, 2, 2, 0}, //9
                            {0, 0, 0, 1, 0, 0, 1, 3, 3, 3, 3}};//10
                           //0  1  2  3  4  5  6  7  8  9  10
    char tabuleiro[11][11];
    for(i=1; i<11; i++){
             for(j=1; j<11; j++){
                      tabuleiro[i][j] =  '.';
                      printf("[ % c ]", tabuleiro[i][j]);
             }
             printf("\n");
    }
    printf("Informe as coordenadas do tiro (linha): ");
    scanf("%d", &i);
    printf("Informe as coordenadas do tiro (Coluna): ");
    scanf("%d", &j);
    printf("\n");
    while(fim !=0){
        if(inimigo[i][j] == 1){
            tabuleiro[i][j] = 'H';
            Beep(1000,200);
            printf("Você destruiu um Hidroaviao!");
            hcontador++;
            printf("\n");
            }
            else{
                if(inimigo[i][j] == 2){
                    tabuleiro[i][j] = 'P';
                    Beep(1000,200);
                    printf("voce acertou um Porta-Aviões!");
                    pcontador++;
                    if(tabuleiro[1][1] == 'P' && tabuleiro[1][2] == 'P' && tabuleiro[1][3] == 'P' || tabuleiro[3][3] == 'P' && tabuleiro[4][3] == 'P' && tabuleiro[5][3] == 'P' || tabuleiro[9][7] == 'P' && tabuleiro[9][8] == 'P' && tabuleiro[9][9] == 'P'){
                        printf("\n");
                        printf("Você destruiu um Porta-Aviões!");
                        printf("\n");
                    }
                    printf("\n");
                }
                else{
                if(inimigo[i][j] == 3){
                    tabuleiro[i][j] = 'E';
                    printf("voce acertou um Encouraçado!");
                    econtador += 1;
                        if(tabuleiro[8][1] == 'E' && tabuleiro[8][2] == 'E' && tabuleiro[8][3] == 'E' && tabuleiro[8][4] == 'E' || tabuleiro[10][7] == 'E' && tabuleiro[10][8] == 'E' && tabuleiro[10][9] == 'E' && tabuleiro[10][10] == 'E'){
                            printf("\n");
                            printf(" Você destruiu um Encouraçado!");
                            printf("\n");
                        }
                    printf("\n");
                    }
                    else
                     {
                        if(inimigo[i][j] == 4){
                            tabuleiro[i][j] = 'C';
                            printf("voce acertou um Cruzador!");
                            ccontador++;
                            if(tabuleiro[1][5] == 'C' && tabuleiro[1][6] == 'C' && tabuleiro[1][7] == 'C' && tabuleiro[1][8] == 'C' && tabuleiro[1][9] == 'C'){
                                printf("\n");
                                printf(" Você destruiu um Cruzador!");
                                printf("\n");
                            }
                            printf("\n");
                        }
                        else{
                            if(inimigo[i][j] == 5){
                                tabuleiro[i][j] = 'T';
                                printf("Você acertou um Transportador!");
                                tcontador++;
                                if(tabuleiro[4][6] == 'T' && tabuleiro[5][6] == 'T' && tabuleiro[6][6] == 'T' && tabuleiro[7][6] == 'T'){
                                    printf("\n");
                                    printf("Você destruiu u Transportador!");
                                    printf("\n");
                                }
                                printf("\n");
                            }
                            else {
                                tabuleiro[i][j] = '0';
                                printf("\n");
                                printf("Acertou Na Agua");
                                printf("\n");
                            }
                        }
                    }
                }
            }
            for(i=1; i<11; i++){
                for(j=1; j<11; j++){
                    printf("[ %c ]", tabuleiro[i][j]);
                }
                printf("\n");
            }
            contador++;
            system(" ");
            if(hcontador >= 16 && tcontador >= 4 && ccontador >= 5 && econtador >= 8 && pcontador >= 9|| contador == 65){
                fim=0;
            }
            else{
                printf("Informe as coordenadas do tiro (linha): \n");
                scanf("%d", &i);
                printf("Informe as coordenadas do tiro (Coluna): \n");
                scanf("%d", &j);
                printf("\n");
            }
        }
        printf("\nFim de jogo\n");
        if(contador >= 75){
            contEXPLODE();
        }
        else{
            contWIN();
        }
    fflush(stdin);
    getchar();
}

int TGD(){
    int hcontador=0, tcontador=0, ccontador=0, econtador=0, pcontador=0,contador=0, fim=1;
    system(" ");
    char inimigo[11][11] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //0
                            {0, 2, 2, 2, 0, 4, 4, 4, 4, 4, 0}, //1
                            {0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0}, //2
                            {0, 1, 0, 2, 0, 0, 0, 0, 1, 0, 0}, //3
                            {0, 0, 1, 2, 0, 0, 5, 0, 0, 0, 0}, //4
                            {0, 0, 0, 2, 0, 0, 5, 0, 1, 0, 1}, //5
                            {0, 1, 0, 0, 1, 0, 5, 0, 0, 0, 0}, //6
                            {0, 0, 0, 0, 0, 0, 5, 0, 1, 0, 0}, //7
                            {0, 3, 3, 3, 3, 0, 0, 1, 0, 0, 1}, //8
                            {0, 0, 0, 0, 0, 1, 0, 2, 2, 2, 0}, //9
                            {0, 0, 0, 1, 0, 0, 1, 3, 3, 3, 3}};//10
                           //0  1  2  3  4  5  6  7  8  9  10
    char tabuleiro[11][11];
    for(i=1; i<11; i++){
             for(j=1; j<11; j++){
                      tabuleiro[i][j] =  '.';
                      printf("[ % c ]", tabuleiro[i][j]);
             }
             printf("\n");
    }
    printf("Informe as coordenadas do tiro (linha): ");
    scanf("%d", &i);
    printf("Informe as coordenadas do tiro (Coluna): ");
    scanf("%d", &j);
    printf("\n");
    while(fim !=0){
        if(inimigo[i][j] == 1){
            tabuleiro[i][j] = 'H';
            Beep(1000,200);
            printf("Você destruiu um Hidroaviao!");
            hcontador++;
            printf("\n");
            }
            else{
                if(inimigo[i][j] == 2){
                    tabuleiro[i][j] = 'P';
                    Beep(1000,200);
                    printf("voce acertou um Porta-Aviões!");
                    pcontador++;
                    if(tabuleiro[1][1] == 'P' && tabuleiro[1][2] == 'P' && tabuleiro[1][3] == 'P' || tabuleiro[3][3] == 'P' && tabuleiro[4][3] == 'P' && tabuleiro[5][3] == 'P' || tabuleiro[9][7] == 'P' && tabuleiro[9][8] == 'P' && tabuleiro[9][9] == 'P'){
                        printf("\n");
                        printf("Você destruiu um Porta-Aviões!");
                        printf("\n");
                    }
                    printf("\n");
                }
                else{
                if(inimigo[i][j] == 3){
                    tabuleiro[i][j] = 'E';
                    printf("voce acertou um Encouraçado!");
                    econtador += 1;
                        if(tabuleiro[8][1] == 'E' && tabuleiro[8][2] == 'E' && tabuleiro[8][3] == 'E' && tabuleiro[8][4] == 'E' || tabuleiro[10][7] == 'E' && tabuleiro[10][8] == 'E' && tabuleiro[10][9] == 'E' && tabuleiro[10][10] == 'E'){
                            printf("\n");
                            printf(" Você destruiu um Encouraçado!");
                            printf("\n");
                        }
                    printf("\n");
                    }
                    else
                     {
                        if(inimigo[i][j] == 4){
                            tabuleiro[i][j] = 'C';
                            printf("voce acertou um Cruzador!");
                            ccontador++;
                            if(tabuleiro[1][5] == 'C' && tabuleiro[1][6] == 'C' && tabuleiro[1][7] == 'C' && tabuleiro[1][8] == 'C' && tabuleiro[1][9] == 'C'){
                                printf("\n");
                                printf(" Você destruiu um Cruzador!");
                                printf("\n");
                            }
                            printf("\n");
                        }
                        else{
                            if(inimigo[i][j] == 5){
                                tabuleiro[i][j] = 'T';
                                printf("Você acertou um Transportador!");
                                tcontador++;
                                if(tabuleiro[4][6] == 'T' && tabuleiro[5][6] == 'T' && tabuleiro[6][6] == 'T' && tabuleiro[7][6] == 'T'){
                                    printf("\n");
                                    printf("Você destruiu u Transportador!");
                                    printf("\n");
                                }
                                printf("\n");
                            }
                            else {
                                tabuleiro[i][j] = '0';
                                printf("\n");
                                printf("Acertou Na Agua");
                                printf("\n");
                            }
                        }
                    }
                }
            }
            for(i=1; i<11; i++){
                for(j=1; j<11; j++){
                    printf("[ %c ]", tabuleiro[i][j]);
                }
                printf("\n");
            }
            contador++;
            system(" ");
            if(hcontador >= 16 && tcontador >= 4 && ccontador >= 5 && econtador >= 8 && pcontador >= 9|| contador == 42){
                fim=0;
            }
            else{
                printf("Informe as coordenadas do tiro (linha): \n");
                scanf("%d", &i);
                printf("Informe as coordenadas do tiro (Coluna): \n");
                scanf("%d", &j);
                printf("\n");
            }
        }
        printf("\nFim de jogo\n");
        if(contador >= 75){
            contEXPLODE();
        }
        else{
            contWIN();
        }
    fflush(stdin);
    getchar();
}

int contEXPLODE(){
    system(" ");
    DeathMusic();
    printf("\n####################YOU DIED#####################");
    printf("\n###########Do you want to Continue?##############");
    printf("\nn###########1-YES               2-NO#############");
    scanf("%i", &f);
    if(f == 1){
        TPF();
    }
    else{
        if(f == 2){
            menu();
        }
        else{
            printf("Invalid Choise!");
            printf("\n");
            printf("\n");
            contEXPLODE();
        }
    }
}

int contWIN(){
    system(" ");
    OofT();
    printf("\n####################YOU WIN######################");
    printf("\n###########Do you want to Continue?##############");
    printf("\n###########1-YES               2-NO##############");
    scanf("%i", &f);
    if(f == 1){
        TPF();
    }
    else{
        if(f == 2){
            menu();
        }
        else{
            printf("Invalid Choise!");
            printf("\n");
            printf("\n");
            contWIN();
        }
    }
}

int escolha(e){
    if(e == 2){
    }
    else{
        printf("\nOpção invalida!\n");
        escolha();
    }
}

int OofT(){
    /*Beep(880,500);
    Beep(587.33,1000);
    Beep(698.46,500);
    Beep(880,500);
    Beep(587.33,1000);*/
    Beep(698.46,500);
    Beep(880,250);
    Beep(1046.50,250);
    Beep(987.77,500);
    Beep(783.99,500);
    Beep(698.46,250);
    Beep(783.99,250);
    Beep(880,500);
    Beep(587.33,500);
    Beep(523.25,250);
    Beep(659.26,250);
    Beep(587.33,750);
}

int DeathMusic(){
    Beep(392,350);
    Beep(392,350);
    Beep(392,350);
    Beep(311.1,250);
    Beep(466.2,250);
    Beep(392,350);
    Beep(311.1,250);
    Beep(466.2,250);
    Beep(392,700);
}

int Intro(){
printf("          _    _      _                                     \n");
printf("         | |  | |    | |                                    \n");
printf("         | |  | | ___| | ___ ___  _ __ ___   ___            \n");
printf("         | |/\\| |/ _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\      \n");
printf("         \\  /\\  /  __/ | (_| (_) | | | | | |  __/         \n");
printf("          \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___|     \n");
printf(" _____      ______       _   _   _           _     _                \n");
printf("|_   _|     | ___ \\     | | | | | |         | |   (_)              \n");
printf("  | | ___   | |_/ / __ _| |_| |_| | ___  ___| |__  _ _ __           \n");
printf("  | |/ _ \\  | ___ \\/ _` | __| __| |/ _ \\/ __| '_ \\| | '_ \\      \n");
printf("  | | (_) | | |_/ / (_| | |_| |_| |  __/\\__ \\ | | | | |_) |       \n");
printf("  \\_/\\___/  \\____/ \\__,_|\\__|\\__|_|\\___||___/_| |_|_| .__/   \n");
printf("                                                    | |             \n");
printf("                                                    |_|             \n");

printf("          Aperte Qualquer Tecla para Continuar!                     \n");
getch();
}

int MT(){
    Beep(658, 125);
    Beep(1320, 500);
    Beep(990, 250);
    Beep(1056, 250);
    Beep(1188, 250);
    Beep(1320, 125);
    Beep(1188, 125);
    Beep(1056, 250);
    Beep(990, 250);
    Beep(880, 500);
    Beep(880, 250);
    Beep(1056, 250);
    Beep(1320, 500);
    Beep(1188, 250);
    Beep(1056, 250);
    Beep(990, 750);
    Beep(1056, 250);
    Beep(1188, 500);
    Beep(1320, 500);
    Beep(1056, 500);
    Beep(880, 500);
    Beep(880, 500);
    Sleep(250);
    printf("\n\n#############################\n#                           #\n#          Creditos         #\n#                           #\n#############################\n\n\n");
    Beep(1188, 500);
    Beep(1408, 250);
    Beep(1760, 500);
    Beep(1584, 250);
    Beep(1408, 250);
    Beep(1320, 750);
    Beep(1056, 250);
    Beep(1320, 500);
    Beep(1188, 250);
    Beep(1056, 250);
    Beep(990, 500);
    Beep(990, 250);
    Beep(1056, 250);
    Beep(1188, 500);
    Beep(1320, 500);
    Beep(1056, 500);
    Beep(880, 500);
    Beep(880, 500);
    Sleep(500);
    printf("\n\n#############################\n#                           #\n# Criado e Desenvolvido Por #\n#                           #\n#      Vinicius Moreira     #\n#                           #\n#     Guilherme Takeshi     #\n#                           #\n#         Caio Peres        #\n#                           #\n#############################\n\n\n");
    Beep(1320, 500);
    Beep(990, 250);
    Beep(1056, 250);
    Beep(1188, 250);
    Beep(1320, 125);
    Beep(1188, 125);
    Beep(1056, 250);
    Beep(990, 250);
    Beep(880, 500);
    Beep(880, 250);
    Beep(1056, 250);
    Beep(1320, 500);
    Beep(1188, 250);
    Beep(1056, 250);
    Beep(990, 750);
    Beep(1056, 250);
    Beep(1188, 500);
    Beep(1320, 500);
    Beep(1056, 500);
    Beep(880, 500);
    Beep(880, 500);
    Sleep(250);
    printf("\n\n#############################\n#                           #\n#     Obrigado Por Jogar    #\n#                           #\n#############################\n\n");
    Beep(1188, 500);
    Beep(1408, 250);
    Beep(1760, 500);
    Beep(1584, 250);
    Beep(1408, 250);
    Beep(1320, 750);
    Beep(1056, 250);
    Beep(1320, 500);
    Beep(1188, 250);
    Beep(1056, 250);
    Beep(990, 500);
    Beep(990, 250);
    Beep(1056, 250);
    Beep(1188, 500);
    Beep(1320, 500);
    Beep(1056, 500);
    Beep(880, 500);
    Beep(880, 500);
    Sleep(500);
    system("pause");
}

void main(){
    Intro();
    setlocale(LC_ALL, "Portuguese");
    menu();
}
