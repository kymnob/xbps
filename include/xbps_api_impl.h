/*-
 * Copyright (c) 2010-2012 Juan Romero Pardines.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *-
 */

#ifndef _XBPS_API_IMPL_H_
#define _XBPS_API_IMPL_H_

#include <assert.h>
#include <xbps_api.h>
/*
 * By default all public functions have default visibility, unless
 * visibility has been detected by configure and the HIDDEN definition
 * is used.
 */
#if HAVE_VISIBILITY
#define HIDDEN __attribute__ ((visibility("hidden")))
#else
#define HIDDEN
#endif

#include "compat.h"
#include "queue.h"
#include "fetch.h"

#define ARCHIVE_READ_BLOCKSIZE	10240

#define EXTRACT_FLAGS	ARCHIVE_EXTRACT_SECURE_NODOTDOT | \
			ARCHIVE_EXTRACT_SECURE_SYMLINKS
#define FEXTRACT_FLAGS	ARCHIVE_EXTRACT_OWNER | ARCHIVE_EXTRACT_PERM | \
			ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_UNLINK | \
			EXTRACT_FLAGS

#ifndef __UNCONST
#define __UNCONST(a)	((void *)(unsigned long)(const void *)(a))
#endif

__BEGIN_DECLS

/**
 * @private
 * From lib/external/dewey.c
 */
int HIDDEN dewey_match(const char *, const char *);

/**
 * @private
 * From lib/pkgdb.c
 */
int HIDDEN xbps_pkgdb_init(struct xbps_handle *);
void HIDDEN xbps_pkgdb_release(struct xbps_handle *);

/**
 * @private
 * From lib/plist.c
 */
bool HIDDEN xbps_add_obj_to_dict(prop_dictionary_t,
				 prop_object_t, const char *);
bool HIDDEN xbps_add_obj_to_array(prop_array_t, prop_object_t);

int HIDDEN xbps_array_replace_dict_by_name(prop_array_t,
					   prop_dictionary_t,
					   const char *);
int HIDDEN xbps_array_replace_dict_by_pattern(prop_array_t,
					      prop_dictionary_t,
					       const char *);

/**
 * @private
 * From lib/plist_remove.c
 */
bool HIDDEN xbps_remove_pkg_from_array_by_name(prop_array_t, const char *);
bool HIDDEN xbps_remove_pkg_from_array_by_pattern(prop_array_t, const char *);
bool HIDDEN xbps_remove_pkg_from_array_by_pkgver(prop_array_t, const char *);
bool HIDDEN xbps_remove_pkgname_from_array(prop_array_t, const char *);
bool HIDDEN xbps_remove_string_from_array(prop_array_t, const char *);

/**
 * @private
 * From lib/util.c
 */
char HIDDEN *xbps_repository_pkg_path(struct xbps_handle *, prop_dictionary_t);

/**
 * @private
 * From lib/rpool.c
 */
int HIDDEN xbps_rpool_init(struct xbps_handle *);
void HIDDEN xbps_rpool_release(struct xbps_handle *);

/**
 * @private
 * From lib/download.c
 */
void HIDDEN xbps_fetch_set_cache_connection(int, int);
void HIDDEN xbps_fetch_unset_cache_connection(void);

/**
 * @private
 * From lib/package_config_files.c
 */
int HIDDEN xbps_entry_is_a_conf_file(prop_dictionary_t, const char *);
int HIDDEN xbps_entry_install_conf_file(struct xbps_handle *,
					prop_dictionary_t,
					struct archive_entry *,
					const char *,
					const char *,
					const char *);
/**
 * @private
 * From lib/plist_archive_entry.c
 */
prop_dictionary_t HIDDEN
	xbps_dictionary_from_archive_entry(struct archive *,
					   struct archive_entry *);

/**
 * @private
 * From lib/rpool_pkgdeps.c
 */
int HIDDEN xbps_repository_find_deps(struct xbps_handle *,
				     prop_array_t,
				     prop_dictionary_t);

/**
 * @private
 * From lib/plist_find.c
 */
prop_dictionary_t HIDDEN xbps_find_pkg_in_array(prop_array_t, const char *);
prop_dictionary_t HIDDEN
	xbps_find_virtualpkg_in_array(struct xbps_handle *, prop_array_t,
				      const char *);

/**
 * @private
 * From lib/transaction_sortdeps.c
 */
int HIDDEN xbps_transaction_sort(struct xbps_handle *);

/**
 * @private
 * From lib/transaction_dictionary.c
 */
int HIDDEN xbps_transaction_init(struct xbps_handle *);

/**
 * @private
 * From lib/rindex_sync.c
 */
char HIDDEN *xbps_get_remote_repo_string(const char *);
int HIDDEN xbps_rindex_sync(struct xbps_handle *, const char *, const char *);

/**
 * @private
 * From lib/util_hash.c
 */
int HIDDEN xbps_file_hash_check_dictionary(struct xbps_handle *,
					   prop_dictionary_t d,
					   const char *,
					   const char *);

/**
 * @private
 * From lib/external/fexec.c
 */
int HIDDEN xbps_file_exec(struct xbps_handle *, const char *, ...);

/**
 * @private
 * From lib/cb_util.c
 */
void HIDDEN xbps_set_cb_fetch(struct xbps_handle *, off_t, off_t, off_t,
			      const char *, bool, bool, bool);
void HIDDEN xbps_set_cb_state(struct xbps_handle *, xbps_state_t, int,
			      const char *, const char *, const char *, ...);

/**
 * @private
 * From lib/package_unpack.c
 */
int HIDDEN xbps_unpack_binary_pkg(struct xbps_handle *, prop_dictionary_t);

int HIDDEN xbps_transaction_package_replace(struct xbps_handle *);

/**
 * @private
 * From lib/package_conflicts.c
 */
void HIDDEN xbps_pkg_find_conflicts(struct xbps_handle *,
				    prop_array_t,
				    prop_dictionary_t);
/**
 * @private
 * From lib/rindex_get.c
 */
const char HIDDEN *vpkg_user_conf(struct xbps_handle *, const char *, bool);

__END_DECLS

#endif /* !_XBPS_API_IMPL_H_ */
