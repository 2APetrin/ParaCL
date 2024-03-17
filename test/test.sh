#!/bin/bash

project_dir=$(dirname "$(realpath $0)")/..

obj=${project_dir}/build/ParaCL

tests_folder=${project_dir}/test/simple/

test_files_names=( "01.prcl" "02.prcl" "03.prcl" "04.prcl" "05.prcl" "06.prcl" "07.prcl" "08.prcl" "09.prcl" "10.prcl" "11.prcl" "12.prcl" "13.prcl" "14.prcl" "15.prcl")


for i in ${!test_files_names[@]}; do
    echo
    ${obj} ${tests_folder}${test_files_names[$i]}
done
