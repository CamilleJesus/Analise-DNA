/*
Autora: Camille de L. Jesus

Componente Curricular: EXA854 - MI Algoritmos

Data: 24/10/2014

Declaro que este código foi elaborado por mim de forma individual e não contém nenhum
trecho de código de outro colega ou de outro autor, tais como provindos de livros e
apostilas, e páginas ou documentos eletrônicos da Internet. Qualquer trecho de código
de outra autoria que não a minha está destacado com uma citação para o autor e a fonte
do código, e estou ciente que estes trechos não serão considerados para fins de avaliação.
*/


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

// Código do Sistema de Análise de DNA (SAD) //

int main ()
{   //Os nomes das variáveis são autoexplicativos e de fácil entendimento, o que torna sua finalidade deduzível:		
	int i, j, caracter, peso_duploAT = 0, peso_duploCG = 0, peso_duploGC = 0, peso_duploTA = 0, contA = 0, contC = 0, contG = 0, contT = 0;
	int total_peso[20], totalA[20], totalC[20], totalG[20], totalT[20], Id[20], maior_Id = 0, menor_Id = 0, fita_maiorId, fita_menorId, fita_maiorId2, fita_menorId2;	
	float porcentagemA[20], porcentagemC[20], porcentagemG[20], porcentagemT[20];	
	char matriz[20][11], matriz_complementar[20][11];
	
	system("color 0F");
	FILE *file = fopen ("Fitas de DNA.txt", "r");   //Leitura do arquivo onde constam as fitas de DNA.

	if (file == NULL) {   //Caso o arquivo não exista.
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

    //Conversão de letras (para gerar matriz complementar) e soma dos valores correspondentes à cada uma delas, em ambas as fitas. 
    for (i = 0; i < 20; i++) {

	    for (j = 0; j <= 10; j++) {

			if (matriz[i][j] == 'A') {   //Identificação do caractere, no caso, A;
				peso_duploAT += 3;   //Soma direta das duplas fitas. 1 do A, caso apareça, e 2 do T, quando o A for substituído;
				contA++;   //Soma-se 1 à variável contadora de bases A;
				contT++;   ////Soma-se 1 à variável contadora de bases T;
                matriz_complementar[i][j] = 'T';   //Conversão, no caso, para T, na mesma posição em uma matriz complementar também 20x10.
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
            } else {   //Caso não apareça nenhuma dessas 4 letras:
                matriz_complementar[i][j] = matriz[i][j];   //não haverá conversão, nem contagem.
            }
        }
		total_peso[i] = peso_duploAT + peso_duploCG + peso_duploGC + peso_duploTA;   //Total de peso das bases das duplas fitas.
		Id[i] = total_peso[i] + contG;   //Id (total de peso + quantidade de Guanina) das duplas fitas.
		 
		if (Id[i] > maior_Id) {   //Comparação de Ids para estabelecer um maior:
            maior_Id = Id[i];   //O Id é salvo numa variável;
            fita_maiorId = i;   //Para printar a fita responsável pelo maior Id, precisa-se da localização de sua linha, a variável "fita_maiorId" recebe a posição que se encontra o maior Id.
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
		//Variáveis que serão usadas novamente devem ser zeradas.
        peso_duploAT = peso_duploCG = peso_duploGC = peso_duploTA = 0;
		contA = contC = contT = contG = 0;
    }    
    menor_Id = Id[0];   //menor_Id precisa de um valor inicial antes da verificação do menor Id, pois ele é inicializado com 0, e nenhum Id será tão ou mais baixo.
    fita_menorId = 0;

    for (i = 0; i < 20; i++) {   //Informações a serem exibidas para cada pessoa:
    	printf ("\n%i%c pessoa:\n Adenina:  %2i (%.2f%%)", i + 1, 166, totalA[i], porcentagemA[i]);   //total e percentual de base A por dupla fita,
    	printf ("\n Citosina: %2i (%.2f%%)", totalC[i], porcentagemC[i]);   //total e percentual de base C por dupla fita,
    	printf ("\n Guanina:  %2i (%.2f%%)", totalG[i], porcentagemG[i]);   //total e percentual de base G por dupla fita,
    	printf ("\n Timina:   %2i (%.2f%%)\n", totalT[i], porcentagemT[i]);   //total e percentual de base T por dupla fita.
		
		if (porcentagemG[i] + porcentagemC[i] > 50) {   //Verificação de propensão à atividades artísticas com base na porcentagem de guanina e citosina.
    		printf ("\n Propens%co %cs atividades art%csticas.\n", 198, 133, 161);
    	}

		if (porcentagemA[i] + porcentagemT[i] > 50) {   //Verificação de propensão à atividades esportivas com base na porcentagem de adenina timina.
    		printf ("\n Propens%co %cs atividades esportivas.\n", 198, 133);
    	}

    	if (porcentagemG[i] == porcentagemA[i]) {   //Caso os níveis de Adenina e Guanina estejam iguais, nada se pode determinar.
    		printf ("\n Nada se pode determinar quanto propens%co %c atividades.\n", 198, 133);
    	}
    	
    	//Verificação de propensão à doenças com base no valor do Id.
    	if ((Id[i] != 0) && (Id[i] < 50)) {   
    		printf ("\n Propens%co %cs doen%cas card%cacas.\n",198, 133, 135, 161);
    	} else if (Id[i] > 50) {
    		printf ("\n Propens%co %cs doen%cas respirat%crias.\n",198, 133, 135, 162);
    	} else if (Id[i] == 50) {
    		printf ("\n Nada se pode determinar quanto propens%co %c doen%cas.\n", 198, 133, 135);
    	}
    	
    	if (Id[i] < menor_Id) {   //Comparação de Ids para estabelecer um menor:
          menor_Id = Id[i];   //O Id é salvo numa variável;
          fita_menorId = i;   //Para printar a fita responsável pelo menor Id, precisa-se da localização de sua linha, a variável "fita_menorId" recebe a posição que se encontra o menor Id.
        }
    }    
	getch ();
    system ("cls");    
    printf ("\nMaior Id: %i\n\n", maior_Id);   //Exibição do maior Id:    
    
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
        	printf("%c", matriz[fita_maiorId2][j]);   //Filamento correspondente do provável segundo maior Id.
    	}
    }    
    printf ("\n");       
    printf ("\n\n\nMenor Id: %i\n\n", menor_Id);   //Exibição do menor Id:    
    
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
        	printf("%c", matriz[fita_menorId2][j]);   //Filamento correspondente do provável segundo menor Id.
    	}
    }    
    printf ("\n");	        
    /* Foram criados vários for independentes pois cada arquivos precisa ser aberto/criado primeiro.
    Caso isso fosse feito dentro do for, somente os últimos valores que passassem pela condição seriam 
    printados no arquivo, já que ao abrir e escrever nele a cada novo ciclo, há a substituição do que havia nele anteriormente. */
	FILE *card;
	card = fopen ("card.txt", "w");   //O card.txt é aberto/criado			
				
	for (i = 0; i < 20; i++) {
		
		if ((Id[i] != 0) && (Id[i] < 50)) {   //Caso o Id seja menor que 50 e maior que 0:
		
			for (j = 0; j < 10; j++) {
				fprintf (card,"%c", matriz[i][j]);   //o filamento será printado no arquivo,
			}			
			fprintf (card,"%i\n\n", Id[i]);   //seguido de seu Id correspondente.
		}
	}	
	FILE *resp;
	resp = fopen ("resp.txt", "w");   //O resp.txt é aberto/criado:
		
	for (i = 0; i < 20; i++) {
		
		if (Id[i] > 50) {   //Caso o Id seja maior que 50:
		
			for (j = 0; j < 10; j++) {
				fprintf (resp,"%c", matriz[i][j]);   //o filamento será printado no arquivo,
			}			
			fprintf (resp,"%i\n\n", Id[i]);   //seguido de seu Id correspondente.
		}
	}	
	FILE *indeterminado;
	indeterminado = fopen ("indeterminado.txt", "w");   //O indeterminado.txt é aberto/criado:
		
	for (i = 0; i < 20; i++) {
		
		if (Id[i] == 50) {   //Caso o Id seja igual a 50:   
		
			for (j = 0; j < 10; j++) {
				fprintf (indeterminado,"%c", matriz[i][j]);   //o filamento será printado no arquivo,
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
            printf ("%c", matriz[i][j]);   //Exibição dos filamentos de DNA lidos no arquivo.
        }        
        printf ("\n");
        
        for (j = 0; j <= 10; j++) { 
            printf ("%c", matriz_complementar[i][j]);   //Exibição dos filamentos complementares de DNA gerados a partir do arquivo 
    	}                                               //(sem fazer a leitura, somente printando a matriz complementar salva).
    	printf ("\n\n\n");
    }	
	printf ("\n");
	getch ();

    return 0;
}