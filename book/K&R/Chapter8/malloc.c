#include <stdio.h>

typedef long Align;

union header {
    struct
    {
        union header *ptr; // pointer to next
        unsigned size;     // Header size metric, include header and my_free space
    } s;
    Align x;
};

typedef union header Header;

static Header *morecore(unsigned nu);
static void my_free(void *ap);

static Header base;          /* empty list to get started */
static Header *freep = NULL; /* start of my_free list */

/* my_malloc: general-purpose storage allocator */
void *my_malloc(unsigned nbytes)
{
    Header *p, *prevp;
    Header *morecore(unsigned);
    unsigned nunits;

    // round up to muliple size of Header
    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

    if ((prevp = freep) == NULL)
    {
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }

    // BAD: if new allocate memory join lower nbr,
    // it will iterate list one addition time to get the new allocate memory, very inefficient.
    for (p = prevp->s.ptr;; prevp = p, p = p->s.ptr)
    {
        if (p->s.size >= nunits) /* big enough */
        {
            if (p->s.size == nunits) /* exactly */
                prevp->s.ptr = p->s.ptr;
            else
            {
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)p + 1;
        }

        if (p == freep) /* wrapped around my_free list */
        {
            if ((p = morecore(nunits)) == NULL)
                return NULL;
        }
    }
}

#define NALLOC 1024

/* morecore: ask system for more memory */
static Header *morecore(unsigned nu)
{
    char *cp, *sbrk(int);
    Header *up;

    if (nu < NALLOC)
        nu = NALLOC;
    cp = sbrk(nu * sizeof(Header));
    if (cp == (char *)-1)
        return NULL;
    up = (Header *)cp;
    up->s.size = nu;
    my_free((void *)(up + 1));
    return freep;
}

/* my_free: put block ap in my_free list */
void my_free(void *ap)
{
    Header *bp, *p;

    bp = (Header *)ap - 1; /* point to block header */
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break; /* freed block at start or end of arena */

    if (bp + bp->s.size == p->s.ptr) /* join to upper nbr */
    {
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    }
    else
        bp->s.ptr = p->s.ptr;

    if (p + p->s.size == bp) /* join to lower nbr */
    {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    }
    else
        p->s.ptr = bp;
    freep = p;
}