void sort_index()
{
	int i, j;
	for (i = 0;i < no - 1;i++)
		for (j = 0;j < no - i - 1;j++)
			if (strcmp(in[j].name, in[j + 1].name) > 0)
			{
				temp = in[j];
				in[j] = in[j + 1];
				in[j + 1] = temp;
			}
}
