# MemorySimulator (MMU)

Simulador de:
1. Traducción de direcciones virtuales a físicas con **paginación de 1 nivel** (también se deja extendible a segmentación).
2. Reemplazo de páginas con **FIFO**, **LRU** y **OPT**.

## Build (Windows / local)
Recomendado: `g++` con C++17.

```bash
cd MemorySimulator
g++ -std=c++17 -O2 -Isrc -o mmu.exe \
  src/main.cpp \
  src/core/Simulator.cpp \
  src/translation/AddressTranslator.cpp \
  src/io/FileReader.cpp \
  src/io/ConfigParser.cpp \
  src/ui/Menu.cpp \
  src/replacement/FIFO.cpp \
  src/replacement/LRU.cpp \
  src/replacement/OPT.cpp

./mmu.exe
```

## Docker
Esta carpeta incluye `Dockerfile` y `docker-compose.yml`.

### Ejecutar con docker-compose
Desde la raíz:
```bat
docker compose -f MemorySimulator/docker-compose.yml up --build
```

### Ejecutar directo (alternativa)
Desde la raiz:
```bat
docker build -t mmu-sim .
docker run -it mmu-sim
```

### Nota
Si Docker Desktop no está corriendo, los comandos fallarán con error de conexión al motor de Docker.

## Run (ejemplos)
- Traducción:
  - `examples/translation1.txt`
- Reemplazo:
  - `examples/replacement1.txt`

En el menú se indica qué archivo cargar.


## Nota de formato de entrada
Los formatos están documentados en los archivos de `examples/`.

# Autor
Juan Pablo Lozano Restrepo - 2521505

