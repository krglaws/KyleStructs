#include <stdio.h>
#include <string.h>
#include <kylestructs.h>


int main()
{
  ks_hashmap* phonebook = ks_hashmap_new(KS_CHARP, 10);
  const ks_datacont* number_dc;
  const ks_datacont* name_dc;

  char number[30] = {0};
  char name[30] = {0};

  printf("Enter a name followed by a 10-digit phone number:\n");

  while (scanf("%s %s", name, number) != -1)
  {
    number_dc = ks_datacont_new(number, KS_CHARP, strlen(number));
    name_dc = ks_datacont_new(name, KS_CHARP, strlen(name));

    if (ks_hashmap_add(phonebook, number_dc, name_dc) == 1)
      printf("Replaced existing number %s.\n", number);

    memset(number, 0, 30);
    memset(name, 0, 30);
  }

  int count = ks_hashmap_count(phonebook);

  for (int i = 0; i < count; i++)
  {
    number_dc = ks_hashmap_get_key(phonebook, i);
    name_dc = ks_hashmap_get(phonebook, number_dc);

    printf("%s => %s\n", number_dc->cp, name_dc->cp);
  }

  ks_hashmap_delete(phonebook);
}
