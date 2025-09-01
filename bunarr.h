#pragma once
#include "buntypes.h"

typedef struct bunarr {
	void *items; /**< points to a static array that is passed in the creation
                  function the array are stored */
	usize isize; /**< the size of each item */
	usize len; /**< the number of items currently held by the array */
	usize cap; /**< the number of items the array can hold */
	void (*free_fn)(
		usize i,
		void *itm); /**< NULL or function to be called on item removal */

} bunarr;

/** \brief creates an dynamic array
 * \param isize The size in bytes of each item,
 * \param cap the max capacity of the array,
 * \param len The initial lenght of the array,
 * \param free_fn NULL or a pointer to a callback function that's called on
 * items when they are removed, meant to free other pointers contained in each
 * item.
 * \returns bunarr the created array
 * \sa bunarr_create_ex */
bunarr *bunarr_create(usize isize, usize cap, usize len, void *arr_data,
		      void (*free_fn)(usize i, void *itm));

/** \brief creates an dynamic array with but with extra arguments
 * \param isize the size in bytes of each item,
 * \param cap the initial capacity of the array
 * \param incr how much the array will grow / increase once  it's resized
 * \param mult if true the incr value will be used as a multiplyer of the array
 * capacity: newcap = cap * (incr/10)
 * \param subarr - if true this will be treated as a subarray, which means it
 * will not allow memory reallocations
 * \param free_fn NULL or a pointer to a callback function that's called on
 * items when they are removed, meant to free other pointers contained in each
 * item.
 * \returns bunarr the created array */
bunarr *bunarr_create_ex(usize isize, usize cap, usize len, void *arr_data,
			 void (*free_fn)(usize i, void *itm));

/** \brief Destroys the array, also calls the free_fn passed in bunarr_create in
 * each item, if it's not NULL.
 * \param arr array to be destroyed
 * \returns bool true if it worked, false if an error happened
 * \sa bunarr_clear */
bool bunarr_destroy(bunarr *arr);

/** \brief Appends item to bunarr by copying
 * \param arr array where itm will be appended to
 * \param itm item to be appended to array
 * \returns i index of the appended item */
usize bunarr_append(bunarr *arr, void *itm);

/** \brief Appends item to bunarr by copying, and then runs free(itm)
 * \param arr array where itm will be appended to
 * \param itm item to be appended to array
 * \returns i index of the appended item */
usize bunarr_append_free(bunarr *arr, void *itm);

/** \brief removes item i from the array, slower than remove_lazy
 * \param i the index of the item we wish to remove.
 * \returns bool True if it worked, false if an error happened */
bool bunarr_remove(bunarr *arr, usize i);

/** \brief lazy remove, copys last item into the index and reduces the list size, breaks array ordering
 * \param arr the array where i will be removed
 * \param i the index of the item we wish to remove.
 * \returns bool if true it worked, if false an error happened */
bool bunarr_remove_lazy(bunarr *arr, usize i);

/** \brief Clears the array by setting everything to 0
 * \param arr the array to be cleared*/
bool bunarr_clear(bunarr *arr);

/** \brief Get a void pointer the item of the given index from the array
 * \param arr the array we will get the item from
 * \param i the item's index
 * \returns ptr to array item */
void *bunarr_get(bunarr *arr, usize i);

/** \brief Sets item i to *item if i < arr->len, else appends item to the array
 * \param arr The array duh
 * \param item the item to be set or appended to the array
 * \param i the desired index */
bool bunarr_set(bunarr *arr, void *item, usize i);

/** \brief Loops trough the array and executes the given function on every item,
 * also passes the index to the function
 * \param arr the array that will be parsed
 * \param function the function that will be executed in every item of the array
 */
void bunarr_exe(bunarr *arr, void (*function)(usize i, void *itm));

/** \brief runs bsearch on the array and returns the requested key, ensure the
 * array is sorted properly
 * \param key the desired item you want to find
 * \param compar_fn_t comparison function
 * \returns ptr a pointer to the found item, or NULL if nothing that matches the
 * key was found. */
void *bunarr_bsearch(bunarr *arr, void *key,
		     i32 (*fn)(const void *, const void *));

/** \brief Runs quick sort on the array using the given compare function
 * \param arr array to be sorted
 * \param fn function that receives pointers to two items of the arr and returns
 * the result of the comparison */
void bunarr_qsort(bunarr *arr, i32 (*fn)(const void *, const void *));
