#Testador Laboratorios de MC202 por Nicholas Okita (23/08/15)

#!/bin/bash

#Funcao para instalar o curl
function installCurl {
	echo "Curl nao esta instalado"
	which apt-get 2>/dev/null && packManager=1
	which yum 2>/dev/null && packManager=2
	which zypper 2>/dev/null && packManager=3
	which pacman 2>/dev/null && packManager=4

	case $packManager in
		1)
		echo "Instalando..."
		sudo apt-get install curl
		;;

		2)
		echo "Instalando..."
		sudo yum install curl
		;;

		3)
		echo "Instalando..."
		sudo zypper install curl
		;;

		4)
		echo "Instalando..."
		sudo pacman -S curl
		;;

		*)
		echo "Seu package manager nao foi encontrado."
		echo "Por favor instale manualmente o pacote curl"
		exit
		;;
	esac
}

#Funcao erro de arquivo nao encontrado
function fileNotFound {
	echo "Arquivos de lab nao encontrados. Por favor verifique os nomes dos arquivos."
	echo "Lembrando que os arquivos devem ser nomeado: main.c, pilha.c, pilha.h, matrioshka.c"
	echo "matrioshka.h e estarem na mesma pasta do testador"
	echo "Saindo..."
}

#Verifica o numero de argumentos
if [[ $1 == "" ]]; then
	echo "Usage: ./tester.sh *numero do lab*"
	echo "Exemplo: ./tester.sh 02"
	exit
fi

#Verifica o comando curl
which curl > /dev/null || installCurl

#Verifica a existencia do diretorio tests
if [ ! -d "testes" ]; then
	echo "Criando diretorio de testes"
	mkdir testes/
fi

#Verifica a existencia dos arquivos de lab
if [[ ! -f "main.c" ]]; then
	fileNotFound
	exit
else if [[ ! -f "matrioshka.h" ]]; then
	fileNotFound
	exit
else if [[ ! -f "pilha.h" ]]; then
	fileNotFound
	exit
fi
fi
fi


#Copia o lab para o diretorio de testes
cp main.c testes/
cp pilha.h testes/
cp pilha.c testes/
cp matrioshka.h testes/
cp matrioshka.c testes/

#Entra no diretorio de testes
cd testes

#Compila o programa
echo "Compilando..."
gcc main.c matrioshka.c pilha.c -o test
if [ $? -ne 0 ]; then
	echo "Erro de compilacao. Verifique seu programa e tente novamente."
	echo "Saindo..."
	exit
fi

#Baixando arquivos de testes
if [ ! -f "arq01.in" ]; then
	echo "Baixando testes..."
fi
for ((i=1 ; i <= 15 ; i++)); do
	arq="arq$(printf '%02i' $i)"
	if [ ! -f "$arq.in" ]; then
		curl -k https://susy.ic.unicamp.br:9999/mc202ab/$1/dados/$arq.in -o $arq.in 2>/dev/null
	fi
	if [ ! -f "$arq.res" ]; then
		curl -k https://susy.ic.unicamp.br:9999/mc202ab/$1/dados/$arq.res > $arq.res 2>/dev/null
	fi
done

echo "Executando..."
erros=0;
for ((i=1 ; i <= 15 ; i++)); do
	echo "Test $i"
	arq="arq$(printf '%02i' $i)"
	./test < $arq.in > $arq.out
	echo "Difference:"
	diff $arq.out $arq.res
	comp=$(diff $arq.out $arq.res)
	if [[ $comp != "" ]]; then
		erros=$(($erros+1))
	fi
done

echo "Total de erros: $erros"
echo ""
echo ""

if [[ $erros == 0 ]]; then
	echo "Gostaria de testar para o Valgrind?"
	echo "[ 1 ] Sim"
	echo "[ 2 ] Nao"
	read val
	if [[ $val == 1 ]]; then
		for ((i=1 ; i <= 15 ; i++)); do
			echo "Test $i"
			arq="arq$(printf '%02i' $i)"
			valgrind --leak-check=full ./test < $arq.in > $arq.out
			echo "Testar proximo caso?"
			echo "[ 1 ] Sim"
			echo "[ 2 ] Nao"
			read next
			if [[ $next == 2 ]]; then
				clear
				exit
			fi
		done
	fi
fi

exit
