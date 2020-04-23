#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

typedef struct token {
    int tip;
    int val;
} TOKEN;

vector<string> tabela_val_unice;
vector<string>::iterator gasit;

// Tipuri de caractere
const int LITERA = 1;
const int LITERA_E = 2;
const int LITERA_N = 3;
const int CIFRA = 4;

const int SPATIU = 5;
const int APOSTROF = 6;
const int GHILIMEA = 7;

const int PARANTEZA = 8;
const int ACOLADA = 9;
const int BACK_SLASH = 10;

const int PLUS = 11;
const int MINUS = 12;
const int STAR = 13;
const int SLASH = 14;
const int PROCENT = 15;
const int AMPERSAND = 16;
const int BARA = 17;
const int NOT = 18;
const int EGAL = 19;
const int MAI_MIC = 20;
const int MAI_MARE = 21;

const int PUNCT = 22;
const int VIRGULA = 23;
const int PUNCT_VIRGULA = 24;


int get_tip(char caracter)
{
    if(isalpha(caracter)){
        if(caracter == 'e' || caracter == 'E')
            return LITERA_E;
        else if (caracter == 'N')
            return LITERA_N;
        else
            return LITERA;
    }
    else if(isdigit(caracter)){
        return CIFRA;
    }
    else{
        switch(caracter){
            case ' ': return SPATIU;
            case '\'': return APOSTROF;
            case '"': return GHILIMEA;
            
            case '(': 
            case ')': 
            case '[': 
            case ']': return PARANTEZA;
            
            case '{':
            case '}': return ACOLADA;
            
            case '\\': return BACK_SLASH;

            case '+': return PLUS;
            case '-': return MINUS;
            case '*': return STAR;
            case '/': return SLASH;
            case '%': return PROCENT;
            case '=': return EGAL;
            case '<': return MAI_MIC;
            case '>': return MAI_MARE;
            case '!': return NOT;
            case '&': return AMPERSAND;
            case '|': return BARA;

            case '.': return PUNCT;
            case ',': return VIRGULA;
            case ';': return PUNCT_VIRGULA;

            default : return -1;            
        }
    }
}

int tranzitie_afd(int stare, int tip)
{
    switch(stare) 
    {
        case 0: {
            switch (tip) {
                case LITERA: return 1;
                case LITERA_N: return 1;
                case LITERA_E: return 1;
                
                case CIFRA: return 2;
                case SLASH: return 8;
                case SPATIU: return 16;
                case APOSTROF: return 17;
                case GHILIMEA: return 21;
                
                case PLUS: return 24;
                case MINUS: return 26;
                case STAR: return 28;
                case PROCENT: return 30;
                case AMPERSAND: return 32;
                case BARA: return 34;
                case NOT: return 36;
                case EGAL: return 38;
                case MAI_MIC: return 40;
                case MAI_MARE: return 42;
                
                case PUNCT: return 44;
                case VIRGULA: return 44;
                
                case PARANTEZA: return 45;
                case ACOLADA: return 46;
                case PUNCT_VIRGULA: return 47;
                
                case BACK_SLASH: return 48;

                default: return -1;}  
        }
        
        case 1: {
            switch (tip) {
                case LITERA:
                case LITERA_N:
                case LITERA_E:
                case CIFRA: return 1;
                
                default: return -1;}
        }
        
        case 2: {
            switch (tip) {
                case CIFRA: return 2;
                // case LITERA_E: return 3;
                // case PUNCT: return 6;
                case PUNCT: return 3;
                case LITERA_E: return 5;

                default: return -1;}
        }
        case 3: {
            switch (tip) {
                case CIFRA: return 4;
                // case PLUS :
                // case MINUS: return 4;
                // case CIFRA: return 5;

                default: return -1;}
        }
        case 4: {
            switch (tip) {
                case CIFRA: return 4;
                case LITERA_E: return 5;
                // case CIFRA: return 5;
                
                default: return -1;}
        }
        case 5:{
            switch (tip) {
                case PLUS :
                case MINUS: return 6;
                case CIFRA: return 7;
                // case CIFRA: return 5;
                
                default: return -1;}
        }
        case 6: {
            switch (tip) {
                case CIFRA: return 7;
                // case CIFRA: return 7;

                default: return -1;}
        }
        case 7: {
            switch (tip) {
                case CIFRA: return 7;
                // case LITERA_E: return 3;
                // case CIFRA: return 7;

                default: return -1;}
        }
        
        case 8: {
            switch (tip) {
                case EGAL: return 9;
                case STAR: return 10;
                case SLASH: return 13;

                default: return -1;}
        }
        case 10: {
            switch (tip) {
                case STAR: return 11;

                default: return 10;}
        }
        case 11: {
            switch (tip) {
                case STAR: return 11;
                case SLASH: return 12;

                default: return 10;}
        }
        case 13: {
            switch (tip) {
                case BACK_SLASH: return 14;

                default: return 13;}
        }
        case 14: {
            switch (tip) {
                case BACK_SLASH: return 14;
                case LITERA_N: return 15;

                default: return 13;}
        }

        case 16: {
            switch (tip) {
                case SPATIU: return 16;

                default: return -1;}
        }

        case 17: {
            switch (tip) {
                case BACK_SLASH: return 18;
                case APOSTROF: return 20;

                default: return 19;}
        }
        case 18: return 19;
        case 19: {
            switch (tip) {
                case APOSTROF: return 20;

                default: return -1;}
        }

        case 21: {
            switch (tip) {
                case BACK_SLASH: return 22;
                case GHILIMEA: return 23;

                default: return 21;}
        }
        case 22: return 21;

        case 24: {
            switch (tip) {
                case PLUS:
                case EGAL: return 25;

                default: return -1;}
        }

        case 26: {
            switch (tip) {
                case MINUS:
                case EGAL: return 27;

                default: return -1;}
        }
        
        case 28: {
            switch (tip) {
                case EGAL: return 29;

                default: return -1;}
        }
        
        case 30: {
            switch (tip) {
                case EGAL: return 31;

                default: return -1;}
        }

        case 32: {
            switch (tip) {
                case AMPERSAND: return 33;

                default: return -1;}
        }
        
        case 34: {
            switch (tip) {
                case BARA: return 35;

                default: return -1;}
        }

        case 36: {
            switch (tip) {
                case EGAL: return 37;

                default: return -1;}
        }
        
        case 38: {
            switch (tip) {
                case EGAL: return 39;

                default: return -1;}
        }

        case 40: {
            switch (tip) {
                case EGAL: return 41;

                default: return -1;}
        }
        
        case 42: {
            switch (tip) {
                case EGAL: return 43;

                default: return -1;}
        }

        case 48: {
            switch (tip) {
                case LITERA_N: return 49;

                default: return -1;}
        }

        default: return -1;
        
    }
}

