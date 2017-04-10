all:clean client server

client:
	g++ -o client -g -O0 -w client.cpp -levent

server:
	g++ -o server -g -O0 -w -fpermissive server.cpp -levent

clean:
	rm -f client 
	rm -f server
