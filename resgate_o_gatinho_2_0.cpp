#include <iostream>
#include <string>
#include <random>
using namespace std;


void titulo(int sim, int largura = 0, int altura = 0, string **jogo = nullptr);  /* Insere o titulo */
int verificacao(string);  /* Verifica se digitou sim ou não e suas variações*/
void printa(int x, int y, string **matriz);  /* Printa o campo*/
void livre(int movimento, int *px, int *py, string **matriz, string valor_1, string valor_2);  /* Verifica se o movimento */


int main(void)
{
    string entrada, gato = " * ", bloqueio = " X ", vazio = "   ";
    bool continua_geral = true, continua_etapa = true;
    int a, b, x, y;
    int gx, gy;

    while(continua_geral)
    {
        continua_etapa = true;

        VOLTA_INICIO:
            entrada.clear();

            titulo(0);
            cout << "  Deseja que o campo seja quadrado? \n  ";
            getline(cin, entrada);

            switch(verificacao(entrada))
            {
                case 0:
                    goto VOLTA_INICIO;
                    break;
                
                case 1:
                    titulo(0);
                    cout << "  Informe uma quantidade impar de campos: \n  ";
                    cin >> x; y = x;
                    break;
                
                case 2:
                    titulo(0);
                    cout << "  Informe uma quantidade impar de linhas: \n  ";
                    cin >> y;

                    cout << "  Informe uma quantidade impar de colunas: \n  ";
                    cin >> x;
                    break;
            }
            
            if((x % 2 == 0) || (y % 2 == 0))
            {
                titulo(0);
                cout << "  O numero precisa ser impar \n\n";
                cout << "  PRESSIONE ENTER PARA CONTINUAR \n\n  ";
                cin.ignore().get();
                goto VOLTA_INICIO;
            }
            

            string **campo = new string*[y];
            for(a = 0; a < y; a++) campo[a] = new string[x];
            
            for(a = 0; a < y; a++) for(b = 0; b < x; b++) campo[a][b] = vazio;
            campo[(y - 1) / 2][(x - 1) / 2] = gato;


            /* Imprime o tabuleiro e começa o jogo */
            
            while(continua_etapa)
            {
                VOLTA_MARCACAO:
                    titulo(1, x, y, campo);
                    cout << "Informe a linha do campo que deseja bloquear: ";
                    cin >> a;
                    
                    titulo(1, x, y, campo);
                    cout << "Agora a coluna: ";
                    cin >> b;

                    cout << "\n\n";

                    if((a > y) || (b > x))
                    {
                        titulo(0);
                        cout << "  A linha e a coluna precisam ser existentes  \n\n";
                        cout << "  PRESSIONE ENTER PARA CONTINUAR \n\n  ";
                        cin.ignore().get();
                        goto VOLTA_MARCACAO;
                    }

                    a--; b--;
                    
                    if((campo[a][b] == gato) || (campo[a][b] == bloqueio))
                    {
                        titulo(0);
                        cout << "  A linha e a coluna não podem estar ocupados  \n\n";
                        cout << "  PRESSIONE ENTER PARA CONTINUAR \n\n  ";
                        cin.ignore().get();
                        goto VOLTA_MARCACAO;
                    }
                    
                campo[a][b] = bloqueio;


                for(a = 0; a < y; a++) for(b = 0; b < x; b++){
                if(campo[a][b] == gato) { gx = b; gy = a;  break; }
                }
                
                if((gx == 0) || (gy == 0) || (gx == (x - 1)) || (gy == (y - 1)))
                {
                    VOLTA_PERDEU: 
                        entrada.clear();

                        titulo(0);
                        cout << "  Seu gatinho escapou, você perdeu \n";
                        cout << "  Deseja jogar novamente? \n  ";
                        cin >> entrada;
                        
                        if((verificacao(entrada)) == 0) goto VOLTA_PERDEU;
                    if((verificacao(entrada)) == 2) { continua_geral = false; break; }
                    else { continua_etapa = false; break; }
                }
                
                a = 0;
                if(campo[gy - 1][gx] == bloqueio) a++; 
                if(campo[gy + 1][gx] == bloqueio) a++;
                if(campo[gy][gx - 1] == bloqueio) a++;
                if(campo[gy][gx + 1] == bloqueio) a++;

                if(a == 4)
                {
                    VOLTA_GANHOU:
                        titulo(0);
                        cout << "  Seu gatinho foi resgatado \n";
                        cout << "  Deseja jogar novamente? \n  ";
                        cin >> entrada;
                            
                        if((verificacao(entrada)) == 0) goto VOLTA_GANHOU;
                    if((verificacao(entrada)) == 2) { continua_geral = false; break; }
                    else { continua_etapa = false; break; }
                }


                b = 0;
                if(a == 3)
                {
                    if(campo[gy - 1][gx] == vazio)
                    { 
                        campo[gy][gx] = vazio;
                        gy--;
                        campo[gy][gx] = gato; 
                    } 

                    else if(campo[gy + 1][gx] == vazio)
                    {
                        campo[gy][gx] = vazio;
                        gy++;
                        campo[gy][gx] = gato;
                    }

                    else if(campo[a][b - 1] == vazio)
                    {
                        campo[gy][gx] = vazio;
                        gx--;
                        campo[gy][gx] = gato;
                    }
                    
                    else
                    {
                        campo[gy][gx] = vazio;
                        gx++;
                        campo[gy][gx] = gato;
                    }

                    b = 1;
                }
                if(b) continue;

                b = 0;
                int c = 0, d = 0, e = 0; 
                if(!a)
                {
                    for(a = 0; a < gx; a++) if(campo[gy][a] == vazio) b++;
                    for(a = (gx + 1); a < x; a++) if(campo[gy][a] == vazio) c++;

                    for(a = 0; a < gy; a++) if(campo[a][gx] == vazio) d++;
                    for(a = (gy + 1); a < y; a++) if(campo[a][gx] == vazio) e++;


                    if(((b > c) && (b > d) && (b > e))) livre(1, &gx, &gy, campo, gato, vazio);
                    else if((c > b) && (c > d) && (c > e)) livre(2, &gx, &gy, campo, gato, vazio);
                    else if((d > b) && (d > c) && (d > e)) livre(3, &gx, &gy, campo, gato, vazio);
                    else if((e > b) && (e > c) && (e > d)) livre(4, &gx, &gy, campo, gato, vazio);
                    else livre(5, &gx, &gy, campo, gato, vazio);

                }
            }

        for(a = 0; a < y; a++) delete[] campo[a];
        delete[] campo;
    }
    return 0;
}



