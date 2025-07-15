Simulación Geant4: SolarSim ☀️Este proyecto usa Geant4 para simular el efecto de la radiación solar sobre la piel, con y sin la protección de una sombrilla.RequisitosGeant4CMakePython 3 (con pandas, matplotlib, numpy)Cómo Usar1. CompilarDesde la carpeta raíz del proyecto:mkdir build
cd build
cmake ..
make
cd ..
2. SimularEjecuta la simulación desde la carpeta raíz:# Sintaxis: ./build/SolarSim <con|sin> [archivo.mac]
Simulación Geant4: SolarSim ☀️Este proyecto usa Geant4 para simular el efecto de la radiación solar sobre la piel, con y sin la protección de una sombrilla.RequisitosGeant4CMakePython 3 (con pandas, matplotlib, numpy)Cómo Usar1. CompilarDesde la carpeta raíz del proyecto:mkdir build
cd build
cmake ..
make
cd ..
2. SimularEjecuta la simulación desde la carpeta raíz:# Sintaxis: ./build/SolarSim <con|sin> [archivo.mac]

# Ejemplo CON sombrilla
./build/SolarSim con run.mac

# Ejemplo SIN sombrilla
./build/SolarSim sin run.mac
Esto generará los archivos de datos .csv en el directorio raíz.3. AnalizarEjecuta el script de Python para generar los gráficos:# Reemplaza 'tu_script_de_analisis.py' con el nombre real de tu archivo
python tu_script_de_analisis.py
Las imágenes se guardarán automáticamente en la carpeta graficos/.
# Ejemplo CON sombrilla
./build/SolarSim con run.mac

# Ejemplo SIN sombrilla
./build/SolarSim sin run.mac
Esto generará los archivos de datos .csv en el directorio raíz.3. AnalizarEjecuta el script de Python para generar los gráficos:# Reemplaza 'tu_script_de_analisis.py' con el nombre real de tu archivo
python tu_script_de_analisis.py
Las imágenes se guardarán automáticamente en la carpeta graficos/.