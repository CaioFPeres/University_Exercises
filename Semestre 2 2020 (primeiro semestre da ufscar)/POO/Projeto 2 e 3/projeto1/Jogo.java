package com.mycompany.projeto1;

import java.io.*;
import java.util.NoSuchElementException;
import java.util.Scanner;

/**
 *
 * @author Caio Peres
 */
public class Jogo {

    //branco
    private Jogador jogador1;
    //preto
    private Jogador jogador2;

    private int vez;
    private int estado; //0 - inicio, 1 - xeque, 2 - xeque-mate
    private Tabuleiro tabuleiro;

    //na especificacao do projeto, jogo possui 32 peças
    private Peca pecas[] = new Peca[32];



    public Jogo(String nome1, String nome2){

        //jogo comeca com o branco
        setVez(1);
        setEstado(0);

        //inicializa conjunto de pecas
        inicializarPecas();


        try {

            //inicializa o tabuleiro
            tabuleiro = new Tabuleiro(pecas, false);

            //inicializa jogadores
            jogador1 = new Jogador(nome1, pecas, 1);
            jogador2 = new Jogador(nome2, pecas, 2);

        }
        catch(Exception e){ //erro de inicialização (falta de memoria)
            System.out.println("Ocorreu um erro.");
            return;
        }


        tabuleiro.desenhar();

    }


    //construtor para iniciar jogo salvo
    public Jogo() throws NoSuchElementException, FileNotFoundException, NumberFormatException {


        File arquivo = new File("jogosalvo.txt");

        Scanner s = new Scanner(arquivo);


        //inicializa conjunto de pecas
        inicializarPecas();


        //carrega as pecas do arquivo
        carregarPecasArq();


        try {

            //inicializa o tabuleiro
            tabuleiro = new Tabuleiro(pecas, true);


            //inicializa jogadores
            jogador1 = new Jogador(s.next(), pecas, 1);
            jogador2 = new Jogador(s.next(), pecas, 2);

        }
        catch(Exception e){ //erro de inicialização (falta de memoria)
            System.out.println("Ocorreu um erro.");
            return;
        }


        //insere no tabuleiro a partir do arquivo
        insereTabuleiroArq(s);


        tabuleiro.desenhar();

    }



    private void inicializarPecas(){

        try {

            //inicializar conjunto de peças
            for (int i = 0; i < 8; i++) {
                pecas[i] = new Peao(1);
            }

            pecas[8] = new Torre(1);
            pecas[9] = new Cavalo(1);
            pecas[10] = new Bispo(1);
            pecas[11] = new Dama(1);
            pecas[12] = new Rei(1);
            pecas[13] = new Bispo(1);
            pecas[14] = new Cavalo(1);
            pecas[15] = new Torre(1);


            for (int i = 16; i < 24; i++) {
                pecas[i] = new Peao(2);
            }

            pecas[24] = new Torre(2);
            pecas[25] = new Cavalo(2);
            pecas[26] = new Bispo(2);
            pecas[27] = new Dama(2);
            pecas[28] = new Rei(2);
            pecas[29] = new Bispo(2);
            pecas[30] = new Cavalo(2);
            pecas[31] = new Torre(2);

        }
        catch (Exception e){ //erro de inicialização (falta de memoria)
            System.out.println("Ocorreu um erro. Não foi possivel instanciar peças.");
            return;
        }

    }


