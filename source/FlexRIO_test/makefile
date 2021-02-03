#variables
CC=gcc
CFLAGS=-O2 -Wall
LDFLAGS=-O2 -L/usr/lib/x86_64-linux-gnu/ -lniflexrioapi -lniriosession -lpthread

#executable
# flexrio_test.o getstarted.o NiFpga_IF_5764_FPGA.o NiFpga.o
flexrio_test : NiFpga.o NiFpga_IF_5764_FPGA.o getstarted.o flexrio_test.o      
	$(CC) -o flexrio_test NiFpga.o NiFpga_IF_5764_FPGA.o getstarted.o flexrio_test.o  


#sources

flexrio_test.o : flexrio_test.c
	$(CC) $(CFLAGS) $(LDFLAGS) flexrio_test.c 

getstarted.o: getstarted.c
	$(CC) $(CFLAGS) getstarted.c 

NiFpga_IF_5764_FPGA.o: NiFpga_IF_5764_FPGA.c
	$(CC) $(CFLAGS) NiFpga_IF_5764_FPGA.c 	

NiFpga.o: NiFpga.c
	$(CC) $(CFLAGS) NiFpga.c 




#cleaning
clean:
	rm -f *.o flexrio_test