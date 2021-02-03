#variables
CC=gcc
CFLAGS=-O2 -Wall -c
LDFLAGS=-O2 -L/usr/lib/x86_64-linux-gnu/ -lniflexrioapi -lNiFpga -lpthread -ldl

EXE=flexrio_test

#syntax :
# TARGET : DEPEDENCIES
#	COMMANDS
#
# $@ >> variable for target	,	$^ >> variable for dependencies
# $(..) >> .. = variable name

#executable
$(EXE) : NiFpga.o NiFpga_IF_5764_FPGA.o getstarted.o flexrio_test.o      
	$(CC) -o $@ $^ $(LDFLAGS)
	make clean

#sources
flexrio_test.o : flexrio_test.c 
	$(CC) $(CFLAGS) $^

getstarted.o: getstarted.c
	$(CC) $(CFLAGS) $^

NiFpga_IF_5764_FPGA.o: NiFpga_IF_5764_FPGA.c 
	$(CC) $(CFLAGS) $^	

NiFpga.o: NiFpga.c
	$(CC) $(CFLAGS) $^

#cleaning
clean:
	rm -f *.o $(EXE)