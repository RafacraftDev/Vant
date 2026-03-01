#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <limits>
#include <algorithm>
#include <cstdlib>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <thread>

// Librerías de soporte
#include <boost/any.hpp>

// Headers de tu proyecto (según tu CMake)
#include "eval.h"
#include "strops.h"
#include "builtin.h"
#include "main.h"
#include "anyops.h"
#include "Vant.h" 
#include "graphics.h"

// Definiciones de Motor
#define DEVELOPER_MESSAGES false
#define NAMEVERSION "Vant Engine v1.0-Native"

#if defined(__unix__)
    #define PLATFORM_NAME "Unix-based"
    #include <unistd.h>
#elif defined(_WIN32)
    #define PLATFORM_NAME "Windows"
    #include <windows.h>
#endif

using namespace std;
using namespace boost;

// Memoria del Motor Vant
unordered_map<string, boost::any> globalVariableValues;
unordered_map<string, vector<vector<string>>> functionValues;

// --- BUSCADOR DE VARIABLES ---
boost::any GetVantVariable(const string& varName, const unordered_map<string, boost::any>& localVars) {
    string baseName = trim(varName);
    
    // Soporte para acceso a propiedades: objeto.propiedad
    if (count(varName, '.') > 0) {
        string sub = trim(varName.substr(indexInStr(varName, '.') + 1, -1));
        baseName = trim(split(varName, '.')[0]);
        boost::any obj = GetVantVariable(baseName, localVars);
        return GetClassSubComponent(obj, sub);
    }

    auto itLocal = localVars.find(baseName);
    if (itLocal != localVars.end()) return itLocal->second;

    auto itGlobal = globalVariableValues.find(baseName);
    if (itGlobal != globalVariableValues.end()) return itGlobal->second;

    return varName; // Si no existe, lo trata como literal o identificador
}

// --- EVALUADOR DE EXPRESIONES (Vant Lexer) ---
boost::any EvalVantExpression(const string& ex, unordered_map<string, boost::any>& localVars) {
    string expr = trim(ex);
    string root = split(expr, '(')[0];

    // ¿Es una función del usuario?
    if (functionValues.count(root) && countOutsideParenthesis(expr, '+') == 0) {
        string argsStr = betweenChars(expr, '(', ')');
        vector<string> argList = splitNoOverlap(argsStr, ',', '(', ')');
        vector<boost::any> finalArgs = VarValues(argList, localVars);
        return ExecuteVantFunction(root, finalArgs);
    }

    // ¿Es una función interna de Vant? (Vant.Graphics, Vant.System, etc)
    if (startsWith(expr, "Vant.") && countOutsideParenthesis(expr, '(') > 0) {
        string argsStr = betweenChars(expr, '(', ')');
        vector<string> argList = splitNoOverlap(argsStr, ',', '(', ')');
        vector<boost::any> finalArgs = VarValues(argList, localVars);
        return VantBuiltinHandler(root, finalArgs);
    }

    // Si es una operación matemática o lógica compleja
    return evaluate(expr); 
}

// --- PROCESADOR DE LÍNEAS (Vant Runtime) ---
boost::any ProcessVantLine(const vector<vector<string>>& words, int& lineNum, unordered_map<string, boost::any>& localVars) {
    string cmd = words.at(lineNum).at(0);

    // Salida por consola
    if (cmd == "printl") {
        cout << AnyAsString(EvalVantExpression(unWrapVec(vector<string>(words.at(lineNum).begin() + 1, words.at(lineNum).end())), localVars)) << endl;
        return nullType;
    }

    // Declaración de Variables
    if (countInVector(types, cmd) > 0) {
        localVars[words.at(lineNum).at(1)] = EvalVantExpression(unWrapVec(slice(words.at(lineNum), 3, -1)), localVars);
        return nullType;
    }

    // Estructura IF
    if (cmd == "if") {
        // ... (Tu lógica de bloques de llaves que tenías antes)
    }

    return nullType;
}

// --- PUNTO DE ENTRADA ---
int main(int argc, char* argv[]) {
    // Logo de bienvenida
    cout << "-----------------------------------" << endl;
    cout << "  " << NAMEVERSION << " ON " << PLATFORM_NAME << endl;
    cout << "-----------------------------------" << endl;

    if (argc < 2) {
        cout << "[!] Error: No se proporcionó un archivo .vant" << endl;
        return 1;
    }

    // Leer archivo .vant
    string scriptPath = argv[1];
    ifstream file(scriptPath);
    if (!file.is_open()) {
        cout << "[!] Error al abrir: " << scriptPath << endl;
        return 1;
    }

    stringstream buffer;
    buffer << file.rdbuf();
    string code = buffer.str();

    // Iniciar Motor Gráfico (SDL2)
    // InitVantGraphics(); 

    // Cargar Script
    ParseVantScript(code);

    try {
        // Ejecutar función de entrada
        ExecuteVantFunction("Main", vector<boost::any>{});
    } catch (const std::exception& e) {
        cerr << "Vant Runtime Error: " << e.what() << endl;
    }

    return 0;
}
