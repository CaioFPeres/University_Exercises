package com.mycompany.projeto1;

/**
 *
 * @author Caio Peres
 */
public class Posicao {
    
    
    private final int linha;
    private final char coluna;
    //private Peca peca;
    private final int cor;

    
    public Posicao(int linha, char coluna, int cor){

        this.linha = linha;
        this.coluna = coluna;
        this.cor = cor;
        
    }

    
    public int getLinha() {
        return linha;
    }

    public char getColuna() {
        return coluna;
    }
    
    public int getCor(){
        return cor;
    }
    
    
    /*
    public Peca getPeca(){
        
        return this.peca;
    }
    */
    
    /*
    public void setPeca(Peca peca){
        
        this.peca = peca;
    
    }
    */
    
    
    
    

    
}
