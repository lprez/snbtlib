Installation
============
	make
	sudo make install

Linking
-------
Add '-lsnbt -lz' options when linking.

Constants
=========

Errors
------
	#define NBT_ERR_FILE		-1
I/O error.

	#define NBT_ERR_MEMORY		-2
Memory error.

	#define NBT_ERR_INVALID_ID	-3
Invalid tag ID.

	#define NBT_ERR_NULL_PTR	-4
Internal NULL pointer.

	#define NBT_ERR_INVALID_ARG	-5
Invalid argument (e.g., a NULL pointer, an invalid type)

	#define NBT_ERR_INVALID_TYPE	-6
Tag type is not suitable for that operation.

	#define NBT_ERR_NONEMPTY	-7
See nbt_set_children_type.

Tag types
---------
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
	#define NBT_TAG_INVALID		126
	#define NBT_TAG_TAG		127

Functions
=========

nbt_new
-------
	nbt_tag *nbt_new(void)
Allocates an NBT tag. Returns the new tag, or NULL if there was an error.

nbt_read
--------
	int nbt_read(nbt_tag *tag, char *path)
Reads an NBT tag from an NBT file. Returns the number of bytes read from the file, or an error code.

nbt_write
---------
	int nbt_write(nbt_tag *tag, char *path)
Writes an NBT tag in an NBT file. Returns the number of bytes written, or an error code.

nbt_free
--------
	void nbt_free(nbt_tag *tag)
Frees the memory allocated by the tag, and the tag itself.

nbt_free_children
-----------------
	void nbt_free_children(nbt_tag *tag)
Frees only the memory allocated by the tag.

Macros
======

Examples
========
