#include <stdio.h>

#include <ks_types.h>
#include <ks_datacont.h>
#include <ks_listnode.h>


static int ks_listnode_new_tests()
{
  int retval = 0;

  /* TEST 1 */
  ks_listnode* ln = ks_listnode_new(ks_datacont_new("A", KS_CHAR, 1));

  if (ln->next != NULL)
  {
    printf("TEST 1: ln->next should be NULL.\n");
    retval = -1;
  }
  if (ln->dc->c != 'A')
  {
    printf("TEST 1: Unexpected ks_datacont value: '%c'. Expected: 'A'.\n", ln->dc->c);
    retval = -1;
  }

  ks_listnode_delete(ln);

  return retval;
}


static int ks_listnode_copy_tests()
{
  int retval = 0;

  /* TEST 1 */
  ks_listnode* ln = ks_listnode_new(ks_datacont_new("A", KS_CHAR, 1));
  ks_listnode* ln_copy = ks_listnode_copy(ln);

  if (ln_copy == NULL)
  {
    printf("TEST 1: Unexpected NULL return from ks_listnode_copy().\n");
    retval = -1;
  }

  ks_listnode_delete(ln);
  ks_listnode_delete(ln_copy);

  return retval;
}


static int ks_listnode_copy_all_tests()
{
  int retval = 0;

  /* TEST 1 */
  ks_listnode* ln = ks_listnode_new(ks_datacont_new("A", KS_CHAR, 1));
  ln->next = ks_listnode_new(ks_datacont_new("B", KS_CHAR, 1));

  ks_listnode* ln_copy = ks_listnode_copy_all(ln);
  if (ln_copy == NULL)
  {
    printf("TEST 1: Unexpected NULL return from ks_listnode_copy().\n");
    return -1;
  }

  if (ln_copy->dc->c != 'A' || ln_copy->next->dc->c != 'B')
  {
    printf("TEST 1: Unexpected ks_datacont values after ks_listnode_copy_all()\n");
    retval = -1;
  }

  ks_listnode_delete_all(ln);
  ks_listnode_delete_all(ln_copy);

  return retval;
}


static int ks_listnode_add_tests()
{
  int retval = 0;

  /* TEST 1 */
  ks_datacont* dc = ks_datacont_new("B", KS_CHAR, 1);

  if (ks_listnode_add(NULL, dc) != -1)
  {
    printf("TEST 1: ks_listnode_add() with any NULL parameters should return -1\n");
    retval = -1;
  }

  /* TEST 2 */
  ks_listnode* ln = ks_listnode_new(ks_datacont_new("A", KS_CHAR, 1));
  if (ks_listnode_add(ln, dc) != 0)
  {
    printf("TEST 2: ks_listnode_add() should return 0 when successful");
    retval = -1;
  }

  if (ln->dc->c != 'A')
  {
    printf("TEST 2: unexpected ks_datacont value at first ks_listnode: %c. Expected: %c\n", ln->dc->c, 'A');
    retval = -1;
  }

  if (ln->next->dc->c != 'B')
  {
    printf("TEST 2: unexpected ks_datacont value at second ks_listnode: %c. Expected: %c\n", ln->next->dc->c, 'B');
    retval = -1;
  }
  
  ks_listnode_delete_all(ln);

  return retval;
}


static int ks_listnode_merge_tests()
{
  int retval = 0;

  /* TEST 1 */
  ks_listnode* lna = ks_listnode_new(ks_datacont_new("A", KS_CHAR, 1));
  ks_listnode* lnb = ks_listnode_new(ks_datacont_new("B", KS_CHAR, 1));

  lna = ks_listnode_merge(lna, lnb);

  if (ks_listnode_length(lna) != 2)
  {
    printf("TEST 1: Unexpected ks_listnode length after ks_listnode_merge()\n");
    retval = -1;
  }

  if (lna->dc->c != 'A' || lna->next->dc->c != 'B')
  {
    printf("TEST 1: Unexpected ks_datacont values after ks_listnode_merge()\n");
    retval = -1;
  }

  ks_listnode_delete_all(lna);

  return retval;
}


