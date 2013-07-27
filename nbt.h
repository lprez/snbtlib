#ifndef SNBT_H
#define SNBT_H

#include <stdint.h>
#include <stdio.h>

#define NBT_ERR_FILE		-1
#define NBT_ERR_MEMORY		-2
#define NBT_ERR_INVALID_ID	-3
#define NBT_ERR_NULL_PTR	-4
#define NBT_ERR_INVALID_ARG	-5
#define NBT_ERR_INVALID_TYPE	-6
#define NBT_ERR_NONEMPTY	-7

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
#define NBT_TAG_TAG		127

#define NBT_IS_PARENT(x)	(					\
					(x == NBT_TAG_BYTE_ARRAY) ||	\
					(					\
						(x >= NBT_TAG_LIST) &&	\
						(x <= NBT_TAG_INT_ARRAY)\
					)				\
				)

#define NBT_IS_INTEGER(x)	(					\
					(x >= NBT_TAG_BYTE) &&		\
					(x <= NBT_TAG_LONG)		\
				)

#define NBT_IS_REAL(x)		(					\
					(x == NBT_TAG_FLOAT) ||		\
					(x == NBT_TAG_DOUBLE)		\
				)

#define NBT_IS_STRING(x)	(x == NBT_TAG_STRING)

#define NBT_IS_TAG(x)		(x == NBT_TAG_TAG)

#define NBT_IS_END(x)		(x == NBT_TAG_END)


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
	nbt_payload payload;
	uint64_t position;
	nbt_string name;
} nbt_tag;

extern nbt_tag *nbt_new(void);

extern nbt_byte nbt_get_type(nbt_tag *tag);
extern char *nbt_get_name(nbt_tag *tag);
extern size_t nbt_get_length(nbt_tag *tag);
extern nbt_byte nbt_get_children_type(nbt_tag *tag);
extern int64_t nbt_get_integer(nbt_tag *tag);
extern double nbt_get_real(nbt_tag *tag);
extern char *nbt_get_string(nbt_tag *tag);
extern nbt_tag *nbt_get_tag(nbt_tag *tag);
extern nbt_tag nbt_get_multiple(nbt_tag *tag);

extern int nbt_set_position(nbt_tag *tag, uint64_t value);
extern int nbt_set_type(nbt_tag *tag, nbt_byte value);
extern int nbt_set_name(nbt_tag *tag, char *value);
extern int nbt_set_children_type(nbt_tag *tag, nbt_byte value);
extern int nbt_set_integer(nbt_tag *tag, int64_t value);
extern int nbt_set_real(nbt_tag *tag, double value);
extern int nbt_set_string(nbt_tag *tag, char *value);

extern int nbt_insert_integer(nbt_tag *tag, int64_t value);
extern int nbt_insert_real(nbt_tag *tag, double value);
extern int nbt_insert_string(nbt_tag *tag, char *value);
extern int nbt_insert_tag(nbt_tag *tag, nbt_tag *value);

extern int nbt_remove(nbt_tag *tag);
extern void nbt_free(nbt_tag *tag);
extern void nbt_free_children(nbt_tag *tag);

extern int nbt_read(char *path, nbt_tag *tag);
extern int nbt_write(char *path, nbt_tag *tag);

#endif
