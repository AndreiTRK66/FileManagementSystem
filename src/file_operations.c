#include "../include/file_operations.h"


void createFile(char* nume)
{
    if((strlen(nume)<255) && (strpbrk(nume,"\\/:*?\"<>|")==NULL)){
        FILE* fptr = fopen(nume,"w");
        if(fptr!= NULL){
            printf("Fisier creat cu succes! \n Numele fisierului este %s\n", nume);
            fclose(fptr);
        }else{
        log_error("Eroare creare fisier", nume);
        }
    }
    else {
        log_error("Eroare creare fisier", nume);
    }
   // }
}
void write_to_file(char*nume, char* text)
{
    FILE *fptr = fopen(nume,"a");
    if(fptr == NULL){
        log_error("Eroare scriere in fisier", nume);
    } else{
        fputs(text, fptr);
        fputs("\n",fptr);
        fclose(fptr);
    }
}
void read_from_file(char* nume)
{
    FILE* fptr = fopen(nume,"r");
    if(fptr != NULL)
    {
        char buffer[100];
        
        while(fgets(buffer,100,fptr))
        {
            printf("%s\n",buffer);
        }
        fclose(fptr);
    }else{
        log_error("Eroare citire din fisier", "Fisier.txt");
    }
}
void delete_file(char* nume)
{
   if(remove(nume))
   {
        fopen(nume,"r");
        log_error("Eroare stergere fisier", nume);
       // fclose(nume);
   }else {
        printf("Fisier Sters cu succes\n");
        //fclose(nume);
   }
}
int check_file_exists(char* nume) {
    FILE* temp = fopen(nume, "r");
    if (temp) {
        printf("Fisierul exista: %s\n", nume);
        fclose(temp);
        return 1;
    }

    char alt_path[300];
    snprintf(alt_path, sizeof(alt_path), "src/%s", nume);
    temp = fopen(alt_path, "r");
    if (temp) {
        printf("Fisierul exista: %s\n", alt_path);
        fclose(temp);
        return 2;
    }

    snprintf(alt_path, sizeof(alt_path), "include/%s", nume);
    temp = fopen(alt_path, "r");
    if (temp) {
        printf("Fisierul exista: %s\n", alt_path);
        fclose(temp);
        return 3;
    }

    printf("Fisierul nu exista\n");
    return 0;
}
void log_error(char* message,char* nume)
{
    perror(message);
    FILE* fptr = fopen("log.error", "a");
    if(fptr != NULL)
    {
        fprintf(fptr," Error: %s, File: %s, Description: %s \n", message, nume, strerror(errno));
        fclose(fptr);
    }
}
void file_check_permission(char *nume)
{
    if(access(nume,F_OK) == 0)
    {
        printf("Fisierul %s exista\n",nume);
        if(access(nume,R_OK) == 0)
        {
            printf("Fisierul %s poate fi citit\n", nume);
        } else {
            log_error("Eroare, fisierul nu poate fi citit\n",nume);
        }

        if(access(nume,W_OK) == 0)
        {
            printf("Fisierul %s are permisiunea de a fi scris\n", nume);
        } else {
            log_error("Eroare, fisierul nu poate fi citit\n", nume);
        }

    }else {
        log_error("Fisierul nu a fost gasit sau nu exista\n",nume);
    }
}
void file_backup(char* nume)
{
    if(check_file_exists(nume)==0)
    {
        return;
    }
    else {

        ensure_backup("backup");
        ensure_backup("backup/src");
        ensure_backup("backup/include");


        char nume_backup[50]="";
        strcat(nume_backup,"backup/");
        if(check_file_exists(nume)==2)
        {
            strcat(nume_backup,"src/");
        } else if(check_file_exists(nume)==3)
        {
            strcat(nume_backup,"include/");
        }
        strcat(nume_backup,nume);
        FILE* fptr = fopen(nume, "r");
        FILE* fbackup = fopen(nume_backup,"w");
        FILE* fjurnal = fopen("backup/jurnal.txt","a");
        unsigned char buffer[100];
        size_t numRead;
        while ((numRead = fread(buffer, sizeof(unsigned char), sizeof(buffer), fptr)) > 0) {
             fwrite(buffer, sizeof(unsigned char), numRead, fbackup);
        }
        time_t mytime = time(NULL);
        char jurnal_entry[300];
        char time_str[50];
        strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S",localtime(&mytime));

        snprintf(jurnal_entry,sizeof(jurnal_entry),"%s - backup facut cu succes la ora %s\n",nume, time_str);
        //char* time_str = ctime(&mytime);
        //time_str[strlen(time_str)-1] = '\0';
       // fopen("backup/jurnal.txt","a");
       // strcat(nume," - backup facut cu succes la ora: ");
        //strcat(nume, time_str);
        fputs(jurnal_entry, fjurnal);
        fclose(fptr);
        fclose(fbackup);
        fclose(fjurnal);
    }
}
void ensure_backup(const char* path) {
    struct stat file_stat;
    if (stat(path, &file_stat) != 0) {
        mkdir(path);
    }
}
