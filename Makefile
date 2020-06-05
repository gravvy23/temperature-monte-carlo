# WARNING: -fpermissive flag needed due to incorrect precedence 
# of template declaration and use in old-fashioned Orbacus code.
# WARNING: all warnings are disabled with -w flag.


ORBACUS_DIR = /opt/nfs/corba/OB
JTC_DIR     = $(ORBACUS_DIR)/jtc
LIB_PATH    = $(ORBACUS_DIR)/lib

all:  idl server client  # make all and strip executables to reduce their size
	@echo 'Stripping executables...'
	strip server
	strip client
	@echo 'CORBA server and client programs ready:'
	@ls -l --color server client
	@echo -e "Start Naming Service:\n LD_LIBRARY_PATH=$(LIB_PATH) $(ORBACUS_DIR)/bin/nameserv -OAport <port> &"
	@echo -e "Start Server:\n LD_LIBRARY_PATH=$(LIB_PATH) ./server -ORBnaming corbaloc:iiop:<host>:<port>/NameService <server_name> &"
	@echo -e "Start Client:\n LD_LIBRARY_PATH=$(LIB_PATH) ./client -ORBnaming corbaloc:iiop:<host>:<port>/NameService <server_name> <power>"


idl:    TemperatureDataInterface.idl  # create C++ interfaces from IDL file
	@echo 'Creating CORBA interfaces...'
	LD_LIBRARY_PATH=$(LIB_PATH) $(ORBACUS_DIR)/bin/idl TemperatureDataInterface.idl

server: idl temperature_server.cpp Temperature*.cpp *.c  # .cpp - server files, .c - solution
	@echo 'Compiling server...'
	c++ -w -fpermissive \
	-I. -I$(ORBACUS_DIR)/include \
	-L$(ORBACUS_DIR)/lib -o server \
	temperature_server.cpp Temperature*.cpp *.c \
	-lOB -lCosNaming -lJTC -ldl -lpthread

client: idl client*.cpp TestImplementation.* # client files
	@echo 'Compiling client...'
	c++ -w -fpermissive \
	-I. -I$(ORBACUS_DIR)/include -I$(ORBACUS_DIR)/include/JTC \
	-L$(ORBACUS_DIR)/lib -o client client-naming_service.cpp \
	TestInterface.cpp -lOB -lCosNaming -lJTC -ldl -lpthread

clean:  # remove executables and secondary files
	@echo 'Clearing files...'
	rm -f server client *Interface*.cpp *Interface*.h

	