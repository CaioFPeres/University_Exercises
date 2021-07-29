#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
    int t1, t2, t3;
    printf("Escolha entre 1 = ave e 2 = mamifero\n");
    scanf("%d",&t1);
    switch(t1){
    case 1:
        printf("\nEscolha entre 1 = nao voador e 2 = nadador\n");
        scanf("%d",&t2);
        switch(t2)
        {
        case 2:
            {
                printf("\n\tpato\n\t");
                break;
            }
        case 1:
            printf("\nEscolha entre 1 = polar e 2 = tropical\n");
            scanf("%d",&t3);
            switch(t3)
            {
            case 1:
                {
                    printf("\n\tpinguim\n\t");
                    break;
                }
            case 2:
                {
                    printf("\n\tavestruz\n\t");
                    break;
                }
            }
        }
	break;
            case 2:
                printf("\nEscolha entre 1 = bipede e 2 = quadrupede\n");
                scanf("%d",&t2);
                switch(t2)
                {
                case 1:
                    {
                        printf("\nEscolha entre 1 = onivoro e 2 = frutifero\n");
                        scanf("%d",&t3);
                    }
                        switch(t3)
                        {
                        case 1:
                            {
                              printf("\n\thumano\n\t");
                              break;
                            }
                        case 2:
                            {
                                printf("\n\tmacaco\n\t");
                                break;
                            }
                        }break;
                        case 2:
                            {
                                printf("\nEscolha entre 1 = carnivoro e 2 = herbivoro\n");
                                scanf("%d",&t3);
                            }
                                switch(t3)
                                  {
                                  case 1:
                                    {
                                        printf("\n\tleao\n\t");
                                        break;
                                    }
                                  case 2:
                                    {
                                        printf("\n\tcavalo\n\t");
                                        break;
                                    }
                                  }break;
                }
}
	
	return 0;
}
