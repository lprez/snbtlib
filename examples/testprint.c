#include "nbt.h"

int main(int argc, char **argv)
{
	nbt_tag *t = nbt_new();

	if (argc < 2) {
		return 2;
	}

	if (!nbt_read(t, argv[1])) {
		return 1;
	}

	nbt_print(t);
	nbt_free(t);

	return 0;
}
