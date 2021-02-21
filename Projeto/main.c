#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main()
{

    setlocale(LC_ALL,"");

    FILE *fp = fopen("login.txt", "a+");
    char caractere,comp[10]= {'\0'},user[10]= {'\0'},senha[10]= {'\0'},nulo[10]= {'\0'};
    int i=0,existuser,op,n,aux=0;
    struct dados
    {
        char user[10];
        char pw[10];
    };
    struct dados *dds=NULL;

inicio:
    printf("Digite a opção desejada:\n\n[1]Cadastrar novo usuário\n[2]Fazer login com usuário cadastrado\n[0]Fechar programa\n\n-> ");
    scanf("%d",&op);
    fflush(stdin);

    if(op==1)
    {
        printf("\nQuantos usuários deseja cadastrar?\n\n-> ");
        scanf("%d",&n);
        fflush(stdin);

        dds=malloc(n*sizeof(struct dados)); // ALOCA MEMORIA PRO VETOR DA STRUCT
        struct dados login[n]; // DECLARA VETOR DE STRUCT

        for(i=0; i<n; i++)
        {
            printf("\nDigite o novo usuário:\n\n-> ");
            gets(login[i].user);
            printf("\nDigite a senha do usuário:\n\n-> ");
            gets(login[i].pw);
        }

        for (i=0; i<n; i++)
        {
            fprintf(fp,"%s\n",login[i].user); // PRINTA USUARIO NO ARQUIVO
            fprintf(fp,"%s\n\n",login[i].pw); // PRINTA SENHA EM BAIXO DO USUARIO NO ARQUIVO
        }
        free(dds);
        dds=NULL;
        fseek(fp,0, SEEK_SET); // APONTA PRO INICIO DO ARQUIVO
        for(i=0; i<10; i++) // ERA A VARIAVEL COMP
                            comp[i]='\0';
        printf("\n");
        goto inicio;
    }

    if(op==2) //FAZER LOGIN
    {
        printf("\nDigite um usuário:\n\n-> ");
        gets(user);

        while((caractere = fgetc(fp)) != EOF)
        {
            if(caractere!='\n')
            {
                comp[i]=caractere;
                i++;
            }
            if(caractere=='\n')
            {
                if (strcmp(user,comp)==0)
                {
                    printf("\nDigite a senha:\n\n-> ");
digsenha:
                    gets(senha);
                    if(aux!=1)
                    {
                        for(i=0; i<10; i++) // ZERA A VARIAVEL COMP
                            comp[i]='\0';
                        i=0;
                        while((caractere = fgetc(fp))!='\n')
                        {
                            comp[i]=caractere;
                            i++;
                        }
                    }
                    if(caractere=='\n')
                    {
                        if (strcmp(senha,comp)==0) // COMPARA SENHA DIGITADA COM SENHA DO ARQUIVO
                            printf("\nBem-vindo!\n");

                        else
                        {
                            printf("\nFalha na autenticação. Digite a senha novamente:\n\n-> ");
                            aux=1;
                            goto digsenha;
                        }
                    }
                    existuser=1; //VARIAVEL DE CONTROLE
                }
                else
                {
                    for(i=0; i<10; i++) // ZERA VARIAVEL COMP PARA EVITAR PROBLEMAS
                        comp[i]='\0';
                    i=0;
                }
            }
        }
        if (existuser!=1)
        {
            printf("\nUsuário não cadastrado. ");
            fseek(fp,0, SEEK_SET);
            goto inicio;
        }
    }

    if(op==0) // FECHA PROGRAMA
        return 0;

    if(op>2)
    {
        printf("\nOpção inválida. ");
        goto inicio;
    }
}
