#!/bin/bash
echo "Inicio la creación del ejecutable client"
cd cliente
make clean
make
cd ..
echo "Finalizo la creación del ejecutable client"

echo "Inicio la creación del ejecutable server"
cd servidor
make clean
make
cd ..
echo "Finalizo la creación del ejecutable server"

echo "Inicio la creación de archivos intermedios de utils"
cd utils
make clean
make
cd ..
echo "Finalizo la creación de archivos intermedios de utils"
