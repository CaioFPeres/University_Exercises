% Integrantes: 
% ------------
% 769298: Caio Fernando Peres
% 743545: Guilherme Madureira Engler
% 726598: Vitoria Rodrigues Silva
%-------------


clear all, clc
k = imread('rice_binary.png');
%figure, imshow(k);
%k = rgb2gray(k);
[lin, col]=size(k);
janela=3;



%t = [1 1 1 ; 1 -2 1; -1 -1 -1]; %NORTE
%t = [-1 -1 -1 ; 1 -2 1; 1 1 1]; %SUL
t = [-1 1 1 ; -1 -2 1; -1 1 1]; %LESTE
%t = [1 1 -1 ; 1 -2 -1; 1 1 -1]; %OESTE
%t = [1 1 1 ; -1 -2 1; -1 -1 1]; %NORDESTE
%t = [1 1 1 ; 1 -2 -1; 1 -1 -1]; %NOROESTE
%t = [-1 -1 1 ; -1 -2 1; 1 1 1]; %SUDESTE
%t = [1 -1 -1 ; 1 -2 -1; 1 1 1]; %SUDOESTE


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%Aperiodica

for i=1:lin
    for j=1:col
        soma = 0;
        u = 1;
        for indice_linha=i-1:i+1
            p = 1;
            for indice_coluna=j-1:j+1
               
               if(indice_linha == 0 || indice_coluna == 0 || indice_linha == lin+1 || indice_coluna == col+1)
                  soma = soma + (0*t(u,p));

               else
                  soma = soma + (k(indice_linha,indice_coluna)*t(u,p));
               
               endif
               p = p + 1;
            end
            u = u + 1;
        end
        k1(i,j)=soma;
    end
end



%Periodica

for i=1:lin
    for j=1:col
        soma = 0;
        u = 1;
        for indice_linha=i-1:i+1
            p = 1;
           for indice_coluna=j-1:j+1

             if(indice_linha == 0 && indice_coluna == 0) %quina
                soma = soma + (k(lin,col)*t(u,p));

             elseif(indice_linha == lin+1 && indice_coluna == col+1) %quina
                soma = soma + (k(1,1)*t(u,p));

             elseif(indice_linha == lin+1 && indice_coluna == 0) %quina
                soma = soma + (k(1,col)*t(u,p));

             elseif(indice_linha == 0 && indice_coluna == col+1) %quina
                soma = soma + (k(lin,1)*t(u,p));

             elseif(indice_linha == 0 && indice_coluna >= 0 && indice_coluna <= col) %linha acima
                soma = soma + (k(lin,indice_coluna)*t(u,p));

            elseif(indice_linha <= col && indice_coluna == col+1 && indice_linha >= 1) %coluna a direita
                soma = soma + (k(indice_linha,1)*t(u,p));

            elseif(indice_linha == lin+1 && indice_coluna <= col && indice_coluna >= 1) %linha abaixo
                soma = soma + (k(1,indice_coluna)*t(u,p));

             elseif(indice_linha >= 0 && indice_coluna == 0 && indice_linha <= lin) %coluna a esquerda
                soma = soma + (k(indice_linha,col)*t(u,p)); 

             else
                soma = soma + (k(indice_linha,indice_coluna)*t(u,p));
             endif
                p = p + 1;
            end
            u = u + 1;
        end
        k2(i,j)=soma;
    end
end


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



t = [1 1 1 ; -1 -2 1; -1 -1 1]; %NORDESTE



%Aperiodica

for i=1:lin
    for j=1:col
        soma = 0;
        u = 1;
        for indice_linha=i-1:i+1
            p = 1;
           for indice_coluna=j-1:j+1

             if(indice_linha == 0 || indice_coluna == 0 || indice_linha == lin+1 || indice_coluna == col+1)
                soma = soma + (0*t(u,p));

             else
                soma = soma + (k(indice_linha,indice_coluna)*t(u,p));

             endif
                p = p + 1;
            end
            u = u + 1;
        end
        k3(i,j)=soma;
    end
end



%Periodica

for i=1:lin
    for j=1:col
        soma = 0;
        u = 1;
        for indice_linha=i-1:i+1
            p = 1;
           for indice_coluna=j-1:j+1

             if(indice_linha == 0 && indice_coluna == 0) %quina
                soma = soma + (k(lin,col)*t(u,p));

             elseif(indice_linha == lin+1 && indice_coluna == col+1) %quina
                soma = soma + (k(1,1)*t(u,p));

             elseif(indice_linha == lin+1 && indice_coluna == 0) %quina
                soma = soma + (k(1,col)*t(u,p));

             elseif(indice_linha == 0 && indice_coluna == col+1) %quina
                soma = soma + (k(lin,1)*t(u,p));

             elseif(indice_linha == 0 && indice_coluna >= 0 && indice_coluna <= col) %linha acima
                soma = soma + (k(lin,indice_coluna)*t(u,p));

             elseif(indice_linha <= col && indice_coluna == col+1 && indice_linha >= 1) %coluna a direita
                soma = soma + (k(indice_linha,1)*t(u,p));   

             elseif(indice_linha == lin+1 && indice_coluna <= col && indice_coluna >= 1) %linha abaixo
                soma = soma + (k(1,indice_coluna)*t(u,p));

             elseif(indice_linha >= 0 && indice_coluna == 0 && indice_linha <= lin) %coluna a esquerda
                soma = soma + (k(indice_linha,col)*t(u,p)); 

             else
                soma = soma + (k(indice_linha,indice_coluna)*t(u,p));
             endif
                p = p + 1;
            end
            u = u + 1;
        end
        k4(i,j)=soma;
    end
