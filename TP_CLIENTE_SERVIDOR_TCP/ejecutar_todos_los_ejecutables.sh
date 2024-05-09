#!/bin/bash

# Función para ejecutar un comando en una nueva terminal y mantenerla abierta
function ejecutar_en_terminal {
    gnome-terminal -- bash -c "$1; exec bash"
}

# Entrar en la carpeta server
cd servidor || exit
# Abrir una nueva terminal y ejecutar ./bin/server
ejecutar_en_terminal "./bin/servidor"
# Volver a la carpeta inicial
cd ..

# Entrar en la carpeta client
cd cliente || exit
# Abrir una nueva terminal y ejecutar ./bin/cpu
ejecutar_en_terminal "./bin/cliente"
# Volver a la carpeta inicial
cd ..