    public void jogada(int linhaOrigem, char colunaOrigemChar, int linhaDestino, char colunaDestinoChar) throws IllegalArgumentException{

        //converter para indices reais dos vetores e verificar se a coluna é valida
        //nao havia outra forma de fazer que não fosse aqui, pois iria repetir todo esse codigo.
        //não tinha como colocar em um método para converter, pois era necessário retornar 2 valores (as 2 colunas)
        linhaOrigem = 8 - linhaOrigem;
        linhaDestino = 8 - linhaDestino;



        if (Character.isDigit(colunaOrigemChar) || Character.isDigit(colunaDestinoChar)) {
            throw new IllegalArgumentException();
        }




        int colunaOrigem = 0;
        int colunaDestino = 0;

        char colunas[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
        int j = 0;

        int adversario;
        int checaXeque;
        int checaXequeAdversario;
        boolean podia = false;

        if(vez == 1)
            adversario = 2;
        else
            adversario = 1;


        //converter char para indice real de vetores
        for(int i = 0; i<8; i++){


            if(colunaOrigemChar == colunas[i]){
                colunaOrigem = i;
                j++;
            }
            if(colunaDestinoChar == colunas[i]){
                colunaDestino = i;
                j++;
            }

        }


        if (j == 0) {
            throw new IllegalArgumentException();
        }



        //checa o movimento no tabuleiro
        if( tabuleiro.checaMovimento(linhaOrigem, colunaOrigem, linhaDestino, colunaDestino, vez)){

            //funcao utilizada para resolver um problema de verificacao de peca.
            //quando uma peca que poderia resolver o xeque é movida para outra posicao, a funcao checaXeque nao consegue identificar que não resolveu o xeque,
            //pois seria identificado que ainda está em xeque a partir da peca que foi movida.
            //Desse modo se tornaria um xeque-mate.
            //para resolver isso, foi feito uma verificacao antes e depois.
            if(tabuleiro.podiaResolver(linhaOrigem, colunaOrigem, adversario))
                podia = true;

            // coloca a peca na nova posicao e recebe uma peca caso o movimento tenha envolvido comer uma peca
            Peca removida = tabuleiro.setPeca(linhaOrigem, colunaOrigem, linhaDestino, colunaDestino);

            //verifica se comeu uma peça
            if(removida != null) {

                try {
                    setCapturada(removida); //remove a peça colocando status de capturada
                }
                catch(NullPointerException e){
                    System.out.println("Houve um erro. Peca nula.");
                    return;
                }

            }


            //checa os cheques
            checaXeque = tabuleiro.checaXeque(vez);
            checaXequeAdversario = tabuleiro.checaXeque(adversario);

            //faz checagens para ver a situação atual da jogada.
            if( estado == 1 && (checaXeque == 1 || checaXequeAdversario == 1)) {
                System.out.println("");
                System.out.println("Resolva o xeque!");
                tabuleiro.setPeca(linhaDestino, colunaDestino, linhaOrigem, colunaOrigem);
                tabuleiro.setPeca(linhaDestino, colunaDestino, removida);
                return;
            }


            else if(checaXequeAdversario == 1 || checaXequeAdversario == 2){
                System.out.println("");
                System.out.println("Nao se coloque em xeque!");
                tabuleiro.setPeca(linhaDestino, colunaDestino, linhaOrigem, colunaOrigem);
                tabuleiro.setPeca(linhaDestino, colunaDestino, removida);
                return;
            }


            else if (podia && ( (checaXeque == 1 || checaXequeAdversario == 1) || (checaXeque == 2 || checaXequeAdversario == 2 ) ) ){
                System.out.println("");
                System.out.println("Resolva o xeque!");
                tabuleiro.setPeca(linhaDestino, colunaDestino, linhaOrigem, colunaOrigem);
                tabuleiro.setPeca(linhaDestino, colunaDestino, removida);
                return;
            }


            else if(checaXeque == 2 || checaXequeAdversario == 2) {
                tabuleiro.desenhar();
                System.out.println("");
                System.out.println("");
                System.out.println("Xeque-Mate!");
                System.exit(1); //finaliza o jogo
            }


        }
        else{
            System.out.println("Movimento invalido!");
            return;
        }


        //checa xeque
        if(checaXeque == 1 || checaXequeAdversario == 1)
            setEstado(1);
        else if(checaXeque == 2 || checaXequeAdversario == 2)
            setEstado(2);
        else
            setEstado(0);


        //muda a vez para o prox jogador
        if(vez == 1)
            setVez(2);
        else
            setVez(1);


        if(estado != 1) {

            try {
                limparTela();
            }
            catch(IOException | InterruptedException e){
                System.out.println("Não foi possivel limpar a tela.");
            }

        }


        //salva o jogo
        try {
            salvar();
        }
        catch(IOException e){
            System.out.println("Não foi possivel salvar o jogo."); //embora não tenha sido possivel, o jogo continua.
        }


        //desenha
        tabuleiro.desenhar();

    }


    //salva o jogo. Trata exceção no caso de algum problema no arquivo.
    private void salvar() throws IOException{

        String nome = "jogosalvo.txt";

        File arquivo = new File(nome);
        FileWriter fw;

        if (arquivo.exists()) {
            fw = new FileWriter(nome, false);
        }
        else {
            arquivo.createNewFile();
            fw = new FileWriter(nome);
        }

            fw.write(jogador1.getNome() + " " + jogador2.getNome());
            fw.write(System.lineSeparator());
            fw.write(String.valueOf(estado));
            fw.write(System.lineSeparator());
            fw.write(String.valueOf(vez));
            fw.write(System.lineSeparator());

            for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++) {
                    if(tabuleiro.getDesenho(i, j) != 0) {
                        fw.write(tabuleiro.getDesenho(i,j) + " ");
                    }
                    else
                        fw.write("N ");
                }
                fw.write(System.lineSeparator());
            }


