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
const int BARA_JOS = 3;
const int CIFRA = 4;

const int SPATIU = 5;
const int APOSTROF = 6;
const int GHILIMELE = 7;
const int BARA_OBLICA_INVERSA = 8;

const int PLUS = 9;
const int MINUS = 10;
const int ASTERISC = 11;
const int BARA_OBLICA = 12;
const int PROCENT = 13;
const int EGAL = 14;
const int MAI_MIC = 15;
const int MAI_MARE = 16;
const int NEGAT = 17;

const int AMPERSAND = 18;
const int BARA_VERTICALA = 19;
const int CIRCUMFLEX = 20;
const int TILDA = 21;

const int PARANTEZA = 22;
const int PUNCT = 23;
const int VIRGULA = 24;

const int DELIMITATOR = 25;
const int NEWLINE = 26;

int get_tip(char caracter)
{
    if(isalpha(caracter))
    {
        if(caracter == 'e' || caracter == 'E')
            return LITERA_E;
        else
            return LITERA;
    }
    else if(isdigit(caracter))
    {
        return CIFRA;
    }
    else
    {
        switch(caracter)
        {
            case '_': return BARA_JOS;
            
            case ' ': return SPATIU;
            case '\'': return APOSTROF;
            case '"': return GHILIMELE;
            case '\\': return BARA_OBLICA_INVERSA;
            
            case '+': return PLUS;
            case '-': return MINUS;
            case '*': return ASTERISC;
            case '/': return BARA_OBLICA;
            case '%': return PROCENT;
            case '=': return EGAL;
            case '<': return MAI_MIC;
            case '>': return MAI_MARE;
            case '!': return NEGAT;
            
            case '&': return AMPERSAND;
            case '|': return BARA_VERTICALA;
            case '^': return CIRCUMFLEX;
            case '~': return TILDA;

            case '(': 
            case ')': 
            case '[': 
            case ']': return PARANTEZA;
            case '.': return PUNCT;
            case ',': return VIRGULA;

            case '{':
            case '}':
            case ';': return DELIMITATOR;

            case '\n': return NEWLINE;

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
                case LITERA_E: return 1;
                case BARA_JOS: return 1;
                
                case CIFRA: return 2;
                
                case SPATIU: return 12;
                case APOSTROF: return 13;
                case GHILIMELE: return 17;
                
                case PLUS: return 20;
                case MINUS: return 21;
                case ASTERISC: return 22;
                case BARA_OBLICA: return 23;
                case PROCENT: return 24;
                case EGAL: return 25;
                case MAI_MIC: return 26;
                case MAI_MARE: return 27;
                
                case NEGAT: return 28;
                case AMPERSAND: return 29;
                case BARA_VERTICALA: return 30;
                case CIRCUMFLEX: return 31;
                
                case TILDA: return 36;
                
                case PUNCT: 
                case PARANTEZA:return 38;

                case VIRGULA: return 39;
                
                case DELIMITATOR: return 40;
                
                case NEWLINE: return 41;


                default: return -1;}  
        }
        
        case 1: {
            switch (tip) {
                case LITERA:
                case LITERA_E:
                case BARA_JOS:
                case CIFRA: return 1;
                
                default: return -1;}
        }
        
        case 2: {
            switch (tip) {
                case CIFRA: return 2;
                case PUNCT: return 3;
                case LITERA_E: return 5;

                default: return -1;}
        }
        case 3: {
            switch (tip) {
                case CIFRA: return 4;

                default: return -1;}
        }
        case 4: {
            switch (tip) {
                case CIFRA: return 4;
                case LITERA_E: return 5;
                
                default: return -1;}
        }
        case 5:{
            switch (tip) {
                case PLUS :
                case MINUS: return 6;
                case CIFRA: return 7;
                
                default: return -1;}
        }
        case 6: {
            switch (tip) {
                case CIFRA: return 7;

                default: return -1;}
        }
        case 7: {
            switch (tip) {
                case CIFRA: return 7;

                default: return -1;}
        }
        
        case 8: {
            switch (tip) {
                case ASTERISC: return 9;

                default: return 8;}
        }
        case 9: {
            switch (tip) {
                case ASTERISC: return 9;
                case BARA_OBLICA: return 10;

                default: return 8;}
        }
        case 11: {
            switch (tip) {
                case NEWLINE: return 10;

                default: return 11;}
        }

        case 12: {
            switch (tip) {
                case SPATIU: return 12;

                default: return -1;}
        }

        case 13: {
            switch (tip) {
                case BARA_OBLICA_INVERSA: return 14;
                case APOSTROF: return 16;
                case NEWLINE: return -1;

                default: return 15;}
        }
        case 14: {
            switch (tip) {
                case NEWLINE: return -1;

                default: return 15;}
        }
        case 15: {
            switch (tip) {
                case APOSTROF: return 16;

                default: return -1;}
        }

        case 17: {
            switch (tip) {
                case BARA_OBLICA_INVERSA: return 18;
                case GHILIMELE: return 19;
                case NEWLINE: return -1;

                default: return 17;}
        }
        case 18: return 17;

        case 20: {
            switch (tip) {
                case PLUS: return 32;
                case EGAL: return 33;

                default: return -1;}
        }
        case 21: {
            switch (tip) {
                case MINUS: return 32;
                case EGAL: return 33;
                case MAI_MARE: return 38;

                default: return -1;}
        }
        case 22: {
            switch (tip) {
                case EGAL: return 33;

                default: return -1;}
        }
        case 23: {
            switch (tip) {
                case ASTERISC: return 8;
                case BARA_OBLICA: return 11;
                case EGAL: return 33;

                default: return -1;}
        }
        case 24: {
            switch (tip) {
                case EGAL: return 33;

                default: return -1;}
        }

        case 25: {
            switch (tip) {
                case EGAL: return 34;

                default: return -1;}
        }
        case 26: {
            switch (tip) {
                case EGAL: return 34;
                case MAI_MIC: return 37;

                default: return -1;}
        }
        case 27: {
            switch (tip) {
                case EGAL: return 34;
                case MAI_MARE: return 37;

                default: return -1;}
        }

        case 28: {
            switch (tip) {
                case EGAL: return 34;

                default: return -1;}
        }
        case 29: {
            switch (tip) {
                case EGAL: return 33;
                case AMPERSAND: return 35;

                default: return -1;}
        }
        case 30: {
            switch (tip) {
                case EGAL: return 33;
                case BARA_VERTICALA: return 35;

                default: return -1;}
        }
        case 31: {
            switch (tip) {
                case EGAL: return 33;

                default: return -1;}
        }

        case 37: {
            switch (tip) {
                case EGAL: return 33;

                default: return -1;}
        }

        default: return -1;
        
    }
}

