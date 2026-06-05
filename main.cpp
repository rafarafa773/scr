#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>
#include <iomanip>

void imprimir_con_resaltado(const std::string& linea, const std::string& objetivo) {
	size_t pos = linea.find(objetivo);
	if (pos == std::string::npos) {
		std::cout << linea << "\n";
		return;
    }
	std::cout << linea.substr(0, pos);
	std::cout << "\033[31m" << objetivo << "\033[0m";
	std::cout << linea.substr(pos + objetivo.length()) << "\n";
}

struct objeto_archivo {
	int lineas = 0;
	std::string linea1;
	std::size_t caracteres_del_archivo = 0;

	void reiniciar_flujo(std::ifstream& archivo1) {
		archivo1.clear();
		archivo1.seekg(0);
	}
	int ayuda(char* nombre_prog) {
		std::cout << "uso: " << nombre_prog << " <archivo> <opcion>\n\n"
				  << "comandos:\n"
				  << "  list [dir]     : listar archivos en directorio (por defecto: .)\n"
				  << "  whihi          : imprimir directorio de trabajo actual\n"
				  << "  change <dir>   : cambiar directorio de trabajo\n"
				  << "  show           : mostrar contenido del archivo\n"
				  << "  show <str>     : buscar un string en el archivo\n"
				  << "  count          : contar lineas y caracteres\n"
				  << "  hex            : mostrar archivo en hexadecimal\n"
				  << "  rm             : eliminar el archivo (!peligroso!)\n"
				  << "  tocar          : crear un archivo\n"
				  << "  tocar_legal    : crear un directorio\n"
				  << "  modify         : escribir texto\n";
		return 0;
	}

	int contar_lineas(std::ifstream& archivo1) {
		reiniciar_flujo(archivo1);
		lineas = 0;
		while (std::getline(archivo1, linea1)) {
			lineas++;
		}
		return lineas;
	}

	size_t contar_caracteres(std::ifstream& archivo1) {
		reiniciar_flujo(archivo1);
		caracteres_del_archivo = 0;
		while (std::getline(archivo1, linea1)) {
			caracteres_del_archivo += linea1.size();
			caracteres_del_archivo++;
		}
		return caracteres_del_archivo;
	}
	void listar_archivos(const std::string& ruta_directorio = ".") {
			for (const auto& entrada : std::filesystem::directory_iterator(ruta_directorio)) {
				std::cout << entrada.path().filename().string() << "\n";
			}
	}

	int eliminar_archivo(std::string nombre_del_archivo) {
		std::filesystem::path ruta1 = nombre_del_archivo;
		if(std::filesystem::remove(ruta1)) {
			std::cout << nombre_del_archivo << " eliminado\n";
			return 0;
		} else {
			std::cout << "error\n";
			return 1;
		}
	}
	void imprimir_dir() {
		std::cout << std::filesystem::current_path().string() << "\n";
	}

	int cambiar1(const std::string& nueva_ruta) {
		std::filesystem::current_path(nueva_ruta);
		std::cout << "cambiado a: " << std::filesystem::current_path().string() << "\n";
		return 0;
	}

	void mostrar_todo(std::ifstream& archivo1) {
		reiniciar_flujo(archivo1);
		while(std::getline(archivo1, linea1)) {
			std::cout << linea1 << "\n";
		}
	}
	/* compensando lineas boludeces 
	... 
	*/
};

int main(int argc, char *archivo_pasado[]) {
	double version = 0.23;

	if (argc > 1 && (std::string)archivo_pasado[1] == "--version") {
		std::cout << "version: " << version << "\n";
		return 0;
	}
	
	if (argc > 1 && (std::string)archivo_pasado[1] == "--help") {
		objeto_archivo obj1;
		obj1.ayuda(archivo_pasado[0]);
		return 0;
    }
	if (argc > 1 && (std::string)archivo_pasado[1] == "whihi") {
		objeto_archivo prueba1;
		prueba1.imprimir_dir();
		return 0;
	}
	if (argc > 1 && (std::string)archivo_pasado[1] == "change") {
		if (argc < 3) {
			std::cout << "sos un boludo\n";
			return 1;
		}
		objeto_archivo prueba1;
		prueba1.cambiar1(archivo_pasado[2]);
		return 0;
	}

	if (argc < 2) {
		std::cout << "che, provee un archivo.\n";
		return 1;
	}
	if (argc > 1 && (std::string)archivo_pasado[1] == "list") {
    	std::string ruta_dir = (argc > 2) ? archivo_pasado[2] : ".";
    	objeto_archivo prueba1;
   		prueba1.listar_archivos(ruta_dir);
		return 0;
	}
	
	if (argc == 2) {
		std::cout << "?sos bobo? usa count o show.\n";
	}
	if (argc > 2 && (std::string)archivo_pasado[2] == "tocar") {
		std::ofstream archivo(archivo_pasado[1]);
		if (archivo.is_open()) {
			return 0;
		} else {
			std::cout << "error\n";
			return 1;
		}
	}
	if(argc > 2 and (std::string)archivo_pasado[2]=="tocar_legal") {
		std::filesystem::create_directory(archivo_pasado[1]);
	}
	std::ifstream archivo(archivo_pasado[1]); 
	if(!archivo.is_open()) {
		std::cout << "che, ese archivo no existe.\n";
		return 1;
	}
	

	objeto_archivo prueba1;

	if (argc > 2) {
		if ((std::string)archivo_pasado[2] == "show" and argc == 3) {
			prueba1.mostrar_todo(archivo);
		} else if ((std::string)archivo_pasado[2] == "count") {
			std::cout << "lineas: " << prueba1.contar_lineas(archivo) << "\n";
			std::cout << "caracteres: " << prueba1.contar_caracteres(archivo) << "\n";
		} else if ((std::string)archivo_pasado[2] == "show" and argc > 3) {
			std::string busqueda = archivo_pasado[3];
			std::string linea_temp;
			prueba1.reiniciar_flujo(archivo);
			while (std::getline(archivo, linea_temp)) {
				if (linea_temp.find(busqueda) != std::string::npos) {
					imprimir_con_resaltado(linea_temp, busqueda);
				}
			}
		} else if ((std::string)archivo_pasado[2] == "hex") {
			std::string linea_temp;
			prueba1.reiniciar_flujo(archivo);
			while (std::getline(archivo, linea_temp)) {
				for(unsigned char c : linea_temp) {
					std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c) << " ";
				}
				std::cout << "\n";
			}
		} else if((std::string)archivo_pasado[2] == "rm") {
			prueba1.eliminar_archivo(archivo_pasado[1]);
		} else if((std::string)archivo_pasado[2]=="modify") {
			std::string linea_temp1;
			archivo.close();
			std::ofstream archivos_var(archivo_pasado[1], std::ios::app);
			while (std::getline(std::cin, linea_temp1)) {
				archivos_var << linea_temp1 << "\n";
			}
		}
	}
	return 0;
}
