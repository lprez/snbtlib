/*
 * Copyright (c) 2013, ZioCrocifisso
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met: 
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer. 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution. 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "nbt.h"

static char *typenames[] = {
	"End",
	"Byte",
	"Short",
	"Int",
	"Long",
	"Float",
	"Double",
	"Byte Array",
	"String",
	"List",
	"Compound",
	"Int Array",
	"Tag",
	"?"
};

static int printval(nbt_tag *tag, nbt_byte type, int depth);
static int printmul(nbt_tag *tag, int depth);
static int printtag(nbt_tag *tag, int depth);

static int printval(nbt_tag *tag, nbt_byte type, int depth)
{
	if (NBT_IS_INTEGER(type)) {
		printf("%ld\n", nbt_get_integer(tag));
	} else if (NBT_IS_REAL(type)) {
		printf("%f\n", nbt_get_real(tag));
	} else if (NBT_IS_STRING(type)) {
		printf("%s\n", nbt_get_string(tag));
	} else if (NBT_IS_MULTIPLE(type)) {
		return printmul(tag, depth);
	} else if (NBT_IS_TAG(type)) {
		return printtag(nbt_get_tag(tag), depth);
	} else {
		return NBT_ERR_INVALID_TYPE;
	}

	return 1;
}

static int printmul(nbt_tag *tag, int depth)
{
	uint64_t length = nbt_get_length(tag);
	uint64_t i;
	char *depthchars = (char *) malloc(depth + 2);
	nbt_byte ctype = nbt_get_children_type(tag);
	nbt_tag muls;

	memset(depthchars, '-', depth + 1);
	depthchars[depth + 1] = 0;

	printf("(%ss)\n", nbt_type_name(nbt_get_children_type(tag)));

	for (i = 0; i < length; i++) {
		printf("%s", depthchars);
		if (NBT_IS_MULTIPLE(ctype)) {
			muls = nbt_get_multiple(tag);
			printmul(&muls, depth + 1);
		} else {
			printval(tag, ctype, depth + 1);
		}
	}

	free(depthchars);

	return 1;
}

static int printtag(nbt_tag *tag, int depth)
{
	printf("[%s] %s: ", nbt_type_name(tag->id), nbt_get_name(tag));
	return printval(tag, tag->id, depth);
}

int nbt_print(nbt_tag *tag)
{
	if (!tag) {
		return NBT_ERR_INVALID_ARG;
	}

	return printtag(tag, 0);
}

char *nbt_type_name(nbt_byte id) {
	if (id == NBT_TAG_TAG) {
		id = 12;
	} else if (id < NBT_TAG_END || id > NBT_TAG_INT_ARRAY) {
		id = 13;
	}

	return typenames[id];
}
