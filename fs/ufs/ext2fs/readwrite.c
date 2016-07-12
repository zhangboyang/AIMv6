
#include <sys/types.h>
#include <fs/vnode.h>
#include <fs/uio.h>
#include <fs/bio.h>
#include <fs/ufs/inode.h>
#include <fs/ufs/ext2fs/ext2fs.h>
#include <buf.h>
#include <ucred.h>
#include <panic.h>

int
ext2fs_read(struct vnode *vp, struct uio *uio, int ioflags, struct ucred *cred)
{
	struct buf *bp = NULL;
	struct m_ext2fs *fs = VTOI(vp)->superblock;
	off_t fsb;
	size_t len = 0, b_off;
	int i;
	int err;

	/* sanity checks */
	for (i = 0; i < uio->iovcnt; ++i)
		len += uio->iov[i].iov_len;
	assert(len == uio->resid);
	assert(uio->rw == UIO_READ);

	fsb = lblkno(fs, uio->offset);
	b_off = lblkoff(fs, uio->offset);

	while (uio->resid > 0) {
		err = bread(vp, fsb, fs->bsize, &bp);
		if (err) {
			if (bp != NULL)
				brelse(bp);
			return err;
		}
		len = min2(uio->resid, fs->bsize - b_off);
		err = uiomove(bp->data + b_off, len, uio);
		if (err) {
			brelse(bp);
			return err;
		}
		b_off = 0;
		++fsb;
		brelse(bp);
	}
	return 0;
}
