NoArvBinaria *buscaArvBinRec(NoArvBinaria *raiz, int k)
{
	if(raiz == NULL)
		return NULL;

	if(raiz->chave == k)
		return raiz;

	if(raiz->chave < k)
		buscaArvBinRec(raiz->dir, k);
	else
		buscaArvBinRec(raiz->esq, k);

}


NoArvBinaria *insereArvBinRec(NoArvBinaria **raiz, int k)
{
	if(*raiz == NULL)	/
	{
		*raiz = (NoArvBinaria *) malloc (sizeof(NoArvBinaria));
        if(*raiz == NULL)
			return NULL;

		(*raiz)->chave = k;
		(*raiz)->esq = NULL;
		(*raiz)->dir = NULL;

		return *raiz;
	}

	if((*raiz)->chave == k)
	{
		printf("Ja existe um no com este valor.");
	}
	else
	{
		if((*raiz)->chave < k)
			insereArvBinRec((&(*raiz)->dir), k);
		else
			insereArvBinRec((&(*raiz)->esq), k);
	}
	return *raiz;
}
