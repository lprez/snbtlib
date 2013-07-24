#include <stdlib.h>
#include <zlib.h>

#include "nbt.h"

static int nbt_read_payload(gzFile file, nbt_byte id, nbt_payload *payload);
static int nbt_read_tag(gzFile file, nbt_tag *tag);
static int nbt_read_byte(gzFile file, nbt_byte *payload);
static int nbt_read_short(gzFile file, nbt_short *payload);
static int nbt_read_int(gzFile file, nbt_int *payload);
static int nbt_read_long(gzFile file, nbt_long *payload);
static int nbt_read_float(gzFile file, nbt_float *payload);
static int nbt_read_double(gzFile file, nbt_double *payload);
static int nbt_read_byte_array(gzFile file, nbt_byte_array *payload);
static int nbt_read_string(gzFile file, nbt_string *payload);
static int nbt_read_list(gzFile file, nbt_list *payload);
static int nbt_read_compound(gzFile file, nbt_compound *payload);
static int nbt_read_int_array(gzFile file, nbt_int_array *payload);

static int nbt_write_byte(gzFile file, nbt_byte *payload);
static int nbt_write_short(gzFile file, nbt_short *payload);
static int nbt_write_int(gzFile file, nbt_int *payload);
static int nbt_write_long(gzFile file, nbt_long *payload);
static int nbt_write_float(gzFile file, nbt_float *payload);
static int nbt_write_double(gzFile file, nbt_double *payload);
static int nbt_write_byte_array(gzFile file, nbt_byte_array *payload);
static int nbt_write_string(gzFile file, nbt_string *payload);
static int nbt_write_list(gzFile file, nbt_list *payload);
static int nbt_write_compound(gzFile file, nbt_compound *payload);
static int nbt_write_int_array(gzFile file, nbt_int_array *payload);

int nbt_read(char *path, nbt_tag *tag)
{
	gzFile file;
	int res;

	if (!tag) {
		return NBT_ERR_INVALID_ARG;
	}

	file = gzopen(path, "rb");

	if (!file) {
		return NBT_ERR_FILE;
	}

	res = nbt_read_tag(file, tag);
	gzclose(file);

	return res;
}

int nbt_write(char *path, nbt_tag *tag)
{
}

void nbt_free(nbt_tag *tag)
{
}

static int nbt_read_payload(gzFile file, nbt_byte id, nbt_payload *payload)
{
	//printf("%d\n", id);
	switch (id) {
		case NBT_TAG_END:
			return 0;

		case NBT_TAG_BYTE:
			return nbt_read_byte(file, (nbt_byte *) payload);

		case NBT_TAG_SHORT:
			return nbt_read_short(file, (nbt_short *) payload);

		case NBT_TAG_INT:
			return nbt_read_int(file, (nbt_int *) payload);

		case NBT_TAG_LONG:
			return nbt_read_long(file, (nbt_long *) payload);

		case NBT_TAG_FLOAT:
			return nbt_read_float(file, (nbt_float *) payload);

		case NBT_TAG_DOUBLE:
			return nbt_read_double(file, (nbt_double *) payload);

		case NBT_TAG_BYTE_ARRAY:
			return nbt_read_byte_array(file, (nbt_byte_array *) payload);

		case NBT_TAG_STRING:
			return nbt_read_string(file, (nbt_string *) payload);

		case NBT_TAG_LIST:
			return nbt_read_list(file, (nbt_list *) payload);

		case NBT_TAG_COMPOUND:
			return nbt_read_compound(file, (nbt_compound *) payload);

		case NBT_TAG_INT_ARRAY:
			return nbt_read_int_array(file, (nbt_int_array *) payload);

		default:
			return NBT_ERR_INVALID_ID;
	}
}

static int nbt_read_tag(gzFile file, nbt_tag *tag)
{
	int res;

	if (!tag) {
		return NBT_ERR_MEMORY;
	}

	if (!(
		nbt_read_byte(file, &tag->id) &&
		(tag->id == NBT_TAG_END || nbt_read_string(file, &tag->name))
	)) {
		return NBT_ERR_FILE;
	}

	res = nbt_read_payload(file, tag->id, &tag->payload);

	if (res >= 0) {
		return sizeof(nbt_byte) + sizeof(nbt_short) + tag->name.length + res;
	} else {
		return res;
	}
}

static int nbt_read_byte(gzFile file, nbt_byte *payload)
{
	return payload ? gzread(file, payload, 1) : NBT_ERR_NULL_PTR;
}

static int nbt_read_short(gzFile file, nbt_short *payload)
{
	int read = 0;

	if (!payload) {
		return NBT_ERR_NULL_PTR;
	}

	read += gzread(file, ((nbt_byte *) payload) + 1, 1);
	read += gzread(file, ((nbt_byte *) payload), 1);

	return read;
}

static int nbt_read_int(gzFile file, nbt_int *payload)
{
	int read = 0;

	if (!payload) {
		return NBT_ERR_NULL_PTR;
	}

	read += gzread(file, ((nbt_byte *) payload) + 3, 1);
	read += gzread(file, ((nbt_byte *) payload) + 2, 1);
	read += gzread(file, ((nbt_byte *) payload) + 1, 1);
	read += gzread(file, ((nbt_byte *) payload), 1);

	return read;
}

