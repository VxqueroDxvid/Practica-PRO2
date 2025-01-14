OPCIONS2 = -std=c++11
OPCIONS1 = -std=c++11 -D_GLIBCXX_DEBUG
OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

program.exe: program.o Proceso.o Procesador.o Cluster.o Prioridad.o Area_procesos.o
	g++ -o program.exe program.o Proceso.o Procesador.o Cluster.o Prioridad.o Area_procesos.o

Proceso.o:  Proceso.cc Proceso.hh
	g++ -c Proceso.cc $(OPCIONS)

Procesador.o:  Procesador.cc Procesador.hh Proceso.hh
	g++ -c Procesador.cc $(OPCIONS)

Cluster.o:  Cluster.cc Cluster.hh Procesador.hh Proceso.hh
	g++ -c Cluster.cc $(OPCIONS)

Prioridad.o:  Prioridad.cc Prioridad.hh Cluster.hh Proceso.hh
	g++ -c Prioridad.cc $(OPCIONS)

Area_procesos.o: Area_procesos.cc Area_procesos.hh Prioridad.hh Cluster.hh
	g++ -c Area_procesos.cc $(OPCIONS)

program.o: program.cc Cluster.hh Area_procesos.hh Prioridad.hh Procesador.hh Proceso.hh
	g++ -c program.cc $(OPCIONS)

clean:
	rm *.o
	rm *.exe