#ifndef SNBT_H
#define SNBT_H

#include <stdint.h>
#include <stdio.h>

#define NBT_ERR_FILE		-1
#define NBT_ERR_MEMORY		-2
#define NBT_ERR_INVALID_ID	-3
#define NBT_ERR_NULL_PTR	-4
#define NBT_ERR_INVALID_ARG	-5

#define NBT_TAG_END		0
#define NBT_TAG_BYTE		1
#define NBT_TAG_SHORT		2
#define NBT_TAG_INT		3
#define NBT_TAG_LONG		4
#define NBT_TAG_FLOAT		5
#define NBT_TAG_DOUBLE		6
#define NBT_TAG_BYTE_ARRAY	7
#define NBT_TAG_STRING		8
#define NBT_TAG_LIST		9
#define NBT_TAG_COMPOUND	10
#define NBT_TAG_INT_ARRAY	11

struct nbt_tag;
union nbt_payload;

typedef int8_t nbt_byte;
typedef int16_t nbt_short;
typedef int32_t nbt_int;
typedef int64_t nbt_long;
typedef float nbt_float;
typedef double nbt_double;

typedef struct {
	nbt_int size;
	nbt_byte *bytes;
} nbt_byte_array;

typedef struct {
	nbt_short length;
	char *chars;
} nbt_string;

typedef struct {
	nbt_byte tag_id;
	nbt_int size;
	union nbt_payload *tags;
} nbt_list;

typedef struct nbt_tag *nbt_compound;

typedef struct {
	nbt_int size;
	nbt_int *ints;
} nbt_int_array;

typedef union nbt_payload {
	nbt_byte byte_payload;
	nbt_short short_payload;
	nbt_int int_payload;
	nbt_long long_payload;
	nbt_float float_payload;
	nbt_double double_payload;
	nbt_byte_array byte_array_payload;
	nbt_string string_payload;
	nbt_list list_payload;
	nbt_compound compound_payload;
	nbt_int_array int_array_payload;
} nbt_payload;

typedef struct nbt_tag {
	nbt_byte id;
	nbt_string name;
	nbt_payload payload;
	nbt_tag *parent;
} nbt_tag;

extern int nbt_read(char *path, nbt_tag *tag);
extern int nbt_write(char *path, nbt_tag *tag);
extern void nbt_free(nbt_tag *tag);

#endif
