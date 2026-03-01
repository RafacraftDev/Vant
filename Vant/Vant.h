#ifndef VANT_CORE_H
#define VANT_CORE_H

#include <string>

std::string VantContents = R"(
////////////////////////////////////////////////////////////////////////////////
//  VANT ENGINE - OFFICIAL SYNTAX
////////////////////////////////////////////////////////////////////////////////

var PI = 3.1415926535
var EXIT_WHEN_DONE = true

// Definición con 'def'
def Sin(input) {
    return Vant.Math.Sin(input);
}

def printl(text) {
    Vant.System.PrintLine(text);
}

def Sprite(path, x, y) {
    var s = Vant.Graphics.Sprite(path, x, y);
    return s;
}

//////////////////////////////////////////
// Ejemplo de lógica con tu nueva sintaxis
//////////////////////////////////////////

def GetWelcome() {
    return "Bienvenido a Vant Engine";
}

var starterMessage = GetWelcome();
)";

#endif
