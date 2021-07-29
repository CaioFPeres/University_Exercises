package com.mycompany.projeto1;

import java.io.IOException;
import java.util.Scanner;

/**
 *
 * @author Caio Peres
 */
public class Teste {
    
     public static void main(String[] args) throws IOException, InterruptedException{
         
         
        Scanner s = new Scanner(System.in);
        
        System.out.println("Digite o nome do primeiro jogador (branco)");
        
        String nome = s.next();
        
        System.out.println("Digite o nome do segundo jogador (preto)");
        
        String nome2 = s.next();
       
        Jogo jogoXadrez = new Jogo(nome, nome2);
     
           
        Rei rei = new Rei();
        Dama dama = new Dama();
        Cavalo cavalo = new Cavalo();
        Bispo bispo = new Bispo();
        Torre torre = new Torre();
        Peao peao = new Peao();
        
        //teste cores, linhas e colunas das posicoes
        for(int i = 0; i<8;i++){
            for(int j = 0; j<8; j++){
            
            System.out.println("Cor: " + jogoXadrez.getTabuleiro().getPosicao(i, j).getCor() + " Linha: " + jogoXadrez.getTabuleiro().getPosicao(i, j).getLinha() + " Coluna: " + jogoXadrez.getTabuleiro().getPosicao(i, j).getColuna());
            }
        }
         
        //simulação de atribuição de cor para testar o movimento do peao
        peao.setCor(0);
        
        
            int linhaOrigem = 0;
            char colunaOrigemChar;
            int linhaDestino = 0;
            char colunaDestinoChar;
            
            int colunaOrigem = 0;
            int colunaDestino = 0;
        
       
        while(1==1){
            
            System.out.println("Jogador " + jogoXadrez.getNomeJogador() + " faca sua jogada! Digite a linha origem, coluna origem, linha destino e coluna destino.");
        
            
            if(s.hasNextInt())
                linhaOrigem = Integer.parseInt(s.next());
            
            colunaOrigemChar = s.next().charAt(0);
            
            if(s.hasNextInt())
                linhaDestino = Integer.parseInt(s.next());
            
            colunaDestinoChar = s.next().charAt(0);
            
            
            Jogo.limparTela();
            
            System.out.println("");
            
            //converter para posicoes reais dos vetores
            //embora no metodo jogoXadrez.jogada() também converta, precisei converter aqui para poder testar o movimento de cada peça individualmente
            linhaOrigem = linhaOrigem - 1;
            linhaDestino = linhaDestino - 1;
            

            char colunas[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
            int j = 0;

            //converter char para indice real de vetores
            //essas conversoes são feitas na jogada, porem precisei fazer aqui também
            //para testar as classes das peças, pois recebem inteiros nos parametros
            for(int i = 0; i<8; i++){


                if(colunaOrigemChar == colunas[i]){
                    colunaOrigem = i;
                    j++;
                }
                if(colunaDestinoChar == colunas[i]){
                    colunaDestino = i;
                    j++;
                }

            }

            if(j == 0){
                System.out.println("Jogada inválida!");
                
            }
            else{


            //checa os movimentos (aqui como é teste está aceitando qualquer valor, mas no jogo principal a checagem do movimento das peças
            //só ia acontecer após checagem do tabuleiro)
            //ou seja, vai imprimir um resultado independente se o valor é invalido para o tabuleiro ou não.
            //Logo após, o metodo jogoXadrez.jogada() irá checar se o movimento foi valido ou não

            if(rei.checaMovimento(linhaOrigem, colunaOrigem, linhaDestino, colunaDestino) == 1)
                 System.out.println("Rei: Valido");
            else
                 System.out.println("Rei: Invalido");


            if(dama.checaMovimento(linhaOrigem, colunaOrigem, linhaDestino, colunaDestino) == 1)
                 System.out.println("Dama: Valido");
            else
                System.out.println("Dama: Invalido");


            if(cavalo.checaMovimento(linhaOrigem, colunaOrigem, linhaDestino, colunaDestino) == 1)
                 System.out.println("Cavalo: Valido");
            else
                 System.out.println("Cavalo: Invalido");


            if(bispo.checaMovimento(linhaOrigem, colunaOrigem, linhaDestino, colunaDestino) == 1)
                 System.out.println("Bispo: Valido");
            else
                 System.out.println("Bispo: Invalido");


            if(torre.checaMovimento(linhaOrigem, colunaOrigem, linhaDestino, colunaDestino) == 1)
                 System.out.println("Torre: Valido");
            else
                 System.out.println("Torre: Invalido");


            if(peao.checaMovimento(linhaOrigem, colunaOrigem, linhaDestino, colunaDestino) == 1)
                 System.out.println("Peao: Valido");
            else if( peao.checaMovimento(linhaOrigem, colunaOrigem, linhaDestino, colunaDestino) == 2 )
                 System.out.println("Peao: Valido para comer");
            else
                 System.out.println("Peao: Invalido");

     
            //faz a jogada (está fora de ordem, mas é para facilitar o teste)
            //colocando +1 pois precisei testar o movimento de cada peça antes dessa linha, e dentro do metodo ele já está corrigindo o valor da linha
            jogoXadrez.jogada(linhaOrigem +1, colunaOrigemChar, linhaDestino +1, colunaDestinoChar);
            
            
            System.out.println("");
            System.out.println("");
            
            
            //teste getEstado (set estado já está sendo testado no construtor)
            System.out.println("Estado: " + jogoXadrez.getEstado());
                
            
            //teste getters, setters e desenho das peças individuais
            rei.setCapturada(1);
            System.out.println(rei.getCapturada());
            rei.setCor(1);
            System.out.println(rei.getCor());
            System.out.println(rei.desenho(1));
            
            dama.setCapturada(1);
            System.out.println(dama.getCapturada());
            dama.setCor(1);
            System.out.println(dama.getCor());
            System.out.println(dama.desenho(1));
            
            cavalo.setCapturada(1);
            System.out.println(cavalo.getCapturada());
            cavalo.setCor(1);
            System.out.println(cavalo.getCor());
            System.out.println(cavalo.desenho(1));
            
            bispo.setCapturada(1);
            System.out.println(bispo.getCapturada());
            bispo.setCor(1);
            System.out.println(bispo.getCor());
            System.out.println(bispo.desenho(1));
            
            torre.setCapturada(1);
            System.out.println(torre.getCapturada());
            torre.setCor(1);
            System.out.println(torre.getCor());
            System.out.println(torre.desenho(1));
            
            peao.setCapturada(1);
            System.out.println(peao.getCapturada());
            peao.setCor(1);
            System.out.println(peao.getCor());
            System.out.println(peao.desenho(1));
            ////////////////////////////////////////
           
            
        }
    
        }
        
     }
    
    
}
