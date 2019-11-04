
#include <stdio.h>

#include "../src/include/datacont.h"
#include "../src/include/list.h"
#include "../src/include/list.h"


static int list_new_tests()
{
  int retval = 0;

  /* TEST 1 */
  list* ls = list_new();
  list_add(ls, datacont_new("A", CHAR, 1));

  if (ln->next != NULL)
  {
    printf("TEST 1: ln->next should be NULL.\n");
    retval = -1;
  }
  if (ln->dc->c != 'A')
  {
    printf("TEST 1: Unexpected datacont value: '%c'. Expected: 'A'.\n", ln->dc->c);
    retval = -1;
  }

  list_delete(ln);

  return retval;
}


static int list_add_tests()
{
  int retval = 0;

  /* TEST 1 */
  datacont* dc = datacont_new("B", CHAR, 1);

  if (list_add(NULL, dc) != -1)
  {
    printf("TEST 1: list_add() with any NULL parameters should return -1\n");
    retval = -1;
  }

  /* TEST 2 */
  list* ls = list_new(datacont_new("A", CHAR, 1));
  if (list_add(ln, dc) != 0)
  {
    printf("TEST 2: list_add() should return 0 when successful");
    retval = -1;
  }

  if (ln->dc->c != 'A')
  {
    printf("TEST 2: unexpected datacont value at first list: %c. Expected: %c\n", ln->dc->c, 'A');
    retval = -1;
  }

  if (ln->next->dc->c != 'B')
  {
    printf("TEST 2: unexpected datacont value at second list: %c. Expected: %c\n", ln->next->dc->c, 'B');
    retval = -1;
  }
  
  list_delete_all(ln);

  return retval;
}


static int list_remove_by_tests()
{
  int retval = 0;

  /* TEST 1 */
  datacont* dcA = datacont_new("A", CHAR, 1);
  datacont* dcB = datacont_new("B", CHAR, 1);
  datacont* dcC = datacont_new("C", CHAR, 1);

  list* ls = list_new(datacont_copy(dcA));
  list_add(ln, datacont_copy(dcB));
  list_add(ln, datacont_copy(dcC));

  if (list_remove_by(&ln, dcC) != 1)
  {
    printf("TEST 1: list_remove_by() should return 1 on successful removal\n");
    retval = -1;
  }

  /* TEST 2 */
  if (list_remove_by(&ln, dcC) != 0)
  {
    printf("TEST 2: list_remove_by() should return 0 when removing not-present datacont\n");
    retval = -1;
  }

  /* TEST 3 */
  if (list_remove_by(&ln, dcB) != 1)
  {
    printf("TEST 3: list_remove_by() should return 1 on successful removal\n");
    retval = -1;
  }

  /* TEST 4 */
  if (list_remove_by(&ln, dcA) != 1)
  {
    printf("TEST 4: list_remove_by() should return 1 on successful removal\n");
    retval = -1;
  }

  if (ln != NULL)
  {
    printf("TEST 4: list should be NULL after final removal\n");
    retval = -1;
  }

  /* TEST 5 */
  if (list_remove_by(NULL, dcA) != -1)
  {
    printf("TEST 5: list_remove_by() should return -1 when NULL params are passed\n");
    retval = -1;
  }

  datacont_delete(dcA);
  datacont_delete(dcB);
  datacont_delete(dcC);

  return retval;
}


static int list_remove_at_tests()
{
  int retval = 0;

  /* TEST 1 */
  datacont* dcA = datacont_new("A", CHAR, 1);
  datacont* dcB = datacont_new("B", CHAR, 1);
  datacont* dcC = datacont_new("C", CHAR, 1);

  list* ls = list_new(datacont_copy(dcA));
  list_add(ln, datacont_copy(dcB));
  list_add(ln, datacont_copy(dcC));

  if (list_remove_at(&ln, -1) != 0)
  {
    printf("TEST 1: list_remove_at() should return 0 on successful removal\n");
    retval = -1;
  }

  /* TEST 2 */
  if (list_remove_at(&ln, 10) != -1)
  {
    printf("TEST 2: list_remove_at() should return -1 on index OOB\n");
    retval = -1;
  }

  /* TEST 3 */
  if (list_remove_at(&ln, 0) != 0)
  {
    printf("TEST 3: list_remove_at() should return 0 on successful removal\n");
    retval = -1;
  }

  /* TEST 4 */
  if (list_remove_at(&ln, -1) != 0)
  {
    printf("TEST 4: list_remove_at() should return 0 on successful removal\n");
    retval = -1;
  }

  if (ln != NULL)
  {
    printf("TEST 4: list should be NULL after final removal\n");
    retval = -1;
  }

  /* TEST 5 */
  if (list_remove_at(&ln, 0) != -1)
  {
    printf("TEST 5: list_remove_at() should return -1 when params are NULL\n");
    retval = -1;
  }

  datacont_delete(dcA);
  datacont_delete(dcB);
  datacont_delete(dcC);

  return retval;
}


