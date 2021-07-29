package com.mycompany.projeto1;

/**
 *
 * @author Caio Peres
 */
public class Peao {
    
    
     
   private int capturada;
   private int cor;
    
    
    public int checaMovimento(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino){

        
        if(linhaOrigem == 2 && linhaDestino <= linhaOrigem + 2 && linhaDestino > linhaOrigem && colunaOrigem == colunaDestino && cor == 0)
            return 1;
        
        else if(linhaOrigem == 7 && linhaDestino >= linhaOrigem - 2 && linhaDestino < linhaOrigem && colunaOrigem == colunaDestino && cor == 1)
            return 1;
        
        else if(linhaDestino == linhaOrigem + 1 && colunaOrigem == colunaDestino && cor == 0)
            return 1;
        
        else if(linhaDestino == linhaOrigem - 1 && colunaOrigem == colunaDestino && cor == 1)
            return 1;
        
        else if( Math.abs( colunaDestino - colunaOrigem) == 1 && linhaDestino - linhaOrigem == 1 && cor == 0)
            return 2;
        
        else if( Math.abs( colunaDestino - colunaOrigem) == 1 && linhaDestino - linhaOrigem == -1 && cor == 1)
            return 2;
        
        else{
            return 0;
        }
        
    }
    
    
    public char desenho(int player){
        
        if(player == 1){
            return 'P';
        }
        else if(player == 2){
            return 'p';
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
