#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"

#include "user.c"




char login1[60];
char sexe[60];
int check=0;

// function show msg error dialog
void show_error_dialog(const char *message) {
    GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "%s", message);
    gtk_window_set_title(GTK_WINDOW(dialog), "Erreur");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}


//btn inscrit thiz mil login lil page ajout
void
on_inscription_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *login,*ajouterhadil;
login = lookup_widget(GTK_WIDGET(button), "login");
   gtk_widget_destroy(login);
        ajouterhadil = create_ajouterhadil();
        gtk_widget_show(ajouterhadil);


}




//btn ajouter  
void
on_ajouthadil_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{


GtkWidget *ajouterhadil, *login;
    ajouterhadil = lookup_widget(GTK_WIDGET(button), "ajouterhadil");

    user d;

    GtkWidget *cin, *nom, *prenom, *jour, *mois, *annee, *pwd, *email, *telephone;
    cin = lookup_widget(GTK_WIDGET(button), "entry32");
    nom = lookup_widget(GTK_WIDGET(button), "entry26");
    prenom = lookup_widget(GTK_WIDGET(button), "entry27");
    jour = lookup_widget(GTK_WIDGET(button), "spinbutton22");
    mois = lookup_widget(GTK_WIDGET(button), "combobox1");
    annee = lookup_widget(GTK_WIDGET(button), "spinbutton24");

    telephone = lookup_widget(GTK_WIDGET(button), "entry28");
    email = lookup_widget(GTK_WIDGET(button), "entry29");
    pwd = lookup_widget(GTK_WIDGET(button), "entry33");

    strcpy(d.cin, gtk_entry_get_text(GTK_ENTRY(cin)));
    if (strlen(d.cin) == 0) {
        show_error_dialog("Le CIN ne doit pas être vide");
        return;
    }
    if (strlen(d.cin) != 8 || !is_all_digits(d.cin)) {
        show_error_dialog("Le CIN ne respecte pas la forme (contient 8 chiffres)");
        return;
    }
   if (cin_exists(d.cin)) {
        show_error_dialog("Le CIN existe déjà");
        return;
    }


    strcpy(d.First_name, gtk_entry_get_text(GTK_ENTRY(nom)));
    if (strlen(d.First_name) == 0) {
        show_error_dialog("Le nom ne doit pas être vide");
        return;
    }


    strcpy(d.Last_name, gtk_entry_get_text(GTK_ENTRY(prenom)));
    if (strlen(d.Last_name) == 0) {
        show_error_dialog("Le prénom ne doit pas être vide");
        return;
    }



    int j = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(jour));
    int a = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(annee));

    sprintf(d.day, "%d", j);
    if (strlen(d.day) == 0) {
        show_error_dialog("Le jour ne doit pas être vide");
        return;
    }

    sprintf(d.year, "%d", a);
    if (strlen(d.year) == 0) {
        show_error_dialog("L'année ne doit pas être vide");
        return;
    }

    strcpy(d.month, gtk_combo_box_get_active_text(GTK_COMBO_BOX(mois)));
    if (strlen(d.month) == 0) {
        show_error_dialog("Le mois doit être sélectionné");
        return;
    }

    strcpy(d.email, gtk_entry_get_text(GTK_ENTRY(email)));
    if (strlen(d.email) == 0) {
        show_error_dialog("L'email ne doit pas être vide");
        return;
    }

    strcpy(d.phone_number, gtk_entry_get_text(GTK_ENTRY(telephone)));
    if (strlen(d.phone_number) != 8 || !is_all_digits(d.phone_number)) {
        show_error_dialog("Le numéro de téléphone est incorrect");
        return;
    }

    strcpy(d.pwd, gtk_entry_get_text(GTK_ENTRY(pwd)));
    if (strlen(d.pwd) == 0) {
        show_error_dialog("Le mot de passe ne doit pas être vide");
        return;
    }

    strcpy(d.gender, sexe);  
    if (strlen(d.gender) == 0) {
        show_error_dialog("Sélectionnez le sexe d'utilisateur");
        return;
    }

    if (!check) {
        show_error_dialog("j'accepte les conditions générales et la politique de confidentialité");
        return;
    }

    addUser("users.txt", d);
    check = 0;

    GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                               GTK_DIALOG_DESTROY_WITH_PARENT,
                                               GTK_MESSAGE_OTHER,
                                               GTK_BUTTONS_OK,
                                               "votre compte a été crée avec succès ✔");
    gtk_window_set_title(GTK_WINDOW(dialog), "Succès");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    gtk_widget_destroy(ajouterhadil);
    login = create_login();
    gtk_widget_show(login);

}



