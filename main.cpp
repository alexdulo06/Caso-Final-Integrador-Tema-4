#include <vector>
#include <string>
#include <map>
#include <stdexcept>
#include "./json11-master/json11.hpp"
#include "./JSONLib-master/JSONLib/src/JSONLib.h"

// Enumeración para los diferentes tipos de variantes
enum VariantType { Symbol, Number, List, Proc, Lambda, Cadena };

// Declaración previa del entorno (puedes definirlo posteriormente según tus necesidades)
struct Entorno;

class Variant {
public:
    // Tipos de datos y estructuras auxiliares
    using ProcType = Variant(*)(const std::vector<Variant>&); // Puntero a función
    using ConstIter = std::vector<Variant>::const_iterator;   // Iterador constante
    using Map = std::map<std::string, Variant>;               // Mapa para almacenar variables/valores

    // Miembros de la clase
    VariantType type;            // Tipo de la variante
    std::string val;             // Valor en caso de cadenas o símbolos
    std::vector<Variant> list;   // Lista para almacenar otras variantes
    ProcType proc;               // Función del tipo proceso
    Entorno* env;                // Entorno al que pertenece

    // Constructores
    Variant(VariantType type = Symbol) : type(type), env(nullptr), proc(nullptr) {}
    Variant(VariantType type, const std::string& val) : type(type), val(val), env(nullptr), proc(nullptr) {}
    Variant(ProcType proc) : type(Proc), proc(proc), env(nullptr) {}

    // Métodos
    std::string toString() const;                    // Convierte la variante a string
    std::string toJsonString() const;                // Convierte la variante a JSON string
    static Variant fromJsonString(const std::string& json); // Crea una variante desde un string JSON
    static Variant parseJson(const json11::Json& job);      // Analiza un objeto JSON

private:
    static void trimTrailingComma(std::string& str); // Utilidad para manejar la última coma
};

// Implementación de los métodos
std::string Variant::toString() const {
    switch (type) {
        case Symbol:
            return "Symbol: " + val;
        case Number:
            return "Number: " + val;
        case List: {
            std::string result = "List: [";
            for (const auto& item : list) {
                result += item.toString() + ", ";
            }
            if (!list.empty()) {
                trimTrailingComma(result);
            }
            result += "]";
            return result;
        }
        case Proc:
            return "Proc: <function>";
        case Lambda:
            return "Lambda: <function>";
        case Cadena:
            return "Cadena: \"" + val + "\"";
        default:
            return "Unknown";
    }
}

std::string Variant::toJsonString() const {
    switch (type) {
        case Symbol:
            return "\"" + val + "\"";
        case Number:
            return val;
        case List: {
            std::string result = "[";
            for (const auto& item : list) {
                result += item.toJsonString() + ",";
            }
            if (!list.empty()) {
                trimTrailingComma(result);
            }
            result += "]";
            return result;
        }
        case Cadena:
            return "\"" + val + "\"";
        default:
            return "{}";
    }
}

Variant Variant::fromJsonString(const std::string& sjson) {
    std::string err;
    json11::Json parsed = json11::Json::parse(sjson, err);
    if (!err.empty()) {
        throw std::invalid_argument("Error al analizar JSON: " + err);
    }
    return parseJson(parsed);
}

Variant Variant::parseJson(const json11::Json& job) {
    if (job.is_string()) {
        return Variant(Cadena, job.string_value());
    } else if (job.is_number()) {
        return Variant(Number, std::to_string(job.number_value()));
    } else if (job.is_array()) {
        Variant varList(List);
        for (const auto& item : job.array_items()) {
            varList.list.push_back(parseJson(item));
        }
        return varList;
    } else if (job.is_object()) {
        Variant varMap(Symbol);
        for (const auto& kv : job.object_items()) {
            Variant key(Cadena, kv.first);
            Variant value = parseJson(kv.second);
            varMap.list.push_back(key);
            varMap.list.push_back(value);
        }
        return varMap;
    }
    return Variant(Symbol); // Valor por defecto si no se reconoce
}

void Variant::trimTrailingComma(std::string& str) {
    if (!str.empty() && str.back() == ',') {
        str.pop_back();
    }
}
