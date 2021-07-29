package com.mycompany.projeto1;

import java.io.IOException;
import java.util.Scanner;


/**
 *
 * @author Caio Peres
 */
public class Gerenciador {
 
    public static void main(String[] args) throws InterruptedException, IOException{
        
        Scanner s = new Scanner(System.in);
        
        System.out.println("Digite o nome do primeiro jogador (branco)");
        
        String nome = s.next();
        
        System.out.println("Digite o nome do segundo jogador (preto)");
        
        String nome2 = s.next();
       
        Jogo jogoXadrez = new Jogo(nome, nome2);
        
        Jogo.limparTela();
        
        int linhaOrigem = 0;
        char colunaOrigem;
        int linhaDestino = 0;
        char colunaDestino;

        
        while(1 == 1){
            
            System.out.println("");
            System.out.println("Jogador " + jogoXadrez.getNomeJogador() + " faca sua jogada! Digite a linha origem, coluna origem, linha destino e coluna destino.");
            
            if(s.hasNextInt())
                linhaOrigem = Integer.parseInt(s.next());
            
            colunaOrigem = s.next().charAt(0);
            
            if(s.hasNextInt())
                linhaDestino = Integer.parseInt(s.next());
            
            colunaDestino = s.next().charAt(0);
            
            Jogo.limparTela();
           
            jogoXadrez.jogada(linhaOrigem, colunaOrigem, linhaDestino, colunaDestino);
        
           
        }
        
        
    }
    
    
    
}