void
on_button28_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_checkbutton15_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton)) {
        check = 1;
    } else {
        check = 0; 
    }
}


void
on_radiofemme_toggled                  (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton)){
strcpy(sexe,"F");}
}


void
on_radiomale_toggled                   (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton)){
strcpy(sexe,"M");}
}


void
on_button45_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button46_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_radiobutton11_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton)){
strcpy(sexe,"M");}
}


void
on_radiobutton12_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton)){
strcpy(sexe,"F");}
}

//btn login 
void
on_loginbtn_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{




    GtkWidget *login, *profil,*dialog,*menu_admin3;
    GtkWidget *logi, *mtp;

    
    char mot_de_passe[100];

    login = lookup_widget(GTK_WIDGET(button), "login");
    logi = lookup_widget(GTK_WIDGET(button), "entry1");
    mtp = lookup_widget(GTK_WIDGET(button), "entry2");

    g_strlcpy(login1, gtk_entry_get_text(GTK_ENTRY(logi)), sizeof(login1)+20);
    g_strlcpy(mot_de_passe, gtk_entry_get_text(GTK_ENTRY(mtp)), sizeof(mot_de_passe)+20);

    int is_authenticated = verify_login(login1, mot_de_passe);

    if (is_authenticated==1) {



        gtk_widget_destroy(login);
        profil = create_profil();
        gtk_widget_show(profil);


    GtkWidget *a11, *a22,*a33,*a44, *a55,*a66,*a77, *a88,*a99;
        a11 = lookup_widget(profil, "name");
        a22 = lookup_widget(profil, "prenom");
        a33 = lookup_widget(profil, "cin");
        a44 = lookup_widget(profil, "tds");
        a55 = lookup_widget(profil, "label625");
        a66 = lookup_widget(profil, "label626");
        a77 = lookup_widget(profil, "label627");
        a88 = lookup_widget(profil, "label628");
        a99 = lookup_widget(profil, "label629");

        FILE *f = fopen("users.txt", "r");

user temp;

        if (f != NULL) {
            while (fscanf(f, "%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^\n]\n",
       temp.cin, temp.First_name, temp.Last_name, temp.phone_number,
       temp.day, temp.month, temp.year, temp.gender,
       temp.email, temp.pwd) != EOF) {

                if (strcmp(temp.cin, login1) == 0) {
                    gtk_label_set_text(GTK_LABEL(a11), temp.First_name);
                    gtk_label_set_text(GTK_LABEL(a22), temp.Last_name);
                    gtk_label_set_text(GTK_LABEL(a33), temp.cin);

                    gtk_label_set_text(GTK_LABEL(a44), temp.phone_number);
                    gtk_label_set_text(GTK_LABEL(a55), temp.day);
                    gtk_label_set_text(GTK_LABEL(a66), temp.month);
                    gtk_label_set_text(GTK_LABEL(a77), temp.year);
                    gtk_label_set_text(GTK_LABEL(a88), temp.gender);
                    gtk_label_set_text(GTK_LABEL(a99), temp.email);

                    break;
                }
            }
            fclose(f);
        }
    
	


}

//admin
	else if((strcmp("admin", login1) == 0) && (strcmp("admin", mot_de_passe) == 0)){

        gtk_widget_destroy(login);
        menu_admin3 = create_menu_admin3();
        gtk_widget_show(menu_admin3);

}

     else {
        dialog = gtk_message_dialog_new(NULL,
                                         GTK_DIALOG_DESTROY_WITH_PARENT,
                                         GTK_MESSAGE_ERROR,
                                         GTK_BUTTONS_OK,
                                         "Le nom d'utilisateur ou le mot de passe est incorrect");
        gtk_window_set_title(GTK_WINDOW(dialog), "Alerte");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }




}






