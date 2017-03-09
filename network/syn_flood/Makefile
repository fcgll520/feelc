all:client server

client:clean
	gcc -o client_flood -g -O0 -w -Wall -Werror client.c

server:
	gcc -o server_flood -g -O0 -w -Wall -Werror server.c

clean:
	rm -f client_flood 
	rm -f server_flood
