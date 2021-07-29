package com.mycompany.projeto1;

import java.io.IOException;

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
    private int estado; //0 - inicio, 1 - meio, 3 - xeque, 4 - xeque-mate
    private Tabuleiro tabuleiro;
    
    //Pecas pecas[] = new Pecas[];
    
    public Jogo(String nome1, String nome2){
        
        tabuleiro = new Tabuleiro();
        
        //jogo comeca com o branco
        vez = 1;
        
        setEstado(0);
        
        jogador1 = new Jogador(nome1);
        jogador2 = new Jogador(nome2);
        
    }
    
    
    public void jogada(int linhaOrigem, char colunaOrigemChar, int linhaDestino, char colunaDestinoChar){
    
        
        //converter para indices reais dos vetores e verificar se a coluna é valida
        //nao havia outra forma de fazer que não fosse aqui, pois iria repetir todo esse codigo.
        //não tinha como colocar em um método para converter, pois era necessário retornar 2 valores (as 2 colunas)    
        linhaOrigem = linhaOrigem - 1;
        linhaDestino = linhaDestino -1;

        
        
        int colunaOrigem = 0;
        int colunaDestino = 0;
        
        char colunas[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
        int j = 0;
        
        
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
        
        if(j == 0){
            System.out.println("Jogada inválida!");
            return;
        }
        
        
        //checa o movimento da peça
        if( tabuleiro.checaMovimento(linhaOrigem, colunaOrigem, linhaDestino, colunaDestino) == 1){
            //tabuleiro.getPosicao(linhaDestino, colunaDestino).setPeca( tabuleiro.getPosicao(linhaOrigem, colunaOrigem).getPeca() );
        }
        else{
            System.out.println("Movimento invalido!");
            return;
        }
            
        
        
        if(vez == 1)
            vez = 2;
        else{
            vez = 1;
        }
        
        //desenha
        tabuleiro.desenhar();
    }
    
    
    // funciona apenas nos terminais windows e linux
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
    
    
    public int getVez(){
        return vez;
    }
    
    
    //apenas para testes das posicoes
    public Tabuleiro getTabuleiro(){
        
        return tabuleiro;
    }

    public int getEstado() {
        return estado;
    }

    public void setEstado(int estado) {
        this.estado = estado;
    }
    
    
  
    
}