void
on_button37_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *login,*ajouterhadil;
ajouterhadil = lookup_widget(GTK_WIDGET(button), "ajouterhadil");
   gtk_widget_destroy(ajouterhadil);
        login = create_login();
        gtk_widget_show(login);
}



//btn deconnection

void
on_deconnexion_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *login,*profil;
profil = lookup_widget(GTK_WIDGET(button), "profil");
   gtk_widget_destroy(profil);
        login = create_login();
        gtk_widget_show(login);
}

//btn ili thiz lil supprimer
void
on_suprimer_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *hadil10,*profil;
profil = lookup_widget(GTK_WIDGET(button), "profil");
   gtk_widget_destroy(profil);
        hadil10 = create_hadil10();
        gtk_widget_show(hadil10);

}

//btn thiz lil formulaire modifier
void on_modifier_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *modifierhadil, *profil, *a11;
    profil = lookup_widget(GTK_WIDGET(button), "profil");
  gtk_widget_destroy(profil);
    modifierhadil = create_modifierhadil();
    gtk_widget_show(modifierhadil);
    int jj, mm, aa;

    a11 = lookup_widget(modifierhadil, "label633");

    FILE *f = fopen("users.txt", "r");

    user temp;

    if (f != NULL) {
        while (fscanf(f, "%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^\n]\n",
                      temp.cin, temp.First_name, temp.Last_name, temp.phone_number,
                      temp.day, temp.month, temp.year, temp.gender,
                      temp.email, temp.pwd) != EOF) {

            if (strcmp(temp.cin, login1) == 0) {
                gtk_label_set_text(GTK_LABEL(a11), temp.cin);

                gtk_entry_set_text(GTK_ENTRY(lookup_widget(modifierhadil, "entry18")), temp.First_name);
                gtk_entry_set_text(GTK_ENTRY(lookup_widget(modifierhadil, "entry19")), temp.Last_name);
                gtk_entry_set_text(GTK_ENTRY(lookup_widget(modifierhadil, "entry21")), temp.phone_number);
                gtk_entry_set_text(GTK_ENTRY(lookup_widget(modifierhadil, "entry20")), temp.email);
                gtk_entry_set_text(GTK_ENTRY(lookup_widget(modifierhadil, "entry25")), temp.pwd);

                // Convertir le jour et l'année en entier
                jj = atoi(temp.day);
                aa = atoi(temp.year); // Changement ici pour l'année

                // Définir les valeurs dans les boutons de spin pour le jour et l'année
                gtk_spin_button_set_value(GTK_SPIN_BUTTON(lookup_widget(modifierhadil, "spinbutton18")), jj);
                gtk_spin_button_set_value(GTK_SPIN_BUTTON(lookup_widget(modifierhadil, "spinbutton20")), aa);

                // Tableau des mois pour simplifier la comparaison
                const char *months[] = {
                    "Janvier", "Février", "Mars", "Avril", "Mai", "Juin", "Juillet",
                    "Août", "Septembre", "Octobre", "Novembre", "Décembre"
                };

                for (int i = 0; i < 12; i++) {
                    if (strcmp(temp.month, months[i]) == 0) {
                        gtk_combo_box_set_active(GTK_COMBO_BOX(lookup_widget(modifierhadil, "combobox2")), i);
                        break;
                    }
                }

                break;
            }
        }
        fclose(f);
    }

  
}
//supprimer 
void
on_button51_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *login,*hadil10;

