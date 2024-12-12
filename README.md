# Caso-Final-Integrador-Tema-4
https://github.com/alexdulo06/Caso-Final-Integrador-Tema-4.git

Para este proyecto, se te pide que implementes un intérprete "tiny-lisp" basado en la clase Variant y las capacidades de la Standard Template Library (STL) de C++. Deberás trabajar en CLion para este proyecto.

Requisitos del proyecto:

Definir e implementar una clase Variant. Esta clase deberá ser capaz de representar diferentes tipos de datos, incluyendo símbolos, números, listas y procedimientos.
Implementar un método to_string() para la clase Variant que convierta una instancia de la clase a una cadena de texto.
Implementar un método to_json_string() para la clase Variant que convierta una instancia de la clase a una representación en formato JSON.
Implementar un método estático from_json_string() que tome una cadena en formato JSON y la convierta a una instancia de la clase Variant.
Implementar un método parse_json() que tome una cadena en formato JSON y la convierta a una instancia de la clase Variant.
Rúbrica
(30%) Implementación de la clase Variant:

Se implementó la clase Variant correctamente, y se incluyeron todos los tipos de datos requeridos.
(20%) Método to_string():

El método to_string() está implementado correctamente y devuelve una cadena de texto que representa correctamente la instancia de la clase Variant.
(20%) Método to_json_string():

El método to_json_string() está implementado correctamente y devuelve una representación JSON válida de la instancia de la clase Variant.
(15%) Método estático from_json_string():

El método estático from_json_string() está implementado correctamente y puede tomar una cadena en formato JSON y convertirla en una instancia de la clase Variant.
(15%) Método parse_json():

El método parse_json() está implementado correctamente y puede tomar una cadena en formato JSON y convertirla en una instancia de la clase Variant.
Entrega
Todo el código debe estar bien comentado y organizado.
Se debe incluir un archivo README con instrucciones sobre cómo compilar y ejecutar tu programa.
El proyecto debe compilarse sin errores ni advertencias en CLion.
Propuesta de Solución
Aquí está el código de tu clase Variant completo con los métodos to_string(), to_json_string(), from_json_string() y parse_json() que has proporcionado.

Antes de pegar el código en CLion, necesitas tener la librería json11 y la supuesta jsonlib instalada en tu sistema.

#include <vector>
#include <string>
#include <map>
#include "json11.hpp" // Asegúrate de tener esta biblioteca en tu sistema
#include "jsonlib.hpp" // No estoy seguro de qué biblioteca es esta, asegúrate de tenerla en tu sistema

enum variant_type { Symbol, Number, List, Proc, Lambda, Cadena };

struct Entorno;

class Variant {
public:
    typedef Variant(*proc_type) ( const std::vector<Variant>& );
    typedef std::vector<Variant>::const_iterator iter;
    typedef std::map<std::string, Variant> map;

    variant_type type;
    std::string val;
    std::vector<Variant> list;
    proc_type proc;
    Entorno* env;

    Variant(variant_type type = Symbol) : type(type) , env(0), proc(0) { }
    Variant(variant_type type, const std::string& val) : type(type), val(val) , env(0) , proc(0) { }
    Variant(proc_type proc) : type(Proc), proc(proc) , env(0) { }

    std::string to_string();
    std::string to_json_string();
    static Variant from_json_string(std::string json);
    static Variant parse_json(jsonlib::Json job);  // Asegúrate de que esta es la definición correcta de la función
};

std::string Variant::to_string() {
    // Tu implementación aquí
}

std::string Variant::to_json_string() {
    // Tu implementación aquí
}

Variant Variant::from_json_string(std::string sjson) {
    // Tu implementación aquí
}

Variant Variant::parse_json(jsonlib::Json job) {
    // Tu implementación aquí
}
Este código aún no es funcional porque no has proporcionado la definición del tipo Entorno ni el código para jsonlib::Json. Asegúrate de incluir estas definiciones en tu proyecto antes de tratar de compilar.
