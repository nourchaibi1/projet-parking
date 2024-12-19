#ifndef USER_H
#define USER_H

#include <stdio.h>
#include <string.h>

#include <gtk/gtk.h>



typedef struct {
    char cin[60];
    char First_name[60];
    char Last_name[60];
    char phone_number[60];
    char day[60];
    char month[60];
    char year[60];
    char gender[60];  
    char email[60];
    char pwd[60];
} user;

int verify_login(const char *username, const char *password) ;

int cin_exists(char *cin1) ;
int is_all_digits(const char *str) ;
void addUser(char *filename, user u) ;

void modifieruser(char *filename, user u);

void supprimer(const char *cin_to_delete);

void mes_services(GtkWidget *treeview,char *cin,char *mois,char *annee) ;
double calculerPrixTotal(const char* cin, const char* mois, const char* annee) ;

void show_user(GtkWidget *fr) ;

void chercher(GtkWidget *fr,char *cherche) ;



#endif 