hadil10 = lookup_widget(GTK_WIDGET(button), "hadil10");



    GtkWidget *dialog;
    GtkWidget  *mtp;

    
    char mot_de_passe[100];



    mtp = lookup_widget(GTK_WIDGET(button), "entry53");

    g_strlcpy(mot_de_passe, gtk_entry_get_text(GTK_ENTRY(mtp)), sizeof(mot_de_passe)+20);

    int is_authenticated = verify_login(login1, mot_de_passe);

    if (is_authenticated==1) {

	

	supprimer(login1);


   gtk_widget_destroy(hadil10);

        login = create_login();
        gtk_widget_show(login);

}

     else {
        dialog = gtk_message_dialog_new(NULL,
                                         GTK_DIALOG_DESTROY_WITH_PARENT,
                                         GTK_MESSAGE_ERROR,
                                         GTK_BUTTONS_OK,
                                         "le mot de passe est incorrect");
        gtk_window_set_title(GTK_WINDOW(dialog), "Alerte");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }




}

//btn retour mil factures
void
on_button52_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *hadil10,*profil;
hadil10 = lookup_widget(GTK_WIDGET(button), "hadil10");
   gtk_widget_destroy(hadil10);
        profil = create_profil();
        gtk_widget_show(profil);

    GtkWidget *a11, *a22,*a33,*a44, *a55,*a66,*a77, *a88,*a99;
        a11 = lookup_widget(profil, "name");
        a22 = lookup_widget(profil, "prenom");
        a33 = lookup_widget(profil, "cin");
        a44 = lookup_widget(profil, "tds");
        a55 = lookup_widget(profil, "label625");
        a66 = lookup_widget(profil, "label626");
        a77 = lookup_widget(profil, "label627");
        a88 = lookup_widget(profil, "label628");
        a99 = lookup_widget(profil, "label629");

        FILE *f = fopen("users.txt", "r");

user temp;

        if (f != NULL) {
            while (fscanf(f, "%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^\n]\n",
       temp.cin, temp.First_name, temp.Last_name, temp.phone_number,
       temp.day, temp.month, temp.year, temp.gender,
       temp.email, temp.pwd) != EOF) {

                if (strcmp(temp.cin, login1) == 0) {
                    gtk_label_set_text(GTK_LABEL(a11), temp.First_name);
                    gtk_label_set_text(GTK_LABEL(a22), temp.Last_name);
                    gtk_label_set_text(GTK_LABEL(a33), temp.cin);

                    gtk_label_set_text(GTK_LABEL(a44), temp.phone_number);
                    gtk_label_set_text(GTK_LABEL(a55), temp.day);
                    gtk_label_set_text(GTK_LABEL(a66), temp.month);
                    gtk_label_set_text(GTK_LABEL(a77), temp.year);
                    gtk_label_set_text(GTK_LABEL(a88), temp.gender);
                    gtk_label_set_text(GTK_LABEL(a99), temp.email);

                    break;
                }
            }
            fclose(f);
        }
    


}


void
on_radiobutton10_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton)){
strcpy(sexe,"F");}
}



// modifier
void
on_button31_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

