package com.mycompany.projeto1;

/**
 *
 * @author Caio Peres
 */
public class Tabuleiro {


    private Posicao posicoes[][] = new Posicao[8][8];



    public Tabuleiro(Peca pecas[], boolean load) {

        //inicializa as posicoes do tabuleiro
        inicializaPosicoes(pecas);


        //Coloca as peças no tabuleiro. Se load for verdadeiro, as peças não serão colocadas para que seja possivel colocar a partir do arquivo.
        if(!load)
            inicializaPecas(pecas);
        
    }



    //inicializa as posicoes do tabuleiro
    private void inicializaPosicoes(Peca pecas[]){

        char colunas[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
        int cor;

        try {

            for (int i = 0; i < 8; i++) {

                if ((i + 1) % 2 == 0) {
                    cor = 0;
                } else {
                    cor = 1;
                }

                for (int j = 0; j < 8; j++) {

                    if (j == 0) {
                        posicoes[i][j] = new Posicao(i + 1, colunas[j], cor);

                        if (cor == 1)
                            cor = 0;
                        else
                            cor = 1;

                    } else {
                        posicoes[i][j] = new Posicao(i + 1, colunas[j], cor);

                        if (cor == 1)
                            cor = 0;
                        else
                            cor = 1;
                    }

                }

            }
        }
        catch(Exception e){
            System.out.println("Houve um erro ao inicializar posicoes.");
            return;
        }

    }


    //coloca as peças novas no tabuleiro
    private void inicializaPecas(Peca pecas[]){

        try {

            if(pecas == null){
                throw new NullPointerException();
            }

            for (int i = 0; i < 8; i++) {
                posicoes[6][i].setPeca(pecas[i]);
            }

            for (int i = 8; i < 16; i++) {
                posicoes[7][i - 8].setPeca(pecas[i]);
            }

            for (int i = 16; i < 24; i++) {
                posicoes[1][i - 16].setPeca(pecas[i]);
            }

            for (int i = 24; i < 32; i++) {
                posicoes[0][i - 24].setPeca(pecas[i]);
            }

        }
        catch( NullPointerException e){
            System.out.println("Erro: Peças nulas na inicialização!");
            return;
        }
    }

    
    //checa o movimento da jogada. Faz checagens no tabuleiro e também chamando o método específico da peça.
    public boolean checaMovimento(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino, int vez) {

        //faz checagem se a posição é a mesma
        if (linhaOrigem == linhaDestino && colunaOrigem == colunaDestino) {
            return false;
        }

        //faz checagem dos limites do tabuleiro (coluna já foi checada na jogada pois era necessario converter char para inteiro)
        else if (linhaDestino > 7 || linhaDestino < 0 || linhaOrigem > 7 || linhaOrigem < 0)
            return false;

        //como na descricao do projeto o tabuleiro é quem faz as verificacoes de movimentos das peças, aqui está sendo verificado.

        Peca pecaOrigem = posicoes[linhaOrigem][colunaOrigem].getPeca();
        Peca pecaDestino = posicoes[linhaDestino][colunaDestino].getPeca();

        //verifica se existe uma peça na posicao de origem para fazer a jogada
        if (pecaOrigem == null) {
            return false;
        }
        else {

            //checa se a peça é do jogador
            if(pecaOrigem.getCor() != vez)
                return false;

            //checa se o movimento é valido
            if (pecaOrigem.checaMovimento(linhaOrigem, colunaOrigem, linhaDestino, colunaDestino) == 1 ){

                if(pecaDestino == null) {

                    //checando se tem peças no caminho ( retorna true se tiver livre)
                    if(checaCaminho(linhaOrigem, colunaOrigem, linhaDestino, colunaDestino))
                        return true;
                    else
                        return false;

                }

                else {

                    //peao não pode comer na vertical
                    if (Character.toUpperCase(pecaOrigem.desenho()) == 'P')
                        return false;

                    if(checaCaminho(linhaOrigem, colunaOrigem, linhaDestino, colunaDestino)) {
                        //só pode comer se for peça de cor diferente
                        if (pecaDestino.getCor() != pecaOrigem.getCor())
                            return true;
                        else
                            return false;
                    }
                    else
                        return false;
                }
            }
            else if (pecaOrigem.checaMovimento(linhaOrigem, colunaOrigem, linhaDestino, colunaDestino) == 2 ) {

                //peao só pode ir para diagonal se for para comer uma peça
                if ( pecaDestino != null) {

                    if (pecaDestino.getCor() != pecaOrigem.getCor())
                        return true;
                    else
                        return false;

                }
                else
                    return false;
            }
            else
                return false;
        }

    }



    //funcao baseada em verificações algébricas cobrindo todas as direções dos movimentos
    private boolean checaCaminho(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino){

        Peca pecaOrigem = posicoes[linhaOrigem][colunaOrigem].getPeca();

        //movimento na horizontal
        if(linhaOrigem == linhaDestino && Math.abs(colunaOrigem - colunaDestino) > 1){

            //esquerda
            if(colunaOrigem - colunaDestino > 0) {

                for (int i = colunaOrigem - 1; i > colunaDestino; i--) {
                    if (posicoes[linhaOrigem][i].getPeca() != null) {
                        return false;
                    }
                }

            }

            //direita
            else if(colunaOrigem - colunaDestino < 0) {

                for (int i = colunaOrigem + 1; i < colunaDestino; i++) {
                    if (posicoes[linhaOrigem][i].getPeca() != null) {
                        return false;
                    }
                }

            }

        }

        //movimento na vertical
        else if ( colunaOrigem == colunaDestino && Math.abs(linhaOrigem - linhaDestino) > 1){

            //cima
            if(linhaOrigem - linhaDestino > 0) {

                for (int i = linhaOrigem - 1; i > linhaDestino; i--) {
                    if (posicoes[i][colunaOrigem].getPeca() != null) {
                        return false;
                    }
                }

            }

            //baixo
            else if(linhaOrigem - linhaDestino < 0) {

                for (int i = linhaOrigem + 1; i < linhaDestino; i++) {
                    if (posicoes[i][colunaOrigem].getPeca() != null) {
                        return false;
                    }
                }

            }

        }

        else if (Character.toUpperCase(pecaOrigem.desenho()) == 'C'){
            return true;
        }

        //movimento na diagonal
        else if (Math.abs( colunaDestino - colunaOrigem) == Math.abs( linhaDestino - linhaOrigem)){

            //caso superior esquerdo
            if(colunaOrigem - colunaDestino > 0 && linhaOrigem - linhaDestino > 0){

                int j = colunaOrigem-1;

                for(int i = linhaOrigem - 1; i > linhaDestino; i--){

                    if(posicoes[i][j].getPeca() != null){
                        return false;
                    }

                    j--;
                }

            }

            //caso inferior esquerdo
            else if (colunaOrigem - colunaDestino > 0 && linhaOrigem - linhaDestino < 0){

                int j = colunaOrigem-1;

                for(int i = linhaOrigem + 1; i < linhaDestino; i++){

                    if(posicoes[i][j].getPeca() != null){
                        return false;
                    }

                    j--;
                }

            }

            //caso superior direito
            else if (colunaOrigem - colunaDestino < 0 && linhaOrigem - linhaDestino > 0){

                int j = colunaOrigem+1;

                for(int i = linhaOrigem - 1; i > linhaDestino; i--){

                    if(posicoes[i][j].getPeca() != null){
                        return false;
                    }

                    j++;
                }

            }

            //caso inferior direito
            else if (colunaOrigem - colunaDestino < 0 && linhaOrigem - linhaDestino < 0){

                int j = colunaOrigem+1;

                for(int i = linhaOrigem + 1; i < linhaDestino; i++){

                    if(posicoes[i][j].getPeca() != null){
                        return false;
                    }

                    j++;
                }

            }

        }

        return true;

    }



    //verifica se está em xeque simulando uma posicao do rei ( ou se alguma peça especifica poderia ser comida por outra)
    private boolean checaXequeSimulacao(int linhaRei, int colunaRei, int vez){

        int xeque = 0;

        for( int i = 0; i < 8; i++) {
            for( int j = 0; j < 8; j++) {
                if (posicoes[i][j].getPeca() != null && posicoes[i][j].getPeca().getCor() == vez) {
                    if (checaMovimento(i, j, linhaRei, colunaRei, vez)) {
                        xeque++;
                    }
                }
            }
        }

        if(xeque > 0)
            return true;
        else
            return false;

    }



    //verifica se o rei adversário está em xeque após a jogada
    public int checaXeque(int vez){

        int linhaRei = 0;
        int colunaRei = 0;
        int linhaOrigem = 0;
        int colunaOrigem = 0;
        int xeque = 0;

        for( int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (posicoes[i][j].getPeca() != null) {
                    if (Character.toUpperCase(posicoes[i][j].getPeca().desenho()) == 'R' && posicoes[i][j].getPeca().getCor() != vez) {
                        linhaRei = i;
                        colunaRei = j;
                        break;
                    }
                }
            }
        }



        for( int i = 0; i < 8; i++) {
            for( int j = 0; j < 8; j++) {
                if (posicoes[i][j].getPeca() != null && posicoes[i][j].getPeca().getCor() == vez) {
                    if (checaMovimento(i, j, linhaRei, colunaRei, vez)) {
                        System.out.println("Rei em xeque por: " + posicoes[i][j].getPeca().getClass().getSimpleName());
                        xeque++;
                        linhaOrigem = i;
                        colunaOrigem = j;
                    }
                }
            }
        }



        if(xeque > 0){
            if(consegueResolver(linhaOrigem, colunaOrigem, linhaRei, colunaRei, vez, xeque))
                return 1;
            else
                return 2;

        }
        else{
            return 0;
        }

    }



