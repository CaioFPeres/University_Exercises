package com.mycompany.projeto1;

/**
 *
 * @author Caio Peres
 */
public class Dama extends Peca{

    public Dama(int cor) {
        super(cor);
    }

    public int checaMovimento(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino){

        
        //percurso linha
        if ( (linhaDestino > linhaOrigem && colunaDestino == colunaOrigem) || (linhaDestino < linhaOrigem && colunaDestino == colunaOrigem) ){
            return 1;
        }
        
        //percurso coluna
        else if ( (colunaDestino > colunaOrigem && linhaDestino == linhaOrigem) || (colunaDestino < colunaOrigem && linhaDestino == linhaOrigem) ){
            return 1;
        }
        
        //percurso diagonal
        else if ( Math.abs( colunaDestino - colunaOrigem) == Math.abs( linhaDestino - linhaOrigem) ){
            return 1;
        }
        
        else{
            return 0;
        }
        
    }
    
    
    public char desenho(){
        
        if(getCor() == 1){
            return 'D';
        }
        else if(getCor() == 2){
            return 'd';
        }
        else{
            return 0;
        }
        
    }
    
}
