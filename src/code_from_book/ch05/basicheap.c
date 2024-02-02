/*basicheap.c*/
int
main(int argc, char** argv) {
        char *buf;
        char *buf2;
  buf=(char*)malloc(1024);
  buf2=(char*)malloc(1024);
  printf("buf=%p buf2=%p\n",buf,buf2);
  strcpy(buf,argv[1]);
  free(buf2);
}
