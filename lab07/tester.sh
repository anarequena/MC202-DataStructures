#Testador Laboratorios de MC202 por Nicholas Okita
#Atualizado em (21/10/15)

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
		sudo apt-get update
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
	echo "Lembrando que os arquivos devem ser nomeados: main.c, lab07.c, lab07.h e devem "
	echo "estar na mesma pasta do testador"
	echo "Saindo..."
}

#Verifica o numero de argumentos
if [[ $1 == "" ]]; then
	echo "Usage: ./tester.sh *numero do lab*"
	echo "Exemplo: ./tester.sh 07"
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
else if [[ ! -f "lab07.h" ]]; then
	fileNotFound
	exit
else if [[ ! -f "lab07.c" ]]; then
	fileNotFound
	exit
fi
fi
fi


#Copia o lab para o diretorio de testes
cp lab07.c testes/
cp lab07.h testes/
cp main.c testes/

#Entra no diretorio de testes
cd testes

#Compila o programa
echo "Compilando..."6
gcc *.c -o test -std=c99
if [ $? -ne 0 ]; then
	echo "Erro de compilacao. Verifique seu programa e tente novamente."
	echo "Saindo..."
	exit
fi

#Baixando arquivos de testes
for ((i=1 ; i <= 16 ; i++)); do
	arq="arq$(printf '%02i' $i)"
	if [ ! -f "$arq.in" ]; then
		echo "Baixando teste $i"
		curl -k https://susy.ic.unicamp.br:9999/mc202ab/$1/dados/$arq.in > $arq.in -s
	fi
	if [ ! -f "$arq.res" ]; then
		echo "Baixando resposta do teste $i"
		curl -k https://susy.ic.unicamp.br:9999/mc202ab/$1/dados/$arq.res > $arq.res -s
	fi
done

echo "Executando..."
erros=0;
for ((i=1 ; i <= 16 ; i++)); do
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
		for ((i=1 ; i <= 16 ; i++)); do
			echo "Test $i"
			arq="arq$(printf '%02i' $i)"
			valout=$(valgrind -q --leak-check=full ./test < $arq.in > $arq.out)			
			if [[ $valout == "" ]]; then
				echo "Não foram encontrados erros nesse teste!"
				echo "Testar proximo caso?"
				echo "[ 1 ] Sim"
				echo "[ 2 ] Nao"
				read next
				if [[ $next == 2 ]]; then
					clear
					exit
				fi
			else
				echo "Erro encontrado no valgrind..."
				echo "Terminando testes..."
				echo ""
				echo ""
				exit
			fi	
		done
	fi
fi

exit