static int list_remove_all_tests()
{
  int retval = 0;

  /* TEST 1 */
  datacont* dcA = datacont_new("A", CHAR, 1);
  datacont* dcB = datacont_new("B", CHAR, 1);
  datacont* dcC = datacont_new("C", CHAR, 1);

  list* ls = list_new(datacont_copy(dcA));
  list_add(ln, datacont_copy(dcB));
  list_add(ln, datacont_copy(dcA));
  list_add(ln, datacont_copy(dcC));
  list_add(ln, datacont_copy(dcA));

  int num;

  if ((num = list_remove_all(&ln, dcA)) != 3)
  {
    printf("TEST 1: list_remove_all() should return the number of nodes removed. Returned: %d. Expected: 3\n", num);
    retval = -1;
  }

  /* TEST 2 */
  if ((num = list_remove_all(&ln, dcB)) != 1)
  {
    printf("TEST 2: list_remove_all() should return the number of nodes removed. Returned: %d. Expected: 1\n", num);
    retval = -1;
  }

  /* TEST 3 */
  if ((num = list_remove_all(&ln, dcB)) != 0)
  {
    printf("TEST 3: list_remove_all() should return the number of nodes removed. Returned: %d. Expected: 0\n", num);
    retval = -1;
  }

  /* TEST 4 */
  if ((num = list_remove_all(&ln, dcC)) != 1)
  {
    printf("TEST 4: list_remove_all() should return the number of nodes removed. Returned: %d. Expected: 1\n", num);
    retval = -1;
  }

  if (ln != NULL)
  {
    printf("TEST 4: list should be NULL after final removal\n");
    retval = -1;
  }

  /* TEST 5 */
  if (list_remove_all(&ln, dcC) != -1)
  {
    printf("TEST 5: list_remove_all() should return -1 when either param is NULL\n");
    retval = -1;
  }

  datacont_delete(dcA);
  datacont_delete(dcB);
  datacont_delete(dcC);

  return retval;
}


static int list_replace_by_tests()
{
  int retval = 0;

  /* TEST 1 */
  datacont* get_dc;
  datacont* dcA = datacont_new("A", CHAR, 1);
  datacont* dcB = datacont_new("B", CHAR, 1);
  datacont* dcC = datacont_new("C", CHAR, 1);

  list* ls = list_new(datacont_copy(dcA));
  list_add(ln, datacont_copy(dcB));
  list_add(ln, datacont_copy(dcC));

  if (list_replace_by(ln, dcB, datacont_new("Z", CHAR, 1)) != 0)
  {
    printf("TEST 1: list_replace_by() should return 0 on successful replacement\n");
    retval = -1;
  }

  get_dc = list_get(ln, 1);
  if (get_dc->c != 'Z')
  {
    printf("TEST 1: Unexpected datacont value at 2nd list following list_replace_by(): %c. Expected Z\n", get_dc->c);
    retval = -1;
  }
  datacont_delete(get_dc);

  /* TEST 2 */
  if (list_replace_by(ln, dcB, dcB) != -1)
  {
    printf("TEST 2: list_replace_by() should return -1 when trying to remove not-present datacont\n");
    retval = -1;
  }

  /* TEST 3 */
  if (list_replace_by(NULL, NULL, NULL) != -1)
  {
    printf("TEST 3: list_replace_by() should return -1 when params are NULL\n");
    retval = -1;
  }

  list_delete_all(ln);
  datacont_delete(dcA);
  datacont_delete(dcB);
  datacont_delete(dcC);

  return retval;
}


