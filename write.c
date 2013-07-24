#include <zlib.h>

#include "nbt.h"

static int nbt_write_payload(gzFile file, nbt_byte id, nbt_payload *payload);
static int nbt_write_tag(gzFile file, nbt_tag *tag);
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

int nbt_write(char *path, nbt_tag *tag)
{
	int res;
	gzFile file;

	if (!tag) {
		return NBT_ERR_INVALID_ARG;
	}

	file = gzopen(path, "wb");

	if (!file) {
		return NBT_ERR_FILE;
	}

	res = nbt_write_tag(file, tag);
	gzclose(file);

	return res;
}

static int nbt_write_payload(gzFile file, nbt_byte id, nbt_payload *payload)
{
	switch (id) {
		case NBT_TAG_END:
			return 0;

		case NBT_TAG_BYTE:
			return nbt_write_byte(file, (nbt_byte *) payload);

		case NBT_TAG_SHORT:
			return nbt_write_short(file, (nbt_short *) payload);

		case NBT_TAG_INT:
			return nbt_write_int(file, (nbt_int *) payload);

		case NBT_TAG_LONG:
			return nbt_write_long(file, (nbt_long *) payload);

		case NBT_TAG_FLOAT:
			return nbt_write_float(file, (nbt_float *) payload);

		case NBT_TAG_DOUBLE:
			return nbt_write_double(file, (nbt_double *) payload);

		case NBT_TAG_BYTE_ARRAY:
			return nbt_write_byte_array(file, (nbt_byte_array *) payload);

		case NBT_TAG_STRING:
			return nbt_write_string(file, (nbt_string *) payload);

		case NBT_TAG_LIST:
			return nbt_write_list(file, (nbt_list *) payload);

		case NBT_TAG_COMPOUND:
			return nbt_write_compound(file, (nbt_compound *) payload);

		case NBT_TAG_INT_ARRAY:
			return nbt_write_int_array(file, (nbt_int_array *) payload);

		default:
			return NBT_ERR_INVALID_ID;
	}
}

static int nbt_write_tag(gzFile file, nbt_tag *tag)
{
	int written = 0;

	if (!tag) {
		return NBT_ERR_NULL_PTR;
	}

	written += nbt_write_byte(file, &tag->id);

	if (tag->id != NBT_TAG_END) {
		written += nbt_write_string(file, &tag->name);
		written += nbt_write_payload(file, tag->id, &tag->payload);
	}

	return written;
}

static int nbt_write_byte(gzFile file, nbt_byte *payload)
{
	return payload ? gzwrite(file, payload, 1) : NBT_ERR_NULL_PTR;
}

static int nbt_write_short(gzFile file, nbt_short *payload)
{
	int written = 0;

	if (!payload) {
		return NBT_ERR_NULL_PTR;
	}

	written += gzwrite(file, ((nbt_byte *) payload) + 1, 1);
	written += gzwrite(file, ((nbt_byte *) payload), 1);

	return written;
}

static int nbt_write_int(gzFile file, nbt_int *payload)
{
	int written = 0;

	if (!payload) {
		return NBT_ERR_NULL_PTR;
	}

	written += gzwrite(file, ((nbt_byte *) payload) + 3, 1);
	written += gzwrite(file, ((nbt_byte *) payload) + 2, 1);
	written += gzwrite(file, ((nbt_byte *) payload) + 1, 1);
	written += gzwrite(file, ((nbt_byte *) payload), 1);

	return written;
}

static int nbt_write_long(gzFile file, nbt_long *payload)
{
	int written = 0;

	if (!payload) {
		return NBT_ERR_NULL_PTR;
	}

	written += gzwrite(file, ((nbt_byte *) payload) + 7, 1);
	written += gzwrite(file, ((nbt_byte *) payload) + 6, 1);
	written += gzwrite(file, ((nbt_byte *) payload) + 5, 1);
	written += gzwrite(file, ((nbt_byte *) payload) + 4, 1);
	written += gzwrite(file, ((nbt_byte *) payload) + 3, 1);
	written += gzwrite(file, ((nbt_byte *) payload) + 2, 1);
	written += gzwrite(file, ((nbt_byte *) payload) + 1, 1);
	written += gzwrite(file, ((nbt_byte *) payload), 1);

	return written;
}