GtkWidget *modifierhadil, *profil;
    modifierhadil = lookup_widget(GTK_WIDGET(button), "modifierhadil");

    user d;

    GtkWidget  *nom, *prenom, *jour, *mois, *annee, *pwd, *email, *telephone;

    nom = lookup_widget(GTK_WIDGET(button), "entry18");
    prenom = lookup_widget(GTK_WIDGET(button), "entry19");
    jour = lookup_widget(GTK_WIDGET(button), "spinbutton18");
    mois = lookup_widget(GTK_WIDGET(button), "combobox2");
    annee = lookup_widget(GTK_WIDGET(button), "spinbutton20");

    telephone = lookup_widget(GTK_WIDGET(button), "entry21");
    email = lookup_widget(GTK_WIDGET(button), "entry20");
    pwd = lookup_widget(GTK_WIDGET(button), "entry25");

    strcpy(d.cin, login1);
  


    strcpy(d.First_name, gtk_entry_get_text(GTK_ENTRY(nom)));
    if (strlen(d.First_name) == 0) {
        show_error_dialog("Le nom ne doit pas être vide");
        return;
    }


    strcpy(d.Last_name, gtk_entry_get_text(GTK_ENTRY(prenom)));
    if (strlen(d.Last_name) == 0) {
        show_error_dialog("Le prénom ne doit pas être vide");
        return;
    }



    int j = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(jour));
    int a = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(annee));

    sprintf(d.day, "%d", j);
    if (strlen(d.day) == 0) {
        show_error_dialog("Le jour ne doit pas être vide");
        return;
    }

    sprintf(d.year, "%d", a);
    if (strlen(d.year) == 0) {
        show_error_dialog("L'année ne doit pas être vide");
        return;
    }

    strcpy(d.month, gtk_combo_box_get_active_text(GTK_COMBO_BOX(mois)));
    if (strlen(d.month) == 0) {
        show_error_dialog("Le mois doit être sélectionné");
        return;
    }

    strcpy(d.email, gtk_entry_get_text(GTK_ENTRY(email)));
    if (strlen(d.email) == 0) {
        show_error_dialog("L'email ne doit pas être vide");
        return;
    }

    strcpy(d.phone_number, gtk_entry_get_text(GTK_ENTRY(telephone)));
    if (strlen(d.phone_number) != 8 || !is_all_digits(d.phone_number)) {
        show_error_dialog("Le numéro de téléphone est incorrect");
        return;
    }

    strcpy(d.pwd, gtk_entry_get_text(GTK_ENTRY(pwd)));
    if (strlen(d.pwd) == 0) {
        show_error_dialog("Le mot de passe ne doit pas être vide");
        return;
    }

    strcpy(d.gender, sexe);  
    if (strlen(d.gender) == 0) {
        show_error_dialog("Sélectionnez le sexe d'utilisateur");
        return;
    }

    if (!check) {
        show_error_dialog("j'accepte les conditions générales et la politique de confidentialité");
        return;
    }


   modifieruser("users.txt", d);
    check = 0;

    GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                               GTK_DIALOG_DESTROY_WITH_PARENT,
                                               GTK_MESSAGE_OTHER,
                                               GTK_BUTTONS_OK,
                                               "votre compte a été modifier avec succès ✔");
    gtk_window_set_title(GTK_WINDOW(dialog), "Succès");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    gtk_widget_destroy(modifierhadil);
    profil = create_profil();
    gtk_widget_show(profil);


    GtkWidget *a11, *a22,*a33,*a44, *a55,*a66,*a77, *a88,*a99;
        a11 = lookup_widget(profil, "name");
        a22 = lookup_widget(profil, "prenom");
        a33 = lookup_widget(profil, "cin");
        a44 = lookup_widget(profil, "tds");
        a55 = lookup_widget(profil, "label625");
        a66 = lookup_widget(profil, "label626");
        a77 = lookup_widget(profil, "label627");
        a88 = lookup_widget(profil, "label628");
        a99 = lookup_widget(profil, "label629");

        FILE *f = fopen("users.txt", "r");