end


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


t = [-1 -1 1 ; -1 -2 1; 1 1 1]; %SUDESTE



%Aperiodica

for i=1:lin
    for j=1:col
        soma = 0;
        u = 1;
        for indice_linha=i-1:i+1
            p = 1;
           for indice_coluna=j-1:j+1

             if(indice_linha == 0 || indice_coluna == 0 || indice_linha == lin+1 || indice_coluna == col+1)
                soma = soma + (0*t(u,p));

             else
                soma = soma + (k(indice_linha,indice_coluna)*t(u,p));

             endif
                p = p + 1;
            end
            u = u + 1;
        end
        k5(i,j)=soma;
    end
end



%Periodica

for i=1:lin
    for j=1:col
        soma = 0;
        u = 1;
        for indice_linha=i-1:i+1
            p = 1;
           for indice_coluna=j-1:j+1

             if(indice_linha == 0 && indice_coluna == 0) %quina
                soma = soma + (k(lin,col)*t(u,p));

             elseif(indice_linha == lin+1 && indice_coluna == col+1) %quina
                soma = soma + (k(1,1)*t(u,p));
                
             elseif(indice_linha == lin+1 && indice_coluna == 0) %quina
                soma = soma + (k(1,col)*t(u,p));

             elseif(indice_linha == 0 && indice_coluna == col+1) %quina
                soma = soma + (k(lin,1)*t(u,p));

             elseif(indice_linha == 0 && indice_coluna >= 0 && indice_coluna <= col) %linha acima
                soma = soma + (k(lin,indice_coluna)*t(u,p));

             elseif(indice_linha <= col && indice_coluna == col+1 && indice_linha >= 1) %coluna a direita
                soma = soma + (k(indice_linha,1)*t(u,p));

             elseif(indice_linha == lin+1 && indice_coluna <= col && indice_coluna >= 1) %linha abaixo
                soma = soma + (k(1,indice_coluna)*t(u,p));

             elseif(indice_linha >= 0 && indice_coluna == 0 && indice_linha <= lin) %coluna a esquerda
                soma = soma + (k(indice_linha,col)*t(u,p)); 

             else
                soma = soma + (k(indice_linha,indice_coluna)*t(u,p));
             endif
                p = p + 1;
            end
            u = u + 1;
        end
        k6(i,j)=soma;
    end
end


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


t = [1 -1 -1 ; 1 -2 -1; 1 1 1]; %SUDOESTE



%Aperiodica

for i=1:lin
    for j=1:col
        soma = 0;
        u = 1;
        for indice_linha=i-1:i+1
            p = 1;
           for indice_coluna=j-1:j+1

             if(indice_linha == 0 || indice_coluna == 0 || indice_linha == lin+1 || indice_coluna == col+1)
                soma = soma + (0*t(u,p));

             else
                soma = soma + (k(indice_linha,indice_coluna)*t(u,p));

             endif
                p = p + 1;
            end
            u = u + 1;
        end
        k7(i,j)=soma;
    end
end



%Periodica

for i=1:lin
    for j=1:col
        soma = 0;
        u = 1;
        for indice_linha=i-1:i+1
            p = 1;
           for indice_coluna=j-1:j+1
           
             if(indice_linha == 0 && indice_coluna == 0) %quina
                soma = soma + (k(lin,col)*t(u,p));

             elseif(indice_linha == lin+1 && indice_coluna == col+1) %quina
                soma = soma + (k(1,1)*t(u,p));

             elseif(indice_linha == lin+1 && indice_coluna == 0) %quina
                soma = soma + (k(1,col)*t(u,p));
                
             elseif(indice_linha == 0 && indice_coluna == col+1) %quina
                soma = soma + (k(lin,1)*t(u,p));

             elseif(indice_linha == 0 && indice_coluna >= 0 && indice_coluna <= col) %linha acima
                soma = soma + (k(lin,indice_coluna)*t(u,p));

             elseif(indice_linha <= col && indice_coluna == col+1 && indice_linha >= 1) %coluna a direita
                soma = soma + (k(indice_linha,1)*t(u,p));

            elseif(indice_linha == lin+1 && indice_coluna <= col && indice_coluna >= 1) %linha abaixo
                soma = soma + (k(1,indice_coluna)*t(u,p));

             elseif(indice_linha >= 0 && indice_coluna == 0 && indice_linha <= lin) %coluna a esquerda
                soma = soma + (k(indice_linha,col)*t(u,p)); 

             else
                soma = soma + (k(indice_linha,indice_coluna)*t(u,p));
             endif
                p = p + 1;
            end
            u = u + 1;
        end
        k8(i,j)=soma;
    end
end



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



subplot(2,4,1),imshow(k1),title("Aperiodica com filtro noroeste");
subplot(2,4,5),imshow(k2),title("Periodica com filtro noroeste");
subplot(2,4,2),imshow(k3),title("Aperiodica com filtro nordeste");
subplot(2,4,6),imshow(k4),title("Periodica com filtro nordeste");
subplot(2,4,3),imshow(k5),title("Aperiodica com filtro sudeste");
subplot(2,4,7),imshow(k6),title("Periodica com filtro sudeste");
subplot(2,4,4),imshow(k7),title("Aperiodica com filtro sudoeste");
subplot(2,4,8),imshow(k8),title("Periodica com filtro sudoeste");