static int list_replace_at_tests()
{
  int retval = 0;

  /* TEST 1 */
  datacont* get_dc;
  datacont* dcA = datacont_new("A", CHAR, 1);
  datacont* dcB = datacont_new("B", CHAR, 1);
  datacont* dcC = datacont_new("C", CHAR, 1);

  list* ls = list_new(datacont_copy(dcA));
  list_add(ln, datacont_copy(dcB));
  list_add(ln, datacont_copy(dcC));

  if (list_replace_at(ln, datacont_new("Z", CHAR, 1), 1) != 0)
  {
    printf("TEST 1: list_replace_at() should return 0 on successful replacement\n");
    retval = -1;
  }
  
  get_dc = list_get(ln, 1);
  if (get_dc->c != 'Z')
  {
    printf("TEST 1: Unexpected datacont value at 2nd list following list_replace_at(): %c. Expected Z\n", get_dc->c);
    retval = -1;
  }
  datacont_delete(get_dc);

  /* TEST 2 */
  if (list_replace_at(ln, dcB, 10) != -1)
  {
    printf("TEST 2: list_replace_at() should return -1 when index is OOB\n");
    retval = -1;
  }

  /* TEST 3 */
  if (list_replace_at(NULL, NULL, 0) != -1)
  {
    printf("TEST 3: list_replace_at() should return -1 when params are NULL\n");
    retval = -1;
  }

  list_delete_all(ln);
  datacont_delete(dcA);
  datacont_delete(dcB);
  datacont_delete(dcC);

  return retval;
}


static int list_replace_all_tests()
{
  int retval = 0;

  /* TEST 1 */
  datacont* get_dc;
  datacont* dcA = datacont_new("A", CHAR, 1);
  datacont* dcB = datacont_new("B", CHAR, 1);
  datacont* dcC = datacont_new("C", CHAR, 1);

  list* ls = list_new(datacont_copy(dcA));
  list_add(ln, datacont_copy(dcB));
  list_add(ln, datacont_copy(dcA));
  list_add(ln, datacont_copy(dcC));
  list_add(ln, datacont_copy(dcA));

  if (list_replace_all(ln, dcA, datacont_new("Z", CHAR, 1)) != 3)
  {
    printf("TEST 1: list_replace_all() should return the number of replacements that occurred\n");
    retval = -1;
  }

  get_dc = list_get(ln, -1);
  if (get_dc->c != 'Z')
  {
    printf("TEST 1: Unexpected datacont value in last node after list_replace_all(): %c. Expected: Z\n", get_dc->c);
    retval = -1;
  }

  /* TEST 2 */
  if (list_replace_all(ln, dcA, get_dc) != 0)
  {
    printf("TEST 2: list_replace_all() should return 0 when replacing not-present datacont value\n");
    retval = -1;
  }

  list_delete_all(ln);
  datacont_delete(get_dc);
  datacont_delete(dcA);
  datacont_delete(dcB);
  datacont_delete(dcC);

  return retval;
}


static int list_insert_tests()
{
  int retval = 0;

  /* TEST 1 */
  datacont* dcA = datacont_new("A", CHAR, 1);
  datacont* dcB = datacont_new("B", CHAR, 1);
  datacont* dcC = datacont_new("C", CHAR, 1);
  datacont* get_dc;
  list* ls = list_new(datacont_copy(dcA));
  list_add(ln, datacont_copy(dcC));

  if (list_insert(&ln, datacont_copy(dcB), 0) != 0)
  {
    printf("TEST 1: list_insert() should return 0 on successful insertion\n");
    retval = -1;
  }

  get_dc = list_get(ln, 0); 
  if (get_dc->c != 'B')
  {
    printf("TEST 1: Unexpected datacont value at first list after list_insert(): %c. Expected B\n", get_dc->c);
    retval = -1;
  }
  datacont_delete(get_dc);

  /* TEST 2 */
  if (list_insert(&ln, datacont_copy(dcB), -1) != 0)
  {
    printf("TEST 2: list_insert() should return 0 on successful insertion\n");
    retval = -1;
  }
 
  get_dc = list_get(ln, -2);
  if (get_dc->c != 'B')
  {
    printf("TEST 2: Unexpected datacont value at 2nd to last list after list_insert(): %d. Expected: B\n", get_dc->c);
    retval = -1;
  }
  datacont_delete(get_dc); 

  /* TEST 3 */
  if (list_insert(&ln, NULL, 2) != -1)
  {
    printf("TEST 3: list_insert() should return -1 when any params are NULL\n");
    retval = -1;
  }

  list_delete_all(ln);
  datacont_delete(dcA);
  datacont_delete(dcB);
  datacont_delete(dcC);

  return retval;
}


