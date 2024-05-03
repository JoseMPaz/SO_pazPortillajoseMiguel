#!/bin/bash

# Función para ejecutar un comando en una nueva terminal y mantenerla abierta
function ejecutar_en_terminal {
    gnome-terminal -- bash -c "$1; exec bash"
}

# Entrar en la carpeta memoria
cd memoria || exit

# Abrir una nueva terminal y ejecutar ./bin/memoria
ejecutar_en_terminal "./bin/memoria"

# Volver a la carpeta inicial
cd ..

# Entrar en la carpeta cpu
cd cpu || exit

# Abrir una nueva terminal y ejecutar ./bin/cpu
ejecutar_en_terminal "./bin/cpu"

# Volver a la carpeta inicial
cd ..

# Entrar en la carpeta kernel
cd kernel || exit

# Abrir una nueva terminal y ejecutar ./bin/kernel
ejecutar_en_terminal "./bin/kernel"

# Volver a la carpeta inicial
cd ..

# Entrar en la carpeta entradasalida
cd entradasalida || exit

# Abrir una nueva terminal y ejecutar ./bin/entradasalida
ejecutar_en_terminal "./bin/entradasalida"

# Volver a la carpeta inicial
cd ..