static int nbt_write_float(gzFile file, nbt_float *payload)
{
	int written = 0;

	if (!payload) {
		return NBT_ERR_NULL_PTR;
	}

	written += gzwrite(file, ((nbt_byte *) payload) + 3, 1);
	written += gzwrite(file, ((nbt_byte *) payload) + 2, 1);
	written += gzwrite(file, ((nbt_byte *) payload) + 1, 1);
	written += gzwrite(file, ((nbt_byte *) payload), 1);

	return written;
}

static int nbt_write_double(gzFile file, nbt_double *payload)
{
	int written = 0;

	if (!payload) {
		return NBT_ERR_NULL_PTR;
	}

	written += gzwrite(file, ((nbt_byte *) payload) + 7, 1);
	written += gzwrite(file, ((nbt_byte *) payload) + 6, 1);
	written += gzwrite(file, ((nbt_byte *) payload) + 5, 1);
	written += gzwrite(file, ((nbt_byte *) payload) + 4, 1);
	written += gzwrite(file, ((nbt_byte *) payload) + 3, 1);
	written += gzwrite(file, ((nbt_byte *) payload) + 2, 1);
	written += gzwrite(file, ((nbt_byte *) payload) + 1, 1);
	written += gzwrite(file, ((nbt_byte *) payload), 1);

	return written;
}

static int nbt_write_byte_array(gzFile file, nbt_byte_array *payload)
{
	int i, res, written = 0;

	if (!payload) {
		return NBT_ERR_NULL_PTR;
	}

	res = nbt_write_int(file, &payload->size);

	if (!res) {
		return written;
	}

	written += res;

	for (i = 0; i < payload->size; i++) {
		res = gzwrite(file, payload->bytes + i, 1);

		if (res) {
			written += res;
		}
	}

	return written;
}

static int nbt_write_string(gzFile file, nbt_string *payload)
{
	int i, res, written = 0;

	if (!payload) {
		return NBT_ERR_NULL_PTR;
	}

	res = nbt_write_short(file, &payload->length);

	if (!res) {
		return written;
	}

	written += res;

	for (i = 0; i < payload->length; i++) {
		res = gzwrite(file, payload->chars + i, 1);

		if (res) {
			written += res;
		}
	}

	return written;
}

static int nbt_write_list(gzFile file, nbt_list *payload)
{
	int i, res, written = 0;

	if (!payload) {
		return NBT_ERR_NULL_PTR;
	}

	res = nbt_write_byte(file, &payload->tag_id);

	if (!res) {
		return written;
	}

	written += res;
	res = nbt_write_int(file, &payload->size);

	if (!res) {
		return written;
	}

	written += res;

	for (i = 0; i < payload->size; i++) {
		res = nbt_write_payload(file, payload->tag_id, (nbt_payload *) (payload->tags + i));

		if (res) {
			written += res;
		}
	}

	return written;
}

static int nbt_write_compound(gzFile file, nbt_compound *payload)
{
	int res, written = 0;
	nbt_tag *curr;

	if (!payload) {
		return NBT_ERR_NULL_PTR;
	}

	for (curr = * (nbt_tag **) payload;; curr++) {
		res = nbt_write_tag(file, curr);

		if (res) {
			written += res;
		}

		if (curr->id == NBT_TAG_END) {
			break;
		}
	}

	return written;
}

static int nbt_write_int_array(gzFile file, nbt_int_array *payload)
{
	int i, res, written = 0;

	if (!payload) {
		return NBT_ERR_NULL_PTR;
	}

	res = nbt_write_int(file, &payload->size);

	if (!res) {
		return written;
	}

	written += res;

	for (i = 0; i < payload->size; i++) {
		res = nbt_write_int(file, payload->ints + i);

		if (res) {
			written += res;
		}
	}

	return written;
}
