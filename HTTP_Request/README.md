# HTTP_Request modules

HTTP Request를 파싱하는 모듈입니다.<br>
기본적인 헤더의 정의 및 헤더 테이블 관리 등을 다룹니다.<br>

## 1. sc_header_table.h

- strcut sc_header_table_t
HTTP Header들의 정보를 다루기 위한 구조체입니다. 연결리스트 형태로 데이터가 저장됩니다.

| 멤버 | 설명 |
|-----|------|
| key | 헤더의 유형 (Content-Length, Host) |
| value | 헤더의 값 |
| next | 다음 노드 |

- 헤더의 키와 값을 분리
```
void sc_line_seperate(char* line, char key[], char value[]);
```

- 헤더 테이블의 노드를 생성
```
sc_header_table_t* sc_header_create(char key[], char value[]); 
```

- 헤더 테이블에 노드를 추가
```
void sc_header_table_append(header_table **root, header_table *new_header);
``` 


## 2. sc_request_type.h

- struct sc_http_request_t
HTTP Request의 정보를 저장한 구조체입니다.

| 멤버 | 설명 |
|-----|------|
| Method| HTTP Method를 다룹니다.(GET, POST 등)|
| URL  | URL 정보를 다룹니다.(/home, /post.cgi?name=hello) |
| Version | HTTP 버전정보를 다룹니다. |
| header | Header들의 정보를 Header table의 형태로 키와 값의 형태로 저장합니다. |
| Body   | HTTP의 실질적인 데이터 부분(Body)를 다룹니다. |


## 3. sc_content_type.h

- struct sc_content_type_t
Content-Type 헤더 부분에 들어갈 데이터의 키와 값을 정의합니다.

| 멤버 | 설명 |
|-----|------|
| extension | 확장자 명입니다. 키에 해당합니다. |
| mime_type  | Content-Type에 들어갈 데이터를 다루는 부분입니다. 값에 해당합니다. |


- struct content_type content_type_list
Content-Type에 관련된 테이블을 다룹니다.


## 4. sc_http_method.h

- sc_http_method_table
Status-Line부분의 Method를 다루는 테이블입니다.


## 5. sc_http_version.h

- sc_http_version_table
Status-Line부분의 Version을 다루는 테이블입니다.


## 6. sc_request_check.h

- 유효한 Method인지 체크
```
int sc_method_check(char *method);
```

- 유효한 Version인지 체크
```
int sc_version_check(char* version);
```

- 지원가능한 content_type인지 체크
```
int sc_content_type_check(char *type);
```

## 7. sc_request_parser.h

- HTTP Request의 Header와 Body를 분리시킴
```
void sc_header_body_seperate(char* req_stream, char* header, char* body);
```

- Content-Length의 정보를 정수로 바꿔줌 (Wrapping)
```
int sc_content_length_get(char *contentLength);
```

- Status-Line 부분을 분리시킴 (method, url, version)
```
int sc_status_line_seperate(char* line, char* method, char* url, char* version);
```

- Request 내용을 읽어서 분리시킨 후 HTTPRequest구조체에 정보를 저장 <br>
 url은 파싱 후 sc_url_t 구조체에 저장
```
int sc_request_reader (char* req_stream, sc_http_request_t* req, sc_url_t* _url);
```

## 8. sc_url_parser.h

- sc_url_arguement_t
url의 arguement의 정보를 저장한 구조체입니다.

| 멤버 | 설명 |
|-----|------|
| key | Arguement의 이름 정보를 가집니다. |
| value | Arguement의 값을 가집니다. |
| next | Arguement들을 연결리스트로 관리하기 위해 만든 포인터입니다.|


- sc_url_t
url의 정보를 저장한 구조체입니다.

| 멤버 | 설명 |
|-----|------|
| url | Arguement의 이름 정보를 가집니다. |
| value | Arguement의 값을 가집니다. |
| next | Arguement들을 연결리스트로 관리하기 위해 만든 포인터입니다.|


- strtok로 나눌 때 사용한 포인터를 문자열로 바꿔줍니다. (arr) 
```
void sc_string_getter(char* p, char arr[]);
```

- Arguement단을 키와 값으로 나눕니다.
```
void sc_arg_seperate(char* line, char key[], char value[]);
```

- Arguement 노드를 생성합니다.
```
sc_url_arguement_t* sc_url_arguement_create (char key[], char value[]);
```

- Arguement 노드를 연결합니다.
```
void sc_arguement_append(sc_url_arguement_t** root, sc_url_arguement_t* new_arguement);
```

- url Arguement을 분리시켜서 url 구조체에 저장합니다.
```
int sc_url_arguement_parser(char* arguments, sc_url_t* url);
```

- url 전체를 경로와 매개변수로 나눕니다.
```
int sc_url_parse (char* str, sc_url_t* url);
```
