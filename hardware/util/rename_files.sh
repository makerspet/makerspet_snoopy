#!/bin/bash

# Clean up Fusion 360 3MF, STL long file names after export
sudo apt update && sudo apt install rename
find . -type f \( -name  '*.3mf' -o  -iname '*.stl' \) -exec rename 's/Snoopy v126_Snoopy v126_//g' {} +
find . -type f \( -name  '*.3mf' -o  -iname '*.stl' \) -exec rename 's/Bottom plate v155_1_//g' {} +
find . -type f \( -name  '*.3mf' -o  -iname '*.stl' \) -exec rename 's/Top plate v71_1_//g' {} +
find . -type f \( -name  '*.3mf' -o  -iname '*.stl' \) -exec rename 's/Bumper assembly v43_1_//g' {} +
find . -type f \( -name  '*.3mf' -o  -iname '*.stl' \) -exec rename 's/Bumper sensor assembly_Bumper assembly v43_//g' {} +
find . -type f \( -name  '*.3mf' -o  -iname '*.stl' \) -exec rename 's/Motion_1_//g' {} +
find . -type f \( -name  '*.3mf' -o  -iname '*.stl' \) -exec rename 's/65mm blue wheel 4mm ID shaft adapter v4_2_//g' {} +
find . -type f \( -name  '*.3mf' -o  -iname '*.stl' \) -exec rename 's/Bumper sensor assembly_1_//g' {} +
find . -type f \( -name  '*.3mf' -o  -iname '*.stl' \) -exec rename 's/Cliff sensors_1_//g' {} +
find . -type f \( -name  '*.3mf' -o  -iname '*.stl' \) -exec rename 's/Battery pack v50_1_//g' {} +
find . -type f \( -name  '*.3mf' -o  -iname '*.stl' \) -exec rename 's/Cliff sensor v21_1_//g' {} +
find . -type f \( -name  '*.3mf' -o  -iname '*.stl' \) -exec rename 's/Caster wheel assembly v24_1_//g' {} +
find . -type f \( -name  '*.3mf' -o  -iname '*.stl' \) -exec rename 's/Battery array_1_//g' {} +
find . -type f \( -name  '*.3mf' -o  -iname '*.stl' \) -exec rename 's/Bumper sensor assembly\(Mirror\)_1_//g' {} +
find . -type f \( -name  '*.3mf' -o  -iname '*.stl' \) -exec rename 's/Bumper sensor assembly\(Mirror\)_//g' {} +
find . -type f \( -name  '*.3mf' -o  -iname '*.stl' \) -exec rename 's/Bumper assembly v43_//g' {} +
find . -type f \( -name  '*.3mf' -o  -iname '*.stl' \) -exec rename 's/Head_1_//g' {} +
find . -type f \( -name  '*.3mf' -o  -iname '*.stl' \) -exec rename 's/Middle plate v85_1_//g' {} +
find . -type f \( -name  '*.3mf' -o  -iname '*.stl' \) -exec rename 's/YDLidar X4 assembly v41_1_//g' {} +
find . -type f \( -name  '*.3mf' -o  -iname '*.stl' \) -exec rename 's/ /_/g' {} +
find . -type f \( -name  '*.3mf' -o  -iname '*.stl' \) -exec rename -f 'y/A-Z/a-z/' {} +
# find . -type f \( -name  '*.3mf' -o  -iname '*.stl' \) -exec rename 's///g' {} +
