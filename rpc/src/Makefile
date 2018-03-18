GENERATED=vocabulary_clnt.c vocabulary.h vocabulary_xdr.c vocabulary_svc.c
BIN=vocabulary_server vocabulary_client

all: ${BIN}

strip: all
	strip ${BIN}

.c.o:
	gcc -c $<

vocabulary_server: ${GENERATED} vocabulary_server.o vocabulary_xdr.o vocabulary_svc.o server_jobs.o list.o
	gcc -pthread -o $@ vocabulary_server.o vocabulary_xdr.o vocabulary_svc.o server_jobs.o list.o

vocabulary_client: ${GENERATED} vocabulary_client.o vocabulary_xdr.o vocabulary_clnt.o
	gcc -pthread -o $@ vocabulary_client.o vocabulary_xdr.o vocabulary_clnt.o

${GENERATED}: vocabulary.x
	rpcgen vocabulary.x

clean:
	rm -f ${GENERATED} ${BIN} *.o core 
