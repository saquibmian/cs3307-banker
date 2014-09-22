all: build 

build:
	cd Banker; g++ *.cpp -o banker; cd ..;
