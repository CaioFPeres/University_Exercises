package com.mycompany.projeto1;

/**
 *
 * @author Caio Peres
 */
public class Peao extends Peca{

    public Peao(int cor) {
        super(cor);
    }

    public int checaMovimento(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino){

        if(linhaOrigem == 6 && linhaOrigem - linhaDestino <= 2 && linhaDestino < linhaOrigem && colunaOrigem == colunaDestino && getCor() == 1)
            return 1;
        
        else if(linhaOrigem == 1 && linhaOrigem - linhaDestino >= -2 && linhaDestino > linhaOrigem && colunaOrigem == colunaDestino && getCor() == 2)
            return 1;
        
        else if(linhaDestino == linhaOrigem - 1 && colunaOrigem == colunaDestino && getCor() == 1)
            return 1;
        
        else if(linhaDestino == linhaOrigem + 1 && colunaOrigem == colunaDestino && getCor() == 2)
            return 1;
        
        else if( Math.abs( colunaDestino - colunaOrigem) == 1 && linhaDestino - linhaOrigem == -1 && getCor() == 1)
            return 2;
        
        else if( Math.abs( colunaDestino - colunaOrigem) == 1 && linhaDestino - linhaOrigem == 1 && getCor() == 2)
            return 2;
        
        else{
            return 0;
        }

    }
    
    
    public char desenho(){

        if(getCor() == 1){
            return 'P';
        }
        else if(getCor() == 2){
            return 'p';
        }
        else{
            return 0;
        }
        
    }
    
    
}
