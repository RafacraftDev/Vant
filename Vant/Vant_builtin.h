#ifndef VANT_BUILTIN_H
#define VANT_BUILTIN_H

// Identificación de Plataforma
#if defined(__unix__)
    #define UNIX true
    #define WINDOWS false
#elif defined(_MSC_VER)
    #define UNIX false
    #define WINDOWS true
#endif

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <boost/any.hpp>
#include <SDL.h>
#include <ctime>
#include <cmath>
#include <sys/stat.h>
#include <cstdlib>

#include "strops.h"
#include "graphics.h"
#include "anyops.h"

#if WINDOWS
    #include "color.hpp"
#endif

using namespace std;
using namespace boost;

// Tipos oficiales de Vant
vector<string> vant_types = { "int", "float", "string", "bool", "void", "Sprite", "Vec2", "Text" };

// Colores de Consola (ANSI)
const string yellowFG = "\x1B[33m";
const string greenFG  = "\x1B[32m";
const string redFG    = "\x1B[31m";
const string blueFG   = "\x1B[34m";
const string reset    = "\033[0m";

// Clases de control internas
class NullType { public: string type = "NULL"; };
class BREAK    { public: string type = "BREAK"; };

boost::any nullType = NullType();

// --- Utilidades Matemáticas ---

float clamp(float v, float min, float max) {
    if (v < min) return min;
    if (v > max) return max;
    return v;
}

float lerp(float a, float b, float f) {
    return a + f * (b - a);
}

inline bool fileExists(const std::string& name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

// --- Sistema de Logs de Vant ---

void PrintColored(string text, string color, bool isError) {
#if WINDOWS
    // Aquí podrías usar tu librería color.hpp adaptada
    if (color == redFG) cerr << text; else cout << text;
#else
    if (isError) cerr << color << text << reset;
    else cout << color << text << reset;
#endif
}

int LogVantError(const string& errorText) {
    PrintColored("[Vant Error]: ", redFG, true);
    cerr << errorText << endl;
    return 2;
}

int VantInterpreterLog(const string& logText) {
    time_t now = time(0);
    tm ltm;
#if WINDOWS
    localtime_s(&ltm, &now);
#else
    localtime_r(&now, &ltm);
#endif
    printf("[%02d:%02d:%02d] ", ltm.tm_hour, ltm.tm_min, ltm.tm_sec);
    PrintColored("Vant Engine: ", yellowFG, false);
    cout << logText << endl;
    return 1;
}

// --- Puentes de Funciones Nativas (Vant API) ---

boost::any VantNativeFunction(const string& name, const vector<boost::any>& args) {
    
    // --- Vant.Math ---
    if (name == "Vant.Math.Sin")   return sin(AnyAsFloat(args.at(0)));
    if (name == "Vant.Math.Cos")   return cos(AnyAsFloat(args.at(0)));
    if (name == "Vant.Math.Round") return round(AnyAsFloat(args.at(0)));
    if (name == "Vant.Math.Abs")   return abs(AnyAsFloat(args.at(0)));

    // --- Vant.Graphics ---
    if (name == "Vant.Graphics.Window") {
        initGraphics(AnyAsString(args.at(2)), AnyAsInt(args.at(0)), AnyAsInt(args.at(1)));
        return nullType;
    }

    if (name == "Vant.Graphics.Sprite") {
        string path = StringRaw(AnyAsString(args.at(0)));
        if (!fileExists(path)) {
            LogVantError("No se pudo cargar el Sprite: " + path);
            return nullType;
        }
        // Creamos el objeto VantSprite definido en graphics.h
        return CreateVantSprite(path, AnyAsFloat(args.at(1)), AnyAsFloat(args.at(2)), gRenderer);
    }

    if (name == "Vant.Graphics.Draw") {
        VantSprite s = any_cast<VantSprite>(args.at(0));
        // Aquí llamas a la función real de renderizado en SDL
        SDL_Rect dest = { (int)s.x, (int)s.y, s.w, s.h };
        SDL_RenderCopyEx(gRenderer, s.texture, NULL, &dest, s.rotation, NULL, SDL_FLIP_NONE);
        return nullType;
    }

    // --- Vant.System ---
    if (name == "Vant.System.PrintLine") {
        cout << AnyAsString(args.at(0)) << endl;
        return nullType;
    }

    if (name == "Vant.System.Vec2") {
        return VantVec2(AnyAsFloat(args.at(0)), AnyAsFloat(args.at(1)));
    }

    if (name == "Vant.Input.GetKey") {
        string key = AnyAsString(args.at(0));
        return KEYS[key] == 1;
    }

    LogVantError("La funcion nativa '" + name + "' no esta definida.");
    return nullType;
}

#endif
