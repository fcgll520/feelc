all:clean client server

client:
	gcc -o client -g -O0 -w -Wall client.c -levent

server:
	gcc -o server -g -O0 -w -Wall server.c -levent

clean:
	rm -f client 
	rm -f server
