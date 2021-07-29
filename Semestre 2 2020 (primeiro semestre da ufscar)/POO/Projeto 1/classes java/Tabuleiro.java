package com.mycompany.projeto1;

import java.io.IOException;

/**
 *
 * @author Caio Peres
 */
public class Tabuleiro {
    
    private Posicao posicoes[][] = new Posicao[8][8];
    
    public Tabuleiro () {
        
        char colunas[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
        int cor;
        
        for( int i=0; i<8;i++){
            
            if( (i+1) % 2 == 0){
                cor = 0;
            }
            else{
                cor = 1;
            }
            
            for(int j=0;j<8; j++){
               
                if( j == 0){
                    posicoes[i][j] = new Posicao(i+1, colunas[j], cor);
                    
                    if(cor == 1)
                        cor = 0;
                    else
                        cor = 1;
                
                }
                else{
                    posicoes[i][j] = new Posicao(i+1, colunas[j], cor);
                                        
                    if(cor == 1)
                        cor = 0;
                    else
                        cor = 1;
                }
                
            }
            
        }
       
        
        
    }
    
    
    
    public int checaMovimento(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino){
        
        //faz checagem se a posição é a mesma
        if(linhaOrigem == linhaDestino && colunaOrigem == colunaDestino){
            return 0;
        }
        
        //faz checagem dos limites do tabuleiro (coluna já foi checada na jogada pois era necessario converter char para inteiro)
        
        else if(linhaDestino > 7 || linhaDestino < 0 || linhaOrigem > 7 || linhaOrigem < 0)
            return 0;
        
        
        
        //Peca peca = getPosicao(linhaOrigem, colunaOrigem).getPeca();
        //if peca == null
            //sout("Jogada invalida!");
            //return;
        
        
        //else
        /*    
            if( peca.checaMovimento(linhaOrigem, colunaOrigem, linhaDestino, colunaDestino) == 1){
                return 1;
            }
            else if (peca.checaMovimento(linhaOrigem, colunaOrigem, linhaDestino, colunaDestino) == 2){
                if( getPosicao(linhaDestino, colunaDestino).getPeca() != null )
                    return 1;
            }
        */
        
        
        else{
            return 1;
        }
            
        
    }
    
    

    public Posicao getPosicao(int linha, int coluna) {
        
        //faz checagem se a linha pertence ao vetor.
        //a coluna já foi checada antes desse método ser chamado.
        if(linha > 7 || linha < 0){
            Posicao posicao = null;
            return posicao;
        }
        else{
            return posicoes[linha][coluna];
        }
    }
    
    
    public void desenhar(){
        
        System.out.println("");
        
        for(int i = 0; i<8; i++){
            
            System.out.print(9 - (i+1) + " ");
            
            System.out.print("|");
            for(int j = 0; j<8; j++){
                
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