static int ks_listnode_remove_by_tests()
{
  int retval = 0;

  /* TEST 1 */
  ks_datacont* dcA = ks_datacont_new("A", KS_CHAR, 1);
  ks_datacont* dcB = ks_datacont_new("B", KS_CHAR, 1);
  ks_datacont* dcC = ks_datacont_new("C", KS_CHAR, 1);

  ks_listnode* ln = ks_listnode_new(ks_datacont_copy(dcA));
  ks_listnode_add(ln, ks_datacont_copy(dcB));
  ks_listnode_add(ln, ks_datacont_copy(dcC));

  if (ks_listnode_remove_by(&ln, dcC) != 1)
  {
    printf("TEST 1: ks_listnode_remove_by() should return 1 on successful removal\n");
    retval = -1;
  }

  /* TEST 2 */
  if (ks_listnode_remove_by(&ln, dcC) != 0)
  {
    printf("TEST 2: ks_listnode_remove_by() should return 0 when removing not-present ks_datacont\n");
    retval = -1;
  }

  /* TEST 3 */
  if (ks_listnode_remove_by(&ln, dcB) != 1)
  {
    printf("TEST 3: ks_listnode_remove_by() should return 1 on successful removal\n");
    retval = -1;
  }

  /* TEST 4 */
  if (ks_listnode_remove_by(&ln, dcA) != 1)
  {
    printf("TEST 4: ks_listnode_remove_by() should return 1 on successful removal\n");
    retval = -1;
  }

  if (ln != NULL)
  {
    printf("TEST 4: ks_listnode should be NULL after final removal\n");
    retval = -1;
  }

  /* TEST 5 */
  if (ks_listnode_remove_by(NULL, dcA) != -1)
  {
    printf("TEST 5: ks_listnode_remove_by() should return -1 when NULL params are passed\n");
    retval = -1;
  }

  ks_datacont_delete(dcA);
  ks_datacont_delete(dcB);
  ks_datacont_delete(dcC);

  return retval;
}


static int ks_listnode_remove_at_tests()
{
  int retval = 0;

  /* TEST 1 */
  ks_datacont* dcA = ks_datacont_new("A", KS_CHAR, 1);
  ks_datacont* dcB = ks_datacont_new("B", KS_CHAR, 1);
  ks_datacont* dcC = ks_datacont_new("C", KS_CHAR, 1);

  ks_listnode* ln = ks_listnode_new(ks_datacont_copy(dcA));
  ks_listnode_add(ln, ks_datacont_copy(dcB));
  ks_listnode_add(ln, ks_datacont_copy(dcC));

  if (ks_listnode_remove_at(&ln, -1) != 0)
  {
    printf("TEST 1: ks_listnode_remove_at() should return 0 on successful removal\n");
    retval = -1;
  }

  /* TEST 2 */
  if (ks_listnode_remove_at(&ln, 10) != -1)
  {
    printf("TEST 2: ks_listnode_remove_at() should return -1 on index OOB\n");
    retval = -1;
  }

  /* TEST 3 */
  if (ks_listnode_remove_at(&ln, 0) != 0)
  {
    printf("TEST 3: ks_listnode_remove_at() should return 0 on successful removal\n");
    retval = -1;
  }

  /* TEST 4 */
  if (ks_listnode_remove_at(&ln, -1) != 0)
  {
    printf("TEST 4: ks_listnode_remove_at() should return 0 on successful removal\n");
    retval = -1;
  }

  if (ln != NULL)
  {
    printf("TEST 4: ks_listnode should be NULL after final removal\n");
    retval = -1;
  }

  /* TEST 5 */
  if (ks_listnode_remove_at(&ln, 0) != -1)
  {
    printf("TEST 5: ks_listnode_remove_at() should return -1 when params are NULL\n");
    retval = -1;
  }

  ks_datacont_delete(dcA);
  ks_datacont_delete(dcB);
  ks_datacont_delete(dcC);

  return retval;
}