user temp;

        if (f != NULL) {
            while (fscanf(f, "%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^\n]\n",
       temp.cin, temp.First_name, temp.Last_name, temp.phone_number,
       temp.day, temp.month, temp.year, temp.gender,
       temp.email, temp.pwd) != EOF) {

                if (strcmp(temp.cin, login1) == 0) {
                    gtk_label_set_text(GTK_LABEL(a11), temp.First_name);
                    gtk_label_set_text(GTK_LABEL(a22), temp.Last_name);
                    gtk_label_set_text(GTK_LABEL(a33), temp.cin);

                    gtk_label_set_text(GTK_LABEL(a44), temp.phone_number);
                    gtk_label_set_text(GTK_LABEL(a55), temp.day);
                    gtk_label_set_text(GTK_LABEL(a66), temp.month);
                    gtk_label_set_text(GTK_LABEL(a77), temp.year);
                    gtk_label_set_text(GTK_LABEL(a88), temp.gender);
                    gtk_label_set_text(GTK_LABEL(a99), temp.email);

                    break;
                }
            }
            fclose(f);
        }
    
}

//btn anuuller modifier
void
on_button32_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{GtkWidget *modifierhadil, *profil;
    modifierhadil = lookup_widget(GTK_WIDGET(button), "modifierhadil");
  gtk_widget_destroy(modifierhadil);
    profil = create_profil();
    gtk_widget_show(profil);


    GtkWidget *a11, *a22,*a33,*a44, *a55,*a66,*a77, *a88,*a99;
        a11 = lookup_widget(profil, "name");
        a22 = lookup_widget(profil, "prenom");
        a33 = lookup_widget(profil, "cin");
        a44 = lookup_widget(profil, "tds");
        a55 = lookup_widget(profil, "label625");
        a66 = lookup_widget(profil, "label626");
        a77 = lookup_widget(profil, "label627");
        a88 = lookup_widget(profil, "label628");
        a99 = lookup_widget(profil, "label629");

        FILE *f = fopen("users.txt", "r");

user temp;

        if (f != NULL) {
            while (fscanf(f, "%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^\n]\n",
       temp.cin, temp.First_name, temp.Last_name, temp.phone_number,
       temp.day, temp.month, temp.year, temp.gender,
       temp.email, temp.pwd) != EOF) {

                if (strcmp(temp.cin, login1) == 0) {
                    gtk_label_set_text(GTK_LABEL(a11), temp.First_name);
                    gtk_label_set_text(GTK_LABEL(a22), temp.Last_name);
                    gtk_label_set_text(GTK_LABEL(a33), temp.cin);

                    gtk_label_set_text(GTK_LABEL(a44), temp.phone_number);
                    gtk_label_set_text(GTK_LABEL(a55), temp.day);
                    gtk_label_set_text(GTK_LABEL(a66), temp.month);
                    gtk_label_set_text(GTK_LABEL(a77), temp.year);
                    gtk_label_set_text(GTK_LABEL(a88), temp.gender);
                    gtk_label_set_text(GTK_LABEL(a99), temp.email);

                    break;
                }
            }
            fclose(f);
        }
    
}


void
on_radiobutton9_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton)){
strcpy(sexe,"M");}
}


void
on_checkbutton16_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton)) {
        check = 1;
    } else {
        check = 0; 
    }
}

//mes factures

void
on_button67_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

 GtkWidget *hadil6,*profil;
profil = lookup_widget(GTK_WIDGET(button), "profil");
   gtk_widget_destroy(profil);
        hadil6 = create_hadil6();
        gtk_widget_show(hadil6);
            gtk_combo_box_set_active(GTK_COMBO_BOX(lookup_widget(hadil6, "combobox3")), 0);
   
    
}

// btn deconnection admin
void
on_button47_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *login, *touscitoyen;
    touscitoyen = lookup_widget(GTK_WIDGET(button), "touscitoyen");
  gtk_widget_destroy(touscitoyen);
    login = create_login();
    gtk_widget_show(login);
}


