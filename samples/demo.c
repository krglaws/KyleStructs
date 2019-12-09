
#include <stdio.h>
#include <kylestructs.h>


int main()
{
  hashmap* phonebook = hashmap_new(CHARP, 10);
  datacont* number_dc;
  datacont* name_dc;

  char number[30] = {0};
  char name[30] = {0};
  
  printf("Enter a name followed by a 10-digit phone number:\n");

  while (scanf("%s %s", name, number) != -1) {

    datacont* number_dc = datacont_new(number, CHARP, strlen(number));
    datacont* name_dc = datacont_new(name, CHARP, strlen(name));

    if (hashmap_add(phonebook, number_dc, name_dc) == 1)
      printf("Replaced existing number %s.\n", number);

    memset(number, 0, 30);
    memset(name, 0, 30);
  }

  int count = hashmap_count(phonebook);

  list* numbers = hashmap_keys(phonebook);
  list* names = hashmap_values(phonebook);

  for (int i = 0; i < count; i++)
  {
    number_dc = list_get(numbers, i);
    name_dc = list_get(names, i);

    printf("%s => %s\n", number_dc->cp, name_dc->cp);
  }

  hashmap_delete(phonebook);
  list_delete(numbers);
  list_delete(names);
}

