#!/bin/sh
_QT5_DIR_=${1:-"/home/abencsik/QtCreator/5.12.0/gcc_64"}

pushd build

cmake -GNinja -DQt5_ROOT:PATH=${_QT5_DIR_} ../

popd