static int nbt_read_long(gzFile file, nbt_long *payload)
{
	int read = 0;

	if (!payload) {
		return NBT_ERR_NULL_PTR;
	}

	read += gzread(file, ((nbt_byte *) payload) + 7, 1);
	read += gzread(file, ((nbt_byte *) payload) + 6, 1);
	read += gzread(file, ((nbt_byte *) payload) + 5, 1);
	read += gzread(file, ((nbt_byte *) payload) + 4, 1);
	read += gzread(file, ((nbt_byte *) payload) + 3, 1);
	read += gzread(file, ((nbt_byte *) payload) + 2, 1);
	read += gzread(file, ((nbt_byte *) payload) + 1, 1);
	read += gzread(file, ((nbt_byte *) payload), 1);

	return read;
}

static int nbt_read_float(gzFile file, nbt_float *payload)
{
	int read = 0;

	if (!payload) {
		return NBT_ERR_NULL_PTR;
	}

	read += gzread(file, ((nbt_byte *) payload) + 3, 1);
	read += gzread(file, ((nbt_byte *) payload) + 2, 1);
	read += gzread(file, ((nbt_byte *) payload) + 1, 1);
	read += gzread(file, ((nbt_byte *) payload), 1);

	return read;
}

static int nbt_read_double(gzFile file, nbt_double *payload)
{
	int read = 0;

	if (!payload) {
		return NBT_ERR_NULL_PTR;
	}

	read += gzread(file, ((nbt_byte *) payload) + 7, 1);
	read += gzread(file, ((nbt_byte *) payload) + 6, 1);
	read += gzread(file, ((nbt_byte *) payload) + 5, 1);
	read += gzread(file, ((nbt_byte *) payload) + 4, 1);
	read += gzread(file, ((nbt_byte *) payload) + 3, 1);
	read += gzread(file, ((nbt_byte *) payload) + 2, 1);
	read += gzread(file, ((nbt_byte *) payload) + 1, 1);
	read += gzread(file, ((nbt_byte *) payload), 1);

	return read;
}

static int nbt_read_byte_array(gzFile file, nbt_byte_array *payload)
{
	int i;

	if (!payload) {
		return NBT_ERR_NULL_PTR;
	}

	if (!nbt_read_int(file, &payload->size)) {
		return NBT_ERR_FILE;
	}

	payload->bytes = (nbt_byte *) malloc(sizeof(nbt_byte) * payload->size);

	if (!payload->bytes) {
		return NBT_ERR_MEMORY;
	}

	for (i = 0; i < payload->size; i++) {
		if (!nbt_read_byte(file, payload->bytes + i)) {
			payload->bytes[i] = 0;
		}
	}

	return payload->size + sizeof(nbt_int);
}

static int nbt_read_string(gzFile file, nbt_string *payload)
{
	int i;

	if (!payload) {
		return NBT_ERR_NULL_PTR;
	}

	if (!nbt_read_short(file, &payload->length)) {
		return NBT_ERR_FILE;
	}

	payload->chars = malloc(sizeof(char) * payload->length);

	if (!payload->chars) {
		return NBT_ERR_MEMORY;
	}

	for (i = 0; i < payload->length; i++) {
		if (!gzread(file, payload->chars + i, 1)) {
			payload->chars[i] = 0;
		}
	}

	return payload->length + sizeof(nbt_short);
}

static int nbt_read_list(gzFile file, nbt_list *payload)
{
	int res, i;
	int read = sizeof(nbt_byte) + sizeof(nbt_int);

	if (!payload) {
		return NBT_ERR_NULL_PTR;
	}

	if (!nbt_read_byte(file, &payload->tag_id)) {
		return NBT_ERR_FILE;
	}

	if (!nbt_read_int(file, &payload->size)) {
		return NBT_ERR_FILE;
	}

	payload->tags = malloc(sizeof(nbt_payload) * payload->size);

	if (!payload->tags) {
		return NBT_ERR_MEMORY;
	}

	for (i = 0; i < payload->size; i++) {
		res = nbt_read_payload(file, payload->tag_id, (nbt_payload *) (payload->tags + i));

		if (res > 0) {
			read += res;
		}
	}

	return read;
}

static int nbt_read_compound(gzFile file, nbt_compound *payload)
{
	int i, max = 0, res, read = 0;
	void *tmpptr;

	if (!payload) {
		return NBT_ERR_NULL_PTR;
	}

	*payload = (nbt_tag *) 0;

	for (i = 0;; i++) {
		if (i >= max) {
			max += 8;
			tmpptr = realloc(*payload, sizeof(struct nbt_tag) * max);

			if (!tmpptr) {
				if (*payload) {
					free(*payload);
				}

				return NBT_ERR_MEMORY;
			}

			*payload = tmpptr;
		}

		res = nbt_read_tag(file, *payload + i);

		if (res > 0) {
			read += res;

			if ((*payload + i)->id == NBT_TAG_END) {
				return read;
			}
		} else {
			if (*payload) {
				free(*payload);
			}

			return res;
		}
	}

	return read;
}

static int nbt_read_int_array(gzFile file, nbt_int_array *payload)
{
	int i;

	if (!payload) {
		return NBT_ERR_NULL_PTR;
	}

	if (!nbt_read_int(file, &payload->size)) {
		return NBT_ERR_FILE;
	}

	payload->ints = (nbt_int *) malloc(sizeof(nbt_int) * payload->size);

	if (!payload->ints) {
		return NBT_ERR_MEMORY;
	}

	for (i = 0; i < payload->size; i++) {
		if (!nbt_read_int(file, payload->ints + i)) {
			payload->ints[i] = 0;
		}
	}

	return payload->size + sizeof(nbt_int);
}
