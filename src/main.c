#include "../include/file_operations.h"


int main(){
    int n,meniu = 10;
    char text[100], textFisier[100],numeFisier[50];
    //FILE *pointer;
    while(meniu != 0){

        printf("MENIU \n Selecteaza actiunea dorita:\n 1 - Creaza fisiere\n 2 - Scrie in fisier\n 3 - Citeste din fisier\n 4 - Verifica existenta fisierului\n 5 - Verifica permisiunea fisierului\n 6 - Sterge fisier\n 7 - Backup fisier \n 0 - EXIT\n");
        scanf("%d",&meniu);
        switch(meniu)
        {
            case 0:
                meniu = 0; 
                break;
            case 1:
                printf("Introdu numele fisierului: \n");
                scanf("%s",numeFisier);
                createFile(numeFisier);
                break;
            case 2: 
                printf("Introdu numele fisierului in care vrei sa scrii: \n");
                scanf("%s",numeFisier);
                while(getchar() != '\n');
                if(check_file_exists(numeFisier))
                {
                    printf("Introdu textul pentru a fi introdus in fisier: \n");
                    //scanf("%s",textFisier);
                    fgets(textFisier,100,stdin);
                    textFisier[strcspn(textFisier, "\n")] = 0;
                    write_to_file(numeFisier,textFisier);
                }
                break;
            case 3:
                printf("Introdu numele fisierului din care sa citesti: \n");
                scanf("%s",numeFisier);
                if(check_file_exists(numeFisier)){
                    read_from_file(numeFisier);
                }
                break;
            case 4:
                printf("Introdu numele fisierului ce vrei sa fie verificat: \n");
                scanf("%s",numeFisier);
                check_file_exists(numeFisier);
                break;
            case 5:
                printf("Introdu numele fisierului ce vrei sa fie verificat: \n");
                scanf("%s",numeFisier);
                file_check_permission(numeFisier);
                break;
            case 6:
                printf("Introdu numele fisierului de sters: \n");
                scanf("%s",numeFisier);
                delete_file(numeFisier);
                break;
            case 7:
                printf("Introdu numele fisierului pentru backup: \n");
                scanf("%s",numeFisier);
                file_backup(numeFisier);
                break;
            default:
                printf("Caracter gresit, Iesire din program.");
                meniu = 0; 
                break;
        }
    }

    /*printf("Introdu numarul de fisiere care for fi create: \n");
    scanf("%d",&n);
    createFile(pointer,n);

    while(1)
    {

        printf("Introdu numele fisierului pentru a verifica daca exista (00 pentru a termina verificarea): \n");
        scanf("%s",text);
        if(strcmp(text, "00") == 0)
        {
            printf("Iesire din program\n");
            break;
        }
        check_file_exists(text);
    }
    printf("Introdu textul pentru a fi scris in fisier: \n");
    scanf("%s",textFisier);
    write_to_file(pointer, textFisier);
    read_from_file(pointer);
    file_check_permission("Fisier.txt");
    //delete_file("Fisier.txt"); */
    return 0;
}