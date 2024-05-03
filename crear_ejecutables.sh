#!/bin/bash
echo "Inicio la creación del ejecutable client"
cd client
make clean
make
cd ..
echo "Finalizo la creación del ejecutable client"

echo "Inicio la creación del ejecutable server"
cd server
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
