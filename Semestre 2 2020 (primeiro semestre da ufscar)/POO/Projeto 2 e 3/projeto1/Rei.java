package com.mycompany.projeto1;

/**
 *
 * @author Caio Peres
 */
public class Rei extends Peca{


    public Rei(int cor) {
        super(cor);
    }

    public int checaMovimento(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino){

        
        //percurso linha
        if( (linhaDestino == linhaOrigem + 1 && colunaDestino == colunaOrigem) || (linhaDestino == linhaOrigem - 1 && colunaDestino == colunaOrigem) ){
            return 1;
        }
        
        //percurso coluna
        else if( (colunaDestino == colunaOrigem + 1 && linhaDestino == linhaOrigem) || (colunaDestino == colunaOrigem - 1 && linhaDestino == linhaOrigem ) ){
            return 1;
        }
        
        //percurso diagonal
        else if( Math.abs( colunaDestino - colunaOrigem) == 1 && Math.abs( linhaDestino - linhaOrigem) == 1 ){
            return 1;
        }
        
        else{
            return 0;
        }
        
    }
    
    
    public char desenho(){
        
        if(getCor() == 1){
            return 'R';
        }
        else if(getCor() == 2){
            return 'r';
        }
        else{
            return 0;
        }
        
    }
    
    
}
