# GameMathematics
Jogo de matemática destinado a crianças de 5° ano envolvendo as 4 operações 

Para executar o jogo é necessário estar em um ambiente Linux

* Requerimentos de instalação para poder executar as animações do jogo:

    - boxes
    - sl
    - cowsay

* Na distribuição Ubuntu os comandos de instalação são os seguintes:

    - sudo apt update
    - sudo apt install boxes
    - sudo apt install cowsay
    - sudo apt install sl

* Caso precise compilar o arquivo sem o uso de uma IDE, utilize o compilador g++ :

    - g++ main.cpp -o GameMath -lpthread

* Comandos para instalar o g++ no Ubuntu:

    - sudo apt update
    - sudo apt install g++
    
Jogo desenvolvido na linguagem de programação C++, utilizando threads para execução
simultânea de processos, como trabalho extra da disciplina de Fundamentos da Computação

Vídeo explicando o funcionamento do jogo: https://youtu.be/PmwCVWXLer4