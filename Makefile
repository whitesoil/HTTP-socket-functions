run : 
	g++ -ggdb -g -O0 -I opt/apr-1.6.3/include/apr-1 -Iopt/apr-util-1.6.1/include/apr-1 -L opt/apr-1.6.3 -L opt/apr-util-1.6.1 -lapr-1 -laprutil-1 test.c HTTP_Connection/sc_http_connection.h HTTP_Request/src/sc_request_parser.h HTTP_Response/sc_http_response_constructor.h
