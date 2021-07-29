package com.mycompany.projeto1;

/**
 *
 * @author Caio Peres
 */
public class Cavalo extends Peca{


    public Cavalo(int cor) {
        super(cor);
    }

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
    
    
    public char desenho(){
        
        if(getCor() == 1){
            return 'C';
        }
        else if(getCor() == 2){
            return 'c';
        }
        else{
            return 0;
        }
        
        
    }
 
    
    
}
