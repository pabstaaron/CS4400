#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <elf.h>
#include <string.h> // I can't be using this when I turn it in

/* Given the in-memory ELF header pointer as `ehdr` and a section
   header pointer as `shdr`, returns a pointer to the memory that
   contains the in-memory content of the section */
#define AT_SEC(ehdr, shdr) ((void *)(ehdr) + (shdr)->sh_offset)

static void check_for_shared_object(Elf64_Ehdr *ehdr);
static void fail(char *reason, int err_code);

// Returns a pointer to the section header of the given section name.
Elf64_Shdr* getSectionByName(Elf64_Ehdr* ehdr, char* name){
  Elf64_Shdr *shdrs = (void*)ehdr + ehdr->e_shoff; // Gets the position of section header information.

  // Get the location of the string table, which will contain the human-readable section names.
  char* strs = (void*)ehdr+shdrs[ehdr->e_shstrndx].sh_offset;
  
  // Loop through all of the section headers
  for(int i = 0; i < ehdr->e_shnum; i++){
    // shdrs[i].sh_name contains the offset into the str table where the section name can be found.
    //printf("%s\n", strs + shdrs[i].sh_name);

    // Todo - What does strcmp return and when?
    if(strcmp(strs + shdrs[i].sh_name, name) == 0){ // If this section is the one we're looking for.
      printf("Section Name: %s\n", strs + shdrs[i].sh_name);
      printf("Offset: %d\n", sizeof(Elf64_Shdr) * i);
      return shdrs + sizeof(Elf64_Shdr) * i;
    }
  }
}

void parseSectionNames(Elf64_Ehdr* ehdr){
  Elf64_Shdr *shdrs = (void*)ehdr + ehdr->e_shoff; // Gets the position of section header information.

  // Get the location of the string table, which will contain the human-readable section names.
  char* strs = (void*)ehdr+shdrs[ehdr->e_shstrndx].sh_offset;
  
  // Loop through all of the section headers
  for(int i = 0; i < ehdr->e_shnum; i++){
    // shdrs[i].sh_name contains the offset into the str table where the section name can be found.
    printf("%s\n", strs + shdrs[i].sh_name);
  }
}

void parseFunctionNames(Elf64_Ehdr* ehdr){
  // Get the location of the dynsym section
  Elf64_Shdr *dynsym_shdr = getSectionByName(ehdr, ".dynsym");
  printf("%p\n", dynsym_shdr);
  
  Elf64_Sym *syms = AT_SEC(ehdr, dynsym_shdr);
  //printf("Made it past first AT_SEC call.");
  
  // Get the location of the string table, which will contain the function names
  char *strs = AT_SEC(ehdr, getSectionByName(ehdr, ".dynstr"));
  
  int i = 0, count = dynsym_shdr->sh_size / sizeof(Elf64_Sym);
  printf("%d\n", dynsym_shdr->sh_size);
  
  // Walk through the symbol table
  for (i = 0; i < count; i++) {
    printf("%s\n", strs + syms[i].st_name);
  }
}

int main(int argc, char **argv) {
  int fd;
  size_t len;
  void *p; 
  Elf64_Ehdr *ehdr; // pointer to the start of the ELF header

  if (argc != 2)
    fail("expected one file on the command line", 0);

  /* Open the shared-library file */
  fd = open(argv[1], O_RDONLY);
  if (fd == -1)
    fail("could not open file", errno);

  /* Find out how big the file is: */
  len = lseek(fd, 0, SEEK_END);

  /* Map the whole file into memory: */
  p = mmap(NULL, len, PROT_READ, MAP_PRIVATE, fd, 0);
  if (p == (void*)-1)
    fail("mmap failed", errno);

  /* Since the ELF file starts with an ELF header, the in-memory image
     can be cast to a `Elf64_Ehdr *` to inspect it: */
  ehdr = (Elf64_Ehdr *)p;  // 

  /* Check that we have the right kind of file: */
  check_for_shared_object(ehdr);

  /* Add a call to your work here */
  parseFunctionNames(ehdr);

  return 0;
}

static void check_for_shared_object(Elf64_Ehdr *ehdr) {
  if ((ehdr->e_ident[EI_MAG0] != ELFMAG0)
      || (ehdr->e_ident[EI_MAG1] != ELFMAG1)
      || (ehdr->e_ident[EI_MAG2] != ELFMAG2)
      || (ehdr->e_ident[EI_MAG3] != ELFMAG3))
    fail("not an ELF file", 0);

  if (ehdr->e_ident[EI_CLASS] != ELFCLASS64)
    fail("not a 64-bit ELF file", 0);
  
  if (ehdr->e_type != ET_DYN)
    fail("not a shared-object file", 0);
}

static void fail(char *reason, int err_code) {
  fprintf(stderr, "%s (%d)\n", reason, err_code);
  exit(1);
}
