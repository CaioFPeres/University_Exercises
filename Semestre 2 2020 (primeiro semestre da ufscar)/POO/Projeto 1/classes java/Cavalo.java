package com.mycompany.projeto1;

/**
 *
 * @author Caio Peres
 */
public class Cavalo {
    
    
     
    private int capturada;
    private int cor;
    
    
    public int checaMovimento(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino){
        
        
        //movimento vertical
        if( Math.abs(linhaOrigem - linhaDestino) == 2 && Math.abs(colunaOrigem - colunaDestino) == 1 ){ 
            return 1;
        }
        //movimento horizontal
        else if ( Math.abs(colunaOrigem - colunaDestino) == 2 && Math.abs(linhaOrigem - linhaDestino) == 1 ){
            return 1;
        }
        else{
            return 0;
        }
        
    }
    
    
    public char desenho(int player){
        
        if(player == 1){
            return 'C';
        }
        else if(player == 2){
            return 'c';
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
