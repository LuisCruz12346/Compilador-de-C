#include<iostream>
#include<string>
#include <stack>

using namespace std;
// Se define el automata a seguir, sigue una estructura de tipo SLR
/*
 Z -> A
 A -> BA'
 A' -> +BA' | -BA' | epsilon
 B -> CB'
 B' -> *CB' | /CB' | epsilon
 C -> n |(A)
*/
int automata[][14] ={
//	|Z	|A	|A'	|B	|B'	|C	|+	|-	|*	|/	|n	|(	|)	|$	|
	{25	, 1	, 25	, 2	, 25	, 3	, 25	, 25 	, 25	, 25 	, 4	, 5	, 25	, 25	},//0
	{25	, 25	, 25	, 25	, 25	, 25 	, 25	, 25	, 25	, 25	, 25	, 25	, 25	, 23	},//1
	{25	, 25	, 6	, 25	, 25	, 25 	, 7	, 8	, -1	, -1	, 25	, 25	, -1	, -1	},//2
	{25	, 25	, 25	, 25	, 13	, 25 	, -2	, -2	, 14	, 15	, 25	, 25	, -2	, -2	},//3
	{25	, 25	, 25	, 25	, 25	, 25 	, -3	, -3	, -3	, -3	, 25	, 25	, -3	, -3	},//4
	{25	, 20	, 25	, 2	, 25	, 3 	, 25	, 25	, 25	, 25	, 4	, 5	, 25	, 25	},//5
	{25	, 25	, 25	, 25	, 25	, 25 	, -4	, -4	, -4	, -4	, 25	, 25	, -4	, -4	},//6
	{25	, 25	, 25	, 9	, 25	, 3 	, 25	, 25	, 25	, 25	, 4	, 5	, 25	, 25	},//7
	{25	, 25	, 25	, 11	, 25	, 3 	, 25	, 25	, 25	, 25	, 4	, 5	, 25	, 25	},//8
	{25	, 25	, 10	, 25	, 25	, 25 	, 7	, 8	, -1	, -1	, 25	, 25	, -1	, -1	},//9
	{25	, 25	, 25	, 25	, 25	, 25 	, -5	, -5	, -5	, -5	, 25	, 25	, -5	, -5	},//10
	{25	, 25	, 12	, 25	, 25	, 25 	, 7	, 8	, -1	, -1	, 25	, 25	, -1	, -1	},//11
	{25	, 25	, 25	, 25	, 25	, 25 	, -6	, -6	, -6	, -6	, 25	, 25	, -6	, -6	},//12
	{25	, 25	, 25	, 25	, 25	, 25 	, -7	, -7	, -7	, -7	, 25	, 25	, -7	, -7	},//13
	{25	, 25	, 25	, 25	, 25	, 16 	, 25	, 25	, 25	, 25	, 4	, 5	, 25	, 25	},//14
	{25	, 25	, 25	, 25	, 25	, 18 	, 25	, 25	, 25	, 25	, 4	, 5	, 25	, 25	},//15
	{25	, 25	, 25	, 25	, 17	, 25 	, -2	, -2	, 14	, 15	, 25	, 25	, -2	, -2	},//16
	{25	, 25	, 25	, 25	, 25	, 25 	, -8	, -8	, -8	, -8	, 25	, 25	, -8	, -8	},//17
	{25	, 25	, 25	, 25	, 19	, 25 	, -2	, -2	, 14	, 15	, 25	, 25	, -2	, -2	},//18
	{25	, 25	, 25	, 25	, 25	, 25 	, -9	, -9	, -9	, -9	, 25	, 25	, -9	, -9	},//19
	{25	, 25	, 25	, 25	, 25	, 25 	, 25	, 25	, 25	, 25	, 25	, 25	, 21	, 25	},//20
	{25	, 25	, 25	, 25	, 25	, 25 	, -10	, -10	, -10	, -10	, 25	, 25	, -10	, -10	}//21
};
// Se definen los estados no terminales
		          //|A'-e	|B'-e	|C-n	|A-BA'	|A'-+BA'|A'--BA'|B-CB'	|B'-*CB'|B'-/CB'|C-(A)	|	 
