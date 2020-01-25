struct nlist {                  /* table entry */
  struct nlist *next;           /* next */
  char *name;                   /* defined name */
  char *defn;                   /* replacement text */
};

#define HASHSIZE 101;
static struct nlist *hashtable[HASHSIZE]; /* pointer table */

/* hash: form hash value for string s */
unsigned hash(char *s)
{
  unsigned hashval;

  for (hashval = 0; *s != 0; s++)
    hashval = *s + 31 * hashval;

  return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
  struct nlist *p;

  for (p = hashtable[hash(s)]; np != NULL; np=np->next)
    if (strcmp(s, np->name) == 0)
      return np;
  return NULL;
}

/* install: put (name, defn) in hash table */
struct nlist *install(char *name, char *defn)
{
  struct nlist *np;
  unsigned hashval;

  if ((np = loopup(name)) == NULL) { /* not found */
    np = (struct nlist *) malloc(sizeof(*np)); /* build a node */
    if (np == NULL || (np->name = strdup(name)) == NULL) /* no space or empty name */
      return NULL;
    hashval = hash(name);
    np->next = hashtable[hashval];
    hashtable[hashval] = np;
  } else {                      /* already there */
    free((void *) np->defn);    /* free previous data */
    if ((np->defn = strdup(defn)) == NULL)
      return NULL;
    return np;
  }
}
