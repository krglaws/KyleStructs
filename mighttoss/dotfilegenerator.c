
/* these will have to be re-written */

/*
static void _generate_dotfile(const treenode* tn)
{
  if (tn->right)
  {
    printf("%s->%s[color=red];\n", tn->dc, tn->right->word);
    _generate_dotfile(tn->right);
  }
  if (tn->left)
  {
    printf("%s->%s[color=blue];\n", tn->dc, tn->left->word);
    _generate_dotfile(tn->left);
  }
}


void generate_dotfile(const treenode* tn)
{
  if (tn)
  {
    printf("%s;\n", tn->dc);
    if (tn->right)
    {
      printf("%s->%s[color=red];\n", tn->dc, tn->right->word);
      _generate_dotfile(tn->right);
    }
    if (tn->left)
    {
      printf("%s->%s[color=blue];\n", tn->dc, tn->left->word);
      _generate_dotfile(tn->left);
    }
  }
  else printf("NULL;\n");
}
*/
