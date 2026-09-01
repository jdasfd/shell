/* htsStub.c - Stub out the few htslib (tabix) functions referenced by
 * linefile.c, so that faToTwoBit / twoBitToFa / twoBitInfo can be linked
 * WITHOUT building htslib and its zlib dependency.
 *
 * linefile.c uses tabix only for reading bgzip-compressed, tabix-indexed
 * files (lineFileTabixMayOpen).  These tools never use that path, so all
 * stubs simply report failure, which lineFileTabixMayOpen handles by
 * returning NULL with a warning.
 *
 * Compile this INSTEAD of the htslib sources - never together with them.
 */

#include "common.h"
#include "htslib/hts.h"
#include "htslib/tbx.h"

htsFile *hts_open(const char *fn, const char *mode)
{
warn("htslib support is not compiled into this program, can not open %s", fn);
return NULL;
}

int hts_close(htsFile *fp)
{
return 0;
}

tbx_t *tbx_index_load2(const char *fn, const char *fnidx)
{
return NULL;
}

void tbx_destroy(tbx_t *tbx)
{
}

int tbx_name2id(tbx_t *tbx, const char *ss)
{
return -1;
}

int tbx_readrec(BGZF *fp, void *tbxv, void *sv, int *tid, int *beg, int *end)
{
return -1;
}

BGZF *hts_get_bgzfp(htsFile *fp)
{
return NULL;
}

hts_itr_t *hts_itr_query(const hts_idx_t *idx, int tid, int beg, int end,
                         hts_readrec_func *readrec)
{
return NULL;
}

int hts_itr_next(BGZF *fp, hts_itr_t *iter, void *r, void *data)
{
return -1;
}

void hts_itr_destroy(hts_itr_t *iter)
{
}