static int ks_listnode_remove_all_tests()
{
  int retval = 0;

  /* TEST 1 */
  ks_datacont* dcA = ks_datacont_new("A", KS_CHAR, 1);
  ks_datacont* dcB = ks_datacont_new("B", KS_CHAR, 1);
  ks_datacont* dcC = ks_datacont_new("C", KS_CHAR, 1);

  ks_listnode* ln = ks_listnode_new(ks_datacont_copy(dcA));
  ks_listnode_add(ln, ks_datacont_copy(dcB));
  ks_listnode_add(ln, ks_datacont_copy(dcA));
  ks_listnode_add(ln, ks_datacont_copy(dcC));
  ks_listnode_add(ln, ks_datacont_copy(dcA));

  int num;

  if ((num = ks_listnode_remove_all(&ln, dcA)) != 3)
  {
    printf("TEST 1: ks_listnode_remove_all() should return the number of nodes removed. Returned: %d. Expected: 3\n", num);
    retval = -1;
  }

  /* TEST 2 */
  if ((num = ks_listnode_remove_all(&ln, dcB)) != 1)
  {
    printf("TEST 2: ks_listnode_remove_all() should return the number of nodes removed. Returned: %d. Expected: 1\n", num);
    retval = -1;
  }

  /* TEST 3 */
  if ((num = ks_listnode_remove_all(&ln, dcB)) != 0)
  {
    printf("TEST 3: ks_listnode_remove_all() should return the number of nodes removed. Returned: %d. Expected: 0\n", num);
    retval = -1;
  }

  /* TEST 4 */
  if ((num = ks_listnode_remove_all(&ln, dcC)) != 1)
  {
    printf("TEST 4: ks_listnode_remove_all() should return the number of nodes removed. Returned: %d. Expected: 1\n", num);
    retval = -1;
  }

  if (ln != NULL)
  {
    printf("TEST 4: ks_listnode should be NULL after final removal\n");
    retval = -1;
  }

  /* TEST 5 */
  if (ks_listnode_remove_all(&ln, dcC) != -1)
  {
    printf("TEST 5: ks_listnode_remove_all() should return -1 when either param is NULL\n");
    retval = -1;
  }

  ks_datacont_delete(dcA);
  ks_datacont_delete(dcB);
  ks_datacont_delete(dcC);

  return retval;
}


static int ks_listnode_replace_by_tests()
{
  int retval = 0;

  /* TEST 1 */
  ks_datacont* get_dc;
  ks_datacont* dcA = ks_datacont_new("A", KS_CHAR, 1);
  ks_datacont* dcB = ks_datacont_new("B", KS_CHAR, 1);
  ks_datacont* dcC = ks_datacont_new("C", KS_CHAR, 1);

  ks_listnode* ln = ks_listnode_new(ks_datacont_copy(dcA));
  ks_listnode_add(ln, ks_datacont_copy(dcB));
  ks_listnode_add(ln, ks_datacont_copy(dcC));

  if (ks_listnode_replace_by(ln, dcB, ks_datacont_new("Z", KS_CHAR, 1)) != 0)
  {
    printf("TEST 1: ks_listnode_replace_by() should return 0 on successful replacement\n");
    retval = -1;
  }

  get_dc = ks_listnode_get(ln, 1);
  if (get_dc->c != 'Z')
  {
    printf("TEST 1: Unexpected ks_datacont value at 2nd ks_listnode following ks_listnode_replace_by(): %c. Expected Z\n", get_dc->c);
    retval = -1;
  }

  /* TEST 2 */
  if (ks_listnode_replace_by(ln, dcB, dcB) != -1)
  {
    printf("TEST 2: ks_listnode_replace_by() should return -1 when trying to remove not-present ks_datacont\n");
    retval = -1;
  }

  /* TEST 3 */
  if (ks_listnode_replace_by(NULL, NULL, NULL) != -1)
  {
    printf("TEST 3: ks_listnode_replace_by() should return -1 when params are NULL\n");
    retval = -1;
  }

  ks_listnode_delete_all(ln);
  ks_datacont_delete(dcA);
  ks_datacont_delete(dcB);
  ks_datacont_delete(dcC);

  return retval;
}