int este_finala(int stare)
{
    switch(stare)
    {
        case 1: return 0;   // identificator
        
        case 2: return 2;   // numar intreg
        case 4: 
        case 7: return 3;   // numar flotant
        
        case 16: return 4;  // caracter
        case 19: return 5;  // sir caractere
        
        case 20: case 21: case 22: case 23: case 24:
        case 32: return 6;  // op. aritmetic
        case 25:
        case 33: return 7;  // op. de atribuire
        case 26: case 27:
        case 34: return 8; // op. relational
        case 28:
        case 35: return 9; // op. logic
        case 29: case 30: case 31: case 36:
        case 37: return 10; // op. pe biti
        case 38: return 11; // op. postfixat
        case 39: return 12; // op. de serializare
        
        case 40: return 13; // separator

        case 10: return 15;  // comentariu
        case 12: return 16;  // spatiu
        case 41: return 17;  // newline
        
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

        case 8:
        case 9: cout<<"Se asteapta */ pentru inchiderea unui comentariu deschis"<<endl; break;

        case 13:
        case 14:
        case 15: cout<<"Se asteapta ' pentru inchiderea declararii unui caracter"<<endl; break;

        case 17:
        case 18: cout<<"Se asteapta \" pentru inchiderea declararii unui sir de caractere"<<endl; break;

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

int este_cuvant_cheie(string identificator)
{
    string tabela_cuvinte_cheie[33] = { "auto","break","case","char","const","continue","default","do","double",
                                        "else","enum","extern","float","for","goto","if","int","long","main",
                                        "register","return","short","signed","sizeof","static","struct","switch",
                                        "typeof","union","unsigned","void","volatile","while"};
    for(int i = 0; i <= 32; i++){
        if (identificator == tabela_cuvinte_cheie[i]){
            return 1;
        }
    }
    return 0;
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
            if(stare_curenta == 18 && caracter == '\n')
                valoare = valoare.substr(0,valoare.length()-1);
            else
                valoare += caracter;
            
            stare_curenta = stare_urmatoare;
            pozitie_curenta++;
            
            if((token.tip = este_finala(stare_curenta)) != -1)
            {
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
            if (token.tip == 15 || token.tip == 16 || token.tip == 17)
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
                    if(token.tip == 0)
                    {
                        token.tip = este_cuvant_cheie(valoare);
                    }   
                }
                return token;
            }

            // TIP TOKEN VALID
            else
            {   
                token.val = index_in_tabela(valoare);
                if(token.tip == 0)
                {
                    token.tip = este_cuvant_cheie(valoare);
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
                text += '\n';
        }
        infile.close();

        TOKEN token;
        vector<TOKEN> tabela_tokeni;
        string tabela_tip_token[15] = { "identificator", "cuvant cheie", "numar intreg", "numar flotant", "caracter", 
                                        "sir caractere", "op. aritmetic","op. atribuire","op. relational","op. logic",
                                        "op. pe biti","op. postfixat","op. virgula","separator", "EOF"};      
        
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
                    cout<<"\nAnaliza finalizata cu SUCCESS!\n";

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