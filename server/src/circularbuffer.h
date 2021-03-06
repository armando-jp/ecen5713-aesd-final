#ifndef _CIRCULARBUFFER_H_
#define _CIRCULARBUFFER_H_

int get_buf_entries(CIRCULAR_BUFFER *buf)
{
    return buf->entries;
}

int buf_copy(CIRCULAR_BUFFER *in_buf, int size, CIRCULAR_BUFFER *out_buf)
{
    int i = 0;
    while(i < size)
    {
        *(out_buf+i) = *(in_buf+i);
        i++;
    }
    return i;
}

void add_entry(CIRCULAR_BUFFER *buf, uint8_t state)
{
    // create new entry and initialize
    BUFFER_ENTRY *new_entry = NULL;
    new_entry = malloc(sizeof(BUFFER_ENTRY));
    new_entry->state = state;
    new_entry->next = NULL;

    // check if this will be the first entry
    if(buf->entries == 0)
    {
        buf->head = new_entry;
        buf->tail = new_entry;
    }
    else
    {
        // obtain the current last entry
        BUFFER_ENTRY *last_entry = NULL;
        last_entry = buf->tail;
        // last entry should point to the new entry
        last_entry->next = new_entry;
        // update the tail pointer to point to new_entry
        buf->tail = new_entry;
    }
    buf->entries++;

}

void print_buffer(CIRCULAR_BUFFER *buf)
{
    int i = 0;
    BUFFER_ENTRY *p = NULL;
    p = buf->head;

    PDEBUG("print: size of buffer: %d\n", buf->entries);
    while(p != NULL)
    {
        PDEBUG("entry %d: %d\n", i, p->state);
        i++;
        p = p->next;
    }
}

//copies the circular buffer contents into a character buffer
// returns the size of the content written into out_buf
int get_buffer(CIRCULAR_BUFFER *buf, char *out_buf)
{
    int i = 0;
    BUFFER_ENTRY *p = NULL;
    p = buf->head;
    while(p != NULL)
    {
        PDEBUG("entry %d: %d\n", i, p->state);
        if( p->state == 0 )
        {
            *(out_buf+i) = '0';
        }
        else
        {
            *(out_buf+i) = '1';
        }

        i++;
        p = p->next;
    }
    *(out_buf+i) = '\n';

    return i+1; // add one because of array starting at zero.
}

void clear_buffer(CIRCULAR_BUFFER *buf)
{
    int i = 0;
    BUFFER_ENTRY *p_next = NULL;
    BUFFER_ENTRY *p = NULL;
    p = buf->head;

    PDEBUG("clear: size of buffer: %d\n", buf->entries);

    while(p != NULL)
    {
        p_next = p->next;
        free(p);
        p = p_next;

        PDEBUG("removed entry %d\n", i);
        i++;
    }

    buf->head = NULL;
    buf->tail = NULL;
    buf->entries = 0;

}

void init_buffer(CIRCULAR_BUFFER *buf)
{
    buf->head = NULL;
    buf->tail = NULL;
    buf->entries = 0;
}

void test_buffer()
{
    CIRCULAR_BUFFER test_buf;
    init_buffer(&test_buf);
    add_entry(&test_buf, 4);
    add_entry(&test_buf, 214);
    add_entry(&test_buf, 132);
    add_entry(&test_buf, 94);
    print_buffer(&test_buf);
    clear_buffer(&test_buf);
    print_buffer(&test_buf);
    add_entry(&test_buf, 212);
    add_entry(&test_buf, 123);
    add_entry(&test_buf, 222);
    print_buffer(&test_buf);
    clear_buffer(&test_buf);

}

#endif // _CIRCULARBUFFER_H_
