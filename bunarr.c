#include "bunarr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool bunarr_chk_index(bunarr *arr, usize i);
static void bunarr_get_len(bunarr *arr);

bunarr *bunarr_create(usize isize, usize cap, usize len, void *arr_data,
		      void (*free_fn)(usize i, void *data))
{
	return bunarr_create_ex(isize, cap, len, arr_data, free_fn);
}

bunarr *bunarr_create_ex(usize isize, usize cap, usize len, void *arr_data,
			 void (*free_fn)(usize i, void *data))
{
	bunarr *arr = malloc(sizeof(bunarr));
	arr->isize = isize;
	arr->len = len;
	arr->cap = cap;
	arr->items = NULL;
	arr->free_fn = free_fn;
	void *items = arr_data;
	arr->items = items;

	return arr;
}

usize bunarr_append(bunarr *arr, void *item)
{
	bunarr_chk_index(arr, arr->len);
	memcpy(arr->items + (arr->len * arr->isize), item, arr->isize);
	if (arr->len < arr->cap) {
		arr->len++;
	}
	return arr->len - 1;
}

usize bunarr_append_free(bunarr *arr, void *item)
{
	usize i = bunarr_append(arr, item);
	free(item);
	return i;
}

bool bunarr_remove(bunarr *arr, usize i)
{
	if (!bunarr_chk_index(arr, i)) {
		return false;
	}
	if (arr->free_fn != NULL) {
		void *itm = bunarr_get(arr, i);
		arr->free_fn(i, itm);
	}
	u8 *dest = (u8 *)(arr->items + arr->isize * (i));
	u8 *src = (u8 *)arr->items + arr->isize * (i + 1);
	usize size = (arr->isize * (arr->len - i));

	// set last item to 0
	memset(arr->items + arr->len * arr->isize, 0, arr->isize);

	// reduce size
	arr->len--;
	// copy half the array one item back
	memcpy(dest, src, size);

	return true;
}

bool bunarr_remove_lazy(bunarr *arr, usize i)
{
	if (!bunarr_chk_index(arr, i)) {
		return false;
	}
	--arr->len;
	u8 *item_ptr = (u8 *)arr->items + i * arr->isize;
	u8 *end_ptr = (u8 *)arr->items + arr->len * arr->isize;
	memcpy(item_ptr, end_ptr, arr->isize);

	return true;
}

bool bunarr_set(bunarr *arr, void *item, usize i)
{
	u8 *dest = (arr->items + arr->isize * (i));

	if (i > arr->len) {
		bunarr_append(arr, item);
	} else {
		memcpy(dest, item, arr->isize);
	}

	return true;
}

bool bunarr_set_free(bunarr *arr, void *item, usize i)
{
	bool r = bunarr_set(arr, item, i);
	free(item);
	return r;
}

bool bunarr_destroy(bunarr *arr)
{
	if (arr->free_fn != NULL) {
		for (usize i = 0; i < arr->cap; i++) {
			void *item = bunarr_get(arr, i);
			arr->free_fn(i, item);
		}
	}
	free(arr);

	return true;
}

bool bunarr_clear(bunarr *arr)
{
	memset(arr->items, 0, arr->cap * arr->isize);
	arr->len = 0;
	return true;
}

void *bunarr_get(bunarr *arr, usize i)
{
	if (!bunarr_chk_index(arr, i)) {
		return NULL;
	}
	void *item = arr->items + (i * arr->isize);
	return item;
}

void bunarr_exe(bunarr *arr, void (*function)(usize, void *))
{
	for (usize i = 0; i < arr->len; i++) {
		void *item = bunarr_get(arr, i);
		function(i, item);
	}
}

void bunarr_qsort(bunarr *arr, i32 (*fn)(const void *, const void *))
{
	qsort(arr->items, arr->len, arr->isize, fn);
}

void *bunarr_bsearch(bunarr *arr, void *key,
		     i32 (*fn)(const void *, const void *))
{
	return bsearch(key, arr->items, arr->len, arr->isize, fn);
}

/** \brief Returns true if the index is valid.
 * if it's invalid, print an error to stderr and return false. */
static bool bunarr_chk_index(bunarr *arr, usize i)
{
	if (i > arr->len) {
		fprintf(stderr, "\nInvalid Index %lu", i);
		return false;
	} else
		return true;
}

/**
 *
 * */
static void bunarr_get_len(bunarr *arr)
{
	for (u32 i = 0; i < arr->cap; i++) {
	}
};