static int list_index_tests()
{
  int retval = 0;

  /* TEST 1 */
  datacont* dcA = datacont_new("A", CHAR, 1);
  datacont* dcB = datacont_new("B", CHAR, 1);
  datacont* dcC = datacont_new("C", CHAR, 1);

  list* ls = list_new(datacont_copy(dcA));
  list_add(ln, dcB);
  list_add(ln, dcC);
  list_add(ln, dcA);

  int index;

  if ((index = list_index(ln, dcA)) != 0)
  {
    printf("TEST 1: Unexpected index for datacont value 'A': %d. Expected: 0\n", index);
    retval = -1;
  }

  /* TEST 2 */
  if ((index = list_index(ln, dcB)) != 1)
  {
    printf("TEST 2: Unexpected index for datacont value 'B': %d. Expected: 1\n", index);
    retval = -1;
  }

  /* TEST 3 */
  if ((index = list_index(ln, dcC)) != 2)
  {
    printf("TEST 3: Unexpected index for datacont value 'C': %d. Expected: 2\n", index);
    retval = -1;
  }

  list_delete_all(ln);
  
  return retval;
}


static int list_get_tests()
{
  int retval = 0;

  /* TEST 1 */
  list* ls = list_new(datacont_new("A", CHAR, 1));
  list_add(ln, datacont_new("B", CHAR, 1));
  list_add(ln, datacont_new("C", CHAR, 1));

  datacont* dcC = list_get(ln, 2);
  if (dcC->c != 'C')
  {
    printf("TEST 1: Unexpected return value: %c. Expected: C\n", dcC->c);
    retval = -1;
  }

  /* TEST 2 */
  datacont* dcA = list_get(ln, 0);
  if (dcA->c != 'A')
  {
    printf("TEST 2: Unexpected return value: %c. Expected: A\n", dcA->c);
    retval = -1;
  }

  /* TEST 3 */
  datacont* dcB = list_get(ln, 1);
  if (dcB->c != 'B')
  {
    printf("TEST 3: Unexpected return value: %c. Expected: B\n", dcB->c);
    retval = -1;
  }

  list_delete_all(ln);
  datacont_delete(dcA);
  datacont_delete(dcB);
  datacont_delete(dcC);

  return retval;
}


static int list_count_tests()
{
  int retval = 0;

  /* TEST 1 */
  datacont* dcA = datacont_new("A", CHAR, 1);
  datacont* dcB = datacont_new("B", CHAR, 1);
  list* ls = list_new(datacont_copy(dcA));
  list_add(ln, datacont_copy(dcA));
  list_add(ln, datacont_copy(dcB));
  list_add(ln, datacont_copy(dcA));

  int count;

  if ((count = list_count(ln, dcA)) != 3)
  {
    printf("TEST 1: Unexpected list_count() result: %d. Expected: 3\n", count);
    retval = -1;
  }

  /* TEST 2 */
  if ((count = list_count(ln, dcB)) != 1)
  {
    printf("TEST 2: Unexpected list_count() result: %d. Expected: 1\n", count);
    retval = -1;
  }

  list_delete_all(ln);
  datacont_delete(dcA);
  datacont_delete(dcB);

  return retval;
}


static int list_length_tests()
{
  int retval = 0;

  /* TEST 1 */
  datacont* dc = datacont_new("A", CHAR, 1);
  list* ls = list_new(datacont_copy(dc));
  list_add(ln, datacont_copy(dc));
  list_add(ln, datacont_copy(dc));

  int len;
  if ((len = list_length(ln)) != 3)
  {
    printf("TEST 1: Unexpected list_length() result: %d. Expected: 3\n", len);
    retval = -1;
  }

  list_delete_all(ln);
  datacont_delete(dc);
  
  return retval;
}


int main()
{
  int retval = 0;

  printf("\nlist tests:\n\n");

  printf("==-----------------------------------==\n");
  printf("Running list_new_tests()...\n");
  if (list_new_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running list_add_tests()...\n");
  if (list_add_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running list_remove_by_tests()...\n");
  if (list_remove_by_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running list_remove_at_tests()...\n");
  if (list_remove_at_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running list_remove_all_tests()...\n");
  if (list_remove_all_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running list_replace_by_tests()...\n");
  if (list_replace_by_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running list_replace_at_tests()...\n");
  if (list_replace_at_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running list_replace_all_tests()...\n");
  if (list_replace_all_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running list_insert_tests()...\n");
  if (list_insert_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running list_index_tests()...\n");
  if (list_index_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running list_get_tests()...\n");
  if (list_get_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running list_count_tests()...\n");
  if (list_count_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running list_length_tests()...\n");
  if (list_length_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  return retval;
}