static int ks_listnode_replace_at_tests()
{
  int retval = 0;

  /* TEST 1 */
  ks_datacont* get_dc;
  ks_datacont* dcA = ks_datacont_new("A", KS_CHAR, 1);
  ks_datacont* dcB = ks_datacont_new("B", KS_CHAR, 1);
  ks_datacont* dcC = ks_datacont_new("C", KS_CHAR, 1);

  ks_listnode* ln = ks_listnode_new(ks_datacont_copy(dcA));
  ks_listnode_add(ln, ks_datacont_copy(dcB));
  ks_listnode_add(ln, ks_datacont_copy(dcC));

  if (ks_listnode_replace_at(ln, ks_datacont_new("Z", KS_CHAR, 1), 1) != 0)
  {
    printf("TEST 1: ks_listnode_replace_at() should return 0 on successful replacement\n");
    retval = -1;
  }
  
  get_dc = ks_listnode_get(ln, 1);
  if (get_dc->c != 'Z')
  {
    printf("TEST 1: Unexpected ks_datacont value at 2nd ks_listnode following ks_listnode_replace_at(): %c. Expected Z\n", get_dc->c);
    retval = -1;
  }

  /* TEST 2 */
  if (ks_listnode_replace_at(ln, dcB, 10) != -1)
  {
    printf("TEST 2: ks_listnode_replace_at() should return -1 when index is OOB\n");
    retval = -1;
  }

  /* TEST 3 */
  if (ks_listnode_replace_at(NULL, NULL, 0) != -1)
  {
    printf("TEST 3: ks_listnode_replace_at() should return -1 when params are NULL\n");
    retval = -1;
  }

  ks_listnode_delete_all(ln);
  ks_datacont_delete(dcA);
  ks_datacont_delete(dcB);
  ks_datacont_delete(dcC);

  return retval;
}


static int ks_listnode_replace_all_tests()
{
  int retval = 0;

  /* TEST 1 */
  ks_datacont* get_dc;
  ks_datacont* dcA = ks_datacont_new("A", KS_CHAR, 1);
  ks_datacont* dcB = ks_datacont_new("B", KS_CHAR, 1);
  ks_datacont* dcC = ks_datacont_new("C", KS_CHAR, 1);

  ks_listnode* ln = ks_listnode_new(ks_datacont_copy(dcA));
  ks_listnode_add(ln, ks_datacont_copy(dcB));
  ks_listnode_add(ln, ks_datacont_copy(dcA));
  ks_listnode_add(ln, ks_datacont_copy(dcC));
  ks_listnode_add(ln, ks_datacont_copy(dcA));

  if (ks_listnode_replace_all(ln, dcA, ks_datacont_new("Z", KS_CHAR, 1)) != 3)
  {
    printf("TEST 1: ks_listnode_replace_all() should return the number of replacements that occurred\n");
    retval = -1;
  }

  get_dc = ks_listnode_get(ln, -1);
  if (get_dc->c != 'Z')
  {
    printf("TEST 1: Unexpected ks_datacont value in last node after ks_listnode_replace_all(): %c. Expected: Z\n", get_dc->c);
    retval = -1;
  }

  /* TEST 2 */
  if (ks_listnode_replace_all(ln, dcA, get_dc) != 0)
  {
    printf("TEST 2: ks_listnode_replace_all() should return 0 when replacing not-present ks_datacont value\n");
    retval = -1;
  }

  ks_listnode_delete_all(ln);
  ks_datacont_delete(dcA);
  ks_datacont_delete(dcB);
  ks_datacont_delete(dcC);

  return retval;
}


