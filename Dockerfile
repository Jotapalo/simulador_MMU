FROM gcc:13
WORKDIR /app
COPY . /app
RUN g++ -std=c++17 -O2 -Isrc -o mmu \
  src/main.cpp \
  src/core/Simulator.cpp \
  src/translation/AddressTranslator.cpp \
  src/io/FileReader.cpp \
  src/io/ConfigParser.cpp \
  src/ui/Menu.cpp \
  src/replacement/FIFO.cpp \
  src/replacement/LRU.cpp \
  src/replacement/OPT.cpp
CMD ["./mmu"]

