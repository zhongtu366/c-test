
decode-nginx:
	g++ decode-nginx.cc base64.c  -o decode-nginx


PYTHON:clean
clean:
	rm decode-nginx
