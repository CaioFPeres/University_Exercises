package com.mycompany.projeto1;

/**
 *
 * @author Caio Peres
 */
public class Posicao {
    
    
    private final int linha;
    private final char coluna;
    private Peca peca;
    private final int cor;

    
    public Posicao(int linha, char coluna, int cor){

        //não dava para fazer try/if nesses atributos, pois o final não deixa. Entretanto já houve verificações antes dessa chamada.
        this.linha = linha;
        this.coluna = coluna;
        this.cor = cor;
        
    }

    public Peca getPeca(){
        return this.peca;
    }

    public void setPeca(Peca peca){
        //deve aceitar peca nula na posicao, então não cabe exceção aqui.
        this.peca = peca;
    }

    
}