int este_finala(int stare)
{
    switch(stare){
        case 1: return 0;   // identificator
        
        case 2: return 2;   // numar
        case 4: return 3;   // numar real
        case 7: return 4;   // numar mare
        
        case 12: 
        case 15: return 5;  // comentariu
        
        case 16: return 6;  // spatiu
        case 20: return 7;  // caracter
        case 23: return 8;  // sir caractere
        
        case  8: case  9: case 24: case 25:
        case 26: case 27: case 28: case 29:
        case 30: case 31: case 33: case 35:
        case 36: case 37: case 38: case 39:
        case 40: case 41: case 42: case 43:
        case 44: return 9;  // operator
        
        case 45: return 10; // paranteza
        case 46: return 11; // acolada
        case 47: return 12; // delimitator
        case 49: return 13; // newline
        
        default: return -1; // eroare
    }
}

void afiseaza_eroare(int stare,string val)
{
    cout<<"\nERROR: ";
    switch(stare)
    {
        case 3: cout<<"Se asteapta cel putin o cifra ca zecimala pentru numarul real "<<val<<endl; break;

        case 5:
        case 6: cout<<"Se asteapta cel putin o cifra ca exponent pentru numarul mare "<<val<<endl; break;

        case 10:
        case 11: cout<<"Se asteapta */ pentru inchiderea unui comentariu deschis"<<endl; break;

        case 18:
        case 19: cout<<"Se asteapta ' pentru inchiderea declararii caracterului "<<val<<endl; break;

        case 21:
        case 22: cout<<"Se asteapta \" pentru inchiderea declararii unui sir de caractere"<<endl; break;

        default: cout<<"A aparut o eroare necunoscuta"<<endl;
    }
}

int index_in_tabela(string valoare)
{
    int index;
    gasit = find(tabela_val_unice.begin(),tabela_val_unice.end(),valoare);
                
    if(gasit != tabela_val_unice.end())
    {   
        index = distance(tabela_val_unice.begin(),gasit);
    }
    else
    {   
        tabela_val_unice.push_back(valoare);
        index = tabela_val_unice.size()-1;
    }
    return index;
}

bool este_cuvant_cheie(string identificator)
{
    string tabela_cuvinte_cheie[33] = { "auto","break","case","char","const","continue","default","do","double",
                                        "else","enum","extern","float","for","goto","if","int","long","main",
                                        "register","return","short","signed","sizeof","static","struct","switch",
                                        "typeof","union","unsigned","void","volatile","while"};
    for(int i = 0; i <= 32; i++){
        if (identificator == tabela_cuvinte_cheie[i]){
            return true;
        }
    }
    return false;
}



