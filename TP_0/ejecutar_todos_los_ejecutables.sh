#!/bin/bash

# Función para ejecutar un comando en una nueva terminal y mantenerla abierta
function ejecutar_en_terminal {
    gnome-terminal -- bash -c "$1; exec bash"
}

# Entrar en la carpeta server
cd server || exit
# Abrir una nueva terminal y ejecutar ./bin/server
ejecutar_en_terminal "./bin/server"
# Volver a la carpeta inicial
cd ..

# Entrar en la carpeta client
cd client || exit
# Abrir una nueva terminal y ejecutar ./bin/cpu
ejecutar_en_terminal "./bin/client"
# Volver a la carpeta inicial
cd ..
