package com.mycompany.projeto1;
/**
 *
 * @author Caio Peres
 */
public class Bispo extends Peca {


    public Bispo(int cor) {
        super(cor);
    }

    public int checaMovimento(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino){
        
        //percurso diagonal
        if ( Math.abs( colunaDestino - colunaOrigem) == Math.abs( linhaDestino - linhaOrigem) ){
            return 1;
        }
        
        else{
            return 0;
        }
        
    }
    
    
    public char desenho(){
        
        if(getCor() == 1){
            return 'B';
        }
        else if(getCor() == 2){
            return 'b';
        }
        else{
            return 0;
        }
        
    }
    
    
    
}