    //verifica se é possivel resolver o xeque. Se não for possivel, é xeque-mate.
    private boolean consegueResolver(int linhaOrigem, int colunaOrigem, int linhaRei, int colunaRei, int vez, int xeque) {

        int adversario;

        if(vez == 1)
            adversario = 2;
        else
            adversario = 1;

        //se o rei consegue se mover para evitar ser comido
        if (checaMovimento(linhaRei, colunaRei, linhaRei, colunaRei + 1, adversario)){

            if(!checaXequeSimulacao(linhaRei, colunaRei + 1, vez))
                return true;

        }

        else if (checaMovimento(linhaRei, colunaRei, linhaRei, colunaRei - 1, adversario)){

            if(!checaXequeSimulacao(linhaRei, colunaRei - 1, vez))
                return true;

        }

        else if (checaMovimento(linhaRei, colunaRei, linhaRei - 1, colunaRei, adversario)){

            if(!checaXequeSimulacao(linhaRei - 1, colunaRei, vez))
                return true;
        }

        else if (checaMovimento(linhaRei, colunaRei, linhaRei + 1, colunaRei, adversario) ){

            if(!checaXequeSimulacao(linhaRei + 1, colunaRei, vez))
                return true;

        }

        else if (checaMovimento(linhaRei, colunaRei, linhaRei - 1, colunaRei - 1, adversario)){

            if(!checaXequeSimulacao(linhaRei - 1, colunaRei - 1, vez))
                return true;

        }

        else if (checaMovimento(linhaRei, colunaRei, linhaRei + 1, colunaRei - 1, adversario)){

            if(!checaXequeSimulacao(linhaRei + 1, colunaRei - 1, vez))
                return true;
        }


        else if (checaMovimento(linhaRei, colunaRei, linhaRei + 1, colunaRei + 1, adversario)){

            if(!checaXequeSimulacao(linhaRei + 1, colunaRei + 1, vez))
                return true;

        }

        else if(checaMovimento(linhaRei, colunaRei, linhaRei - 1, colunaRei + 1, adversario)) {

            if(!checaXequeSimulacao(linhaRei - 1, colunaRei + 1, vez))
                return true;

        }

        if (xeque > 1)
            return false;

        //verifica se a peça que está dando xeque consegue ser comida por alguma outra
        if(checaXequeSimulacao(linhaOrigem, colunaOrigem, adversario)){
            return true;
        }



        int linhaDestino = linhaRei;
        int colunaDestino = colunaRei;

        //verifica se o adversario tem alguma peça que consegue deter o ataque entrando na frente

        //movimento na horizontal
        if (linhaOrigem == linhaDestino && Math.abs(colunaOrigem - colunaDestino) > 1) {

            //esquerda
            if (colunaOrigem - colunaDestino > 0) {

                for (int i = colunaOrigem - 1; i > colunaDestino; i--) {
                    for (int j = 0; j < 8; j++) {
                        for (int k = 0; k < 8; k++) {
                            if(posicoes[j][k].getPeca() != null) {
                                if(Character.toUpperCase(posicoes[j][k].getPeca().desenho()) != 'R') {
                                    if (checaMovimento(j, k, linhaDestino, i, adversario)) {
                                        return true;
                                    }
                                }
                            }
                        }
                    }
                }
            }

            //direita
            else if (colunaOrigem - colunaDestino < 0) {

                for (int i = colunaOrigem + 1; i < colunaDestino; i++) {
                    for (int j = 0; j < 8; j++) {
                        for (int k = 0; k < 8; k++) {
                            if(posicoes[j][k].getPeca() != null) {
                                if(Character.toUpperCase(posicoes[j][k].getPeca().desenho()) != 'R') {
                                    if (checaMovimento(j, k, linhaDestino, i, adversario)) {
                                        return true;
                                    }
                                }
                            }
                        }
                    }
                }

            }

        }

        //movimento na vertical
        else if (colunaOrigem == colunaDestino && Math.abs(linhaOrigem - linhaDestino) > 1) {

            //cima
            if (linhaOrigem - linhaDestino > 0) {

                for (int i = linhaOrigem - 1; i > linhaDestino; i--) {
                    for (int j = 0; j < 8; j++) {
                        for (int k = 0; k < 8; k++) {
                            if(posicoes[j][k].getPeca() != null) {
                                if(Character.toUpperCase(posicoes[j][k].getPeca().desenho()) != 'R') {
                                    if (checaMovimento(j, k, i, colunaDestino, adversario)) {
                                        return true;
                                    }
                                }
                            }
                        }
                    }
                }

            }

            //baixo
            else if (linhaOrigem - linhaDestino < 0) {

                for (int i = linhaOrigem + 1; i < linhaDestino; i++) {
                    for (int j = 0; j < 8; j++) {
                        for (int k = 0; k < 8; k++) {
                            if(posicoes[j][k].getPeca() != null) {
                                if(Character.toUpperCase(posicoes[j][k].getPeca().desenho()) != 'R') {
                                    if (checaMovimento(j, k, i, colunaDestino, adversario)) {
                                        return true;
                                    }
                                }
                            }
                        }
                    }
                }

            }

        }

        //movimento diagonal
        else if (Math.abs(colunaDestino - colunaOrigem) == Math.abs(linhaDestino - linhaOrigem)) {

            //caso superior esquerdo
            if (colunaOrigem - colunaDestino > 0 && linhaOrigem - linhaDestino > 0) {

                int j = colunaOrigem - 1;

                for (int i = linhaOrigem - 1; i > linhaDestino; i--) {

                    for (int k = 0; k < 8; k++) {
                        for (int l = 0; l < 8; l++) {
                            if(posicoes[k][l].getPeca() != null && posicoes[j][k].getPeca() != null) {
                                if(Character.toUpperCase(posicoes[j][k].getPeca().desenho()) != 'R'){
                                    if (checaMovimento(k, l, i, j, adversario)) {
                                        return true;
                                    }
                                }
                            }
                        }
                    }

                    j--;
                }

            }

            //caso inferior esquerdo
            else if (colunaOrigem - colunaDestino > 0 && linhaOrigem - linhaDestino < 0) {

                int j = colunaOrigem - 1;

                for (int i = linhaOrigem + 1; i < linhaDestino; i++) {

                    for (int k = 0; k < 8; k++) {
                        for (int l = 0; l < 8; l++) {
                            if(posicoes[k][l].getPeca() != null && posicoes[j][k].getPeca() != null) {
                                if(Character.toUpperCase(posicoes[j][k].getPeca().desenho()) != 'R') {
                                    if (checaMovimento(k, l, i, j, adversario)) {
                                        return true;
                                    }
                                }
                            }
                        }
                    }

                    j--;
                }

            }

            //caso superior direito
            else if (colunaOrigem - colunaDestino < 0 && linhaOrigem - linhaDestino > 0) {

                int j = colunaOrigem + 1;

                for (int i = linhaOrigem - 1; i > linhaDestino; i--) {

                    for (int k = 0; k < 8; k++) {
                        for (int l = 0; l < 8; l++) {
                            if(posicoes[k][l].getPeca() != null && posicoes[j][k].getPeca() != null) {
                                if(Character.toUpperCase(posicoes[j][k].getPeca().desenho()) != 'R') {
                                    if (checaMovimento(k, l, i, j, adversario)) {
                                        return true;
                                    }
                                }
                            }
                        }
                    }

                    j++;
                }

            }

            //caso inferior direito
            else if (colunaOrigem - colunaDestino < 0 && linhaOrigem - linhaDestino < 0) {

                int j = colunaOrigem + 1;

                for (int i = linhaOrigem + 1; i < linhaDestino; i++) {

                    for (int k = 0; k < 8; k++) {
                        for (int l = 0; l < 8; l++) {
                            if(posicoes[k][l].getPeca() != null && posicoes[j][k].getPeca() != null) {
                                if(Character.toUpperCase(posicoes[j][k].getPeca().desenho()) != 'R') {
                                    if (checaMovimento(k, l, i, j, adversario)) {
                                        return true;
                                    }
                                }
                            }
                        }
                    }

                    j++;
                }

            }

        }

        return false;

    }


