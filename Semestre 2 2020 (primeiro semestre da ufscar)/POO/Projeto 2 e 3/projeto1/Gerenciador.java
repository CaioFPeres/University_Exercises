package com.mycompany.projeto1;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.NoSuchElementException;
import java.util.Scanner;


/**
 *
 * @author Caio Peres
 */
public class Gerenciador {
 
    public static void main(String[] args){
        
        Scanner s = new Scanner(System.in);

        Jogo jogoXadrez = null;

        int linhaOrigem = 0;
        char colunaOrigem = 0;
        int linhaDestino = 0;
        char colunaDestino = 0;


        System.out.println("Deseja recuperar o jogo anterior? (S/N)");

        String escolha = s.next();

        while( !(escolha.equals("S") || escolha.equals("s") || escolha.equals("N") || escolha.equals("n") ) ){
            System.out.println("Faca uma escolha valida!");
            escolha = s.next();
        }

        if(escolha.equals("S") || escolha.equals("s")){

            try {
                Jogo.limparTela();
                jogoXadrez = new Jogo();
            }
            catch (NoSuchElementException | FileNotFoundException | NumberFormatException e){ // multi catch ( a partir do Java 7)

                System.out.println("Arquivo ausente ou corrompido. Criando novo jogo!");

                System.out.println("Digite o nome do primeiro jogador (branco)");

                String nome = s.next();

                System.out.println("Digite o nome do segundo jogador (preto)");

                String nome2 = s.next();


                try {
                    Jogo.limparTela();
                }
                catch(IOException | InterruptedException ex){    // multi catch ( a partir do Java 7)
                    System.out.println("Não foi possivel limpar a tela.");
                }



                jogoXadrez = new Jogo(nome, nome2);


            }
            catch(IOException | InterruptedException ex){    // multi catch ( a partir do Java 7)
                System.out.println("Não foi possivel limpar a tela.");
            }

        }

        else {

            System.out.println("Digite o nome do primeiro jogador (branco)");

            String nome = s.next();

            System.out.println("Digite o nome do segundo jogador (preto)");

            String nome2 = s.next();

            
            try {
                Jogo.limparTela();
            }
            catch(IOException | InterruptedException e){ // multi catch ( a partir do Java 7)
                System.out.println("Não foi possivel limpar a tela.");
            }



            jogoXadrez = new Jogo(nome, nome2);


        }



        while(1 == 1){
            
            System.out.println("");
            System.out.println("");
            System.out.println("Jogador " + jogoXadrez.getNomeJogador() + " faca sua jogada! Digite a linha origem, coluna origem, linha destino e coluna destino.");


            try {
                if (s.hasNext()) {
                    linhaOrigem = Integer.parseInt(s.next());

                    colunaOrigem = s.next().charAt(0);

                    linhaDestino = Integer.parseInt(s.next());

                    colunaDestino = s.next().charAt(0);

                    try {
                        jogoXadrez.jogada(linhaOrigem, colunaOrigem, linhaDestino, colunaDestino);

                    }
                    catch(IllegalArgumentException e){
                        System.out.println("Insira valores validos para a coluna!");
                    }
                    catch(Exception e){
                        System.out.println("Houve um erro: ");
                        e.printStackTrace();
                        break;
                    }


                }
            }
            catch(NumberFormatException e){
                System.out.println("Faça uma jogada válida!");
                s.nextLine();
            }

        }
        
        
    }
    
    
    
}