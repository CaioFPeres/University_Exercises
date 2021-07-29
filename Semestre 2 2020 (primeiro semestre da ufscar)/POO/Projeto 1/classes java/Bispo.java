package com.mycompany.projeto1;

/**
 *
 * @author Caio Peres
 */
public class Bispo {
    
    
    private int capturada;
    private int cor;
    
    
    public int checaMovimento(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino){
        
        //percurso diagonal
        if ( Math.abs( colunaDestino - colunaOrigem) == Math.abs( linhaDestino - linhaOrigem) ){
            return 1;
        }
        
        else{
            return 0;
        }
        
    }
    
    
    public char desenho(int player){
        
        if(player == 1){
            return 'B';
        }
        else if(player == 2){
            return 'b';
        }
        else{
            return 0;
        }
        
    }

    public int getCapturada() {
        return capturada;
    }

    public void setCapturada(int capturada) {
        this.capturada = capturada;
    }
    
    public int getCor() {
        return cor;
    }

    public void setCor(int cor) {
        this.cor = cor;
    }
    
    
    
}
