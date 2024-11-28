#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

// Classe pour un contact
class Contact {
public:
    string nom;
    string telephone;
    string email;
    string adresse;

    Contact(string nom, string telephone, string email, string adresse)
        : nom(move(nom)), telephone(move(telephone)), email(move(email)), adresse(move(adresse)) {}

    void afficher() const {
        cout << "Nom : " << nom << "\n"
             << "Téléphone : " << telephone << "\n"
             << "Email : " << email << "\n"
             << "Adresse : " << adresse << "\n";
    }
};

// Prototypes des fonctions
void afficherMenu();
void ajouterContact(vector<Contact>& contacts);
void modifierContact(vector<Contact>& contacts);
void supprimerContact(vector<Contact>& contacts);
void rechercherContact(const vector<Contact>& contacts);
void trierContacts(vector<Contact>& contacts);
void sauvegarderContacts(const vector<Contact>& contacts);
void chargerContacts(vector<Contact>& contacts);

// Fonction principale
int main() {
    vector<Contact> contacts;
    chargerContacts(contacts);

    int choix;
    do {
        afficherMenu();
        cin >> choix;
        cin.ignore();

        switch (choix) {
            case 1: ajouterContact(contacts); break;
            case 2: modifierContact(contacts); break;
            case 3: supprimerContact(contacts); break;
            case 4: rechercherContact(contacts); break;
            case 5: trierContacts(contacts); break;
            case 6: sauvegarderContacts(contacts); break;
            case 7: cout << "Au revoir !" << endl; break;
            default: cout << "Choix invalide, réessayez." << endl;
        }
    } while (choix != 7);

    return 0;
}

// Afficher le menu principal
void afficherMenu() {
    cout << "\n---- Menu de Gestion de Contacts ----\n"
         << "1. Ajouter un contact\n"
         << "2. Modifier un contact\n"
         << "3. Supprimer un contact\n"
         << "4. Rechercher un contact\n"
         << "5. Trier les contacts\n"
         << "6. Sauvegarder les contacts\n"
         << "7. Quitter\n"
         << "Votre choix : ";
}

// Ajouter un contact
void ajouterContact(vector<Contact>& contacts) {
    string nom, telephone, email, adresse;

    cout << "Entrez le nom : ";
    getline(cin, nom);
    cout << "Entrez le téléphone : ";
    getline(cin, telephone);
    cout << "Entrez l'email : ";
    getline(cin, email);
    cout << "Entrez l'adresse : ";
    getline(cin, adresse);

    contacts.emplace_back(nom, telephone, email, adresse);
    cout << "Contact ajouté avec succès !" << endl;
}

// Modifier un contact
void modifierContact(vector<Contact>& contacts) {
    string nom;
    cout << "Entrez le nom du contact à modifier : ";
    getline(cin, nom);

    for (auto& contact : contacts) {
        if (contact.nom == nom) {
            cout << "Nouveau téléphone : ";
            getline(cin, contact.telephone);
            cout << "Nouvel email : ";
            getline(cin, contact.email);
            cout << "Nouvelle adresse : ";
            getline(cin, contact.adresse);
            cout << "Contact modifié avec succès !" << endl;
            return;
        }
    }
    cout << "Contact introuvable !" << endl;
}

// Supprimer un contact
void supprimerContact(vector<Contact>& contacts) {
    string nom;
    cout << "Entrez le nom du contact à supprimer : ";
    getline(cin, nom);

    auto it = remove_if(contacts.begin(), contacts.end(), [&](const Contact& c) {
        return c.nom == nom;
    });

    if (it != contacts.end()) {
        contacts.erase(it, contacts.end());
        cout << "Contact supprimé avec succès !" << endl;
    } else {
        cout << "Contact introuvable !" << endl;
    }
}

// Rechercher un contact
void rechercherContact(const vector<Contact>& contacts) {
    string nom;
    cout << "Entrez le nom du contact à rechercher : ";
    getline(cin, nom);

    for (const auto& contact : contacts) {
        if (contact.nom == nom) {
            contact.afficher();
            return;
        }
    }
    cout << "Contact introuvable !" << endl;
}

// Trier les contacts par nom
void trierContacts(vector<Contact>& contacts) {
    sort(contacts.begin(), contacts.end(), [](const Contact& a, const Contact& b) {
        return a.nom < b.nom;
    });
    cout << "Contacts triés par nom !" << endl;
}

// Sauvegarder les contacts dans un fichier
void sauvegarderContacts(const vector<Contact>& contacts) {
    ofstream fichier("contacts.txt");

    if (!fichier) {
        cout << "Erreur lors de l'ouverture du fichier !" << endl;
        return;
    }

    for (const auto& contact : contacts) {
        fichier << contact.nom << "\n"
                << contact.telephone << "\n"
                << contact.email << "\n"
                << contact.adresse << "\n";
    }

    cout << "Contacts sauvegardés avec succès !" << endl;
}

// Charger les contacts depuis un fichier
void chargerContacts(vector<Contact>& contacts) {
    ifstream fichier("contacts.txt");

    if (!fichier) {
        cout << "Aucun fichier de sauvegarde trouvé !" << endl;
        return;
    }

    string nom, telephone, email, adresse;
    while (getline(fichier, nom) &&
           getline(fichier, telephone) &&
           getline(fichier, email) &&
           getline(fichier, adresse)) {
        contacts.emplace_back(nom, telephone, email, adresse);
    }

    cout << "Contacts chargés avec succès !" << endl;
}
