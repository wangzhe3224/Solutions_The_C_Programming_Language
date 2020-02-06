#include <stdint.h>
#include <stdio.h>

typedef struct buffer {
  uint16_t * buf; // block of memory
  uint16_t size;  /* must be power of two */
  uint16_t read;  /* holds current read position: 0 to size-1 */
  uint16_t write; /* holds current write position: 0 to size-1 */
} buffer;

/* data length of the buffer */
uint16_t buffer_data_length(buffer *cb) {
  /* return ((cb->write - cb->read) & (cb->size - 1)); */
  int32_t length = cb->write - cb->read;
  if (length >= 0)
    return length;
  return (cb->size - cb->write) + (cb->read);
}

/* enqueue */
int8_t enqueue(buffer *cb, int16_t data) {
  if (buffer_data_length(cb) == (cb->size-1))
    return -1;                  /* buffer is full */

  cb->buf[cb->write] = data;
  cb->write = (cb->write+1) & (cb->size - 1);
  return 0;
}

/* dequeue */
int8_t dequeue(buffer *cb, int16_t *data) {
  if (buffer_data_length(cb) == 0)
    return -1;                  /* empty buffer */
  *data = cb->buf[cb->read];
  cb->read = (cb->read + 1) & (cb->size - 1);
  return 0;
}

int main()
{
  uint16_t buf[256];
  buffer bc = {buf, 256, 0, 0};
  printf("Initialized buffer. ");
  /* enqueue */
  int8_t eq;
  for (int16_t i=0; i<300; ++i) {
    eq = enqueue(&bc, i);
    printf("Enqueue result: %d, %d\n", i, eq);
  }
  /* dequeue */
  int16_t res;
  for (int16_t i=0; i<300; ++i) {
    printf("Dequeue result: %d, %d\n", res, dequeue(&bc, &res));
  }
}
