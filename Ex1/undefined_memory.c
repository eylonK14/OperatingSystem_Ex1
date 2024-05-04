int main (int argc, char *argv[]) 
{
    int* p = (int*) 0xdeadbeef;
    *p = 1;

	return 0;
}