/* ********************************************************************************************** */



inline void titulo(int sim, int largura, int altura, string **jogo)
{
    cout << "\033[H\033[J" << "  _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_";
    cout << "\n             ************* RESGATE O GATINHO ************ \n";
    cout << "  -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_ \n\n";
    cout << "  Seu gatinho (*) escapou e para resgata-lo você deve cerca-lo (X) \n\n\n";

    if(sim) printa(largura, altura, jogo);
}



inline int verificacao(string texto)
{
    if((texto == "sim") || (texto == "Sim") || (texto == "s") || (texto == "S")) return 1;
    else if((texto == "nao") || (texto == "Nao")) return 2;
    else if((texto == "não") || (texto == "Não")) return 2;
    else if((texto == "n") || (texto == "N")) return 2;
    else return 0;

}



void printa(int coluna, int linha, string **matriz)
{
    int i, j;

    cout << "         ";
    for(i = 0; i < coluna; i++) cout << i + 1 << "     ";
    cout << "\n\n";
    
    for(i = 0; i < linha; i++)
    {
        cout << "  " << i + 1 << "   | ";

        for(j = 0; j < coluna; j++) 
            cout << matriz[i][j] << " | ";
        cout << "\n\n";
    }
    cout << "\n  ";
}


void livre(int movimento, int *px, int *py, string **matriz, string valor_1, string valor_2)
{
    int a = *py, b = *px;

    switch(movimento)
    {
        case 1:
            if(matriz[a][b - 1] == valor_2)
            {
                matriz[a][b] = valor_2;
                (*px)--; b--;
                matriz[a][b] = valor_1;
                return;
            }

        case 2:
            if(matriz[a][b + 1] == valor_2)
            {
                matriz[a][b] = valor_2;
                (*px)++; b++;
                matriz[a][b] = valor_1;
                return;
            }
        
        case 3:
            if(matriz[a - 1][b] == valor_2)
            {
                matriz[a][b] = valor_2;
                (*py)--; a--;
                matriz[a][b] = valor_1;
                return;
            }
        
        case 4:
            if(matriz[a + 1][b] == valor_2)
            {
                matriz[a][b] = valor_2;
                (*py)++; a++;
                matriz[a][b] = valor_1;
                return;
            }
        case 5:
        {
            mt19937 aleatorio(random_device{}());
            int c = aleatorio() % 4;

            VOLTA_CASE:
                if(c == 3) if(matriz[a][b - 1] == valor_2)
                {
                    matriz[a][b] = valor_2;
                    (*px)--; b--;
                    matriz[a][b] = valor_1;
                    return;
                }
                else c = 2;

                if(c == 2) if(matriz[a][b + 1] == valor_2)
                {
                    matriz[a][b] = valor_2;
                    (*px)++; b++;
                    matriz[a][b] = valor_1;
                    return;
                }
                else c = 1;

                if(c == 1) if(matriz[a - 1][b] == valor_2)
                {
                    matriz[a][b] = valor_2;
                    (*py)--; a--;
                    matriz[a][b] = valor_1;
                    return;
                }
                else c = 0;

                if(c == 0) if(matriz[a + 1][b] == valor_2)
                {
                    matriz[a][b] = valor_2;
                    (*py)++; a++;
                    matriz[a][b] = valor_1;
                    return;
                }
                else c = 3; goto VOLTA_CASE;
        }
    }
}