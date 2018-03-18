GENERATED=minmax_clnt.c minmax.h minmax_xdr.c minmax_svc.c
BIN=minmax_server minmax_client

all: ${BIN}

strip: all
	strip ${BIN}

.c.o:
	g++ -std=c++11 -lpthread -c $<

minmax_server: ${GENERATED} minmax_server.o minmax_xdr.o minmax_svc.o
	g++ -std=c++11 -lpthread -o $@ minmax_server.o minmax_xdr.o minmax_svc.o

minmax_client: ${GENERATED} minmax_client.o minmax_xdr.o minmax_clnt.o
	g++ -std=c++11 -lpthread -o $@ minmax_client.o minmax_xdr.o minmax_clnt.o

${GENERATED}: minmax.x
	rpcgen minmax.x

clean:
	rm -f ${GENERATED} ${BIN} *.o core 
