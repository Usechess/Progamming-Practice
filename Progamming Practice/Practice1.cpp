#include <iostream>
#include <string>
using namespace std;

void E1()
{
    int pociones;
    int antidotos;
    do 
    {
        cout << "ingrese cantidad de pociones" << endl;
        cin >> pociones;
        if (pociones < 0)
        {
            cout << "cantidad de pociones invalida" << endl;
        }
        cout << "ingrese cantidad de antidotos" << endl; 
        cin >> antidotos;
        if (antidotos < 0)
        {
            cout << "cantidad de antidotos invalida" << endl;
        }
    }
    while(pociones < 0 || antidotos < 0);

    int sumaPA = pociones + antidotos;

    if (sumaPA > 50)
    {
        cout << "Inventario lleno" << endl;
    }
    else 
    {
        cout << "Espacio disponible" << endl;
    }
     
}

void E2()
{
    // Crear un programa que pida al usuario 2 numeros e imprima la suma, resta, producto, resto y cociente de los numeros
    // Crear variables de 2 numeros
    // Operar los numeros entre si (suma, resta, division, multiplicacion)
    int num1;
    int num2;
    cout << "Ingrese el primer numero: ";
    cin >> num1;
    cout << "Ingrese el segundo numero: ";
    cin >> num2;
    int suma = num1 + num2;
    int resta = num1 - num2;
    int mult = num1 * num2;
    int cociente = num1 / num2;
    int resto = num1 % num2;
    cout << suma << " " << resta << " " << mult << " " << cociente << " " << resto;

}

void E3()
{
    //Desarrollar una funcion para calcular el numero factorial de un entero.
    int n;
    do 
    {
        cout << "Ingrese un numero entero: ";
        cin >> n;
        if (n < 0)
        {
            cout << "numero invalido ingrese de nuevo" << endl;
        }
        else if (n == 0)
        {
            cout << "El factorial de 0 es 1" << endl;
            return;
        }
    }
    while (n < 0);

    int factorial = 1;
    for (int i = n; i > 0; i--)
    {
        factorial *= i;
    }
    
    cout << "El factorial de " << n << " es " << factorial << endl;
}

void E4()
{
    // desarrollar una funcion para calcular el combinatorio m sobre n
    int n;
    int m;

    // se pide n
    do
    {
        cout << "Ingrese n: ";
        cin >> n;
            
        if (n < 0)
        {
        cout << "numero invalido ingrese de nuevo" << endl;
        }
    }
    while (n < 0);

    // se pide m
    do
    {
        cout << "Ingrese m: ";
        cin >> m;
            
        if (m < 0)
        {
        cout << "numero invalido ingrese de nuevo" << endl;
        }
        else if (m < n)
        {
        cout << "numero invalido, ingrese de nuevo" << endl;
        }
    }
    while (m < 0 || m < n);

    //factorial n
    int factorialn = 1;
    for (int i = n; i > 0; i--)
    {
        factorialn *= i;
    }

    //factorial m
    int factorialm = 1;
    for (int j = m; j > 0; j--)
    {
        factorialm *= j;
    }

    //factorial n-m
    int mn = (m - n);
    int factorialmn = 1;
    for (int k = mn; k > 0; k--)
    {
        factorialmn *= k;
    }

    cout << factorialn << endl;
    cout << factorialm << endl;
    cout << factorialmn << endl;
    // resolucion del combinatorio
    int combinatorio = (factorialm / (factorialn * factorialmn));
    cout << "El combinatorio de m = " << m << " sobre n = " << n << " es igual a " << combinatorio;
}

void E5()
{
    // Dado el numero entero X y una toleracion TOL, puede obtenerse e^x mediante la suma de los terminos
    // de la serie e^x = 1+(x^1 / 1)+ (x^2 / (1*2)) + (x^3 * (1*2*3)) ... 
    // El proceso termina cuando se obtiene un termino calculado que sea menor que la tolerancia TOL.
    // Desarrollar una funcin para calcular el e^x, dados X y TOL.

    // definir x y tol

    // crear el sistema de potencias mediante una funcion iterativa

    // definir la iteracion definida por el valor TOL 

    double x, tol;
    double suma = 1.0;
    double termino = 1.0;
    int n = 1;

    cout << "Ingrese X: ";
    cin >> x;

    cout << "Ingrese la tolerancia: ";
    cin >> tol;

    // Serie de Taylor de e^x
    while (true)
    {
    termino = termino * x / n;

    if (termino < tol && termino > -tol)
        break;

    suma = suma + termino;
    n++;
    }

    cout << "Resultado aproximado de e^" << x << " = " << suma << endl;
}

void E6()
{
    // Fibonacci c/ termino es la suma de los 2 anteriores, ej: 1 1 2 3 5 8 13 21 34... 
    // Desarrolla una funcion para determinar si un entero pertenece a la serie de Fibonacci.
    int x;

    int fib = 0;
    int fib1 = 1;
    int fibs;
    
    do
    {
        cout << "Ingrese un entero: ";
        cin >> x;
        if (x < 0)
        {
            cout << "El numero no es un entero";
        }
        else if (x == 0)
        {
            cout << "El 0 no pertenece a la serie de Fibonacci." << endl;
        }
    } while(x < 0);
    while (fib1 < x)
    {
        fibs = fib + fib1;
        fib = fib1;
        fib1 = fibs;
    }
    if (x == fib1)
    {
        cout << "El numero pertenece a la serie de Fibonacci";
    }
    else
    {
        cout << "El numero no pertenece a la serie de Fibonacci";
    }
}

void E7()
{
   // Dados X y una tolerancia TOL es posible calcular el seno(x) mediante la suma de los terminos de la serie.
   // seno(x) = x-x^3 / 3! + x^5 / 5! - x^7 / 7! + x^9 / 9! - x^11 / 11! + ...
   // Este proceso continua mientras el termino calculado (en valor absoluto sea mayor que la tolerancia)
   // Desarrollar una funcion que obtenga el seno de X con tolerancia TOL, utilizando dicha serie

    double x, tol, termino, suma;
    int n = 1;

    cout << "DISCLAIMER!!!!, Si no ingresa X en radianes el sen(X) sera erroneo" << endl;
    cout << "Ingrese X (en radianes): ";
    cin >> x;

    cout << "Ingrese la tolerancia: ";
    cin >> tol;

    termino = x;   // primer término
    suma = x;

    while (true)
    {
        termino = termino * (-x * x) / ((2 * n) * (2 * n + 1));

        if (termino < tol && termino > -tol)
        {
            while(false);
        }
        suma += termino;
        n++;
    }

    cout << "sin(" << x << ") ≈ " << suma << endl;
}

void E8()
{
    cout << "ah";
}

int main()
{
    E7();
    return 0;
}