TOKEN get_token(string text, int &pozitie_curenta)
{    
    TOKEN token;
    string valoare;
    char caracter;
    int stare_curenta = 0, stare_urmatoare, tip_caracter, index;
    
    string valoare_revert = "";
    int tip_revert = -1,pozitie_revert = -1;

    while(pozitie_curenta < text.length())
    {
        caracter = text[pozitie_curenta];
        tip_caracter = get_tip(caracter);
        stare_urmatoare = tranzitie_afd(stare_curenta,tip_caracter);

        if(stare_urmatoare != -1)
        {
            stare_curenta = stare_urmatoare;
            valoare += caracter;
            pozitie_curenta++;

            if((token.tip = este_finala(stare_curenta)) != -1){
                tip_revert = token.tip;
                valoare_revert = valoare;
                pozitie_revert = pozitie_curenta;
            } 
        }

        // S-a blocat AFD
        else
        {   
            token.tip = este_finala(stare_curenta);
            
            // COMENTARIU, SPATIU sau NEWLINE
            if (token.tip == 5 || token.tip == 6 || token.tip == 13)
            {   
                valoare = "";
                stare_curenta = 0;
            }

            // EROARE
            else if (token.tip == -1)
            {   
                if(pozitie_revert == -1)
                {
                    afiseaza_eroare(stare_curenta,valoare);
                    token.val = pozitie_curenta;
                }
                else
                {   
                    token.tip = tip_revert;
                    valoare = valoare_revert;
                    pozitie_curenta = pozitie_revert;
                    
                    token.val = index_in_tabela(valoare);
                    if(token.tip == 0 && este_cuvant_cheie(valoare)){
                        token.tip = 1;
                    }   
                }
                return token;
            }

            // TIP TOKEN VALID
            else
            {   
                token.val = index_in_tabela(valoare);
                if(token.tip == 0 && este_cuvant_cheie(valoare)){
                    token.tip = 1;
                }
                return token;
            }
        }
    }

    
    token.tip = este_finala(stare_curenta);
    if(token.tip == -1)
    {
        afiseaza_eroare(stare_curenta,valoare);
        token.val = pozitie_curenta;
    }
    else
    {
        token.tip = 14; //EOF
        token.val = -1;
    }
    return token;
}



int main(int argc, char** argv)
{

        // ifstream infile(argv[1]);
        // string line, text = "";
        // // text.assign( (istreambuf_iterator<char>(infile)),(istreambuf_iterator<char>()) );
        // while(infile >> line){
        //     text += line;
        //     if(infile.peek() == '\n')
        //         text +='\n';
        //     if(infile.peek() == ' ')
        //         text +=' ';
        // }
        // cout<<text;
        // infile.close();
        
    if( argc != 2 )
    {
        cout<<"\nFolosire: analizor.exe InputFile\n";
    }
    else
    {
        ifstream infile(argv[1]);
        string line, text = "";
        while( getline(infile,line) ) 
        {
            text += line;
            if (line != "")
                // text += "\\N";
                text += '\n';
        }
        infile.close();


        TOKEN token;
        vector<TOKEN> tabela_tokeni;
        string tabela_tip_token[15] = { "identificator", "cuvant cheie", "numar", "numar real", "numar mare", 
                                        "comentariu", "spatiu", "caracter","sir caractere", "operator",
                                        "paranteza", "acolada", "delimitator", "newline", "EOF"};                                        
        int pozitie_curenta = 0;
        while(pozitie_curenta < text.length())
        {
            token = get_token(text,pozitie_curenta);
            
            if(token.tip != -1) 
            {
                if(token.tip != 14) 
                {
                    tabela_tokeni.push_back(token);
                }                
                else    
                {
                    cout<<"\nAnalizare finalizata cu SUCCESS!\n";

                    if(tabela_tokeni.size() == 0)
                    {
                        cout<<"Nu s-a gasit niciun token in acest fisier.\n";
                    }
                    else
                    {
                        string valoare, tip;
                        cout<<"S-au gasit "<<tabela_tokeni.size()<<" tokeni dintre care "
                            <<tabela_val_unice.size()<<" au valori unice:\n\n";
                        
                        for(int i = 0; i < tabela_tokeni.size(); i++)
                        {
                            valoare = tabela_val_unice[tabela_tokeni[i].val];
                            tip = tabela_tip_token[tabela_tokeni[i].tip];
                            
                            cout<<tip;
                            for(int i = tip.length(); i < 14; i++)
                            {
                                cout<<" ";
                            }
                            cout<<" -> "<<valoare<<endl;
                        }
                    }
                }
            }
            else
            {
                cout<<"A aparut o eroare la pozitia "<<token.val<<" din fisierul citit!\n";
                pozitie_curenta = text.length();
            }
        }
    }

	return 0;
}