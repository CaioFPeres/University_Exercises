package com.mycompany.projeto1;

/**
 *
 * @author Caio Peres
 */
public class Jogador {

    
    private String nome;
    private Peca pecas[] = new Peca[16];
    
    
    //se k = 1, pega a primeira metade das peças, caso seja 2, pega a segunda metade
    public Jogador (String nome, Peca pecaS[], int k){

        setNome(nome);

        try {
            if (pecaS == null)
                throw new NullPointerException();
        }
        catch(NullPointerException e){
            System.out.println("Ocorreu um erro: Conjunto de peças inválido.");
            return;
        }


        if(k == 1) {
            for (int i = 0; i < 16; i++) {
                pecas[i] = pecaS[i];
            }
        }
        else{
            for(int i = 16; i < 32; i++){
                pecas[i-16] = pecaS[i];
            }
        }


    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

}
