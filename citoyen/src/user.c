#include <stdio.h>
#include <string.h>
#include "user.h"
#include "service.h"








enum {
    EUserCIN,
    EUserFirstName,
    EUserLastName,
    EUserPhoneNumber,
    EUserDay,
    EUserMonth,
    EUserYear,
    EUserGender,
    EUserEmail,
    EUserpwd,
    COLUMNS_USER
};


enum {

    EServiceID,
    EServiceType,
    EServicePrix,
    EServicePaiement,
    EServiceDuree,
    EServicejour,
    EServicemois,
    EServiceannee,
    COLUMNS_SERVICE
};





int verify_login(const char *username, const char *password) {

    FILE *f = fopen("users.txt", "r");
   
int is_authenticated = 0;
    user temp;

    if (f != NULL) {

        while (!is_authenticated && fscanf(f, "%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^\n]\n",
       temp.cin, temp.First_name, temp.Last_name, temp.phone_number,
       temp.day, temp.month, temp.year, temp.gender,
       temp.email, temp.pwd) != EOF) {
          
            if ((strcmp(temp.cin, username) == 0) && (strcmp(temp.pwd, password) == 0)) {
                is_authenticated = 1;
            }
        }
        fclose(f);
    }

    return is_authenticated;
}
//******************************************************************************
int cin_exists(char *cin1) {
    FILE *f = fopen("users.txt", "r");
    if (f == NULL) {

        perror("Error opening file");
        return 0;  
    }

    user temp;


    while (fscanf(f, "%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^\n]\n",
       temp.cin, temp.First_name, temp.Last_name, temp.phone_number,
       temp.day, temp.month, temp.year, temp.gender,
       temp.email, temp.pwd) != EOF) {
        
        if (strcmp(temp.cin, cin1) == 0) {
            fclose(f);
            return 1; 
        }
    }

    fclose(f);
    return 0;  // CIN not found, return 0
}
//******************************************************************************
int is_all_digits(const char *str) {

    for (int i = 0; i < strlen(str); i++) {
        if (!isdigit(str[i])) {
            return 0; 
        }
    }
    return 1; 
}





//******************************************************************************



void addUser(char *filename, user u) {

    FILE *f = fopen(filename, "a+");


    fprintf(f, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s\n", 
            u.cin,
            u.First_name,
            u.Last_name,
            u.phone_number,
            u.day,
            u.month,
            u.year,  
            u.gender,
            u.email,
            u.pwd); 


    fclose(f);


    printf("Account added successfully.\n");
}

//******************************************************************************
void modifieruser(char *filename, user u) {
    FILE *f = fopen(filename, "r");
   
    FILE *f_temp = fopen("user_temp.txt", "w+");

    user temp;
    int found = 0;

    while (fscanf(f, "%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^\n]\n",
                  temp.cin, temp.First_name, temp.Last_name, temp.phone_number,
                  temp.day, temp.month, temp.year, temp.gender,
                  temp.email, temp.pwd) != EOF) {
        
        if (strcmp(temp.cin, u.cin) == 0) {
            fprintf(f_temp, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s\n",
                    u.cin, u.First_name, u.Last_name, u.phone_number,
                    u.day, u.month, u.year, u.gender,
                    u.email, u.pwd);
            found = 1;
        } else {
            fprintf(f_temp, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s\n",
                    temp.cin, temp.First_name, temp.Last_name, temp.phone_number,
                    temp.day, temp.month, temp.year, temp.gender,
                    temp.email, temp.pwd);
        }
    }

    fclose(f);
    fclose(f_temp);


        remove(filename);
        rename("user_temp.txt", "users.txt");
        
        
        printf("User modified successfully.\n");

        
    
}
void supprimer(const char *cin_to_delete) {
    FILE *f = fopen("users.txt", "r");
    FILE *f_temp = fopen("users_temp.txt", "w");
    user temp;

    while (fscanf(f, "%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^\n]\n",
                  temp.cin, temp.First_name, temp.Last_name, temp.phone_number,
                  temp.day, temp.month, temp.year, temp.gender,
                  temp.email, temp.pwd) != EOF) {


        if (strcmp(temp.cin, cin_to_delete) != 0) {
            fprintf(f_temp, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s\n",
                    temp.cin, temp.First_name, temp.Last_name, temp.phone_number,
                    temp.day, temp.month, temp.year, temp.gender,
                    temp.email, temp.pwd);
        }
    }

    fclose(f);
    fclose(f_temp);


    remove("users.txt");
    rename("users_temp.txt", "users.txt");
}

//*********************************************************************
void mes_services(GtkWidget *treeview,char *cin,char *mois,char *annee) {
    service s; 
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;
    FILE *f;

    store = gtk_list_store_new(COLUMNS_SERVICE, 
                               G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, 
                               G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

    if (store == NULL) {
        fprintf(stderr, "Error: Failed to create GtkListStore\n");
        return; 
    }

     if (gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)) == NULL) {
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Service ID", renderer, "text", EServiceID, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Type", renderer, "text", EServiceType, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Prix", renderer, "text", EServicePrix, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Paiement", renderer, "text", EServicePaiement, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Durée", renderer, "text", EServiceDuree, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Jour", renderer, "text", EServicejour, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Mois", renderer, "text", EServicemois, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Année", renderer, "text", EServiceannee, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
}
    // Open the file to read the data
    f = fopen("services.txt", "r");
    if (f == NULL) {
        perror("Unable to open file");
        return;
    }

    // Read the file line by line and insert data into the TreeView
    while (fscanf(f, "%49[^;];%49[^;];%49[^;];%49[^;];%49[^;];%49[^;];%49[^;];%49[^;];%59[^\n]\n", 
                  s.idclient, s.id_service, s.type, s.prix, s.paiement, s.duree, 
                  s.jour, s.mois, s.annee) == 9) {
		if ((strcmp(s.idclient, cin) == 0)&&(strcmp(s.mois,mois) == 0)&&(strcmp(s.annee,annee) == 0)){
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,

            EServiceID, s.id_service,
            EServiceType, s.type,
            EServicePrix, s.prix,
            EServicePaiement, s.paiement,
            EServiceDuree, s.duree,
            EServicejour, s.jour,
            EServicemois, s.mois,
            EServiceannee, s.annee,
            -1);
	}
    }

    // Set the model for the TreeView
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
    g_object_unref(store);  // Free the store when done

    // Close the file
    fclose(f);
}