char EstadoNoTerminales[]={0,'K'	, 'L'	, 'C'	, 'A'	, 'K'	, 'K'	, 'B'	, 'L'	, 'L'	,'C'};
string NoTerminales[] = {"" , "" 	, ""	, "n"	, "BK"	, "+BK"	, "-BK"	, "CL"	, "*CL"	, "/CL"	,"(A)"};

// Se imprimen la transiciones de estados para comprobar el comportamiento
void imprimir(stack<int> copia){
	while (!copia.empty()) {
		cout << copia.top() << " ";
		copia.pop();
	}
	cout << endl;
}

int main(){
	string cadena = "(n+n-n)/(n-n/n)";
	stack<int> estados;
	int estadoActual;
	// Se inicia en el estado 0, con el primer caracter
	int i = 0;
	estados.push(0);
	estadoActual = 0;
	int caracter;
	/*
		Los estados negativos hacen referencia a una accion reduce, por lo cual, se quitan estados y se evualua. 
		Los estados positivos hacen referencia a una accion shift, pero considerando si la siguiente accion es negativa. 
		
		Una opcion de mejora es de que se utilicen numero en vez de caracteres y asi utilizar diferencias para acceder a la ubicacion. 
	*/
	while(estadoActual < 22){
		caracter = cadena[i];
		if (estadoActual < 0){
			estados.pop();
			int q = -1 * estadoActual;
			string NT = NoTerminales[q];
			for (int p = 0; p < NT.length(); p++)
				estados.pop();
			if(EstadoNoTerminales[q] == 'A'){
				estadoActual = automata[estados.top()][1];
			}
			else if(EstadoNoTerminales[q] == 'K'){
				estadoActual = automata[estados.top()][2];
			}
			else if(EstadoNoTerminales[q] == 'B'){
				estadoActual = automata[estados.top()][3];
			}
			else if(EstadoNoTerminales[q] == 'L'){
				estadoActual = automata[estados.top()][4];
			}
			else if(EstadoNoTerminales[q] == 'C'){
				estadoActual = automata[estados.top()][5];
			}
			estados.push(estadoActual);
		}
		else if(caracter == '+'){
			estadoActual = automata[estadoActual][6];
			estados.push(estadoActual);
			i= (estadoActual>0) ? i + 1 : i;
		}
		else if(caracter == '-'){
			estadoActual = automata[estadoActual][7];
			estados.push(estadoActual);
			i= (estadoActual>0) ? i + 1 : i;
		}
		else if(caracter == '*'){
			estadoActual = automata[estadoActual][8];
			estados.push(estadoActual);
			i= (estadoActual>0) ? i + 1 : i;
		}
		else if(caracter == '/'){
			estadoActual = automata[estadoActual][9];
			estados.push(estadoActual);
			i= (estadoActual>0) ? i + 1 : i;
		}
		else if(caracter == 'n'){
			estadoActual = automata[estadoActual][10];
			estados.push(estadoActual);
			i= (estadoActual>0) ? i + 1 : i;
		}
		else if(caracter == '('){
			estadoActual = automata[estadoActual][11];
			estados.push(estadoActual);
			i= (estadoActual>0) ? i + 1 : i;
		}
		else if(caracter == ')'){
			estadoActual = automata[estadoActual][12];
			estados.push(estadoActual);
			i= (estadoActual>0) ? i + 1 : i;
		}
		else if(caracter == '\0'){
			estadoActual = automata[estadoActual][13];
			estados.push(estadoActual);
		}
		else{
			estadoActual = 25;
		}
		imprimir(estados);
	}
	
	if (estadoActual == 23){
		cout << "Se acepta cadena" << endl;
	}
	else{
		cout << "Error de sintaxis" << endl;
	}
	
	return 0;
}