void on_calculer_clicked(GtkButton *button, gpointer user_data) {
    char cin[60];
    char mois[60];
    char annee[60];

    GtkWidget *hadil6, *treeview3;
    GtkWidget *mois1, *annee1, *totale;

    hadil6 = lookup_widget(GTK_WIDGET(button), "hadil6");

    mois1 = lookup_widget(GTK_WIDGET(button), "combobox3");
    annee1 = lookup_widget(GTK_WIDGET(button), "spinbutton35");
    totale = lookup_widget(GTK_WIDGET(button), "label635"); // Label to show the total price

    // Get month
    strcpy(mois, gtk_combo_box_get_active_text(GTK_COMBO_BOX(mois1)));

    // Check if month is valid
    const char *valid_months[] = {
        "Janvier", "Février", "Mars", "Avril", "Mai", "Juin", 
        "Juillet", "Août", "Septembre", "Octobre", "Novembre", "Décembre"
    };
    int month_valid = 0;  // Flag to track if month is valid

    for (int i = 0; i < 12; i++) {
        if (strcmp(mois, valid_months[i]) == 0) {
            month_valid = 1;
            break;
        }
    }

    if (month_valid == 0 || strlen(mois) == 0) {
        show_error_dialog("Le mois doit être sélectionné parmi les mois valides.");
        return;
    }

    // Get year
    int a = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(annee1));
    sprintf(annee, "%d", a);  
    if (strlen(annee) == 0) {
        show_error_dialog("L'année ne doit pas être vide");
        return;
    }

    // Calculate total price
    double total = calculerPrixTotal(login1, mois, annee);

    // Create a string to display the total
    char totalStr[100];
    sprintf(totalStr, "Total: %.2f   dt", total);  // Format the total with 2 decimal places

    // Set the text of the label to the total amount
    gtk_label_set_text(GTK_LABEL(totale), totalStr);

    // Update the treeview (optional, depending on your implementation)
    treeview3 = lookup_widget(hadil6, "treeview3");
    mes_services(treeview3, login1, mois, annee);
}


void
on_button69_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

 GtkWidget *hadil6,*profil;
hadil6 = lookup_widget(GTK_WIDGET(button), "hadil6");
   gtk_widget_destroy(hadil6);
        profil = create_profil();
        gtk_widget_show(profil);

    GtkWidget *a11, *a22,*a33,*a44, *a55,*a66,*a77, *a88,*a99;
        a11 = lookup_widget(profil, "name");
        a22 = lookup_widget(profil, "prenom");
        a33 = lookup_widget(profil, "cin");
        a44 = lookup_widget(profil, "tds");
        a55 = lookup_widget(profil, "label625");
        a66 = lookup_widget(profil, "label626");
        a77 = lookup_widget(profil, "label627");
        a88 = lookup_widget(profil, "label628");
        a99 = lookup_widget(profil, "label629");

        FILE *f = fopen("users.txt", "r");

user temp;

        if (f != NULL) {
            while (fscanf(f, "%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^\n]\n",
       temp.cin, temp.First_name, temp.Last_name, temp.phone_number,
       temp.day, temp.month, temp.year, temp.gender,
       temp.email, temp.pwd) != EOF) {

                if (strcmp(temp.cin, login1) == 0) {
                    gtk_label_set_text(GTK_LABEL(a11), temp.First_name);
                    gtk_label_set_text(GTK_LABEL(a22), temp.Last_name);
                    gtk_label_set_text(GTK_LABEL(a33), temp.cin);

                    gtk_label_set_text(GTK_LABEL(a44), temp.phone_number);
                    gtk_label_set_text(GTK_LABEL(a55), temp.day);
                    gtk_label_set_text(GTK_LABEL(a66), temp.month);
                    gtk_label_set_text(GTK_LABEL(a77), temp.year);
                    gtk_label_set_text(GTK_LABEL(a88), temp.gender);
                    gtk_label_set_text(GTK_LABEL(a99), temp.email);

                    break;
                }
            }
            fclose(f);
        }
    
}


void
on_treeview3_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}


