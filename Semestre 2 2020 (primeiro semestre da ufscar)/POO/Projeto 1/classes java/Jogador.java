package com.mycompany.projeto1;

/**
 *
 * @author Caio Peres
 */
public class Jogador {

    
    private String nome;
    //Peca pecas[] = new Peca[16];
    
    

    public Jogador (String nome){
        setNome(nome);
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }
    
    

    
}
