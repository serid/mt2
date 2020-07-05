void panic(char* msg);

void panic_errno(char* msg);

int assert_ne(int v, int antiexpected, char* msg);

int assert_ne_errno(int v, int antiexpected, char* msg);

int assert_nm1(int v, char* msg);

int assert_nm1_errno(int v, char* msg);

void* assert_pnnull(void* v, char* msg);

void* assert_pnm1(void* v, char* msg);

void* assert_pnm1_errno(void* v, char* msg);
