#include "Letras.h"
#include <ctime>

//constructor vacío
Letras::Letras()
{
    tam=0;
    arregloLetras=nullptr;
}
//constructor con parámetros "tamaño"        
Letras::Letras(int tam)
{
    this->tam=tam;
    arregloLetras= new string[tam];
}
//destructor
Letras::~Letras(){}
//método para llenar el arreglo de letras con letras aleatorias
void Letras::llenarAleatorio()
{
    srand(time(NULL));
    for(int i=0; i<tam; i++)
    {
        arregloLetras[i]=(rand()%26)+97;//letras minúsculas
    }
    cout<<"Arreglo llenado con éxito"<<endl;
}
//método para reemplazar una letra en una posición específica
void Letras::reemplazarLetra(int pos, string letra)
{
    if(pos>=0 and pos<tam)
    {
        arregloLetras[pos]=letra;
        cout<<"Letra "<<letra<<" fue reemplazada con éxito en la posición "<<pos<<endl;
    }
    else
    {
        cout<<"La posición "<<pos<<" no es válida."<<endl;
    }
}
//método para mostrar los datos del arreglo
string Letras::mostrarDatos()
{
    string salida="\n";
    for(int i=0; i<tam; i++)
    {
        salida+=arregloLetras[i]+"\t";
    }
    return salida;
}
//método para mostrar la cantidad de veces que aparece una letra específica en el arreglo
int Letras::mostrarLetra(string letra)
{
    int cant=0;
    for (int i=0; i<tam; i++)
    {
        if(arregloLetras[i]==letra)
        {
            cant++;
        }
    }
    return cant;
}


//retorna un arreglo de enteros con las posiciones de la letra en el arreglo
int* Letras::retornarArreglo(string letra)
{
    int cant=mostrarLetra(letra);
    int *arreglo= new int[cant]; //arreglo dinámico que contendrá las posiciones de la letra
    if(cant==0)
    {
        arreglo=new int[1];
        arreglo[0]=-1;
    }
    else
    {
        int contador=0;
        for(int i=0; i<tam; i++)
        {
            if(arregloLetras[i]==letra)
            {
                arreglo[contador]=i;
                contador++;
            }
        }
    }
    return arreglo;
}
//retorna la letra en la posición indicada
string Letras::retornarLetra(int pos)
{
    if(pos>=0 and pos < tam)
    {
        return arregloLetras[pos];
    }
    else
    {
        return "Posición no válida.\n";
    }
}
//método para borrar el arreglo de letras
void Letras::borrar()
{
    delete [] arregloLetras;
    arregloLetras= nullptr;
}
//método para jugar, solicita al usuario la cantidad de palabras y las palabras a evaluar
void Letras::juego()
{
    int cantidadPalabras=0, cuántas=0;
    bool forma;
    string* palabras=nullptr;
    Validaciones val;

    cantidadPalabras=stoi(val.leerI(0,"\nDigite la cantidad de palabras: "));
    cout<<endl;
    palabras=new string[cantidadPalabras]; //arreglo dinámico de palabras
    for(int i=0; i<cantidadPalabras; i++)//se solicitan las palabras
    {
        palabras[i]=val.leer("Digite la palabra número "+to_string(i)+" : ");
        cout<<endl;
    }
    for(int i=0; i<cantidadPalabras; i++)//se evalúan las palabras
    {
        cout<<"Palabra No. "<<to_string(i)<<": "<<palabras[i]<<endl;
        forma=mecánicaPrincipal(palabras[i]);
        if(forma==true)
        {
            cout<<"La palabra "<<palabras[i]<<" sí se puede formar"<<endl;
            cuántas++;
        }
        else
        {
            cout<<"La palabra "<<palabras[i]<<" no se puede formar"<<endl;
        }
    }
    cout<<"Se pueden formar "<<to_string(cuántas)<<" palabras"<<endl;
    delete [] palabras;
    palabras=nullptr;
}
//método que evalúa si se puede formar la palabra con las letras del arreglo
bool Letras::mecánicaPrincipal(string palabra)
{
    bool forma=true, está=false; //forma indica si se puede formar la palabra inicialmente, "esta" indica si la letra está en el arreglo
    int contador=0;//contador para recorrer la palabra
    string arregloAleatorio="", palabraBinaria="", posiciones="";
    for(int i=0; i<palabra.length(); i++)//se llena la cadena de caracteres con espacios
    {
        palabraBinaria+=' ';
    }

    for (int i=0; i<tam; i++)//se copia el arreglo de letras aleatorias en una cadena de caracteres
    {
        arregloAleatorio+=arregloLetras[i];
    }

    for(int i=0; i<palabra.length(); i++)
    {
        está=false;

        for(int j=0; j<tam;j++)
        {
            if(palabra[i]==arregloAleatorio[j])
            {
                palabraBinaria[contador]='1'; //se cambia el espacio por un 1 si la letra está en el arreglo
                arregloAleatorio[j]=' '; //se cambia la letra por un espacio para no repetirla
                está=true; //se cambia la variable para indicar que si esta la letra en el arreglo
                posiciones+=to_string(j); //se guarda la posición de la letra
                break;
            }
        }
        if(está==false)
        {
            palabraBinaria[contador]='0'; //se cambia el espacio por un 0 si la letra no está en el arreglo
            forma=false; //se cambia la variable para indicar que no se puede formar la palabra
        }
        contador++;//se aumenta el contador para recorrer la palabra
    }

    if(forma==false)//se evalúa si se puede formar la palabra
    {
        for(int i=0; i<palabra.length(); i++)
        {
            if(palabraBinaria[i]=='0')
            {
                cout<<"La letra "<<palabra[i]<<" no se encuentra en el arreglo"<<endl;
            }
        }
    }
    else
    {
        for(int i=0; i<palabra.length(); i++)
        {
            cout<<"La letra "<<palabra[i]<<" se encuentra en la posición "<<posiciones[i]<<endl;
        }
    }
    return forma;
}