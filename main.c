#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int tam;

typedef struct valores
{
    char Origem[4];
    char Destino[4];
    float Valor;
    int Visitado;
}casas;

void imprime(casas vet[])
{
    int i;
    for(i=0;i<tam;i++)
    {
        if(strcmp(vet[i].Origem,"N/A")!=0)
        {
            printf("\n\t---CASA [%d] ----",i);
            printf("\n  ORIGEM: %s\n  DESTINO: %s\n  CUSTO: %.2f",vet[i].Origem,vet[i].Destino,vet[i].Valor);
        }
    }
}

void insAresta(casas vet[], char Origem[],char Destino[],float Valor)
{
    int i=0;
    for(i=0;i<tam;i++)
    {
        if(strcmp(vet[i].Origem,"N/A")==0)
        {
            strcpy(vet[i].Origem,Origem);
            strcpy(vet[i].Destino,Destino);
            vet[i].Valor=Valor;
            break;
        }
    }

}


void leitura(casas vet[], FILE *arquivo)
{
    char Origem[4];
    char Destino[4];
    float Valor=0;

    for(int i=0;i<tam;i++)
    {
        strcpy(vet[i].Origem,"N/A");
        vet[i].Visitado=0;
    }

    for(int i=0 ; i<tam || !feof(arquivo) ; i++)
    {
        fscanf(arquivo,"%s %s R$%f",Origem,Destino,&Valor);
        insAresta(vet,Origem,Destino,Valor);
    }
    fclose(arquivo);

}

void SelectionSort(casas vetor[], int n)
{
    int menor;
    casas aux;
    for(int i=0;i<n;i++)
    {
        menor=i;
        for(int j=i+1;j<n;j++)
        {
            if(strcmp(vetor[j].Origem,vetor[menor].Origem)<0)
                menor=j;
        }

        strcpy(aux.Origem,vetor[i].Origem);
        strcpy(aux.Destino,vetor[i].Destino);
        aux.Valor=vetor[i].Valor;

        strcpy(vetor[i].Origem,vetor[menor].Origem);
        strcpy(vetor[i].Destino,vetor[menor].Destino);
        vetor[i].Valor=vetor[menor].Valor;

        strcpy(vetor[menor].Origem,aux.Origem);
        strcpy(vetor[menor].Destino,aux.Destino);
        vetor[menor].Valor=aux.Valor;
    }
}

void Path(casas vet[], char Origem[], char Destino[],int pos)
{
    int i;



    if(vet[pos].Visitado==1)
    {
        printf("%s",vet[pos].Destino);
    }
    else
    {
        printf("%s ->",vet[pos].Origem);
        vet[pos].Visitado=1;
        for(i=0;i<tam;i++)
        {
            if(strcmp(vet[i].Origem,Destino)==0)
            {
                if(vet[i].Visitado!=1)
                    Path(vet,vet[i].Origem,vet[i].Destino,i);
                else
                    Path(vet,vet[i++].Origem,vet[i++].Destino,i++);
            }
        }
    }


}
void conexoes(casas vet[],char Origem[])
{
    //Origem = =2
    //Visitado = 1
    //Não Visistado = 0
    int i=0;
    for(i=0;i<tam;i++)
    {
        if(strcmp(vet[i].Origem,Origem)==0)
        {
            Path(vet,vet[i].Origem,vet[i].Destino,i);
            printf("\n");
        }
        i++;
    }


}

void Destinos(casas vet[],char Origem[], char Dest[][4], int aeroportos)
{
    int i=0,j=0,flag=0;

    for(int i=0;i<tam;i++)
    {
        strcpy(Dest[i],"N/A");
    }

    for(i=0;i<tam;i++)
    {
        flag=0;
        if(strcmp(vet[i].Origem,Origem)!=0)
        {
            for(j=0;j<aeroportos;j++)
            {
                if(strcmp(vet[i].Origem,Dest[j])==0)
                {
                    flag=1;
                    break;
                }

            }
            if(flag!=1)
            {
                for(j=0;j<aeroportos;j++)
                {
                    if(strcmp("N/A",Dest[j])==0)
                    {
                        strcpy(Dest[j],vet[i].Origem);
                        break;
                    }
                }

            }
        }

    }

    for(i=0;i<tam;i++)
    {
        flag=0;
        if(strcmp(vet[i].Destino,Origem)!=0)
        {
            for(j=0;j<aeroportos;j++)
            {
                if(strcmp(vet[i].Destino,Dest[j])==0)
                {
                    flag=1;
                    break;
                }

            }
            if(flag!=1)
            {
                for(j=0;j<aeroportos;j++)
                {
                    if(strcmp("N/A",Dest[j])==0)
                    {
                        strcpy(Dest[i],vet[i].Destino);
                        break;
                    }
                }

            }
        }
    }
    printf("\n=== Destinos ===\n");
    for(i=0;i<tam;i++)
    {
        if(strcmp("N/A",Dest[i])!=0)
            printf(" %s ",Dest[i]);
    }
}

int main(/*FILE *arquivo, char Origem[4]*/)
{

    FILE* arquivo;
    int aeroportos=0;
    int voos=0;

    arquivo = fopen("Voos.txt", "r");
    fscanf(arquivo,"%d",&aeroportos);
    fscanf(arquivo,"%d",&voos);
    tam=voos;

    casas *vet;
    vet = (casas*)malloc(tam * sizeof(casas));
    char Dest[aeroportos][4];
    leitura(vet,arquivo);
    SelectionSort(vet,voos);
    //conexoes(vet,"VCP");
    Destinos(vet,"CNF",Dest,aeroportos);

    imprime(vet);

    return 0;
}
