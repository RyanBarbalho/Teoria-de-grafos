#!/bin/bash

# Binários
prim=./prim.bin
kruskal=./kruskal.bin
dijkstra=./dijkstra.bin


echo "Testando algoritmo de Kruskal"
for i in instances/*.mtx
do
	echo -e "\e[33mInstância $i\e[0m";
	val=$($kruskal -f $i);
	correto=$(grep $i gabarito_agm.txt | cut -d ' ' -f 2);
	[ $val -eq $correto ] && echo -e "Custo \e[32mOK\e[0m" || echo  -e "\e[31mCusto incorreto\e[0m";

	$kruskal -f $i -s | sed -e 's/ /\n/g' -e 's/,/ /g' -e 's/[()]//g' | ./agm $i
	if [ $? -eq 0 ]; then
		echo -e "\e[32mOK\e[0m"
	else
		echo -e "\e[31mNão é um subgrafo\e[0m";
	fi

done


echo -e "\n\n";

echo "Testando algoritmo de Prim"
for i in instances/*.mtx
do
	echo -e "\e[33mInstância $i\e[0m";
	val=$($prim -f $i);
	correto=$(grep $i gabarito_agm.txt | cut -d ' ' -f 2);
	[ $val -eq $correto ] && echo -e "Custo \e[32mOK\e[0m" || echo  -e "\e[31mCusto incorreto\e[0m";

	$prim -f $i -s | sed -e 's/ /\n/g' -e 's/,/ /g' -e 's/[()]//g' | ./agm $i
	if [ $? -eq 0 ]; then
		echo -e "\e[32mOK\e[0m"
	else
		echo -e "\e[31mNão é um subgrafo\e[0m";
	fi

done


echo "Testando algoritmo de Dijkstra"
for i in instances/*.mtx
do
	echo -e "\e[33mInstância $i\e[0m";
	$dijkstra -f $i > temp;

	j=$(basename $i);
	diff -w temp ./sp/$j > /dev/null ;
	
	if [ $? -eq 0 ]; then
		echo -e "\e[32mOK\e[0m"
	else
		echo -e "\e[31mErro\e[0m";
	fi
	rm temp;

done
