#include<iostream>
#include<string>
#include<vector>

#define es_numero(n) (((n) > 47) && ((n) < 58))
#define es_letra(n) (((n) > 96) && ((n) < 123)) // Recibo siempre en minusculas
#define es_operador(n) ( \
    ((n) == '+') || \
    ((n) == '-') || \
    ((n) == '*') || \
    ((n) == '/') || \
    ((n) == '&') || \
    ((n) == '|') || \
    ((n) == '%') )

using namespace std;
int tamañorese = 8;
string reservadas[] = {"int","float","double", "char","for","if","while","else"};

int comparar(const string& cadena){
	for(int i = 0; i<tamañorese ; i++)
		if(reservadas[i] == cadena)
			return 1;
	return 0;
}

int main(){
	string cadena = "98 + 78";
	string lexico = "";
	for(int i = 0 ;cadena[i]; i++){
		if(es_numero(cadena[i])){
			int num = 0;
			while(es_numero(cadena[i]))
				num = num * 10 + (cadena[i++] - '0');
			lexico.push_back('n');
			i--;
		}
		else if (es_letra(cadena[i]) || cadena[i] == '_'){
			string identificador = "";
			while(es_letra(cadena[i]) || cadena[i] == '_')
				identificador.push_back(cadena[i++]);
			if(comparar(identificador)){
				lexico.append(identificador);
			}
			else{
				lexico.push_back('i');
			}
			i--;
		}
		else{
			lexico.push_back(cadena[i]);
		}
	}
	cout << lexico << endl;
	return 0;
}