double calculerPrixTotal(const char* cin, const char* mois, const char* annee) {
    FILE *f;
    service s;
    double total = 0.0;  // Variable pour stocker le prix total

    // Ouvrir le fichier pour lire les données
    f = fopen("services.txt", "r");


    // Lire chaque ligne du fichier et appliquer les conditions
    while (fscanf(f, "%49[^;];%49[^;];%49[^;];%49[^;];%49[^;];%49[^;];%49[^;];%49[^;];%59[^\n]\n", 
                  s.idclient, s.id_service, s.type, s.prix, s.paiement, s.duree, 
                  s.jour, s.mois, s.annee) == 9) {
        
        // Vérifier les conditions (idclient, mois, annee)
        if ((strcmp(s.idclient, cin) == 0) && (strcmp(s.mois, mois) == 0) && (strcmp(s.annee, annee) == 0)) {
            

            double prix = atof(s.prix);  
            total += prix;
        }
    }


 return total;


    fclose(f);
}








void show_user(GtkWidget *fr) {
    user u; 
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;
    FILE *f;

    store = gtk_list_store_new(COLUMNS_USER, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

    if (store == NULL) {
        fprintf(stderr, "Error: Failed to create GtkListStore\n");
        return; 
    }

    if (gtk_tree_view_get_model(GTK_TREE_VIEW(fr)) == NULL) {

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("CIN", renderer, "text", EUserCIN, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("First Name", renderer, "text", EUserFirstName, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Last Name", renderer, "text", EUserLastName, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Phone Number", renderer, "text", EUserPhoneNumber, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Day", renderer, "text", EUserDay, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Month", renderer, "text", EUserMonth, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Year", renderer, "text", EUserYear, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Gender", renderer, "text", EUserGender, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Email", renderer, "text", EUserEmail, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("password", renderer, "text", EUserpwd, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);
    }

    f = fopen("users.txt", "r");
    if (f == NULL) {
        perror("Unable to open file");
        return;
    }


    while (fscanf(f, "%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^\n]\n", 
                  u.cin, u.First_name, u.Last_name, u.phone_number, u.day, u.month, u.year, u.gender, u.email, u.pwd) != EOF) {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           EUserCIN, u.cin,
                           EUserFirstName, u.First_name,
                           EUserLastName, u.Last_name,
                           EUserPhoneNumber, u.phone_number,
                           EUserDay, u.day,
                           EUserMonth, u.month,
                           EUserYear, u.year,
                           EUserGender, u.gender,
                           EUserEmail, u.email,
                           EUserpwd, u.pwd,
                           -1);
    }


    gtk_tree_view_set_model(GTK_TREE_VIEW(fr), GTK_TREE_MODEL(store));
    g_object_unref(store); 
    fclose(f); 
}




void chercher(GtkWidget *fr,char *cherche) {
    user u; 
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;
    FILE *f;

    store = gtk_list_store_new(COLUMNS_USER, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

    if (store == NULL) {
        fprintf(stderr, "Error: Failed to create GtkListStore\n");
        return; 
    }

    if (gtk_tree_view_get_model(GTK_TREE_VIEW(fr)) == NULL) {

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("CIN", renderer, "text", EUserCIN, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("First Name", renderer, "text", EUserFirstName, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Last Name", renderer, "text", EUserLastName, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Phone Number", renderer, "text", EUserPhoneNumber, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Day", renderer, "text", EUserDay, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Month", renderer, "text", EUserMonth, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Year", renderer, "text", EUserYear, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Gender", renderer, "text", EUserGender, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Email", renderer, "text", EUserEmail, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("password", renderer, "text", EUserpwd, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);
    }

    f = fopen("users.txt", "r");
    if (f == NULL) {
        perror("Unable to open file");
        return;
    }


    while (fscanf(f, "%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^;];%59[^\n]\n", 
                  u.cin, u.First_name, u.Last_name, u.phone_number, u.day, u.month, u.year, u.gender, u.email, u.pwd) != EOF) {

if ((strcmp(u.First_name, cherche) == 0)||(strcmp(u.Last_name,cherche) == 0)||(strcmp(u.cin,cherche) == 0)||(strcmp(u.phone_number,cherche) == 0)){
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           EUserCIN, u.cin,
                           EUserFirstName, u.First_name,
                           EUserLastName, u.Last_name,
                           EUserPhoneNumber, u.phone_number,
                           EUserDay, u.day,
                           EUserMonth, u.month,
                           EUserYear, u.year,
                           EUserGender, u.gender,
                           EUserEmail, u.email,
                           EUserpwd, u.pwd,
                           -1);
    }
}

    gtk_tree_view_set_model(GTK_TREE_VIEW(fr), GTK_TREE_MODEL(store));
    g_object_unref(store); 
    fclose(f); 
}
