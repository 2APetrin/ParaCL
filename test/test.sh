#!/bin/bash

obj="build/ParaCL"

test_files_names=( "00.prcl" "01.prcl" "02.prcl" "03.prcl" "04.prcl" "05.prcl" "06.prcl" "07.prcl" "08.prcl" "09.prcl" "10.prcl" "11.prcl" "12.prcl")
tests_folder="test/simple/"

for i in ${!test_files_names[@]}; do
    echo
    ${obj} ${tests_folder}${test_files_names[$i]}
done