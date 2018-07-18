all:clean client server

export PATH=/home/linux/project/newWifi/staging_dir/toolchain-mipsel_1004kc+dsp_gcc-4.8-linaro_uClibc-0.9.33.2/bin/:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/root/bin:/root/bin:/root/bin
OPENWRT_CPP := mipsel-openwrt-linux-g++
CPP := g++


client:
	${CPP} -o client -g -O0 -w client.cpp

server:
	${OPENWRT_CPP} -o server -g -O0 -w server.cpp

clean:
	rm -f client 
	rm -f server