    //método utilizado para resolver um problema de verificacao de peca.
    //verifica se a peça antes do movimento conseguia resolver o xeque.
    public boolean podiaResolver(int linhaPeca, int colunaPeca, int vez){

        int linhaRei = 0;
        int colunaRei = 0;
        int linhaOrigem = 0;
        int colunaOrigem = 0;
        int adversario = 0;

        if(vez == 1)
            adversario = 2;
        else
            adversario = 1;



        for( int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (posicoes[i][j].getPeca() != null) {
                    if (Character.toUpperCase(posicoes[i][j].getPeca().desenho()) == 'R' && posicoes[i][j].getPeca().getCor() != vez) {
                        linhaRei = i;
                        colunaRei = j;
                        break;
                    }
                }
            }
        }



        for( int i = 0; i < 8; i++) {
            for( int j = 0; j < 8; j++) {
                if (posicoes[i][j].getPeca() != null && posicoes[i][j].getPeca().getCor() == vez) {
                    if (checaMovimento(i, j, linhaRei, colunaRei, vez)) {
                        linhaOrigem = i;
                        colunaOrigem = j;
                    }
                }
            }
        }


        if(checaMovimento(linhaPeca, colunaPeca, linhaOrigem, colunaOrigem, adversario))
            return true;
        else
            return false;

    }


    //para poder salvar o desenho do tabuleiro
    public char getDesenho( int i, int j){

        try{
            if( i >= 0 && i < 8 && j >= 0 && j < 8)
                if(posicoes[i][j].getPeca() != null)
                    return posicoes[i][j].getPeca().desenho();
                else
                    return 0;
            else
                throw new IllegalArgumentException();
        }
        catch(IllegalArgumentException e){
            System.out.println("Valor invalido para a posicao.");
            return 0;
        }



    }



    //metodo para colocar peça na posicao a partir do tabuleiro
    //retorna a peça comida caso o movimento envolva comer uma peça. Caso não coma uma peça, retorna null.
    public Peca setPeca(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino) {


        //ja foi checado linhas e colunas no metodo checaMovimento()
        Peca peca = null;

        if(posicoes[linhaDestino][colunaDestino].getPeca() != null){
            peca = posicoes[linhaDestino][colunaDestino].getPeca();
            posicoes[linhaDestino][colunaDestino].setPeca( posicoes[linhaOrigem][colunaOrigem].getPeca() );
            posicoes[linhaOrigem][colunaOrigem].setPeca(null);
            return peca;
        }
        else {
            posicoes[linhaDestino][colunaDestino].setPeca( posicoes[linhaOrigem][colunaOrigem].getPeca() );
            posicoes[linhaOrigem][colunaOrigem].setPeca(null);
            return peca;
        }

    }


    //importante para colocar a partir do arquivo na classe jogo e também para voltar a peça removida no caso da jogada não resolver o xeque
    //não cabe exceções
    public void setPeca(int linha, int coluna, Peca peca){
        posicoes[linha][coluna].setPeca(peca);
    }


    
    //desenha o tabuleiro
    public void desenhar(){

        System.out.println("");
        
        for(int i = 0; i<8; i++){
            
            System.out.print(8 - (i) + " ");
            
            System.out.print("|");
            for(int j = 0; j<8; j++){

                if(posicoes[i][j].getPeca() != null) {
                    System.out.print(posicoes[i][j].getPeca().desenho() + "|");
                }
                else
                    System.out.print("_|");
                
            }
            
            System.out.println("");
       
        }
       
        for(int i = 0; i<8; i++){
         
            char colunas[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
            
            if(i == 0)
                System.out.print("   " + colunas[0]);
            else
                System.out.print(" " + colunas[i]);
            
            
        }
        
    }
    
    
    
}
