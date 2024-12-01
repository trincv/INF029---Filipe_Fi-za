// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  Cada aluno deve renomear esse arquivo para Aluno<MATRICULA>.c
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome:
//  email:
//  Matrícula:
//  Semestre:

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016

// #################################################

#include <stdio.h>
#include "FilipeFiuza-20241160009-T1.h" // Substitua pelo seu arquivo de header renomeado
#include <stdlib.h>
#include <locale.h>
#include <string.h> // strlen
#ifdef _WIN32
#endif

void remove_accents(char *text);     // usado de https://github.com/johncobain/INF029-Andrey-Gomes-da-Silva-Nascimento/blob/main/Trabalho1/AndreyGomes20241160024.c
DataQuebrada quebraData(char data[]);

/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y)
{
    int soma;
    soma = x + y;
    return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x)
{ //função utilizada para testes
  int i, fat = 1;
    
  for (i = x; i > 1; i--)
    fat = fat * i;
    
  return fat;
}

int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)   
    pode utilizar strlen para pegar o tamanho da string
 */
int q1(char data[])
{
  int datavalida = 1;
  
  //quebrar a string data em strings sDia, sMes, sAno

  DataQuebrada dq = quebraData(data);

  if(dq.valido == 0)
    return 0;
  
  int is_leap_year;
            
  if(dq.iAno % 4 == 0 && dq.iAno % 100 > 0)
    is_leap_year = 0;
  else
    if(dq.iAno % 4 == 0 && dq.iAno % 100 == 0 && dq.iAno % 400 == 0)
      is_leap_year = 0;
    else
      is_leap_year = 1;
  if(dq.iMes > 0 && dq.iMes <= 12){
    switch(dq.iMes){
      case 2:{
        if(is_leap_year == 0){
          if(dq.iDia > 29 ||  dq.iDia < 1)
            datavalida = 0;
        }else
            if(dq.iDia > 28 ||  dq.iDia < 1)
              datavalida = 0;
        break;
      }
      case 4:
      case 6:
      case 9:
      case 11:
        if(dq.iDia > 30 || dq.iDia < 1)
          datavalida = 0;
        break;
      default:
        if(dq.iDia > 31 || dq.iDia < 1)
          datavalida = 0;
        break;
    }
  }else
    datavalida = 0;
  
  //printf("%s\n", data);

  if (datavalida)
      return 1;
  else
      return 0;
}



