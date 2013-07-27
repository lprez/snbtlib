#include <stdio.h>
#include <stdlib.h>

#include "nbt.h"

int main(int argc, char **argv)
{
	nbt_tag *t = nbt_new();
	nbt_tag *t2, *t3;
	int i, j, l, l2;

	if (argc < 3) {
		printf("Wrong number of arguments\n");
		return 1;
	}

	if (!nbt_read(t, argv[1])) {
		printf("Read error\n");
		return 1;
	}

	if (nbt_get_type(t) != NBT_TAG_COMPOUND) {
		printf("Compound not found\n");
		return 1;
	}

	l = nbt_get_length(t);

	for (i = 0; i < l; i++) {
		t2 = nbt_get_tag(t);
		l2 = nbt_get_length(t2);

		if (strcmp(nbt_get_name(t2), "abilities") == 0) {
			for (j = 0; j < l2; j++) {
				t3 = nbt_get_tag(t2);

				if (strcmp(nbt_get_name(t3), "flySpeed") == 0) {
					nbt_set_real(t3, (double) atof(argv[2]));

					if (nbt_write(t, argv[1])) {
						printf("Success\n");
						return 0;
					} else {
						printf("Write error\n");
						return 1;
					}
				}
			}
		}
	}

	printf("flySpeed or abilities not found");
	return 1;
}