static int ks_listnode_insert_tests()
{
  int retval = 0;

  /* TEST 1 */
  ks_datacont* dcA = ks_datacont_new("A", KS_CHAR, 1);
  ks_datacont* dcB = ks_datacont_new("B", KS_CHAR, 1);
  ks_datacont* dcC = ks_datacont_new("C", KS_CHAR, 1);
  ks_datacont* get_dc;
  
  ks_listnode* ln = ks_listnode_new(ks_datacont_copy(dcA));
  ks_listnode_add(ln, ks_datacont_copy(dcC));

  if (ks_listnode_insert(&ln, ks_datacont_copy(dcB), 0) != 0)
  {
    printf("TEST 1: ks_listnode_insert() should return 0 on successful insertion\n");
    retval = -1;
  }

  get_dc = ks_listnode_get(ln, 0); 
  if (get_dc->c != 'B')
  {
    printf("TEST 1: Unexpected ks_datacont value at first ks_listnode after ks_listnode_insert(): %c. Expected B\n", get_dc->c);
    retval = -1;
  }

  /* TEST 2 */
  if (ks_listnode_insert(&ln, ks_datacont_copy(dcB), -1) != 0)
  {
    printf("TEST 2: ks_listnode_insert() should return 0 on successful insertion\n");
    retval = -1;
  }
 
  get_dc = ks_listnode_get(ln, -2);
  if (get_dc->c != 'B')
  {
    printf("TEST 2: Unexpected ks_datacont value at 2nd to last ks_listnode after ks_listnode_insert(): %d. Expected: B\n", get_dc->c);
    retval = -1;
  }

  /* TEST 3 */
  if (ks_listnode_insert(&ln, NULL, 2) != -1)
  {
    printf("TEST 3: ks_listnode_insert() should return -1 when any params are NULL\n");
    retval = -1;
  }

  ks_listnode_delete_all(ln);
  ks_datacont_delete(dcA);
  ks_datacont_delete(dcB);
  ks_datacont_delete(dcC);

  return retval;
}


static int ks_listnode_index_tests()
{
  int retval = 0;

  /* TEST 1 */
  ks_datacont* dcA = ks_datacont_new("A", KS_CHAR, 1);
  ks_datacont* dcB = ks_datacont_new("B", KS_CHAR, 1);
  ks_datacont* dcC = ks_datacont_new("C", KS_CHAR, 1);

  ks_listnode* ln = ks_listnode_new(ks_datacont_copy(dcA));
  ks_listnode_add(ln, dcB);
  ks_listnode_add(ln, dcC);
  ks_listnode_add(ln, dcA);

  int index;

  if ((index = ks_listnode_index(ln, dcA)) != 0)
  {
    printf("TEST 1: Unexpected index for ks_datacont value 'A': %d. Expected: 0\n", index);
    retval = -1;
  }

  /* TEST 2 */
  if ((index = ks_listnode_index(ln, dcB)) != 1)
  {
    printf("TEST 2: Unexpected index for ks_datacont value 'B': %d. Expected: 1\n", index);
    retval = -1;
  }

  /* TEST 3 */
  if ((index = ks_listnode_index(ln, dcC)) != 2)
  {
    printf("TEST 3: Unexpected index for ks_datacont value 'C': %d. Expected: 2\n", index);
    retval = -1;
  }

  ks_listnode_delete_all(ln);
  
  return retval;
}


