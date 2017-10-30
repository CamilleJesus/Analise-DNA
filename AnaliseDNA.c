/*
Autora: Camille de L. Jesus

Componente Curricular: EXA854 - MI Algoritmos

Data: 24/10/2014

Declaro que este c�digo foi elaborado por mim de forma individual e n�o cont�m nenhum
trecho de c�digo de outro colega ou de outro autor, tais como provindos de livros e
apostilas, e p�ginas ou documentos eletr�nicos da Internet. Qualquer trecho de c�digo
de outra autoria que n�o a minha est� destacado com uma cita��o para o autor e a fonte
do c�digo, e estou ciente que estes trechos n�o ser�o considerados para fins de avalia��o.
*/


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

// C�digo do Sistema de An�lise de DNA (SAD) //

int main ()
{   //Os nomes das vari�veis s�o autoexplicativos e de f�cil entendimento, o que torna sua finalidade deduz�vel:		
	int i, j, caracter, peso_duploAT = 0, peso_duploCG = 0, peso_duploGC = 0, peso_duploTA = 0, contA = 0, contC = 0, contG = 0, contT = 0;
	int total_peso[20], totalA[20], totalC[20], totalG[20], totalT[20], Id[20], maior_Id = 0, menor_Id = 0, fita_maiorId, fita_menorId, fita_maiorId2, fita_menorId2;	
	float porcentagemA[20], porcentagemC[20], porcentagemG[20], porcentagemT[20];	
	char matriz[20][11], matriz_complementar[20][11];
	
	system("color 0F");
	FILE *file = fopen ("Fitas de DNA.txt", "r");   //Leitura do arquivo onde constam as fitas de DNA.

	if (file == NULL) {   //Caso o arquivo n�o exista.
        printf ("\nArquivo inv%clido.\n", 160);
        return 0;
    }    
    printf ("\n\t\t\t%c%c Sistema de An%clise de DNA (SAD) %c%c\n\n", 254, 254, 160, 254, 254);    
    
    //Armazenamento de caractere por caracter do arquivo numa matriz 20x10.
    for (i = 0; i < 20; i++) {

		for (j = 0; j <= 10; j++) {
            caracter = fgetc (file);
            matriz[i][j] = caracter; 
        }
    }

    //Convers�o de letras (para gerar matriz complementar) e soma dos valores correspondentes � cada uma delas, em ambas as fitas. 
    for (i = 0; i < 20; i++) {

	    for (j = 0; j <= 10; j++) {

			if (matriz[i][j] == 'A') {   //Identifica��o do caractere, no caso, A;
				peso_duploAT += 3;   //Soma direta das duplas fitas. 1 do A, caso apare�a, e 2 do T, quando o A for substitu�do;
				contA++;   //Soma-se 1 � vari�vel contadora de bases A;
				contT++;   ////Soma-se 1 � vari�vel contadora de bases T;
                matriz_complementar[i][j] = 'T';   //Convers�o, no caso, para T, na mesma posi��o em uma matriz complementar tamb�m 20x10.
            } else if (matriz[i][j] == 'C') {   //
            	peso_duploCG += 7;
            	contC++;
            	contG++;
                matriz_complementar[i][j] = 'G';
            } else if (matriz[i][j] == 'G') {   //
            	peso_duploGC += 7;
            	contG++;
            	contC++;
                matriz_complementar[i][j] = 'C';
            } else if (matriz[i][j] == 'T') {   //
            	peso_duploTA += 3;
            	contT++;
            	contA++;
                matriz_complementar[i][j] = 'A';
            } else {   //Caso n�o apare�a nenhuma dessas 4 letras:
                matriz_complementar[i][j] = matriz[i][j];   //n�o haver� convers�o, nem contagem.
            }
        }
		total_peso[i] = peso_duploAT + peso_duploCG + peso_duploGC + peso_duploTA;   //Total de peso das bases das duplas fitas.
		Id[i] = total_peso[i] + contG;   //Id (total de peso + quantidade de Guanina) das duplas fitas.
		 
		if (Id[i] > maior_Id) {   //Compara��o de Ids para estabelecer um maior:
            maior_Id = Id[i];   //O Id � salvo numa vari�vel;
            fita_maiorId = i;   //Para printar a fita respons�vel pelo maior Id, precisa-se da localiza��o de sua linha, a vari�vel "fita_maiorId" recebe a posi��o que se encontra o maior Id.
        }             	
        //Quantidade total e porcentagem por duplas fitas das bases nitrogenadas:
		totalA[i] = contA;   //-Adenina
		porcentagemA[i] = contA * 100.0 / 20;
		totalC[i] = contC;  //-Citosina
		porcentagemC[i] = contC * 100.0 / 20;
		totalG[i] = contG;   //-Guanina
		porcentagemG[i] = contG * 100.0 / 20;
		totalT[i] = contT;   //-Timina
		porcentagemT[i] = contT * 100.0 / 20;
		//Vari�veis que ser�o usadas novamente devem ser zeradas.
        peso_duploAT = peso_duploCG = peso_duploGC = peso_duploTA = 0;
		contA = contC = contT = contG = 0;
    }    
    menor_Id = Id[0];   //menor_Id precisa de um valor inicial antes da verifica��o do menor Id, pois ele � inicializado com 0, e nenhum Id ser� t�o ou mais baixo.
    fita_menorId = 0;

    for (i = 0; i < 20; i++) {   //Informa��es a serem exibidas para cada pessoa:
    	printf ("\n%i%c pessoa:\n Adenina:  %2i (%.2f%%)", i + 1, 166, totalA[i], porcentagemA[i]);   //total e percentual de base A por dupla fita,
    	printf ("\n Citosina: %2i (%.2f%%)", totalC[i], porcentagemC[i]);   //total e percentual de base C por dupla fita,
    	printf ("\n Guanina:  %2i (%.2f%%)", totalG[i], porcentagemG[i]);   //total e percentual de base G por dupla fita,
    	printf ("\n Timina:   %2i (%.2f%%)\n", totalT[i], porcentagemT[i]);   //total e percentual de base T por dupla fita.
		
		if (porcentagemG[i] + porcentagemC[i] > 50) {   //Verifica��o de propens�o � atividades art�sticas com base na porcentagem de guanina e citosina.
    		printf ("\n Propens%co %cs atividades art%csticas.\n", 198, 133, 161);
    	}

		if (porcentagemA[i] + porcentagemT[i] > 50) {   //Verifica��o de propens�o � atividades esportivas com base na porcentagem de adenina timina.
    		printf ("\n Propens%co %cs atividades esportivas.\n", 198, 133);
    	}

    	if (porcentagemG[i] == porcentagemA[i]) {   //Caso os n�veis de Adenina e Guanina estejam iguais, nada se pode determinar.
    		printf ("\n Nada se pode determinar quanto propens%co %c atividades.\n", 198, 133);
    	}
    	
    	//Verifica��o de propens�o � doen�as com base no valor do Id.
    	if ((Id[i] != 0) && (Id[i] < 50)) {   
    		printf ("\n Propens%co %cs doen%cas card%cacas.\n",198, 133, 135, 161);
    	} else if (Id[i] > 50) {
    		printf ("\n Propens%co %cs doen%cas respirat%crias.\n",198, 133, 135, 162);
    	} else if (Id[i] == 50) {
    		printf ("\n Nada se pode determinar quanto propens%co %c doen%cas.\n", 198, 133, 135);
    	}
    	
    	if (Id[i] < menor_Id) {   //Compara��o de Ids para estabelecer um menor:
          menor_Id = Id[i];   //O Id � salvo numa vari�vel;
          fita_menorId = i;   //Para printar a fita respons�vel pelo menor Id, precisa-se da localiza��o de sua linha, a vari�vel "fita_menorId" recebe a posi��o que se encontra o menor Id.
        }
    }    
	getch ();
    system ("cls");    
    printf ("\nMaior Id: %i\n\n", maior_Id);   //Exibi��o do maior Id:    
    
    for (i = 0; i < 20; i++) {   //Caso haja um "segundo" maior Id.
    	 
        if (Id[i] == maior_Id) {
            maior_Id = Id[i];
            fita_maiorId2 = i;
        }
    }
    
    for (j = 0; j < 10; j++) {   
        printf("%c", matriz[fita_maiorId][j]);   //Filamento correspondente.
    }    
    printf ("\n");
       
    for (j = 0; j < 10; j++) {  
    
		if (fita_maiorId != fita_maiorId2) {
        	printf("%c", matriz[fita_maiorId2][j]);   //Filamento correspondente do prov�vel segundo maior Id.
    	}
    }    
    printf ("\n");       
    printf ("\n\n\nMenor Id: %i\n\n", menor_Id);   //Exibi��o do menor Id:    
    
    for (i = 0; i < 20; i++) {   //Caso haja um "segundo" menor Id.
    	 
        if (Id[i] == menor_Id) {
            menor_Id = Id[i];
            fita_menorId2 = i;
        }
    }
    
    for (j = 0; j < 10; j++) {  
        printf("%c", matriz[fita_menorId][j]);   //Filamento correspondente.
    }    
    printf ("\n");       
    
    for (j = 0; j < 10; j++) {  
    	
		if (fita_menorId != fita_menorId2) {
        	printf("%c", matriz[fita_menorId2][j]);   //Filamento correspondente do prov�vel segundo menor Id.
    	}
    }    
    printf ("\n");	        
    /* Foram criados v�rios for independentes pois cada arquivos precisa ser aberto/criado primeiro.
    Caso isso fosse feito dentro do for, somente os �ltimos valores que passassem pela condi��o seriam 
    printados no arquivo, j� que ao abrir e escrever nele a cada novo ciclo, h� a substitui��o do que havia nele anteriormente. */
	FILE *card;
	card = fopen ("card.txt", "w");   //O card.txt � aberto/criado			
				
	for (i = 0; i < 20; i++) {
		
		if ((Id[i] != 0) && (Id[i] < 50)) {   //Caso o Id seja menor que 50 e maior que 0:
		
			for (j = 0; j < 10; j++) {
				fprintf (card,"%c", matriz[i][j]);   //o filamento ser� printado no arquivo,
			}			
			fprintf (card,"%i\n\n", Id[i]);   //seguido de seu Id correspondente.
		}
	}	
	FILE *resp;
	resp = fopen ("resp.txt", "w");   //O resp.txt � aberto/criado:
		
	for (i = 0; i < 20; i++) {
		
		if (Id[i] > 50) {   //Caso o Id seja maior que 50:
		
			for (j = 0; j < 10; j++) {
				fprintf (resp,"%c", matriz[i][j]);   //o filamento ser� printado no arquivo,
			}			
			fprintf (resp,"%i\n\n", Id[i]);   //seguido de seu Id correspondente.
		}
	}	
	FILE *indeterminado;
	indeterminado = fopen ("indeterminado.txt", "w");   //O indeterminado.txt � aberto/criado:
		
	for (i = 0; i < 20; i++) {
		
		if (Id[i] == 50) {   //Caso o Id seja igual a 50:   
		
			for (j = 0; j < 10; j++) {
				fprintf (indeterminado,"%c", matriz[i][j]);   //o filamento ser� printado no arquivo,
			}			
			fprintf (indeterminado,"%i\n\n", Id[i]);   //seguido de seu Id correspondente.
		}
	}		
	printf ("\n");
	getch ();
    system ("cls");
 	printf ("\nDuplas Fitas:\n\n\n");    
    
	for (i = 0; i < 20; i++) {

		for (j = 0; j <= 10; j++) { 
            printf ("%c", matriz[i][j]);   //Exibi��o dos filamentos de DNA lidos no arquivo.
        }        
        printf ("\n");
        
        for (j = 0; j <= 10; j++) { 
            printf ("%c", matriz_complementar[i][j]);   //Exibi��o dos filamentos complementares de DNA gerados a partir do arquivo 
    	}                                               //(sem fazer a leitura, somente printando a matriz complementar salva).
    	printf ("\n\n\n");
    }	
	printf ("\n");
	getch ();

    return 0;
}