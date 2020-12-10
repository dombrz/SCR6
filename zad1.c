#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
int main()

{

  char nazwa_pliku[100];
  
  int fd_plik;
  int fd_map;
  struct stat rozmiar_pliku;
  char *adres=NULL;
  


  while(1)
    {
      printf("Podaj nazwę pliku \n" );
      scanf("%s", nazwa_pliku);
      fd_plik = open(nazwa_pliku, O_RDONLY);
      printf("\n");
      stat(nazwa_pliku, &rozmiar_pliku);
      //printf("%d", rozmiar_pliku.st_size);

      fd_map=open("/home/dominik/SCR/tekst2.txt", O_RDWR);
      ftruncate(fd_map, rozmiar_pliku.st_size);
      adres=mmap(NULL, rozmiar_pliku.st_size, PROT_WRITE | PROT_READ, MAP_SHARED, fd_map, 0);

      

      read(fd_plik, adres, rozmiar_pliku.st_size);
       msync(adres, rozmiar_pliku.st_size,MS_SYNC);
       close(fd_plik);
      close(fd_map);
     
    }



}