/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal. 
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */
DiasMesesAnos q2(char datainicial[], char datafinal[])
{

    //calcule os dados e armazene nas três variáveis a seguir
    DiasMesesAnos dma;
    DataQuebrada dq[2];
    dq[0] = quebraData(datainicial);
    dq[1] = quebraData(datafinal);

    if (q1(datainicial) == 0){
      dma.retorno = 2;
      return dma;
    }else if (q1(datafinal) == 0){
      dma.retorno = 3;
      return dma;
    }else{
      //verifique se a data final não é menor que a data inicial
      if(dq[0].iAno > dq[1].iAno){
        dma.retorno = 4;
        return dma;
      }else if(dq[0].iAno == dq[1].iAno && dq[0].iMes > dq[1].iMes){
        dma.retorno = 4;
        return dma;
      }else if(dq[0].iAno == dq[1].iAno && dq[0].iMes == dq[1].iMes && dq[0].iDia > dq[1].iDia){
        dma.retorno = 4;
        return dma;
      }
      //calcule a distancia entre as datas
    char month = dq[0].iMes + 1;
    dma.qtdDias = 0;
    dma.qtdMeses = 0;
    dma.qtdAnos = 0;
      
    int is_leap_year;
                
    if(dq[0].iAno % 4 == 0 && dq[0].iAno % 100 > 0)
        is_leap_year = 0;
    else
        if(dq[0].iAno % 4 == 0 && dq[0].iAno % 100 == 0 && dq[0].iAno % 400 == 0)
            is_leap_year = 0;
        else
            is_leap_year = 1;
   
    if(dq[0].iMes == dq[1].iMes && dq[0].iAno == dq[1].iAno)
        dma.qtdDias = dq[1].iDia - dq[0].iDia;
    else{
        for(; month < dq[1].iMes || dq[0].iAno < dq[1].iAno; month++){
            dma.qtdMeses++;
            if(month == 12){
                month = 0;
                dq[0].iAno++;
            }
            if(dma.qtdMeses == 12){
                dma.qtdMeses = 0;
                dma.qtdAnos++;
            }
        }
        dma.qtdDias = dq[1].iDia;
        
        switch(dq[0].iMes){
            case 2:{
                if(is_leap_year == 0){
                    dma.qtdDias += 29 - dq[0].iDia;
                    if(dma.qtdDias >= 29){
                        dma.qtdDias -= 29;
                        dma.qtdMeses++;
                    }
                }else{
                    dma.qtdDias += 28 - dq[0].iDia;
                    if(dma.qtdDias >= 28){
                        dma.qtdDias -= 28;
                        dma.qtdMeses++;
                    }
                }
                break;
            }
            case 4:
            case 6:
            case 9:
            case 11:{
                dma.qtdDias += 30 - dq[0].iDia;
                if(dma.qtdDias >= 30){
                    dma.qtdDias -= 30;
                    dma.qtdMeses++;
                }
                break;
            }
            default:{
                dma.qtdDias += 31 - dq[0].iDia;
                if(dma.qtdDias >= 31){
                    dma.qtdDias -= 31;
                    dma.qtdMeses++;
                }
                break;
            }
        }
        if(dq[1].iAno % 4 == 0 && dq[1].iAno % 100 > 0)
            is_leap_year = 0;
        else
            if(dq[1].iAno % 4 == 0 && dq[1].iAno % 100 == 0 && dq[1].iAno % 400 == 0)
                is_leap_year = 0;
            else
                is_leap_year = 1;
            
        switch(dq[1].iMes){
          case 2:{
            if(is_leap_year == 0){
              if(dma.qtdDias == 29){
                dma.qtdDias = 0;
                dma.qtdMeses++;
              }
            }else{
              if(dma.qtdDias == 28){
                dma.qtdDias = 0;
                dma.qtdMeses++;
              }
            }
            break;
          }
          case 4:
          case 6:
          case 9:
          case 11:{
            if(dma.qtdDias == 30){
              dma.qtdDias = 0;
              dma.qtdMeses++;
            }
            break;
          }
          default:{
            if(dma.qtdDias == 31){
              dma.qtdDias = 0;
              dma.qtdMeses++;
            }
            break;
          }
        }
        if(dma.qtdMeses == 12){
            dma.qtdMeses = 0;
            dma.qtdAnos++;
        }
    }
      //se tudo der certo
      dma.retorno = 1;
      return dma;
      
    }
}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */
int q3(char *texto, char c, int isCaseSensitive)
{
  int qtdOcorrencias = 0;

  remove_accents(texto); //removendo acentos

  int tam = strlen(texto);
  
  if(isCaseSensitive != 1){
    if(c >= 'A' && c <= 'Z')
      c = c + 32;

    for(int icont = 0; icont < tam; icont++){
      if(c == texto[icont]){
        qtdOcorrencias++;
      }else{
        if(texto[icont] >= 'A' && texto[icont] <= 'Z'){
          if(c == texto[icont] + 32)
            qtdOcorrencias++;
        }
      }
    }
  }else{
    for(int icont = 0; icont < tam; icont++){
      if(c == texto[icont])
        qtdOcorrencias++;
    }
  }
  return qtdOcorrencias;
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */
int q4(char *strTexto, char *strBusca, int posicoes[30])
{
  int nfrase[100];
  int nbusca[100];
  int icont, jcont, tam = 0, Pinicial, kcont;
  int qtdOcorrencias = -1;
    
  for(icont = 0; strBusca[icont] != '\0'; icont++)
    if(strBusca[icont] >= 'A' && strBusca[icont] <= 'Z')
      strBusca[icont] = strBusca[icont] + ' ';
    
  for(icont = 0; strTexto[icont] != '\0'; icont++)
    if(strTexto[icont] >= 'A' && strTexto[icont] <= 'Z')
      strTexto[icont] = strTexto[icont] + ' ';
            
  for(icont = 0, jcont = 0; strBusca[icont] != '\0'; icont++)
    if(strBusca[icont] != -61){
      nbusca[jcont++] = strBusca[icont] + '\0';
      tam++;
    }
    
  nbusca[jcont] = '\0';
    
  for(icont = 0, jcont = 0; strTexto[icont] != '\0'; icont++)
    if(strTexto[icont] != -61){
      nfrase[jcont++] = strTexto[icont] + '\0';
    }
    
  nfrase[jcont + 1] = '\0';
    
  for(icont = 0, jcont = 0, kcont = 0; nfrase[icont] != '\0'; icont++){
    if(nfrase[icont] == nbusca[jcont]){
      Pinicial = icont + 1;
      while(nfrase[icont] == nbusca[jcont]){
        icont++;
        jcont++;
      }
      if(jcont == tam){
        posicoes[kcont++] = Pinicial; 
        posicoes[kcont++] = icont;
      }
      icont--;
    }
    jcont = 0;
  }
  
  qtdOcorrencias = kcont / 2; 
  
  return qtdOcorrencias;
}

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num)
{
  int divisor1, divisor2, icont;
  int value = 0;
    
  for(divisor1 = 10; num / divisor1 > 0; divisor1 *= 10){}
    
  divisor1 /= 10;
    
  for(divisor2 = 10; divisor1 >= 1; divisor1 /= 10, divisor2 *= 10){
    value += (num % divisor2) / (divisor2 / 10) * divisor1;
  }
  num = value;

  return num;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca)
{
  int qtdOcorrencias = 0;
  int busca[25];
  int base[25];
  int divisor1, divisor2, icont, jcont, tam = 0;
    
  for(divisor1 = 10; numerobase / divisor1 > 0; divisor1 *= 10){}
    
  for(icont = 0; divisor1 / 10 >= 1; divisor1 /= 10, icont++){
    base[icont] = (numerobase % divisor1) / (divisor1 / 10);
  }
    
  base[icont] = '\0';
    
  for(divisor1 = 10; numerobusca / divisor1 > 0; divisor1 *= 10){}
    
  for(icont = 0; divisor1 / 10 >= 1; divisor1 /= 10, icont++){
    busca[icont] = (numerobusca % divisor1) / (divisor1 / 10);
    tam++;
  }
    
  busca[icont] = '\0';
    
  for(icont = 0, jcont = 0; base[icont] != '\0'; icont++){
    if(base[icont] == busca[jcont]){
      while(base[icont] == busca[jcont] && base[icont] != '\0'){
        icont++;
        jcont++;
      }
      if(jcont == tam)
        qtdOcorrencias++;
      
      jcont = 0;
      icont--;
    }
  }
    return qtdOcorrencias;
}




