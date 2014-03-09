pwd=`pwd`
cd ./server
CPP=server.cpp
gcc $CPP -o server -lstdc++ -g
cd $pwd

cd ./client
CPP=client.cpp
gcc $CPP -o client -lstdc++ -g
cd $pwd
