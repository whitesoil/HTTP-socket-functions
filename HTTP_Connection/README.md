# HTTP Connection

## http_socket.h

### Function
- Connection setup, return client socket
```
int sc_connection_setup(int argc, char *argv[]);
```

- Exiting with Ctrl-C
```
void sc_signal_setup();
```

- Processing request parse and response construct
```
void * sc_http_proc(apr_thread_t * thd, void * data)
```