static int ks_listnode_get_tests()
{
  int retval = 0;

  /* TEST 1 */
  ks_listnode* ln = ks_listnode_new(ks_datacont_new("A", KS_CHAR, 1));
  ks_listnode_add(ln, ks_datacont_new("B", KS_CHAR, 1));
  ks_listnode_add(ln, ks_datacont_new("C", KS_CHAR, 1));

  ks_datacont* dcC = ks_listnode_get(ln, 2);
  if (dcC->c != 'C')
  {
    printf("TEST 1: Unexpected return value: %c. Expected: C\n", dcC->c);
    retval = -1;
  }

  /* TEST 2 */
  ks_datacont* dcA = ks_listnode_get(ln, 0);
  if (dcA->c != 'A')
  {
    printf("TEST 2: Unexpected return value: %c. Expected: A\n", dcA->c);
    retval = -1;
  }

  /* TEST 3 */
  ks_datacont* dcB = ks_listnode_get(ln, 1);
  if (dcB->c != 'B')
  {
    printf("TEST 3: Unexpected return value: %c. Expected: B\n", dcB->c);
    retval = -1;
  }
  
  ks_listnode_delete_all(ln);

  return retval;
}


static int ks_listnode_count_tests()
{
  int retval = 0;

  /* TEST 1 */
  ks_datacont* dcA = ks_datacont_new("A", KS_CHAR, 1);
  ks_datacont* dcB = ks_datacont_new("B", KS_CHAR, 1);

  ks_listnode* ln = ks_listnode_new(ks_datacont_copy(dcA));
  ks_listnode_add(ln, ks_datacont_copy(dcA));
  ks_listnode_add(ln, ks_datacont_copy(dcB));
  ks_listnode_add(ln, ks_datacont_copy(dcA));

  int count;

  if ((count = ks_listnode_count(ln, dcA)) != 3)
  {
    printf("TEST 1: Unexpected ks_listnode_count() result: %d. Expected: 3\n", count);
    retval = -1;
  }

  /* TEST 2 */
  if ((count = ks_listnode_count(ln, dcB)) != 1)
  {
    printf("TEST 2: Unexpected ks_listnode_count() result: %d. Expected: 1\n", count);
    retval = -1;
  }

  ks_listnode_delete_all(ln);
  ks_datacont_delete(dcA);
  ks_datacont_delete(dcB);

  return retval;
}


static int ks_listnode_length_tests()
{
  int retval = 0;

  /* TEST 1 */
  ks_datacont* dc = ks_datacont_new("A", KS_CHAR, 1);
  ks_listnode* ln = ks_listnode_new(ks_datacont_copy(dc));
  ks_listnode_add(ln, ks_datacont_copy(dc));
  ks_listnode_add(ln, ks_datacont_copy(dc));

  int len;
  if ((len = ks_listnode_length(ln)) != 3)
  {
    printf("TEST 1: Unexpected ks_listnode_length() result: %d. Expected: 3\n", len);
    retval = -1;
  }

  ks_listnode_delete_all(ln);
  ks_datacont_delete(dc);
  
  return retval;
}


int main()
{
  int retval = 0;

  printf("\nks_listnode tests:\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_listnode_new_tests()...\n");
  if (ks_listnode_new_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_listnode_copy_tests()...\n");
  if (ks_listnode_copy_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_listnode_copy_all_tests()...\n");
  if (ks_listnode_copy_all_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_listnode_add_tests()...\n");
  if (ks_listnode_add_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_listnode_merge_tests()...\n");
  if (ks_listnode_merge_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_listnode_remove_by_tests()...\n");
  if (ks_listnode_remove_by_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_listnode_remove_at_tests()...\n");
  if (ks_listnode_remove_at_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_listnode_remove_all_tests()...\n");
  if (ks_listnode_remove_all_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_listnode_replace_by_tests()...\n");
  if (ks_listnode_replace_by_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_listnode_replace_at_tests()...\n");
  if (ks_listnode_replace_at_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_listnode_replace_all_tests()...\n");
  if (ks_listnode_replace_all_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_listnode_insert_tests()...\n");
  if (ks_listnode_insert_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_listnode_index_tests()...\n");
  if (ks_listnode_index_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_listnode_get_tests()...\n");
  if (ks_listnode_get_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_listnode_count_tests()...\n");
  if (ks_listnode_count_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_listnode_length_tests()...\n");
  if (ks_listnode_length_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  return retval;
}