void
on_gestion_de_compte_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *menu_admin3, *touscitoyen,*treeview4;
    menu_admin3 = lookup_widget(GTK_WIDGET(button), "menu_admin3");
  gtk_widget_destroy(menu_admin3);
    touscitoyen = create_touscitoyen();
    gtk_widget_show(touscitoyen);

  treeview4 = lookup_widget(touscitoyen, "treeview4");
    show_user(treeview4);
}


void
on_treeview4_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}


void
on_button48_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{


GtkWidget *treeview4, *dialog;
    GtkWidget *entry;

    char cherche[30];
	user u;
    entry = lookup_widget(GTK_WIDGET(button), "entry52");
   treeview4 = lookup_widget(GTK_WIDGET(button), "treeview4");
    strcpy(cherche, gtk_entry_get_text(GTK_ENTRY(entry)));

    FILE *f;
    f = fopen("users.txt", "r");

    if (strcmp(cherche, "") == 0)
    {        dialog = gtk_message_dialog_new(GTK_WINDOW(dialog),
                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_WARNING,
                                        GTK_BUTTONS_OK,
                                        "La recherche n'a pas abouti");
        gtk_window_set_title(GTK_WINDOW(dialog), "Alerte");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
    else if (f != NULL)
    {
        int found = 0; 

        while (fscanf(f, "%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^\n]\n", 
                  u.cin, u.First_name, u.Last_name, u.phone_number, u.day, u.month, u.year, u.gender, u.email, u.pwd) != EOF)
        {
            if ((strcmp(cherche, u.First_name) == 0)||(strcmp(cherche,u.Last_name) == 0)||(strcmp(cherche,u.cin) == 0)||(strcmp(cherche,u.phone_number) == 0))
            {
                found = 1;
                break; 
            }
        }

        fclose(f);

        if (found == 0)
        {
            dialog = gtk_message_dialog_new(GTK_WINDOW(dialog),
                                            GTK_DIALOG_DESTROY_WITH_PARENT,
                                            GTK_MESSAGE_WARNING,
                                            GTK_BUTTONS_OK,
                                            "Aucun résultat trouvé pour votre recherche");
            gtk_window_set_title(GTK_WINDOW(dialog), "Alerte");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        }
        else
        {
            chercher(treeview4, cherche);
        }
    }

}


void
on_button71_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget  *touscitoyen,*treeview4;
    touscitoyen = lookup_widget(GTK_WIDGET(button), "touscitoyen");
  gtk_widget_destroy(touscitoyen);
    touscitoyen = create_touscitoyen();
    gtk_widget_show(touscitoyen);

  treeview4 = lookup_widget(touscitoyen, "treeview4");
    show_user(treeview4);
}


void
on_button70_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *touscitoyen;
    GtkTreeSelection *selection1;
    GtkTreeIter iter;
    GtkTreeModel *model;
    GtkWidget *treeview4;

    // Declare variables to hold the user's details
    gchar *first_name, *last_name, *cin, *phone_number, *email, *address, *gender, *pwd;
    gchar *day, *month, *year;


    treeview4 = lookup_widget(GTK_WIDGET(button), "treeview4");
    selection1 = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview4));


    touscitoyen = lookup_widget(GTK_WIDGET(button), "touscitoyen");

    // Check if a row is selected in the treeview
    if (gtk_tree_selection_get_selected(selection1, &model, &iter)) {
        // Retrieve the values of the selected user
        gtk_tree_model_get(GTK_LIST_STORE(model), &iter,
            0, &cin,
            1, &first_name,
            2, &last_name,
            3, &phone_number,
            4, &day,
            5, &month,
            6, &year,
            7, &gender,
            8, &email,
            9, &pwd,
            -1);


        gtk_list_store_remove(GTK_LIST_STORE(model), &iter);



supprimer(cin);

    } else {

        show_error_dialog("selectionner un citoyen pour le supprimer .");
    }


}

