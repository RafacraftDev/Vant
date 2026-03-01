#ifndef ANYOPS_H
#define ANYOPS_H

#include <iostream>
#include <string>
#include <boost/any.hpp>
#include "builtin.h"
#include "graphics.h" // Para VantSprite

using namespace boost;
using namespace std;

// Prototipos para evitar errores de compilación circular
int LogVantError(const string& text);
int any_type(const boost::any& val);

// Comprueba si el valor es nulo (vacío)
bool any_null(const boost::any& val) {
    return val.empty();
}

// --- CONVERSORES DINÁMICOS (Cerebro de Vant) ---

bool AnyAsBool(const boost::any& val) {
    if (any_null(val)) return false;
    try { return any_cast<bool>(val); }
    catch (bad_any_cast&) {
        try { return any_cast<string>(val) == "true"; }
        catch (bad_any_cast&) {
            try { return any_cast<float>(val) == 1.0f; }
            catch (bad_any_cast&) {
                try { return any_cast<int>(val) == 1; }
                catch (bad_any_cast&) {
                    LogVantError("Vant Runtime: No se puede convertir a 'bool'");
                    return false;
                }
            }
        }
    }
}

string AnyAsString(const boost::any& val) {
    if (any_null(val)) return "";
    try { return any_cast<string>(val); }
    catch (bad_any_cast&) {
        try { return to_string(any_cast<int>(val)); }
        catch (bad_any_cast&) {
            try { return to_string(any_cast<float>(val)); }
            catch (bad_any_cast&) {
                try { return any_cast<bool>(val) ? "true" : "false"; }
                catch (bad_any_cast&) {
                    return "[VantObject]";
                }
            }
        }
    }
}

float AnyAsFloat(const boost::any& val) {
    if (any_null(val)) return 0.0f;
    try { return any_cast<float>(val); }
    catch (bad_any_cast&) {
        try { return (float)any_cast<int>(val); }
        catch (bad_any_cast&) {
            try { return stof(any_cast<string>(val)); }
            catch (bad_any_cast&) {
                return any_cast<bool>(val) ? 1.0f : 0.0f;
            }
        }
    }
}

int AnyAsInt(const boost::any& val) {
    if (any_null(val)) return 0;
    try { return any_cast<int>(val); }
    catch (bad_any_cast&) {
        try { return (int)any_cast<float>(val); }
        catch (bad_any_cast&) {
            try { return stoi(any_cast<string>(val)); }
            catch (bad_any_cast&) {
                return any_cast<bool>(val) ? 1 : 0;
            }
        }
    }
}

// Identificador de tipos nativos de Vant
// 0:int, 1:decimal, 2:bool, 3:string, 4:Sprite, 5:Vec2
int any_type(const boost::any& val) {
    if (val.type() == typeid(int)) return 0;
    if (val.type() == typeid(double)) return 1;
    if (val.type() == typeid(bool)) return 2;
    if (val.type() == typeid(string)) return 3;
    if (val.type() == typeid(VantSprite)) return 4;
    if (val.type() == typeid(VantVec2)) return 5;
    return -1;
}

// Comparador universal para estructuras IF de Vant
bool any_compare(const boost::any& a, const boost::any& b) {
    int aType = any_type(a);
    int bType = any_type(b);

    // Comparación simple para tipos básicos mediante strings
    if (aType <= 3 && bType <= 3) {
        return AnyAsString(a) == AnyAsString(b);
    }
    
    // Comparación lógica para tipos complejos
    if (aType == 5 && bType == 5) {
        VantVec2 va = any_cast<VantVec2>(a);
        VantVec2 vb = any_cast<VantVec2>(b);
        return (va.x == vb.x && va.y == vb.y);
    }

    return false;
}

#endif