            fw.close();

    }



    //carrega as peças do arquivo (coloca se estão capturadas ou nao). Tratando exceção no caso de problema no arquivo.
    private void carregarPecasArq() throws NoSuchElementException, FileNotFoundException, NumberFormatException {

        //coloca todas como capturadas
        for(int i = 0; i < 32; i++){
            pecas[i].setCapturada(1);
        }

        String nome = "jogosalvo.txt";

        File arquivo = new File(nome);

        int rei = 0;

        Scanner sf = new Scanner(arquivo);

        char peca;

        sf.nextLine();

        setEstado(Integer.parseInt(sf.next()));
        setVez(Integer.parseInt(sf.next()));

        while (sf.hasNext()) {

            peca = sf.next().charAt(0);

            if(peca == 'R' || peca == 'r')
                rei++;

            for(int i = 0; i < 32; i++){
                if(pecas[i].desenho() == peca && pecas[i].getCapturada() == 1){
                    pecas[i].setCapturada(0);
                    break;
                }
            }
        }

        if(rei != 2)
            throw new NoSuchElementException();

        sf.close();

    }


    //para inserir no tabuleiro a partir do arquivo. Tratando exceção no caso de problema no arquivo.
    private void insereTabuleiroArq(Scanner sf) throws NoSuchElementException{

        int linha = 0;
        int coluna = 0;
        char peca;


        sf.nextLine();
        sf.nextLine();
        sf.nextLine();


        for (linha = 0; linha < 8; linha++) {

            for (coluna = 0; coluna < 8; coluna++) {

                peca = sf.next().charAt(0);

                for (int i = 0; i < 32; i++) {

                    if (pecas[i].desenho() == peca && pecas[i].getCapturada() == 0) {
                        tabuleiro.setPeca(linha, coluna, pecas[i]);
                        pecas[i].setCapturada(2);
                        break;
                    }
                }
            }
        }


        for(int i = 0; i < 32; i++){
            if(pecas[i].getCapturada() == 2){
                pecas[i].setCapturada(0);
            }
        }

        tabuleiro.checaXeque(1);
        tabuleiro.checaXeque(2);

    }


    //remove a peça do jogo, colocando status de capturada. Pode lançar exceção de peça nula.
    private void setCapturada(Peca peca) throws NullPointerException{

        for(int i = 0; i < 32; i++){
            if(pecas[i].desenho() == peca.desenho() && pecas[i].getCapturada() != 1 && pecas[i].getCor() != vez) {
                pecas[i].setCapturada(1);
                break;
            }
        }

    }

    
    // Funciona apenas nos terminais windows e linux. Pode lançar exceções.
    public static void limparTela() throws IOException, InterruptedException{

        if (System.getProperty("os.name").contains("Windows"))
            new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
        else
            Runtime.getRuntime().exec("clear");

    }
    


    public String getNomeJogador(){
        
        if(vez == 1){
            return jogador1.getNome();
        }
        else{
            return jogador2.getNome();
                
        }
        
    }

    //metodo com tratamento de exceções
    private void setEstado(int estado){

        try{
            if(estado < 3)
                this.estado = estado;
            else
                throw new IllegalArgumentException();
        }
        catch(IllegalArgumentException e){
            System.out.println("Valor invalido para o estado.");
        }

    }

    //metodo com tratamento de exceções
    private void setVez(int vez){

        try{
            if(vez < 3)
                this.vez = vez;
            else
                throw new IllegalArgumentException();
        }
        catch(IllegalArgumentException e){
            System.out.println("Valor invalido para vez.");
        }

    }





}