DataQuebrada quebraData(char data[]){
  DataQuebrada dq;
  char sDia[3];
	char sMes[3];
	char sAno[5];
	int i; 

	for (i = 0; data[i] != '/'; i++){
		sDia[i] = data[i];	
	}
	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sDia[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }  
	

	int j = i + 1; //anda 1 cada para pular a barra
	i = 0;

	for (; data[j] != '/'; j++){
		sMes[i] = data[j];
		i++;
	}

	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sMes[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }
	

	j = j + 1; //anda 1 cada para pular a barra
	i = 0;
	
	for(; data[j] != '\0'; j++){
	 	sAno[i] = data[j];
	 	i++;
	}

	if(i == 2 || i == 4){ // testa se tem 2 ou 4 digitos
		sAno[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno); 

	dq.valido = 1;
    
  return dq;
}
void remove_accents(char *text)
{
  int i, j = 0;
#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);
#elif _linux_
  setlocale(LC_ALL, "Portuguese");
#else
#endif

  const char *comAcentos[] = {"Ä", "Å", "Á", "Â", "À", "Ã", "ä", "á", "â", "à", "ã",
                              "É", "Ê", "Ë", "È", "é", "ê", "ë", "è",
                              "Í", "Î", "Ï", "Ì", "í", "î", "ï", "ì",
                              "Ö", "Ó", "Ô", "Ò", "Õ", "ö", "ó", "ô", "ò", "õ",
                              "Ü", "Ú", "Û", "ü", "ú", "û", "ù",
                              "Ç", "ç"};

  const char *semAcentos[] = {"A", "A", "A", "A", "A", "A", "a", "a", "a", "a", "a",
                              "E", "E", "E", "E", "e", "e", "e", "e",
                              "I", "I", "I", "I", "i", "i", "i", "i",
                              "O", "O", "O", "O", "O", "o", "o", "o", "o", "o",
                              "U", "U", "U", "u", "u", "u", "u",
                              "C", "c"};

  char buffer[256];
  buffer[0] = '\0';

  for (int i = 0; i < strlen(text);)
  {
    int found = 0;
    // Tenta substituir cada caractere acentuado por seu equivalente
    for (int j = 0; j < sizeof(comAcentos) / sizeof(comAcentos[0]); j++)
    {
      int len = strlen(comAcentos[j]);

      if (strncmp(&text[i], comAcentos[j], len) == 0)
      {
        strcat(buffer, semAcentos[j]);
        i += len;
        found = 1;
        break;
      }
    }
    if (!found)
    {
      strncat(buffer, &text[i], 1);
      i++;
    }
  }
  strcpy(text, buffer);
}
