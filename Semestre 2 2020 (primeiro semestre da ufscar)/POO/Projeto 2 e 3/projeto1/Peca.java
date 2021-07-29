package com.mycompany.projeto1;

/**
 *
 * @author Caio Peres
 */
public abstract class Peca {

    private int capturada;
    private int cor;


    //tratando a possivel exceção.
    public Peca(int cor){

        try{
            if( cor > 0 && cor < 3)
                this.cor = cor;
            else
                throw new IllegalArgumentException();
        }
        catch(IllegalArgumentException e){
            System.out.println("Valor invalido para a cor.");
            return;
        }

    }


    public abstract int checaMovimento(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino);
    public abstract char desenho();


    public int getCapturada() {
        return capturada;
    }


    //tratando a possivel exceção.
    public void setCapturada(int capturada) {
        try{
            if(capturada >= 0 && capturada < 3) //utilizo o numero 2 para marcar as peças que já foram lidas do arquivo
                this.capturada = capturada;
            else
                throw new IllegalArgumentException();
        }
        catch(IllegalArgumentException e){
            System.out.println("Valor invalido para a captura.");
            return;
        }
    }

    public int getCor() {
        return cor;
    }


}
